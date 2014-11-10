#include "TaskControlBlock.h"
#include <stdio.h>

int compareTCBPriority(void *elementOfInterest, void *elementInList) {
  TCB *newTCB = (TCB *)elementOfInterest;
  TCB *oldTCB = (TCB *)elementInList;
  
  if(newTCB != NULL && oldTCB != NULL) {
    if(newTCB->priority < oldTCB->priority) // new comer has higher priority
      return 1;
    else // new comer has lower priority
      return 0;
  } else if(newTCB == NULL && oldTCB == NULL) { // both are NULL
    return 0;
  } else if(newTCB != NULL && oldTCB == NULL) { // at the end of list
    return 1;
  } else
    return 0;
}