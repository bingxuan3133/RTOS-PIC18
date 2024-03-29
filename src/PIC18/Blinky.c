/* 
 * File:   Blinky.c
 * Author: Chiew Bing Xuan
 *
 * Created on September 29, 2014, 11:19 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "../18c.h"
#if !(defined(__XC) || defined(__18CXX))
  #include "usart.h"
#endif // __18CXX

#pragma config OSC = INTIO67, PWRT = ON, WDT = OFF, LVP = OFF, DEBUG = ON

void shortDelay() {
  unsigned long i;
  for(i = 0; i < 10000; i++);
}

void configureLED() {
  TRISCbits.TRISC0 = 0;
}

void onLED() {
  PORTCbits.RC0 = 1;
}

void offLED() {
  PORTCbits.RC0 = 0;
}

