#ifndef Semaphore_H
#define Semaphore_H

#include "PriorityLinkedList.h"
#include "TaskControlBlock.h"

extern TCB *runningTCB;

typedef struct Semaphore Semaphore;

struct Semaphore {
  int counter;
  int maxCounter;
  PriorityLinkedList waitingQueue;
};

void upSemaphore(Semaphore *semaphore);
void downSemaphore(TCB *caller, Semaphore *semaphore);

#endif // Semaphore_H
