#include "Interrupt.h"
#include "Clock.h"

void interrupt interruptIsr() {
  timer0Isr();
}