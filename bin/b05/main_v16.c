#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0

unsigned short int MEM(unsigned char a)
{
  unsigned short int MEM;
  if((a & 31) == 0)
    MEM = 50;

  else
    if((a & 31) == 1)
      MEM = 40;

    else
      if((a & 31) == 2)
        MEM = 0;

      else
        if((a & 31) == 3)
          MEM = 229;

        else
          if((a & 31) == 4)
            MEM = 502;

          else
            if((a & 31) == 5)
              MEM = 75;

            else
              if((a & 31) == 6)
                MEM = 229;

              else
                if((a & 31) == 7)
                  MEM = 181;

                else
                  if((a & 31) == 8)
                    MEM = 186;

                  else
                    if((a & 31) == 9)
                      MEM = 229;

                    else
                      if((a & 31) == 10)
                        MEM = 186;

                      else
                        if((a & 31) == 11)
                          MEM = 501;

                        else
                          if((a & 31) == 12)
                            MEM = 0;

                          else
                            if((a & 31) == 13)
                              MEM = 40;

                            else
                              if((a & 31) == 14)
                                MEM = 50;

                              else
                                if((a & 31) == 15)
                                  MEM = 483;

                                else
                                  if((a & 31) == 16)
                                    MEM = 494;

                                  else
                                    if((a & 31) == 17)
                                      MEM = 229;

                                    else
                                      if((a & 31) == 18)
                                        MEM = 229;

                                      else
                                        if((a & 31) == 19)
                                          MEM = 151;

                                        else
                                          if((a & 31) == 20)
                                            MEM = 229;

                                          else
                                            if((a & 31) == 21)
                                              MEM = 100;

                                            else
                                              if((a & 31) == 22)
                                                MEM = 125;

                                              else
                                                if((a & 31) == 23)
                                                  MEM = 10;

                                                else
                                                  if((a & 31) == 24)
                                                    MEM = 75;

                                                  else
                                                    if((a & 31) == 25)
                                                      MEM = 462;

                                                    else
                                                      if((a & 31) == 26)
                                                        MEM = 0;

                                                      else
                                                        if((a & 31) == 27)
                                                          MEM = 490;

                                                        else
                                                          if((a & 31) == 28)
                                                            MEM = 0;

                                                          else
                                                            if((a & 31) == 29)
                                                              MEM = 40;

                                                            else
                                                              if((a & 31) == 30)
                                                                MEM = 50;

                                                              else
                                                                MEM = 50;
  return MEM;
}

unsigned char cDISPMAX1(_Bool EN_DISP, _Bool RES_DISP, unsigned short int MAX)
{
  unsigned short TM;
  unsigned char cDISPMAX1;
  if(MAX >> 8 & 1)
    TM = ~MAX >> 0 & 31 | 15 << 5;

  else
    TM = (MAX >> 0 & 31) << 0 | 0 << 5;
  if(EN_DISP)
    cDISPMAX1 = 0;

  else
    if(!RES_DISP)
      cDISPMAX1 = 64;

    else
      if((TM >> 8 & 1) == 0 && (TM & 511) > 99)
        cDISPMAX1 = 24;

      else
        cDISPMAX1 = 63;
  return cDISPMAX1;
}

unsigned char cDISPMAX2(_Bool EN_DISP, _Bool RES_DISP, unsigned short int MAX)
{
  unsigned short TM;
  unsigned char cDISPMAX2;
  if(MAX >> 8 & 1)
    TM = ~MAX >> 0 & 31 | 15 << 5;

  else
    TM = (MAX >> 0 & 31) << 0 | 0 << 5;
  if((TM >> 8 & 1) == 0 && (TM & 511) > 99)
    TM = (TM & 511) - 100;

  if(EN_DISP)
    cDISPMAX2 = 0;

  else
    if(!RES_DISP)
      cDISPMAX2 = 64;

    else
      if((TM >> 8 & 1) == 0 && (TM & 511) > 89)
        cDISPMAX2 = 126;

      else
        if((TM >> 8 & 1) == 0 && (TM & 511) > 79)
          cDISPMAX2 = 127;

        else
          if((TM >> 8 & 1) == 0 && (TM & 511) > 69)
            cDISPMAX2 = 28;

          else
            if((TM >> 8 & 1) == 0 && (TM & 511) > 59)
              cDISPMAX2 = 119;

            else
              if((TM >> 8 & 1) == 0 && (TM & 511) > 49)
                cDISPMAX2 = 118;

              else
                if((TM >> 8 & 1) == 0 && (TM & 511) > 39)
                  cDISPMAX2 = 90;

                else
                  if((TM >> 8 & 1) == 0 && (TM & 511) > 29)
                    cDISPMAX2 = 121;

                  else
                    if((TM >> 8 & 1) == 0 && (TM & 511) > 19)
                      cDISPMAX2 = 108;

                    else
                      if((TM >> 8 & 1) == 0 && (TM & 511) > 9)
                        cDISPMAX2 = 24;

                      else
                        cDISPMAX2 = 63;
  return cDISPMAX2;
}

unsigned char cDISPMAX3(_Bool EN_DISP, _Bool RES_DISP, unsigned short int MAX)
{
  unsigned short TM;
  unsigned char cDISPMAX3;
  if(MAX >> 8 & 1)
    TM = ~MAX >> 0 & 31 | 15 << 5;

  else
    TM = (MAX >> 0 & 31) << 0 | 0 << 5;
  if((TM >> 8 & 1) == 0 && (TM & 511) > 99)
    TM = (TM & 511) - 100;

  else
    if((TM >> 8 & 1) == 0 && (TM & 511) > 89)
      TM = (TM & 511) - 90;

    else
      if((TM >> 8 & 1) == 0 && (TM & 511) > 79)
        TM = (TM & 511) - 80;

      else
        if((TM >> 8 & 1) == 0 && (TM & 511) > 69)
          TM = (TM & 511) - 70;

        else
          if((TM >> 8 & 1) == 0 && (TM & 511) > 59)
            TM = (TM & 511) - 60;

          else
            if((TM >> 8 & 1) == 0 && (TM & 511) > 49)
              TM = (TM & 511) - 50;

            else
              if((TM >> 8 & 1) == 0 && (TM & 511) > 39)
                TM = (TM & 511) - 40;

              else
                if((TM >> 8 & 1) == 0 && (TM & 511) > 29)
                  TM = (TM & 511) - 30;

                else
                  if((TM >> 8 & 1) == 0 && (TM & 511) > 19)
                    TM = (TM & 511) - 20;

                  else
                    if((TM >> 8 & 1) == 0 && (TM & 511) > 9)
                      TM = (TM & 511) - 10;

  if(EN_DISP)
    cDISPMAX3 = 0;

  else
    if(!RES_DISP)
      cDISPMAX3 = 64;

    else
      if((TM >> 8 & 1) == 0 && (TM & 511) > 8)
        cDISPMAX3 = 126;

      else
        if((TM >> 8 & 1) == 0 && (TM & 511) > 7)
          cDISPMAX3 = 127;

        else
          if((TM >> 8 & 1) == 0 && (TM & 511) > 6)
            cDISPMAX3 = 28;

          else
            if((TM >> 8 & 1) == 0 && (TM & 511) > 5)
              cDISPMAX3 = 119;

            else
              if((TM >> 8 & 1) == 0 && (TM & 511) > 4)
                cDISPMAX3 = 118;

              else
                if((TM >> 8 & 1) == 0 && (TM & 511) > 3)
                  cDISPMAX3 = 90;

                else
                  if((TM >> 8 & 1) == 0 && (TM & 511) > 2)
                    cDISPMAX3 = 121;

                  else
                    if((TM >> 8 & 1) == 0 && (TM & 511) > 1)
                      cDISPMAX3 = 108;

                    else
                      if((TM >> 8 & 1) == 0 && (TM & 511) > 0)
                        cDISPMAX3 = 24;

                      else
                        cDISPMAX3 = 63;
  return cDISPMAX3;
}

unsigned char cDISPNUM1(_Bool EN_DISP, _Bool RES_DISP, unsigned char NUM)
{
  unsigned char cDISPNUM1;
  if(EN_DISP)
    cDISPNUM1 = 0;

  else
    if(!RES_DISP)
      cDISPNUM1 = 64;

    else
      if((NUM & 31) > 9)
        cDISPNUM1 = 24;

      else
        cDISPNUM1 = 63;
  return cDISPNUM1;
}

unsigned char cDISPNUM2(_Bool EN_DISP, _Bool RES_DISP, unsigned char NUM)
{
  unsigned char TN;
  unsigned char cDISPNUM2;
  if((NUM & 31) > 9)
    TN = (NUM & 31) - 10;

  else
    TN = NUM & 31;
  if(EN_DISP)
    cDISPNUM2 = 0;

  else
    if(!RES_DISP)
      cDISPNUM2 = 64;

    else
      if((TN & 31) > 8)
        cDISPNUM2 = 126;

      else
        if((TN & 31) > 7)
          cDISPNUM2 = 127;

        else
          if((TN & 31) > 6)
            cDISPNUM2 = 28;

          else
            if((TN & 31) > 5)
              cDISPNUM2 = 119;

            else
              if((TN & 31) > 4)
                cDISPNUM2 = 118;

              else
                if((TN & 31) > 3)
                  cDISPNUM2 = 90;

                else
                  if((TN & 31) > 2)
                    cDISPNUM2 = 121;

                  else
                    if((TN & 31) > 1)
                      cDISPNUM2 = 108;

                    else
                      if((TN & 31) > 0)
                        cDISPNUM2 = 24;

                      else
                        cDISPNUM2 = 63;
  return cDISPNUM2;
}


int st0 = 0;
int st1 = 1;
int st2 = 2;
int st3 = 3;
int st4 = 4;

unsigned short int mem_mar;
unsigned short int AC1;
unsigned short int AC2;
_Bool MAG1;
_Bool MAG2;
_Bool MIN1;
_Bool last_clk;

struct state_elements_top{
  unsigned short int MAX;
  _Bool FLAG;
  _Bool EN_DISP;
  _Bool RES_DISP;
  unsigned char STATO;
  unsigned char MAR;
  unsigned char NUM;
  unsigned short int TEMP;
};
struct state_elements_top stop;

void top(_Bool clk, _Bool START, _Bool *SIGN, unsigned char *DISPMAX1, unsigned char *DISPMAX2, unsigned char *DISPMAX3, unsigned char *DISPNUM1, unsigned char *DISPNUM2)
{
  MIN1 = AC1 >> 8 & 1;
  MAG1 = !(AC1 >> 8 & 1) && (AC1 >> 0 & 255) != 0;
  MAG2 = AC2 >> 8 & 1;
  if(clk == 1 && last_clk == 0)
  {
    {
      if((stop.STATO & 31) == st0)
      {
        stop.RES_DISP = 0 >> 0 & 1;
        *SIGN = !stop.EN_DISP && (!stop.RES_DISP || stop.MAX >> 8 & 1);
        *DISPMAX1 = cDISPMAX1(stop.EN_DISP, stop.RES_DISP, stop.MAX);
        *DISPMAX2 = cDISPMAX2(stop.EN_DISP, stop.RES_DISP, stop.MAX);
        *DISPMAX3 = cDISPMAX3(stop.EN_DISP, stop.RES_DISP, stop.MAX);
        *DISPNUM1 = cDISPNUM1(stop.EN_DISP, stop.RES_DISP, stop.NUM);
        *DISPNUM2 = cDISPNUM2(stop.EN_DISP, stop.RES_DISP, stop.NUM);
        stop.EN_DISP = 0 >> 0 & 1;
        *SIGN = !stop.EN_DISP && (!stop.RES_DISP || stop.MAX >> 8 & 1);
        *DISPMAX1 = cDISPMAX1(stop.EN_DISP, stop.RES_DISP, stop.MAX);
        *DISPMAX2 = cDISPMAX2(stop.EN_DISP, stop.RES_DISP, stop.MAX);
        *DISPMAX3 = cDISPMAX3(stop.EN_DISP, stop.RES_DISP, stop.MAX);
        *DISPNUM1 = cDISPNUM1(stop.EN_DISP, stop.RES_DISP, stop.NUM);
        *DISPNUM2 = cDISPNUM2(stop.EN_DISP, stop.RES_DISP, stop.NUM);
        stop.STATO = st1;
      }

      else
        if((stop.STATO & 31) == st1)
        {
          if(START)
          {
            stop.NUM = 0;
            *DISPNUM1 = cDISPNUM1(stop.EN_DISP, stop.RES_DISP, stop.NUM);
            *DISPNUM2 = cDISPNUM2(stop.EN_DISP, stop.RES_DISP, stop.NUM);
            stop.MAR = 0;
            mem_mar = MEM(stop.MAR);
            AC1 = (mem_mar & 511) - (stop.TEMP & 511);
            AC2 = (mem_mar & 511) - (stop.MAX & 511);
            MIN1 = AC1 >> 8 & 1;
            MAG1 = !(AC1 >> 8 & 1) && (AC1 >> 0 & 255) != 0;
            MAG2 = AC2 >> 8 & 1;
            stop.FLAG = 0 >> 0 & 1;
            stop.EN_DISP = 1 >> 0 & 1;
            *SIGN = !stop.EN_DISP && (!stop.RES_DISP || stop.MAX >> 8 & 1);
            *DISPMAX1 = cDISPMAX1(stop.EN_DISP, stop.RES_DISP, stop.MAX);
            *DISPMAX2 = cDISPMAX2(stop.EN_DISP, stop.RES_DISP, stop.MAX);
            *DISPMAX3 = cDISPMAX3(stop.EN_DISP, stop.RES_DISP, stop.MAX);
            *DISPNUM1 = cDISPNUM1(stop.EN_DISP, stop.RES_DISP, stop.NUM);
            *DISPNUM2 = cDISPNUM2(stop.EN_DISP, stop.RES_DISP, stop.NUM);
            stop.RES_DISP = 1 >> 0 & 1;
            *SIGN = !stop.EN_DISP && (!stop.RES_DISP || stop.MAX >> 8 & 1);
            *DISPMAX1 = cDISPMAX1(stop.EN_DISP, stop.RES_DISP, stop.MAX);
            *DISPMAX2 = cDISPMAX2(stop.EN_DISP, stop.RES_DISP, stop.MAX);
            *DISPMAX3 = cDISPMAX3(stop.EN_DISP, stop.RES_DISP, stop.MAX);
            *DISPNUM1 = cDISPNUM1(stop.EN_DISP, stop.RES_DISP, stop.NUM);
            *DISPNUM2 = cDISPNUM2(stop.EN_DISP, stop.RES_DISP, stop.NUM);
            stop.STATO = st2;
          }

          else
          {
            stop.STATO = st1;
          }
        }

        else
          if((stop.STATO & 31) == st2)
          {
            stop.MAX = mem_mar & 511;
            AC2 = (mem_mar & 511) - (stop.MAX & 511);
            MAG2 = AC2 >> 8 & 1;
            *SIGN = !stop.EN_DISP && (!stop.RES_DISP || stop.MAX >> 8 & 1);
            *DISPMAX1 = cDISPMAX1(stop.EN_DISP, stop.RES_DISP, stop.MAX);
            *DISPMAX2 = cDISPMAX2(stop.EN_DISP, stop.RES_DISP, stop.MAX);
            *DISPMAX3 = cDISPMAX3(stop.EN_DISP, stop.RES_DISP, stop.MAX);
            stop.TEMP = mem_mar & 511;
            AC1 = (mem_mar & 511) - (stop.TEMP & 511);
            MIN1 = AC1 >> 8 & 1;
            MAG1 = !(AC1 >> 8 & 1) && (AC1 >> 0 & 255) != 0;
            stop.STATO = st3;
          }

          else
            if((stop.STATO & 31) == st3)
            {
              if(MIN1)
              {
                if(stop.FLAG)
                {
                  stop.FLAG = 0 >> 0 & 1;
                  stop.NUM = (stop.NUM & 31) + 1;
                  *DISPNUM1 = cDISPNUM1(stop.EN_DISP, stop.RES_DISP, stop.NUM);
                  *DISPNUM2 = cDISPNUM2(stop.EN_DISP, stop.RES_DISP, stop.NUM);
                }

              }

              else
              {
                if(MAG1)
                {
                  if(MAG2)
                  {
                    stop.MAX = mem_mar & 511;
                    AC2 = (mem_mar & 511) - (stop.MAX & 511);
                    MAG2 = AC2 >> 8 & 1;
                    *SIGN = !stop.EN_DISP && (!stop.RES_DISP || stop.MAX >> 8 & 1);
                    *DISPMAX1 = cDISPMAX1(stop.EN_DISP, stop.RES_DISP, stop.MAX);
                    *DISPMAX2 = cDISPMAX2(stop.EN_DISP, stop.RES_DISP, stop.MAX);
                    *DISPMAX3 = cDISPMAX3(stop.EN_DISP, stop.RES_DISP, stop.MAX);
                  }

                  stop.FLAG = 1 >> 0 & 1;
                }

              }
              stop.TEMP = mem_mar & 511;
              AC1 = (mem_mar & 511) - (stop.TEMP & 511);
              MIN1 = AC1 >> 8 & 1;
              MAG1 = !(AC1 >> 8 & 1) && (AC1 >> 0 & 255) != 0;
              stop.STATO = st4;
            }

            else
              if((stop.STATO & 31) == st4)
              {
                if((stop.MAR & 31) == 31)
                {
                  if(START)
                  {
                    stop.STATO = st4;
                  }

                  else
                  {
                    stop.STATO = st1;
                  }
                  stop.EN_DISP = 0 >> 0 & 1;
                  *SIGN = !stop.EN_DISP && (!stop.RES_DISP || stop.MAX >> 8 & 1);
                  *DISPMAX1 = cDISPMAX1(stop.EN_DISP, stop.RES_DISP, stop.MAX);
                  *DISPMAX2 = cDISPMAX2(stop.EN_DISP, stop.RES_DISP, stop.MAX);
                  *DISPMAX3 = cDISPMAX3(stop.EN_DISP, stop.RES_DISP, stop.MAX);
                  *DISPNUM1 = cDISPNUM1(stop.EN_DISP, stop.RES_DISP, stop.NUM);
                  *DISPNUM2 = cDISPNUM2(stop.EN_DISP, stop.RES_DISP, stop.NUM);
                }

                else
                {
                  stop.MAR = (stop.MAR & 31) + 1;
                  mem_mar = MEM(stop.MAR);
                  AC1 = (mem_mar & 511) - (stop.TEMP & 511);
                  AC2 = (mem_mar & 511) - (stop.MAX & 511);
                  MIN1 = AC1 >> 8 & 1;
                  MAG1 = !(AC1 >> 8 & 1) && (AC1 >> 0 & 255) != 0;
                  MAG2 = AC2 >> 8 & 1;
                  stop.STATO = st3;
                }
              }

    }
  }

  mem_mar = MEM(stop.MAR);
  AC1 = (mem_mar & 511) - (stop.TEMP & 511);
  AC2 = (mem_mar & 511) - (stop.MAX & 511);
  MIN1 = AC1 >> 8 & 1;
  MAG1 = !(AC1 >> 8 & 1) && (AC1 >> 0 & 255) != 0;
  MAG2 = AC2 >> 8 & 1;
  *SIGN = !stop.EN_DISP && (!stop.RES_DISP || stop.MAX >> 8 & 1);
  *DISPMAX1 = cDISPMAX1(stop.EN_DISP, stop.RES_DISP, stop.MAX);
  *DISPMAX2 = cDISPMAX2(stop.EN_DISP, stop.RES_DISP, stop.MAX);
  *DISPMAX3 = cDISPMAX3(stop.EN_DISP, stop.RES_DISP, stop.MAX);
  *DISPNUM1 = cDISPNUM1(stop.EN_DISP, stop.RES_DISP, stop.NUM);
  *DISPNUM2 = cDISPNUM2(stop.EN_DISP, stop.RES_DISP, stop.NUM);
}

void main() {//main function
  _Bool clk;
  _Bool START;
  _Bool SIGN;
  unsigned char DISPMAX1;
  unsigned char DISPMAX2;
  unsigned char DISPMAX3;
  unsigned char DISPNUM1;
  unsigned char DISPNUM2;

  clk = 0;

  while(1) {
    last_clk = clk;
    clk = !clk;
    START = nondet_bool();

    top(clk, START, &SIGN, &DISPMAX1, &DISPMAX2, &DISPMAX3, &DISPNUM1, &DISPNUM2);

    if((stop.STATO & 31) == st2) {
      assert(stop.RES_DISP == 1);
    }

    if((stop.STATO & 31) == st3) {
      assert((stop.MAX >> 0 & 511) == (stop.TEMP >> 0 & 511));
    }

  }

}
