#include "Semaphore.h"
#include "PriorityLinkedList.h"
#include "TaskControlBlock.h"
#include <stdio.h>

TCB *runningTCB;

void upSemaphore(Semaphore *semaphore) {
  if(semaphore->counter < semaphore->maxCounter) {
    semaphore->counter++;
    if(semaphore->counter <= 0) {
      runningTCB = removeTCBFromHead(&semaphore->waitingQueue);
      }
  } else;
  // move caller task from blocking/waitingQueue to run (if any)
}

void downSemaphore(TCB *caller, Semaphore *semaphore) {
  semaphore->counter--;
  if(semaphore->counter >= 0) {
    ;
  } else {// (semaphore->counter <= 0) {
    addTCB(&semaphore->waitingQueue, caller);
    runningTCB = NULL;
  // move caller task to blocking/waitingQueue
  }
}
