#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0
struct state_elements_main{
  _Bool busy[16];
  unsigned char count;
  _Bool alloc;
  _Bool free;
  unsigned char free_addr;
};
struct state_elements_main smain;

void main(_Bool clock, _Bool alloc_raw, _Bool *nack, unsigned char *alloc_addr, _Bool free_raw, unsigned char free_addr_raw)
{
  _Bool busy_old[16];
  unsigned char count_old;
  _Bool alloc_old;
  _Bool free_old;
  unsigned char free_addr_old;
  int i;
  busy_old = smain.busy;
  count_old = smain.count;
  alloc_old = smain.alloc;
  free_old = smain.free;
  free_addr_old = smain.free_addr;
  smain.free_addr = free_addr_raw & 15;
}
void main() {//main function
  _Bool clock;
  _Bool alloc_raw;
  _Bool nack;
  unsigned char alloc_addr;
  _Bool free_raw;
  unsigned char free_addr_raw;
  while(1) {
    main(clock, alloc_raw, &nack, &alloc_addr, free_raw, free_addr_raw);
  }
}
