#include <xinu.h>
#include <stdio.h>

shellcmd xsh_signal(int nargs, char *args[]) {
    int32   num_of_times;
    char    ch;
    char    *chtime;

    if (nargs == 1) {
        kprintf("Signal with no args has been invoked, thus incrementing once only. \n");
        num_of_times = 1;
    }
    else if (nargs == 2) {
        chtime = args[1];
        ch = *chtime++;
        while(ch != NULLCH) {
            if ((ch < '0') || (ch > '9')) {
                kprintf("ERRROR : %s is not a number \n", ch);
                return 1;
            }
            num_of_times = num_of_times + (ch - '0');
            ch = *chtime++;
        }
    }
    signaling(num_of_times);
    return 0;

}
