/* 
 * File:   Blinky.c
 * Author: Chiew Bing Xuan
 *
 * Created on September 29, 2014, 11:19 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "../18c.h"

void shortDelay(void) {
  unsigned long i;
  for(i = 0; i < 10000; i++);
}

void configureLED(void) {
  TRISCbits.TRISC0 = 0;
}

void onLED(void) {
  PORTCbits.RC0 = 1;
}

void offLED(void) {
  PORTCbits.RC0 = 0;
}

