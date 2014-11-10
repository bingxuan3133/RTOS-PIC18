#include "Led2.h"
#include "Tasking.h"
#include "Blinky.h"
#include "Clock.h"

#define MSEC_500 488
#define MSEC_150 146

void testingLed2SM(Led2Data *data) {
    /*
  startTasking(data->state);
  printf("LED2_INIT\n");
  printf("before yield\n");
  
  if(data->ledStatus == 10) {
    yield(data->state);
    printf("after yield\n");
  } else {
    printf("take jadi yield\n");
  }
  endTasking();
     */
}

void led2SM(Led2Data *data) {
  startTasking(data->state);
  while(1) {
    while(getClock() - data->currentClock < MSEC_150) {
      data->ledStatus = LED_OFF;
      offLED();
      yield(data->state);
    }
    data->ledStatus = LED_ON;
    onLED();
    data->currentClock = getClock();
    yield(data->state);
    
    while(getClock() - data->currentClock < MSEC_150) {
      data->ledStatus = LED_ON;
      onLED();
      yield(data->state);
    }
    data->ledStatus = LED_OFF;
    offLED();
    data->currentClock = getClock();
    yield(data->state);
  }
  endTasking();
}