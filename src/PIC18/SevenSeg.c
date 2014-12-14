#include "SevenSeg.h"
#include "Clock.h"
#include "../18c.h"

#if !(defined(__XC) || defined(__18CXX))
  #include "spi.h"
#else
  #include <spi.h>
#endif // __18CXX

#define   SPI_FOSC_4    0b00000000
#define   MODE_11       0b00000011
#define   SMPEND        0b10000000

#define _7SEG_CONTROL (PORTDbits.RD0)
#define _7SEG_CONTROL_TRIS (TRISDbits.TRISD0)

#define MSEC_150 146

char sevenSegPattern[] = {0xee, // 0
                          0x82, // 1
                          0xdc, // 2
                          0xd6, // 3
                          0xb2, // 4
                          0x76, // 5
                          0x7e, // 6
                          0xc2, // 7
                          0xfe, // 8
                          0xf6, // 9
                          0xfa, // A
                          0x3e, // b
                          0x6c, // C
                          0x9e, // d
                          0x7c, // E
                          0x78};// F

void init7Segment(SevenSegmentData *data) {
  data->state = _7SEG_INIT;
}

void init7SegmentHardware(void) {
  OpenSPI(SPI_FOSC_4, MODE_11, SMPEND);
  _7SEG_CONTROL_TRIS = 0;
  _7SEG_CONTROL = 1;
}

void sevenSegmentSM(SevenSegmentData *data) {
  switch(data->state) {
    case _7SEG_INIT:
      init7SegmentHardware();
      data->count = 0;
      data->currentClock = getClock();
      write7Segment(data->count);
      data->state = _7SEG_WAITING;
      break;

    case _7SEG_WAITING:
      if(getClock() - data->currentClock >= MSEC_150) {
        data->count++;
        if(data->count >= 15)
          data->count = 0;
        write7Segment(data->count);
        data->currentClock = getClock();
      }
      data->state = _7SEG_WAITING;
      break;

    default:
      data->state = _7SEG_INIT;
      break;
  }
}

void write7Segment(char data) {
  WriteSPI(sevenSegPattern[data]);
}