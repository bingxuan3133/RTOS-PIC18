#include "Clock.h"
#include "../18c.h"

unsigned long clock = 0;

#define TIMER_INT_OFF  0b01111111  //Disable TIMER Interrupt
#define T0_8BIT        0b11111111  //Timer0 is configured as an 8-bit timer/counter
#define T0_SOURCE_INT  0b11011111  //Internal instruction cycle clock (CLKO) acts as source of clock
#define T0_PS_1_8      0b11110010  //1:8 Prescale value

void initClock() {
  clock = 0;
  OpenTimer0( TIMER_INT_OFF &
              T0_8BIT &
              T0_SOURCE_INT &
              T0_PS_1_8);
}

/**
 * Return the micro-controller's clock since power-up.
 * 1 clock means 1.024 msec.
 */
unsigned long getClock() {
  if(hasTimer0Overflowed()) {
    clearTimer0Overflowed();
    clock++;
  }
  return clock;
}

/////////////////////////////////////////
// These functions are for internal use
/////////////////////////////////////////
char hasTimer0Overflowed() {
  return INTCONbits.TMR0IF;
}

void clearTimer0Overflowed() {
  INTCONbits.TMR0IF = 0;
}
