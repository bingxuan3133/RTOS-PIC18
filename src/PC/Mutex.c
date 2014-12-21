#include "Mutex.h"
#include "PriorityLinkedList.h"
#include "TaskControlBlock.h"
#include <stdio.h>

void acquireMutex(Mutex *mutex, TCB *caller) {
  if(mutex->counter == 1) {
    mutex->counter--;
    mutex->owner = caller;
  } else {
    if(mutex->owner == caller) {
      mutex->counter--;
    } else { // caller is not owner
      addTCB(&mutex->waitingQueue, caller);
    }
  }
}

void releaseMutex(Mutex *mutex, TCB *caller) {
  if(mutex->owner == caller) {
    mutex->counter++;
    if(mutex->counter == 1) {
      mutex->owner = removeTCBFromHead(&mutex->waitingQueue);
      if(mutex->owner != NULL)
        mutex->counter--;
    }
  } else {
    addTCB(&mutex->waitingQueue, caller);
  }
}