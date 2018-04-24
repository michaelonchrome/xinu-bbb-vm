#include <xinu.h>

void    runforever(void) {
    kprintf("running PID: %d\n", getpid());
    while(1) {  }
}
