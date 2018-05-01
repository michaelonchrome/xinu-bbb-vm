#include <xinu.h>
/*  main.c  - main */
#define true 1
#define false 0

void delay_loop() {

    int j,i;
    for(i=0;i<1000;i++)
        for(j=0;j<1000;j++);

}

void run_process(void) {
    intmask mask;
    bool8 slept=false;
    int i;
    while(1) {
        mask = disable();
        delay_loop();
        kprintf("Process %d running \n", getpid());
        restore(mask);
        if(slept == false) {
            slept=true;
            sleep(30);
        }
    }
    return;


}

void test_process(void) { 
    int i;
    for(i=0; i<14;i++) {
        kprintf("Process %d running (dummy) \n", getpid());
    }
    
    return;
}

process	main(void)
{
    kprintf("Process %d running \n", getpid());
    resume(create(test_process, 1024, 2, "lowest_process",0));
    resume(create(run_process, 1024, 5, "process", 0));
    resume(create(run_process, 1024, 10, "process", 0));
    resume(create(run_process, 1024, 20, "process", 0));



	//resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

    /*
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
    */
	return OK;
}
