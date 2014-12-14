#include "Clock.h"
#include "Interrupt.h"
#include "PreemptiveOS.h"
#include "Types.h"
#include "../18c.h"
#if !(defined(__XC) || defined(__18CXX))
  #include "timers.h"
#else
  #include <timers.h>
#endif // __18CXX

volatile unsigned long clock;
uint8 workingReg, bankSelectReg, statusReg, tosHi, tosLo;
uint16 task, stackPointer;

#pragma code high_vector = 0x08
void highPriorityIsr(void) {
  _asm
  goto timer0Isr
  _endasm
}
#pragma code

#pragma interruptlow timer0Isr save=FSR2L
void timer0Isr(void) {
  TCB *newTCB;

  clock++;
  clearTimer0Overflowed();

  tosHi = TOSH;
  tosLo = TOSL;

  //_asm
    //movff   WREG, workingReg
    //movff   STATUS, statusReg
    //movff   BSR, bankSelectReg
    //movff   TOSU, tosUp
    //movff   TOSH, tosHi
    //movff   TOSL, tosLo
  //_endasm
  // 1) Save all data above into TCB pointed by runningTCB
  // 2) Get the highest priority task from the priority linked-list
  // 3) Insert the runningTCB into the priority linked-list
  // 4) Restore all data in high priority task to
  //     1) TOS
  //     ii)Stack pointer
  // 5) Return from interrupt
  // Backup important data
  
  task = ((uint16)tosHi)<<8 | tosLo;
  //task = tosLo + ((int)tosHi)<<8;
  runningTCB->task = task;
  stackPointer = FSR1;
  runningTCB->stackPointer = stackPointer;
  //runningTCB->stackPointer = FSR1;
  newTCB = removeTCBFromHead(&readyQueue);
  //runningTCB->stackPointer = FSR1;
  addTCB(&readyQueue, runningTCB);
  runningTCB = newTCB;

  tosLo = runningTCB->task;
  tosHi = (runningTCB->task)>>8;

  _asm
    movff   tosHi, WREG
    movwf   TOSH, ACCESS
    movff   tosLo, WREG
    movwf   TOSL, ACCESS
  _endasm

  stackPointer = runningTCB->stackPointer;
  FSR1 = stackPointer;
}

void initClock(void) {
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
unsigned long getClock(void) {
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
char hasTimer0Overflowed(void) {
  return INTCONbits.TMR0IF;
}

void clearTimer0Overflowed(void) {
  INTCONbits.TMR0IF = 0;
}