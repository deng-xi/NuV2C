#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0
struct state_elements_main{
  _Bool val;
  unsigned char rega;
  unsigned char regb;
};
struct state_elements_main smain

void main(void)
{
  _Bool val_old;
  unsigned char rega_old;
  unsigned char regb_old;
  val_old = smain.val;
  rega_old = smain.rega;
  regb_old = smain.regb;
}
void initial_main(){
  {
    smain.rega = 4;
    smain.regb = 15;
  }
  {
    smain.val = 4==0;
  }
}
void main() {//main function
  initial_main();
  main();
}
