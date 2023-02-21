#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0


int a = 0;
int b = 1;
int c = 2;
int e = 3;
int f = 4;
int g = 5;
int wf0 = 6;
int wf1 = 7;

_Bool last_clk;

struct state_elements_top{
  _Bool OUTP;
  _Bool OVERFLW;
  unsigned char stato;
};
struct state_elements_top stop;

void top(_Bool LINE1, _Bool LINE2, _Bool *OUTP, _Bool *OVERFLW, _Bool clk)
{
  if(clk == 1 && last_clk == 0)
  {
    {
      if((stop.stato & 7) == a)
      {
        if(LINE1 && LINE2)
        {
          stop.stato = f;
        }

        else
        {
          stop.stato = b;
        }
        stop.OUTP = LINE1 ^ LINE2;
        stop.OVERFLW = 0 >> 0 & 1;
      }

      else
        if((stop.stato & 7) == e)
        {
          if(LINE1 && LINE2)
          {
            stop.stato = f;
          }

          else
          {
            stop.stato = b;
          }
          stop.OUTP = LINE1 ^ LINE2;
          stop.OVERFLW = 1 >> 0 & 1;
        }

        else
          if((stop.stato & 7) == b)
          {
            if(LINE1 && LINE2)
            {
              stop.stato = g;
            }

            else
            {
              stop.stato = c;
            }
            stop.OUTP = LINE1 ^ LINE2;
            stop.OVERFLW = 0 >> 0 & 1;
          }

          else
            if((stop.stato & 7) == f)
            {
              if(LINE1 || LINE2)
              {
                stop.stato = g;
              }

              else
              {
                stop.stato = c;
              }
              stop.OUTP = !(LINE1 ^ LINE2);
              stop.OVERFLW = 0 >> 0 & 1;
            }

            else
              if((stop.stato & 7) == c)
              {
                if(LINE1 && LINE2)
                {
                  stop.stato = wf1;
                }

                else
                {
                  stop.stato = wf0;
                }
                stop.OUTP = LINE1 ^ LINE2;
                stop.OVERFLW = 0 >> 0 & 1;
              }

              else
                if((stop.stato & 7) == g)
                {
                  if(LINE1 || LINE2)
                  {
                    stop.stato = wf1;
                  }

                  else
                  {
                    stop.stato = wf0;
                  }
                  stop.OUTP = !(LINE1 ^ LINE2);
                  stop.OVERFLW = 0 >> 0 & 1;
                }

                else
                  if((stop.stato & 7) == wf0)
                  {
                    if(LINE1 && LINE2)
                    {
                      stop.stato = e;
                    }

                    else
                    {
                      stop.stato = a;
                    }
                    stop.OUTP = LINE1 ^ LINE2;
                    stop.OVERFLW = 0 >> 0 & 1;
                  }

                  else
                    if((stop.stato & 7) == wf1)
                    {
                      if(LINE1 || LINE2)
                      {
                        stop.stato = e;
                      }

                      else
                      {
                        stop.stato = a;
                      }
                      stop.OUTP = !(LINE1 ^ LINE2);
                      stop.OVERFLW = 0 >> 0 & 1;
                    }

    }
  }

  *OUTP = stop.OUTP;
  *OVERFLW = stop.OVERFLW;
}

void main() {//main function
  _Bool LINE1;
  _Bool LINE2;
  _Bool OUTP;
  _Bool OVERFLW;
  _Bool clk;

  clk = 0;

  while(1) {
    last_clk = clk;
    clk = !clk;
    LINE1 = nondet_bool();
    LINE2 = nondet_bool();

    top(LINE1, LINE2, &OUTP, &OVERFLW, clk);

    if(stop.OVERFLW == 1) {
      top(LINE1, LINE2, &OUTP, &OVERFLW, clk);
      top(LINE1, LINE2, &OUTP, &OVERFLW, clk);
      assert(stop.OVERFLW == 0);
    }

  }

}
