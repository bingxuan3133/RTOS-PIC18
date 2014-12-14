#ifndef TaskControlBlock_H
#define TaskControlBlock_H

#include "Types.h"

typedef struct TCB TCB;

struct TCB {
  TCB *next;
  uint8 priority;
  uint8 taskID;
  //void (*task)(void);
  uint16 task;
  uint16 stackPointer; // uint16
  uint16 framePointer; // uint16
  //int  *dataStack;
  //char programCounter[3];
  //char status;
};

int compareTCBPriority(void *elementOfInterest, void *elementInList);

#endif // TaskControlBlock_H