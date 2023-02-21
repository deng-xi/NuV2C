#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0


int cc_nop = 1;
int cc_enin = 1;
int cc_intr = 2;
int cc_ackin = 3;
int out_norm = 1;
int s_init = 0;
int s_wait = 1;
int s_enin = 2;
int s_enin_w = 3;
int s_intr = 4;
int s_intr_1 = 5;
int s_intr_w = 6;

_Bool last_clk;

struct state_elements_top{
  unsigned char CC_MUX;
  unsigned char USCITE;
  _Bool state;
  _Bool ENABLE_COUNT;
  _Bool ACKOUT;
};
struct state_elements_top stop;

void top(unsigned char *CC_MUX, _Bool EQL, unsigned char *USCITE, _Bool clk, _Bool *ENABLE_COUNT, _Bool *ACKOUT, _Bool CONT_EQL)
{
  if(clk == 1 && last_clk == 0)
  {
    if(CONT_EQL)
    {
      stop.ACKOUT = 0 >> 0 & 1;
      stop.ENABLE_COUNT = 0 >> 0 & 1;
    }

    else
    {
      stop.ACKOUT = 1 >> 0 & 1;
      stop.ENABLE_COUNT = 1 >> 0 & 1;
    }
    {
      if(stop.state == s_init)
      {
        stop.CC_MUX = cc_enin & 3;
        stop.USCITE = out_norm & 3;
        stop.state = s_wait >> 0 & 1;
      }

      else
        if(stop.state == s_wait)
        {
          if(EQL)
          {
            stop.USCITE = 0;
            stop.CC_MUX = cc_ackin & 3;
            stop.state = s_enin >> 0 & 1;
          }

          else
          {
            stop.USCITE = out_norm & 3;
            stop.CC_MUX = cc_intr & 3;
            stop.state = s_intr_1 >> 0 & 1;
          }
        }

        else
          if(stop.state == s_intr_1)
          {
            if(EQL)
            {
              stop.USCITE = 0;
              stop.CC_MUX = cc_ackin & 3;
              stop.state = s_intr >> 0 & 1;
            }

            else
            {
              stop.USCITE = out_norm & 3;
              stop.CC_MUX = cc_enin & 3;
              stop.state = s_wait >> 0 & 1;
            }
          }

          else
            if(stop.state == s_enin)
            {
              if(EQL)
              {
                stop.USCITE = 0;
                stop.CC_MUX = cc_ackin & 3;
                stop.state = s_enin >> 0 & 1;
              }

              else
              {
                stop.USCITE = 1;
                stop.ACKOUT = 1 >> 0 & 1;
                stop.ENABLE_COUNT = 1 >> 0 & 1;
                stop.CC_MUX = cc_enin & 3;
                stop.state = s_enin_w >> 0 & 1;
              }
            }

            else
              if(stop.state == s_enin_w)
              {
                if(EQL)
                {
                  stop.USCITE = 1;
                  stop.CC_MUX = cc_enin & 3;
                  stop.state = s_enin_w >> 0 & 1;
                }

                else
                {
                  stop.USCITE = out_norm & 3;
                  stop.CC_MUX = cc_enin & 3;
                  stop.state = s_wait >> 0 & 1;
                }
              }

              else
                if(stop.state == s_intr)
                {
                  if(EQL)
                  {
                    stop.USCITE = 0;
                    stop.CC_MUX = cc_ackin & 3;
                    stop.state = s_intr >> 0 & 1;
                  }

                  else
                  {
                    stop.USCITE = 3;
                    stop.CC_MUX = cc_intr & 3;
                    stop.state = s_intr_w >> 0 & 1;
                  }
                }

                else
                  if(stop.state == s_intr_w)
                  {
                    if(EQL)
                    {
                      stop.USCITE = 3;
                      stop.CC_MUX = cc_intr & 3;
                      stop.state = s_intr_w >> 0 & 1;
                    }

                    else
                    {
                      stop.USCITE = out_norm & 3;
                      stop.CC_MUX = cc_enin & 3;
                      stop.state = s_wait >> 0 & 1;
                    }
                  }

    }
  }

  *CC_MUX = stop.CC_MUX;
  *USCITE = stop.USCITE;
  *ENABLE_COUNT = stop.ENABLE_COUNT;
  *ACKOUT = stop.ACKOUT;
}

void main() {//main function
  unsigned char CC_MUX;
  _Bool EQL;
  unsigned char USCITE;
  _Bool clk;
  _Bool ENABLE_COUNT;
  _Bool ACKOUT;
  _Bool CONT_EQL;

  clk = 0;

  while(1) {
    last_clk = clk;
    clk = !clk;
    CONT_EQL = nondet_bool();
    EQL = nondet_bool();

    top(&CC_MUX, EQL, &USCITE, clk, &ENABLE_COUNT, &ACKOUT, CONT_EQL);

    assert(stop.ENABLE_COUNT == stop.ACKOUT);

    assert((stop.USCITE >> 0 & 3) != 2);

  }

}
