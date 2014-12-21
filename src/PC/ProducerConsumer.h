#ifndef ProducerConsumer_H
#define ProducerConsumer_H

#include "Semaphore.h"
#include "Mutex.h"
#include "TaskControlBlock.h"

extern Semaphore emptyCount;
extern Semaphore itemCount;
extern int itemBuffer[3];
extern Mutex mutexBuffer;

void registerForYield(int *listToYield, int numberOfYields);
void initProducerConsumer(void);
void producer(TCB *self);
void consumer(TCB *self);
  
void addItemIntoBuffer(int item);
int removeItemFromBuffer();

#endif // Producer-Consumer_H
