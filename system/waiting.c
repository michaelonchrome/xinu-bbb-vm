#include <xinu.h>

void waiting(void) {
    kprintf("%d is waiting on a mutex. \n", getpid());
    wait(glbsem);
    kprintf("Mutex has been signaled, killing myself.\n");
    return;

}
