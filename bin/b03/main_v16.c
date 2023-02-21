#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0


int U1 = 4;
int U2 = 2;
int U3 = 1;
int U4 = 7;
int INIT = 0;
int ANALISI_REQ = 1;
int ASSEGNA = 2;

_Bool last_clk;

struct state_elements_top{
  unsigned char grant;
  unsigned char stato;
  unsigned char coda0;
  unsigned char coda1;
  unsigned char coda2;
  unsigned char coda3;
  _Bool ru1;
  _Bool ru2;
  _Bool ru3;
  _Bool ru4;
  _Bool fu1;
  _Bool fu2;
  _Bool fu3;
  unsigned char GRANT_O;
  _Bool fu4;
};
struct state_elements_top stop;

void top(_Bool clk, _Bool REQUEST1, _Bool REQUEST2, _Bool REQUEST3, _Bool REQUEST4, unsigned char *GRANT_O)
{
  if(clk == 1 && last_clk == 0)
  {
    {
      if((stop.stato & 3) == INIT)
      {
        stop.ru1 = REQUEST1;
        stop.ru2 = REQUEST2;
        stop.ru3 = REQUEST3;
        stop.ru4 = REQUEST4;
        stop.stato = ANALISI_REQ;
      }

      else
        if((stop.stato & 3) == ANALISI_REQ)
        {
          stop.GRANT_O = stop.grant & 15;
          if(stop.ru1)
          {
            if(!stop.fu1)
            {
              stop.coda3 = stop.coda2 & 7;
              stop.coda2 = stop.coda1 & 7;
              stop.coda1 = stop.coda0 & 7;
              stop.coda0 = U1 & 7;
            }

          }

          else
            if(stop.ru2)
            {
              if(!stop.fu2)
              {
                stop.coda3 = stop.coda2 & 7;
                stop.coda2 = stop.coda1 & 7;
                stop.coda1 = stop.coda0 & 7;
                stop.coda0 = U2 & 7;
              }

            }

            else
              if(stop.ru3)
              {
                if(!stop.fu3)
                {
                  stop.coda3 = stop.coda2 & 7;
                  stop.coda2 = stop.coda1 & 7;
                  stop.coda1 = stop.coda0 & 7;
                  stop.coda0 = U3 & 7;
                }

              }

              else
                if(stop.ru4)
                {
                  if(!stop.fu4)
                  {
                    stop.coda3 = stop.coda2 & 7;
                    stop.coda2 = stop.coda1 & 7;
                    stop.coda1 = stop.coda0 & 7;
                    stop.coda0 = U4 & 7;
                  }

                }

          stop.fu1 = stop.ru1;
          stop.fu2 = stop.ru2;
          stop.fu3 = stop.ru3;
          stop.fu4 = stop.ru4;
          stop.stato = ASSEGNA;
        }

        else
          if((stop.stato & 3) == ASSEGNA)
          {
            if(stop.fu1 || stop.fu2 || stop.fu3 || stop.fu4)
            {
              {
                if((stop.coda0 & 7) == (U1 & 7))
                {
                  stop.grant = 8;
                }

                else
                  if((stop.coda0 & 7) == (U2 & 7))
                  {
                    stop.grant = 4;
                  }

                  else
                    if((stop.coda0 & 7) == (U3 & 7))
                    {
                      stop.grant = 2;
                    }

                    else
                      if((stop.coda0 & 7) == (U4 & 7))
                      {
                        stop.grant = 1;
                      }

                      else
                        if(TRUE)
                        {
                          stop.grant = 0;
                        }

              }
              stop.coda0 = stop.coda1 & 7;
              stop.coda1 = stop.coda2 & 7;
              stop.coda2 = stop.coda3 & 7;
              stop.coda3 = 0;
            }

            stop.ru1 = REQUEST1;
            stop.ru2 = REQUEST2;
            stop.ru3 = REQUEST3;
            stop.ru4 = REQUEST4;
            stop.stato = ANALISI_REQ;
          }

    }
  }

  *GRANT_O = stop.GRANT_O;
}

void main() {//main function
  _Bool clk;
  _Bool REQUEST1;
  _Bool REQUEST2;
  _Bool REQUEST3;
  _Bool REQUEST4;
  unsigned char GRANT_O;

  clk = 0;

  while(1) {
    last_clk = clk;
    clk = !clk;
    REQUEST1 = nondet_bool();
    REQUEST2 = nondet_bool();
    REQUEST3 = nondet_bool();
    REQUEST4 = nondet_bool();

    top(clk, REQUEST1, REQUEST2, REQUEST3, REQUEST4, &GRANT_O);

    assert((stop.GRANT_O & 15) == 0 || (stop.GRANT_O & 15) == 8 || (stop.GRANT_O & 15) == 4 || (stop.GRANT_O & 15) == 2 || (stop.GRANT_O & 15) == 1);

  }

}
