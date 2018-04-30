#include <xinu.h>
#include <string.h>
#include <stdio.h>

shellcmd xsh_create(int nargs, char *args[]) {

    pid32   pid;
    pri16   priority;
    uint32 num_of_args=0;
    int num_of_times=0;
    char    ch;
    char    *chprio;
    char    *name_process = "";
    // Stores address of function to call
    // This is determined through set logic and 
    // args passed in by the user.
    void    *func_to_call;

    if (nargs == 1) {
        priority=INITPRIO;
        func_to_call = runforever;
        name_process = "Basic";
    }
    else if ( nargs >= 2 ) {
        chprio = args[1];
        ch = *chprio++;
        priority = 0;
        while(ch != NULLCH) {
            if ((ch < '0') || (ch > '9')) {
                kprintf("%s: non-digit in priority\n", args[1]);
                return 1;
            }
            priority = 10*priority + (ch - '0');
            ch = *chprio++;
        }

        if (priority < (pri16)MINKEY) {
            kprintf("%s: invalid prioirty\n", args[1]);
            return 1;
        }

        if ( nargs == 3) {
            if(strncmp(args[2], "--wait", 7) == 0) {
                name_process = "Waiting";
                func_to_call = waiting;
            }
            else if(strncmp(args[2], "--sleep", 8) == 0) {
                name_process = "Sleeping";
                func_to_call = sleeping;
            }
            /*
            else if(strncmp(args[2], "--signal", 9) == 0) {
                kprintf("Signalling happening?\n");
                name_process = "Signaling";
                func_to_call = signaling;
                num_of_args = 1;
                num_of_times = 1;
                kprintf("This is nargs : %d\n",nargs);
                if ( nargs == 4 ) {
                    kprintf("CRAZY 4 args?!\n");
                }
                if( nargs == 4 ) {
                    kprintf("Doin some calcuations\n");
                    char *to_convert = args[3];
                    char num_time = *to_convert;
                    num_of_times =( num_time - 0);
                    kprintf("%d: Is the final out \n", num_of_times);
                }
            }
            */
            else {
                kprintf("%s: Is not a valid argument \n", args[2]);
                return 1;
            }
        }
        else {
            func_to_call = runforever;
            name_process = "Basic";
        }
    }
    else {
        kprintf("Too many arguments\n");
        return 1;
    }
    pid = create(func_to_call, 1024, priority, name_process, 0);
    resume(pid);
    return 0;



}
