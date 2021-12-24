#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0
struct state_elements_main{
  _Bool free;
  unsigned char free_addr;
  _Bool busy[16];
  unsigned char count;
  _Bool alloc;
};
struct state_elements_main smain;

void main(_Bool clock, _Bool alloc_raw, _Bool *nack, unsigned char *alloc_addr, _Bool free_raw, unsigned char free_addr_raw)
