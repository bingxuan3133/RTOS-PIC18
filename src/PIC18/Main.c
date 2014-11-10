/* 
 * File:   Main.c
 * Author: Chiew Bing Xuan
 *
 * Created on September 29, 2014, 11:19 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Blinky.h"
#include "Loopback.h"
#include "Clock.h"
//#include "LEDSM.h"
#include "Led2.h"
#include "SevenSeg.h"
#include "UsartLoopback.h"
#include "Tasking.h"
#include "Interrupt.h"
#include "../18c.h"
#if !(defined(__XC) || defined(__18CXX))
  #include "usart.h"
  #include "spi.h"
  #include "timers.h"
#else
    #include <usart.h>
#endif // __18CXX

#pragma config OSC = INTIO67, PWRT = ON, WDT = OFF, LVP = OFF, DEBUG = ON

#define setFreq8MHz() (OSCCONbits.IRCF = 7)

#define configureUsartTo8Bits9600Baud()\
          OpenUSART(USART_TX_INT_OFF &\
                    USART_RX_INT_OFF &\
                    USART_ASYNCH_MODE &\
                    USART_EIGHT_BIT &\
                    USART_CONT_RX &\
                    USART_BRGH_HIGH, 51);

int main(int argc, char** argv) {
  LoopbackData loopbackData;
  // LEDData ledData;
  Led2Data led2Data;
  SevenSegmentData sevenSegData;

  setFreq8MHz();
  configureUsartTo8Bits9600Baud();

  initClock();
  while(1) {
  }
  initUsartLoopback(&loopbackData);
  //initLed(&ledData);
  configureLED();
  initTasking(&led2Data);
  init7Segment(&sevenSegData);
  while(1) {
    /*
    usartLoopbackSM(&loopbackData);
    // ledSM(&ledData);
    led2SM(&led2Data);
    sevenSegmentSM(&sevenSegData);
    */
  }
  CloseUSART();
  CloseSPI();

  return 0;
}
