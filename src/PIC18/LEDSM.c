#include "LEDSM.h"
#include "Blinky.h"
#include "Clock.h"

#define MSEC_500 488

void initLed(LEDData *ledData) {
  ledData->state = LED_START;
}

void ledSM(LEDData *ledData) {
  switch(ledData->state) {
    case LED_OFF:
      if(getClock() - ledData->currentClock >= MSEC_500) {
        onLED();
        ledData->state = LED_ON;
        ledData->currentClock = getClock();
      } else {
        ledData->state = LED_OFF;
      }
      break;

    case LED_START:
      ledData->currentClock = getClock();
      configureLED();
      ledData->state = LED_OFF;
      break;

    case LED_ON:
      if(getClock() - ledData->currentClock >= MSEC_500) {
        offLED();
        ledData->state = LED_OFF;
        ledData->currentClock = getClock();
      } else {
        ledData->state = LED_ON;
      }
      break;
      
    default:
      // Should not reach here
      ledData->state = LED_START;
      break;
  }
}