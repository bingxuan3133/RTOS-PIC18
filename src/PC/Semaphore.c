#include "Semaphore.h"

void upSemaphore(Semaphore *semaphore){
  if(semaphore->counter < semaphore->maxCounter)
    semaphore->counter++;
  else;
  // move caller task from blocking/waitingQueue to run (if any)
}

void downSemaphore(Semaphore *semaphore){
  semaphore->counter--;
  // move caller task to blocking/waitingQueue
}