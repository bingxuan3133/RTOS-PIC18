#include "ProducerConsumer.h"
#include "Semaphore.h"
#include "Mutex.h"
#include "Tasking.h"
#include <stdio.h>

#include "TaskControlBlock.h"

#define   yieldOn(lineNumber, x) if(yieldPointer[i] == x && i < maxYield) {i++; yield(lineNumber); } else ;
#define   MAX_ITEMS   3

int i; // yield counter
int maxYield;
int *yieldPointer;
Semaphore emptyCount;
Semaphore itemCount;
Mutex mutexBuffer;
int itemBuffer[MAX_ITEMS];


void registerForYield(int *listToYield, int numberOfYields) {
  i = 0;
  maxYield = numberOfYields;
  yieldPointer = listToYield;
}

void initProducerConsumer(void) {
  emptyCount.counter = MAX_ITEMS;
  emptyCount.maxCounter = MAX_ITEMS;
  emptyCount.waitingQueue.head = NULL;
  emptyCount.waitingQueue.tail = NULL;
  itemCount.counter = 0;
  itemCount.maxCounter = MAX_ITEMS;
  itemCount.waitingQueue.head = NULL;
  itemCount.waitingQueue.tail = NULL;
  itemBuffer[0] = 0;
  itemBuffer[1] = 0;
  itemBuffer[2] = 0;
  mutexBuffer.counter = 1;
  mutexBuffer.owner = NULL;
  mutexBuffer.waitingQueue.head = NULL;
  mutexBuffer.waitingQueue.tail = NULL;
}

void addItemIntoBuffer(int item) {
  int i;
  for(i = 0; i < MAX_ITEMS; i++) {
    if(itemBuffer[i] == 0) {
      itemBuffer[i] = item;
      break;
    } 
  }
  if(i == MAX_ITEMS)
    printf("Item Overflow");
}

int removeItemFromBuffer() {
  int itemToReturn;
  int i;
  for(i = MAX_ITEMS - 1; i >= 0; i--) {
    if(itemBuffer[i] != 0) {
      itemToReturn = itemBuffer[i];
      itemBuffer[i] = 0;
      return itemToReturn;
    } 
  }
  if(i == -1)
    printf("Item Underflow");

}

void producer(TCB *self) {
  int item = 0x5A5A5A5A;
  printf("producer%d.__LINE__ = %d\n", self->taskID, self->task);
  startTasking(self->task);
  
  while(1) {
  
  downSemaphore(&emptyCount, self);
  
  yieldOn(self->task, 1);
  
  acquireMutex(&mutexBuffer, self);

  yieldOn(self->task, 3);
  
  addItemIntoBuffer(item);
  
  yieldOn(self->task, 5);
  
  upSemaphore(&itemCount);
  
  yieldOn(self->task, 7);
  
  releaseMutex(&mutexBuffer, self);
  
  yieldOn(self->task, 9);
  
  }
  
  endTasking();
}

void consumer(TCB *self) {
  int item;
  printf("consumer%d.__LINE__ = %d\n", self->taskID, self->task);
  startTasking(self->task);
  
  while(1) {
  
  downSemaphore(&itemCount, self);
  
  yieldOn(self->task, 2);
  
  acquireMutex(&mutexBuffer, self);
  
  yieldOn(self->task, 4);
  
  item = removeItemFromBuffer();
  
  yieldOn(self->task, 6);
  
  upSemaphore(&emptyCount);

  yieldOn(self->task, 8);
  
  releaseMutex(&mutexBuffer, self);
  
  yieldOn(self->task, 10);
  
  }
  
  endTasking();
}