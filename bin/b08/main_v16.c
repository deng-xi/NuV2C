#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0

unsigned int ROM(unsigned char a)
{
  unsigned int ROM;
  if((a & 7) == 0)
    ROM = 522618;

  else
    if((a & 7) == 1)
      ROM = 236898;

    else
      if((a & 7) == 2)
        ROM = 692223;

      else
        if((a & 7) == 3)
          ROM = 1046202;

        else
          if((a & 7) == 4)
            ROM = 1048430;

          else
            if((a & 7) == 5)
              ROM = 1047464;

            else
              if((a & 7) == 6)
                ROM = 829275;

              else
                ROM = 196596;
  return ROM;
}


int start_st = 0;
int init = 1;
int loop_st = 2;
int the_end = 3;

unsigned char ROM_1;
unsigned char ROM_2;
unsigned char ROM_OR;
unsigned int ROM_OUT;
_Bool last_clk;

struct state_elements_top{
  unsigned char IN_R;
  unsigned char MAR;
  unsigned char O;
  unsigned char OUT_R;
  _Bool STATO;
};
struct state_elements_top stop;

void top(_Bool clk, _Bool START, unsigned char I, unsigned char *O)
{
  ROM_1 = ROM_OUT >> 12 & 255;
  ROM_2 = ROM_OUT >> 4 & 255;
  ROM_OR = ROM_OUT >> 0 & 15;
  if(clk == 1 && last_clk == 0)
  {
    {
      if(stop.STATO == start_st)
      {
        if(START)
        {
          stop.STATO = init >> 0 & 1;
        }

      }

      else
        if(stop.STATO == init)
        {
          stop.IN_R = I;
          stop.OUT_R = 0;
          stop.MAR = 0;
          ROM_OUT = ROM(stop.MAR);
          ROM_1 = ROM_OUT >> 12 & 255;
          ROM_2 = ROM_OUT >> 4 & 255;
          ROM_OR = ROM_OUT >> 0 & 15;
          stop.STATO = loop_st >> 0 & 1;
        }

        else
          if(stop.STATO == loop_st)
          {
            if((ROM_2 & ~stop.IN_R | ROM_1 & stop.IN_R | ROM_2 & ROM_1) == 255)
            {
              stop.OUT_R = stop.OUT_R & 15 | ROM_OR & 15;
            }

            stop.STATO = the_end >> 0 & 1;
          }

          else
            if(stop.STATO == the_end)
            {
              if((stop.MAR & 7) != 7)
              {
                stop.MAR = (stop.MAR & 7) + 1;
                ROM_OUT = ROM(stop.MAR);
                ROM_1 = ROM_OUT >> 12 & 255;
                ROM_2 = ROM_OUT >> 4 & 255;
                ROM_OR = ROM_OUT >> 0 & 15;
                stop.STATO = loop_st >> 0 & 1;
              }

              else
                if(!START)
                {
                  stop.O = stop.OUT_R & 15;
                  stop.STATO = start_st >> 0 & 1;
                }

            }

    }
  }

  ROM_OUT = ROM(stop.MAR);
  ROM_1 = ROM_OUT >> 12 & 255;
  ROM_2 = ROM_OUT >> 4 & 255;
  ROM_OR = ROM_OUT >> 0 & 15;
  *O = stop.O;
}

void main() {//main function
  _Bool clk;
  _Bool START;
  unsigned char I;
  unsigned char O;

  clk = 0;

  while(1) {
    last_clk = clk;
    clk = !clk;
    START = nondet_bool();
    I = nondet_uchar();

    top(clk, START, I, &O);

    assert((ROM_OR >> 0 & 15) != 0);

  }

}
