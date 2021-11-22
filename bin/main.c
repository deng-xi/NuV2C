#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0
struct state_elements_main{
_Bool in1;
_Bool out1;
};
struct state_elements_main smain

void main(void)
{
  _Bool in1_old;
  _Bool out1_old;
  _Bool t1;
  in1_old = smain.in1;
  out1_old = smain.out1;
  smain.out1 = in1_old;
  t1 = smain.out1;
}
void main() {//main function
main();
}
