#ifndef TaskControlBlock_H
#define TaskControlBlock_H

typedef struct TCB TCB;

struct TCB {
  TCB *next;
  char priority;
  char programCounter[3];
  int *dataStack;
  char status;
};

int compareTCBPriority(void *elementOfInterest, void *elementInList);

#endif // TaskControlBlock_H
