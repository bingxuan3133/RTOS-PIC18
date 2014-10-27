#include "unity.h"
#include "rs232.h"

#define COMPORT   2
#define MAX_TRIES 2500000
#define RS232_ReadByte(port) _RS232_ReadByte(port, __LINE__)

void setUp(void)
{
}

void tearDown(void)
{
}

// Wait till a byte arrives, then return the value
char _RS232_ReadByte(int comport_number, int line) {
  char data = -1;
  int count = 0;
  while(RS232_PollComport(comport_number, &data, 1) == 0 && count <MAX_TRIES)
    count++;
  if(count >= MAX_TRIES) {
    RS232_CloseComport(COMPORT);
    UNITY_TEST_FAIL(line, "Attempt to read byte but comport seems to be unresponsive");
  }
  return data;
}

void test_RS232_OpenComport(void) {
  RS232_OpenComport(2, 9600);
  RS232_SendByte(2, 0x6a);
  RS232_CloseComport(COMPORT);
}

void test_usartLoopback_should_echo_bytes_sent(void) {
  char buffer[256], *dataPtr = buffer;
  
  RS232_OpenComport(COMPORT, 9600);
  
  RS232_SendByte(COMPORT, 'H');
  *(dataPtr++) = RS232_ReadByte(COMPORT);
  RS232_SendByte(COMPORT, 'e');
  *(dataPtr++) = RS232_ReadByte(COMPORT);
  RS232_SendByte(COMPORT, 'l');
  *(dataPtr++) = RS232_ReadByte(COMPORT);
  RS232_SendByte(COMPORT, 'l');
  *(dataPtr++) = RS232_ReadByte(COMPORT);
  RS232_SendByte(COMPORT, 'o');
  *(dataPtr++) = RS232_ReadByte(COMPORT);
  *(dataPtr++) = '\0';
  
  RS232_CloseComport(COMPORT);
  
  TEST_ASSERT_EQUAL_STRING("Hello", buffer);
}