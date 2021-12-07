#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0
struct state_elements_main{
  _Bool alloc;
  _Bool free;
  unsigned char free_addr;
  unsigned short int busy[16];
  unsigned char count;
};
struct state_elements_main smain

void main(_Bool clock, _Bool alloc_raw, _Bool *nack, unsigned char *alloc_addr, _Bool free_raw, unsigned char free_addr_raw)
{
  unsigned short int busy_old[16];
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
  smain.alloc = alloc_raw;
  smain.free = free_raw;
  smain.free_addr = free_addr_raw;
  smain.count = (smain.count + (smain.alloc && !(*nack))) - (smain.free & smain.busy[smain.free_addr]);
  if(free_old)
    smain.busy[smain.free_addr] = 0;

  *nack = smain.alloc && smain.count == 16;
  *alloc_addr = ~smain.busy[0] ? 0 : (~smain.busy[1] ? 1 : (~smain.busy[2] ? 2 : (~smain.busy[3] ? 3 : (~smain.busy[4] ? 4 : (~smain.busy[5] ? 5 : (~smain.busy[6] ? 6 : (~smain.busy[7] ? 7 : (~smain.busy[8] ? 8 : (~smain.busy[9] ? 9 : (~smain.busy[10] ? 10 : (~smain.busy[11] ? 11 : (~smain.busy[12] ? 12 : (~smain.busy[13] ? 13 : (~smain.busy[14] ? 14 : (~smain.busy[15] ? 15 : 0)))))))))))))));
  if(alloc_old && !nack)
    smain.busy[*alloc_addr] = 1;

  *nack = smain.alloc && smain.count == 16;
  *alloc_addr = ~smain.busy[0] ? 0 : (~smain.busy[1] ? 1 : (~smain.busy[2] ? 2 : (~smain.busy[3] ? 3 : (~smain.busy[4] ? 4 : (~smain.busy[5] ? 5 : (~smain.busy[6] ? 6 : (~smain.busy[7] ? 7 : (~smain.busy[8] ? 8 : (~smain.busy[9] ? 9 : (~smain.busy[10] ? 10 : (~smain.busy[11] ? 11 : (~smain.busy[12] ? 12 : (~smain.busy[13] ? 13 : (~smain.busy[14] ? 14 : (~smain.busy[15] ? 15 : 0)))))))))))))));
}
void initial_main(){
  {
    for(i = 0 & 4294967295; i < 16; i = i + 1 & 4294967295)
      smain.busy[i] = 0;
    smain.count = 0;
    smain.alloc = FALSE;
    smain.free = FALSE;
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
    main(clock, alloc_raw, &nack, &alloc_addr, free_raw, free_addr_raw);
  }
}
