#ifndef Clock_H
#define Clock_H

void initClock();
unsigned long getClock();
char hasTimer0Overflowed();
void clearTimer0Overflowed();

#endif // Clock_H
