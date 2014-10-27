#include "UsartLoopback.h"
#include "usart.h"

/**
 * Initialize the usart loopback's internal data
 */
void initUsartLoopback(LoopbackData *loopbackData) {
  loopbackData->state = WAIT_DATA;
  loopbackData->dataByte = 0;
}


void usartLoopbackSM(LoopbackData *loopbackData) {
  switch(loopbackData->state) {
    case WAIT_DATA:
      if(DataRdyUSART()) {
        loopbackData->dataByte = ReadUSART();
        loopbackData->state = WAIT_TO_TX;
      } else {
        loopbackData->state = WAIT_DATA;
      }
      break;
    case WAIT_TO_TX:
      if(!BusyUSART()) {
        WriteUSART(loopbackData->dataByte);
        loopbackData->state = WAIT_DATA;
      } else {
        loopbackData->state = WAIT_TO_TX;
      }
      break;
    default:
      // Should not reach here
      break;
  }
}