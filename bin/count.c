#include <stdio.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

unsigned char count_old;
_Bool last_clk;
struct state_elements_count {
    unsigned char count;
};
struct state_elements_count scount;
void count(_Bool clk, unsigned char *out) {
    count_old = scount.count;
    if (clk == 1 && last_clk == 0) {
        if ((scount.count & 15) == 7) {
            scount.count = 0;
            *out = scount.count & 15;
        } else {
            scount.count = (count_old & 15) + 1;
            *out = scount.count & 15;
        }
    }
    *out = scount.count & 15;
}
void main() {//main function
    _Bool clk;
    unsigned char out;
    clk = 0;
    while (1) {
        last_clk = clk;
        clk = !clk;
        count(clk, &out);
        assert((out & 15) < 8);
    }

}
