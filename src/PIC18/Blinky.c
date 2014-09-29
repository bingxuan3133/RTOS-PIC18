/* 
 * File:   Blinky.c
 * Author: Chiew Bing Xuan
 *
 * Created on September 29, 2014, 11:19 AM
 */

#pragma config OSC = INTIO67, PWRT = ON, WDT = OFF, LVP = OFF, DEBUG = ON

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

void shortDelay() {
    unsigned long i;
    for(i = 0; i < 5000; i++);
}

void configureLED() {
    TRISCbits.TRISC0 = 0;
}

void setLED() {
    PORTCbits.RC0 = 1;
}

void resetLED() {
    PORTCbits.RC0 = 0;
}


/*
 * 
 */
int main(int argc, char** argv) {
    configureLED();
    while(1) {
        setLED();
        shortDelay();
        resetLED();
        shortDelay();
    }

    return (EXIT_SUCCESS);
}

