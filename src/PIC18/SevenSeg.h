#ifndef SevenSeg_H
#define SevenSeg_H

typedef enum {
  _7SEG_INIT,
  _7SEG_WAITING
} SevenSegmentState ;

typedef struct SevenSegmentData SevenSegmentData;
struct SevenSegmentData {
  SevenSegmentState state;
  unsigned long currentClock;
  char count;
};

void init7Segment(SevenSegmentData *data);
void init7SegmentHardware(void);
void sevenSegmentSM(SevenSegmentData *data);
void write7Segment(char data);

#endif // SevenSeg_H
