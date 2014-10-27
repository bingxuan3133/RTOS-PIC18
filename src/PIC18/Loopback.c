#include "Loopback.h"
#include "../18c.h"
#include <usart.h>

void usartLoopback() {
  char data;
  while(!DataRdyUSART());
  data = getcUSART();
  while(BusyUSART());
  putcUSART(data);
}