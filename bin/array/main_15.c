#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0

unsigned char counter_old;
unsigned char mem_counter_old;

struct state_elements_array{
  unsigned char counter;
  unsigned char mem[8];
};
struct state_elements_array sarray;

void array(_Bool clk, _Bool *safety1)
{
  counter_old = sarray.counter;
  mem_counter_old = sarray.mem[sarray.counter];
  {
    sarray.counter = (counter_old & 7) + 1;
    *safety1 = (sarray.counter & 7) > 0;
  }
  {
    sarray.mem[counter_old] = counter_old & 7;
  }
  *safety1 = (sarray.counter & 7) > 0;
}

void main() {//main function
  _Bool clk;
  _Bool safety1;

  while(1) {
    clk = nondet_bool();

    array(clk, &safety1);

    assert(!((sarray.counter & 7) > 0) || sarray.mem[(sarray.counter & 7) - 1] == (sarray.counter & 7) - 1);

  }

}
