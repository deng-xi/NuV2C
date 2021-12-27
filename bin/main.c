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
{
  int i;
  smain.alloc = alloc_raw;
  smain.free = free_raw;
  smain.free_addr = free_addr_raw & 15;
  smain.count = ((smain.count & 31) + (smain.alloc && !(*nack))) - (smain.free && smain.busy[smain.free_addr & 15]) & 31;
  *nack = smain.alloc && smain.count == 16;
  if(smain.free)
  {
    smain.busy[smain.free_addr] = 0;
    *alloc_addr = !smain.busy[0] ? 0 : (!smain.busy[1] ? 1 : (!smain.busy[2] ? 2 : (!smain.busy[3] ? 3 : (!smain.busy[4] ? 4 : (!smain.busy[5] ? 5 : (!smain.busy[6] ? 6 : (!smain.busy[7] ? 7 : (!smain.busy[8] ? 8 : (!smain.busy[9] ? 9 : (!smain.busy[10] ? 10 : (!smain.busy[11] ? 11 : (!smain.busy[12] ? 12 : (!smain.busy[13] ? 13 : (!smain.busy[14] ? 14 : (!smain.busy[15] ? 15 : 0)))))))))))))));
  }

  if(smain.alloc && !nack)
  {
    smain.busy[*alloc_addr] = 1;
    *alloc_addr = !smain.busy[0] ? 0 : (!smain.busy[1] ? 1 : (!smain.busy[2] ? 2 : (!smain.busy[3] ? 3 : (!smain.busy[4] ? 4 : (!smain.busy[5] ? 5 : (!smain.busy[6] ? 6 : (!smain.busy[7] ? 7 : (!smain.busy[8] ? 8 : (!smain.busy[9] ? 9 : (!smain.busy[10] ? 10 : (!smain.busy[11] ? 11 : (!smain.busy[12] ? 12 : (!smain.busy[13] ? 13 : (!smain.busy[14] ? 14 : (!smain.busy[15] ? 15 : 0)))))))))))))));
  }

  *nack = smain.alloc && smain.count == 16;
  *alloc_addr = !smain.busy[0] ? 0 : (!smain.busy[1] ? 1 : (!smain.busy[2] ? 2 : (!smain.busy[3] ? 3 : (!smain.busy[4] ? 4 : (!smain.busy[5] ? 5 : (!smain.busy[6] ? 6 : (!smain.busy[7] ? 7 : (!smain.busy[8] ? 8 : (!smain.busy[9] ? 9 : (!smain.busy[10] ? 10 : (!smain.busy[11] ? 11 : (!smain.busy[12] ? 12 : (!smain.busy[13] ? 13 : (!smain.busy[14] ? 14 : (!smain.busy[15] ? 15 : 0)))))))))))))));
  assert(!((smain.count & 15) == 0));
}
void initial_main(){
  {
    for(i = 0; i < 16; i = i + 1)
      smain.busy[(unsigned char)i] = 0;
    smain.count = 0;
    smain.alloc = 0;
    smain.free = 0;
    smain.free_addr = 0;
  }
}
void main() {//main function
  _Bool clock;
  _Bool alloc_raw;
  _Bool nack;
  unsigned char alloc_addr;
  _Bool free_raw;
  unsigned char free_addr_raw;
  initial_main();
  while(1) {
    clock = nondet_bool();
    alloc_raw = nondet_bool();
    free_raw = nondet_bool();
    free_addr_raw = nondet_uchar();
    main(clock, alloc_raw, &nack, &alloc_addr, free_raw, free_addr_raw);
  }
}
