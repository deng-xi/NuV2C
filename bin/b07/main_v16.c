#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0

unsigned char mem(unsigned char a)
{
  unsigned char mem;
  if((a & 15) == 0)
    mem = 1;

  else
    if((a & 15) == 1)
      mem = 255;

    else
      if((a & 15) == 2)
        mem = 0;

      else
        if((a & 15) == 3)
          mem = 0;

        else
          if((a & 15) == 4)
            mem = 0;

          else
            if((a & 15) == 5)
              mem = 2;

            else
              if((a & 15) == 6)
                mem = 0;

              else
                if((a & 15) == 7)
                  mem = 0;

                else
                  if((a & 15) == 8)
                    mem = 0;

                  else
                    if((a & 15) == 9)
                      mem = 2;

                    else
                      if((a & 15) == 10)
                        mem = 255;

                      else
                        if((a & 15) == 11)
                          mem = 5;

                        else
                          if((a & 15) == 12)
                            mem = 0;

                          else
                            if((a & 15) == 13)
                              mem = 2;

                            else
                              if((a & 15) == 14)
                                mem = 0;

                              else
                                mem = 2;
  return mem;
}


int S_RESET = 0;
int S_START = 1;
int S_LOAD_X = 2;
int S_UPDATE_MAR = 3;
int S_LOAD_Y = 4;
int S_CALC_RETTA = 5;
int S_INCREMENTA = 6;

unsigned char mem_mar;
_Bool last_clk;

struct state_elements_top{
  _Bool stato;
  unsigned char cont;
  unsigned char x;
  unsigned char y;
  unsigned char t;
  unsigned char mar;
  unsigned char PUNTI_RETTA;
};
struct state_elements_top stop;

void top(unsigned char *PUNTI_RETTA, _Bool START, _Bool clk)
{
  if(clk == 1 && last_clk == 0)
  {
    {
      if(stop.stato == S_RESET)
      {
        stop.stato = S_START >> 0 & 1;
      }

      else
        if(stop.stato == S_START)
        {
          if(START)
          {
            stop.cont = 0;
            stop.mar = 0;
            mem_mar = mem(stop.mar);
            stop.stato = S_LOAD_X >> 0 & 1;
          }

          else
          {
            stop.stato = S_START >> 0 & 1;
            stop.PUNTI_RETTA = 0;
          }
        }

        else
          if(stop.stato == S_LOAD_X)
          {
            stop.x = mem_mar;
            stop.stato = S_UPDATE_MAR >> 0 & 1;
          }

          else
            if(stop.stato == S_UPDATE_MAR)
            {
              stop.mar = (stop.mar & 15) + 1;
              mem_mar = mem(stop.mar);
              stop.t = 0 << 0 | (stop.x >> 0 & 63) << 1;
              stop.stato = S_LOAD_Y >> 0 & 1;
            }

            else
              if(stop.stato == S_LOAD_Y)
              {
                stop.y = mem_mar >> 0 & 127;
                stop.x = ((stop.x >> 0 & 127) << 0 | 0 << 7) + (stop.t << 0 & 1 | 0 << 7);
                stop.stato = S_CALC_RETTA >> 0 & 1;
              }

              else
                if(stop.stato == S_CALC_RETTA)
                {
                  stop.x = ((stop.x >> 0 & 127) << 0 | 0 << 7) + (stop.y << 0 & 1 | 0 << 7);
                  stop.stato = S_INCREMENTA >> 0 & 1;
                }

                else
                  if(stop.stato == S_INCREMENTA)
                  {
                    if((stop.mar & 15) != 15)
                    {
                      if(stop.x == 2)
                      {
                        stop.cont = stop.cont + 1;
                      }

                      stop.mar = (stop.mar & 15) + 1;
                      mem_mar = mem(stop.mar);
                      stop.stato = S_LOAD_X >> 0 & 1;
                    }

                    else
                    {
                      if(START == 0)
                      {
                        if(stop.x == 2)
                        {
                          stop.PUNTI_RETTA = stop.cont + 1;
                        }

                        else
                        {
                          stop.PUNTI_RETTA = stop.cont;
                        }
                        stop.stato = S_START >> 0 & 1;
                      }

                      else
                      {
                        stop.stato = S_INCREMENTA >> 0 & 1;
                      }
                    }
                  }

    }
  }

  mem_mar = mem(stop.mar);
  *PUNTI_RETTA = stop.PUNTI_RETTA;
}

void main() {//main function
  unsigned char PUNTI_RETTA;
  _Bool START;
  _Bool clk;

  clk = 0;

  while(1) {
    last_clk = clk;
    clk = !clk;
    START = nondet_bool();

    top(&PUNTI_RETTA, START, clk);

    assert((stop.x >> 0 & 255) != 148);

  }

}
