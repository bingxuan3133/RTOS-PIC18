#ifndef Semaphore_H
#define Semaphore_H

typedef struct Semaphore Semaphore;

struct Semaphore {
  int counter;
  int maxCounter;
};

void upSemaphore(Semaphore *semaphore);
void downSemaphore(Semaphore *semaphore);

#endif // Semaphore_H
