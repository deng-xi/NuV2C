#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0
struct state_elements_main{
  _Bool x;
};
struct state_elements_main smain

void main(void)
{
  _Bool x_old;
  x_old = smain.x;
}
void initial_main(){
  {
    smain.x = Z_value >> 0 & 1;
  }
}
void main() {//main function
  initial_main();
  main();
}
