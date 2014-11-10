#include "Clock.h"
#include "Interrupt.h"
#include "../18c.h"

volatile unsigned long clock;
char workingReg, bankSelectReg, statusReg, tosUp, tosHi, tosLo;

void timer0Isr() {
  #asm
    movwf   _workingReg
    movff   STATUS, _statusReg
    movff   BSR, _bankSelectReg

    movff   TOSU, _tosUp
    movff   TOSH, _tosHi
    movff   TOSL, _tosLo
  #endasm
  // 1) Save all data above into TCB pointed by runningTCB
  // 2) Get the highest priority task from the priority linked-list
  // 3) Insert the runningTCB into the priority linked-list
  // 4) Restore all data in high priority task to
  //     1) TOS
  //    ii) BSR
  //   iii) STATUS
  //    iv) WREG
  // 5) Return from interrupt
  // Backup important data
  clock++;
  clearTimer0Overflowed();
}

void initClock() {
  clock = 0;
  enableGlobalInterrupt();
  OpenTimer0( TIMER_INT_ON &
              T0_8BIT &
              T0_SOURCE_INT &
              T0_PS_1_8);
}

/**
 * Return the micro-controller's clock since power-up.
 * 1 clock means 1.024 msec.
 */
unsigned long getClock() {
  /*
  if(hasTimer0Overflowed()) {
    clearTimer0Overflowed();
    clock++;
  }
  */
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
