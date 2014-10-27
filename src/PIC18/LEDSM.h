#ifndef LEDSM_H
#define LEDSM_H

typedef enum {
  LED_START,
  LED_OFF,
  LED_ON
} LEDState;

typedef struct LEDData LEDData;
struct LEDData {
  LEDState state;
  unsigned long currentClock;
};

void initLed(LEDData *ledData);
void ledSM(LEDData *ledData);

#endif // LEDSM_H
