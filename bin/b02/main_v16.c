#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0


int A = 0;
int B = 1;
int C = 2;
int D = 3;
int E = 4;
int F = 5;
int G = 6;

_Bool last_clk;

struct state_elements_top{
  _Bool U;
  unsigned char stato;
};
struct state_elements_top stop;

void top(_Bool clk, _Bool LINEA, _Bool *U)
{
  if(clk == 1 && last_clk == 0)
  {
    {
      if((stop.stato & 7) == A)
      {
        stop.stato = B;
        stop.U = 0 >> 0 & 1;
      }

      else
        if((stop.stato & 7) == B)
        {
          if(LINEA == 0)
          {
            stop.stato = C;
          }

          else
          {
            stop.stato = F;
          }
          stop.U = 0 >> 0 & 1;
        }

        else
          if((stop.stato & 7) == C)
          {
            if(LINEA == 0)
            {
              stop.stato = D;
            }

            else
            {
              stop.stato = G;
            }
            stop.U = 0 >> 0 & 1;
          }

          else
            if((stop.stato & 7) == D)
            {
              stop.stato = E;
              stop.U = 0 >> 0 & 1;
            }

            else
              if((stop.stato & 7) == E)
              {
                stop.stato = B;
                stop.U = 1 >> 0 & 1;
              }

              else
                if((stop.stato & 7) == F)
                {
                  stop.stato = G;
                  stop.U = 0 >> 0 & 1;
                }

                else
                  if((stop.stato & 7) == G)
                  {
                    if(LINEA == 0)
                    {
                      stop.stato = E;
                    }

                    else
                    {
                      stop.stato = A;
                    }
                    stop.U = 0 >> 0 & 1;
                  }

    }
  }

  *U = stop.U;
}

void main() {//main function
  _Bool clk;
  _Bool LINEA;
  _Bool U;

  clk = 0;

  while(1) {
    last_clk = clk;
    clk = !clk;
    LINEA = nondet_bool();

    top(clk, LINEA, &U);

    if((stop.stato & 7) == D) {
      top(clk, LINEA, &U);
      top(clk, LINEA, &U);
      assert(stop.stato == B);
    }

    if(stop.U == 1) {
      top(clk, LINEA, &U);
      assert(stop.U == 0);
    }

    if(stop.U == 1) {
      assert((stop.stato & 7) == B);
    }

  }

}
