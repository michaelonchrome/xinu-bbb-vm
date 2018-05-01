/* insert.c - insert */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  insert  -  Insert a process into a queue in descending key order
 *------------------------------------------------------------------------
 */
status	insert(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* Key for the inserted process	*/
	)
{
	int16	curr;			/* Runs through items in a queue*/
	int16	prev;			/* Holds previous node index	*/

	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}
    /*

	curr = firstid(q);
	while (queuetab[curr].qkey >= key) {
		curr = queuetab[curr].qnext;
	}
	prev = queuetab[curr].qprev;	
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[prev].qnext = pid;
	queuetab[curr].qprev = pid;
   */ 
    // This should add stuff to the end of the list 
    //*
    queuetab[pid].qkey = key;
    pid = enqueue(pid, q);
	return OK;
}
