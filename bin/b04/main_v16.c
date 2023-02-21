#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0

unsigned char tc(unsigned char x)
{
  unsigned char tc;
  tc = ~x + 1;
  return tc;
}

unsigned char avg(unsigned char x, unsigned char y)
{
  unsigned short tmp;
  unsigned char tmp2;
  unsigned char avg;
  tmp = (x << 0 | (x >> 7) << 8) + (y << 0 | (y >> 7) << 8);
  tmp2 = tc((tmp >> 0 & 127) << 0 | 0 << 7);
  if(tmp >> 8 & 1)
    avg = tc((tmp2 >> 1 & 127) << 0 | (tmp2 >> 7) << 7);

  else
    avg = (tmp >> 1 & 63) << 0 | 0 << 6;
  return avg;
}

_Bool signGt(unsigned char x, unsigned char y)
{
  _Bool signGt;

  if(!(x >> 7 & 1) && y >> 7 & 1)
    signGt = 1 >> 0 & 1;

  else
    if(x >> 7 & 1 && !(y >> 7 & 1))
      signGt = 0 >> 0 & 1;

    else
      signGt = (x >> 0 & 127) > (y >> 0 & 127);
  return signGt;
}


int sA = 0;
int sB = 1;
int sC = 2;

unsigned char REGD;
unsigned short int temp;
_Bool last_clk;

struct state_elements_top{
  _Bool stato;
  unsigned char RMAX;
  unsigned char RMIN;
  unsigned char RLAST;
  unsigned char REG1;
  unsigned char DATA_OUT;
  unsigned char REG2;
  unsigned char REG3;
  unsigned char REG4;
};
struct state_elements_top stop;

void top(_Bool RESTART, _Bool AVERAGE, _Bool ENABLE, unsigned char DATA_IN, unsigned char *DATA_OUT, _Bool clk)
{
  if(clk == 1 && last_clk == 0)
  {
    {
      if(stop.stato == sA)
      {
        stop.stato = sB >> 0 & 1;
      }

      else
        if(stop.stato == sB)
        {
          stop.RMAX = DATA_IN;
          stop.RMIN = DATA_IN;
          stop.REG1 = 0;
          stop.REG2 = 0;
          stop.REG3 = 0;
          stop.REG4 = 0;
          stop.RLAST = 0;
          stop.DATA_OUT = 0;
          stop.stato = sC >> 0 & 1;
        }

        else
          if(stop.stato == sC)
          {
            if(ENABLE)
            {
              stop.RLAST = DATA_IN;
            }

            if(RESTART)
            {
              stop.DATA_OUT = avg(stop.RMAX, stop.RMIN);
            }

            else
              if(ENABLE)
              {
                if(AVERAGE)
                {
                  stop.DATA_OUT = stop.REG4;
                }

                else
                {
                  stop.DATA_OUT = avg(DATA_IN, stop.REG4);
                }
              }

              else
              {
                stop.DATA_OUT = stop.RLAST;
              }
            if(signGt(DATA_IN, stop.RMAX))
            {
              stop.RMAX = DATA_IN;
            }

            else
              if(signGt(stop.RMIN, DATA_IN))
              {
                stop.RMIN = DATA_IN;
              }

            stop.REG4 = stop.REG3;
            stop.REG3 = stop.REG2;
            stop.REG2 = stop.REG1;
            stop.REG1 = DATA_IN;
            stop.stato = sC >> 0 & 1;
          }

    }
  }

  *DATA_OUT = stop.DATA_OUT;
}

void main() {//main function
  _Bool RESTART;
  _Bool AVERAGE;
  _Bool ENABLE;
  unsigned char DATA_IN;
  unsigned char DATA_OUT;
  _Bool clk;

  clk = 0;

  while(1) {
    last_clk = clk;
    clk = !clk;
    RESTART = nondet_bool();
    AVERAGE = nondet_bool();
    ENABLE = nondet_bool();
    DATA_IN = nondet_uchar();

    top(RESTART, AVERAGE, ENABLE, DATA_IN, &DATA_OUT, clk);

    if((stop.RMAX >> 7 & 1) == 1) {
      assert((stop.RMIN >> 7 & 1) == 1);
    }

  }

}
