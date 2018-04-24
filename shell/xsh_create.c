#include <xinu.h>
#include <string.h>
#include <stdio.h>

// int nargs = Number of arguements that will be passed to the function
// char *args[] = Char array based on int narg
// 
shellcmd xsh_create(int nargs, char *args[]) {

    pri16   priority; //Id of process to kill
    char    ch; // next character of argument
    char    *chprio; //Walks along argument string
    pid32   pid;
    // User did not provide additional arguments 
    if (nargs == 1) {
        priority=INITPRIO; // set to intial priority
        // Type create, and int value
    } else if (nargs == 2) {

        // Compute process priority
        chprio = args[1]; // Get the second element in args array
        ch = *chprio++;
        priority = 0;
        // Read char by char
        while (ch != NULLCH) {
            if ( (ch < '0') || (ch > '9') ) {
                kprintf("%s: non-digit in priority\n", args[1]);
                return 1;
            }
            priority = 10*priority + (ch - '0'); //To get int representation of the string
            ch = *chprio++; // increment pointer everytime we read something
        }

        // Compare priority against the minkey 
        if (priority < (pri16)MINKEY) {
            kprintf("%s: invalid priority\n",args[1]);
            return 1;
        }

    }
    else {
        kprintf("Too many arguments\n");
        return 1;
    }
    //1024 is the stack size
    pid=create(runforever, 1024, priority, "Test", 0);
    if (pid==SYSERR) {
        kprintf("Cannont create new process %d \n");

    }
    resume(pid);
    return 0;

}
