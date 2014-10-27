#ifndef UsartLoopback_H
#define UsartLoopback_H

typedef enum {
  WAIT_DATA,
  WAIT_TO_TX
} LoopbackState;

typedef struct LoopbackData LoopbackData;
struct LoopbackData {
  LoopbackState state;
  char dataByte;
};

void initUsartLoopback(LoopbackData *loopbackData);
void usartLoopbackSM(LoopbackData *data);

#endif // UsartLoopback_H
