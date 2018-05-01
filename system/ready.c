/* ready.c - ready */

// Need to mod this for FCFS
// 1. Ready calls insert, has to change that too
// 2. We dont care about pri in this assignment
// 3. How do we handle null process? 
// 4. what happens if there is an infinite loop?
//      //clkhandler chekc the currpid
//      // in the null process check the ready list and call resched
//      and to yield to trigger context switch
//      might have to change the rescudle

#include <xinu.h>

qid16	readylist;			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	insert(pid, readylist, prptr->prprio);
	resched();

	return OK;
}
