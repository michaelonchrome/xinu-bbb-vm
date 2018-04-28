#include <xinu.h>

void signaling(int time) {
    kprintf("Number of times to signal the semaphore : %d\n", time);
    int32 i;
    for(i=0; i<time; i++) {
        signal(glbsem);
    }
    return;
}
