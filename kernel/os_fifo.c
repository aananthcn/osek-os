#include <stdio.h>
#include <sg_tasks.h>
#include <sg_fifo.h>

#include "os_fifo.h"



int OsFifoWrite(OsFifoType* pFifoQ, TaskType TaskID) {
	u32 head;

	/* Validate inputs */
	if ((TaskID < 0) || (TaskID >= TASK_ID_MAX)) {
		printf("Error: %s() invalid TaskID: %d\n", __func__, TaskID);
		return -1;
	}
	if (pFifoQ == NULL) {
		printf("Error: %s() invalid pFifoQ\n", __func__);
		return -1;
	}

	/* Push to FIFO head as long as the head does't eat the tail */
	if (!pFifoQ->full) {
		head = pFifoQ->head;
		pFifoQ->task[head] = (OsTaskType*)&OsTaskList[TaskID];
		pFifoQ->head = (pFifoQ->head + 1) %
				(pFifoQ->size);
		if (pFifoQ->head == pFifoQ->tail) {
			pFifoQ->full = true;
		}
	}
	else {
		printf("Error: %s() FIFO Full! Missing task = %d\n",
			__func__, TaskID);
		return -1;
	}
#ifdef DEBUG
	printf("Debug Info: Adding task:%d to FIFO: %s\n", TaskID, pFifoQ->name);
#endif
	return 0;
}


OsTaskType* OsFifoRead(OsFifoType* pFifoQ) {
	OsTaskType *task = NULL;

	/* Validate input */
	if (pFifoQ == NULL) {
		printf("Error: %s() pFifoQ is NULL!\n", __func__);
		return NULL;
	}

	/* Read from FIFO tail, always, but don't go beyond head */
	if ((pFifoQ->tail != pFifoQ->head) ||
		(pFifoQ->full)) {
		task = pFifoQ->task[pFifoQ->tail];
		pFifoQ->full = false;
		pFifoQ->tail = (pFifoQ->tail + 1) %
				(pFifoQ->size);
	}
#ifdef DEBUG
	else {
		printf("Debug Info: %s() FIFO Empty!\n", __func__);
	}
#endif

	return task;
}


int AddTaskToFifoQueue(const OsTaskType task, const OsFifoType* fq[]) {
	OsFifoType* pFifo;

	/* validate inputs */
	if (&task == NULL) {
		printf("Error: %s(), task argument is NULL!", __func__);
		return -1;
	}
	if (fq == NULL) {
		printf("Error: %s(), FIFO Queue argument is NULL!", __func__);
		return -1;
	}
	if (task.priority >= SG_FIFO_QUEUE_MAX_LEN) {
		printf("Error: task ID:%d has invalid priority: %d\n",
				task.id, task.priority);
		return -1;
	}

	pFifo = (OsFifoType*) fq[task.priority];
	OsFifoWrite(pFifo, task.id);

	return 0;
}


OsTaskType* GetTaskFromFifoQueue(const OsFifoType* fq[], u32 prio) {
	OsTaskType* task = NULL;

	/* validate inputs */
	if (fq == NULL) {
		printf("Error: %s(), FIFO Queue argument is NULL!", __func__);
		return NULL;
	}
	if (prio >= SG_FIFO_QUEUE_MAX_LEN) {
		printf("Error: %s(), invalid priority: %d\n", __func__, prio);
		return NULL;
	}

	if (fq[prio] != NULL) {
		task = OsFifoRead((OsFifoType*)fq[prio]);
	}

	return task;
}