#ifndef Mutex_H
#define Mutex_H

#include "PriorityLinkedList.h"
#include "TaskControlBlock.h"

typedef struct Mutex Mutex;

struct Mutex {
  int counter;
  TCB *owner;
  PriorityLinkedList waitingQueue;
};

void acquireMutex(Mutex *mutex, TCB *caller);
void releaseMutex(Mutex *mutex, TCB *caller);

#endif // Mutex_H
