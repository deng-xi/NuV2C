#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0
struct state_elements_main{
  _Bool clk;
  _Bool b;
  _Bool t;
};
struct state_elements_main smain

void main(void)
{
  _Bool clk_old;
  _Bool in;
  _Bool a;
  _Bool b_old;
  _Bool t_old;
  _Bool a;
  _Bool c;
  _Bool d;
  clk_old = smain.clk;
  b_old = smain.b;
  t_old = smain.t;
  smain.b = a;
  c = smain.b;
  d = c;
  smain.t = b_old;
}
void main() {//main function
  while(1) {
    main();
  }
}
