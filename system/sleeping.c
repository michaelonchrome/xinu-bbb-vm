#include <xinu.h>
void sleeping(void) {
    kprintf("Running PID: %d\n", getpid());
    kprintf("SLEEPY TIME!\n");
    sleep(10);
    while(1) { };

}

