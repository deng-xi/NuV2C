#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0
struct state_elements_array{
unsigned char counter;
unsigned char mem[8];
};
void array(_Bool clk, _Bool *safety1)
{
  struct state_elements_array  sarray;
  unsigned char counter_old;
  unsigned char mem_old[8];
  counter_old = sarray.counter;
  mem_old = sarray.mem[sarray.counter];
  sarray.counter = counter_old + 1;
  sarray.mem[sarray.counter] = counter_old;
  assert(!(counter > 0) || mem[counter - 1] == counter - 1);
  *safety1 = sarray.counter > 0;
}
void main() {
_Bool clk;
_Bool safety1;
while(1) {
array(clk, &safety1);
}
}
