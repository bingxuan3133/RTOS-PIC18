#ifndef PreemptiveOS_H
#define PreemptiveOS_H

#include "TaskControlBlock.h"
#include "PriorityLinkedList.h"

extern TCB *runningTCB;
extern TCB allTCBs[3];
extern PriorityLinkedList readyQueue;

void initPreemptiveMultitasking(void);

#endif // PreemptiveOS_H
