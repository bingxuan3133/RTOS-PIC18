#include "unity.h"
#include "rs232.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_RS232_OpenComport(void) {
  RS232_OpenComport(2, 9600);
  RS232_SendByte(2, 0x6a);
}
