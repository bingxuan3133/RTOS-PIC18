#include "unity.h"
#include "SevenSeg.h"
#include "p18f4520.h"
#include "mock_Clock.h"
#include "mock_spi.h"

#define   SPI_FOSC_4    0b00000000
#define   MODE_11       0b00000011
#define   SMPEND        0b10000000

#define _7SEG_EN_PIN (PORTDbits.RD0)
#define _7SEG_EN_TRIS (TRISDbits.TRISD0)

void setUp(void)
{
}

void tearDown(void)
{
}

void test_init7Segment(void) {
  SevenSegmentData data = {.state = _7SEG_WAITING, .count = 0xff, .currentClock = 0};
  init7Segment(&data);

  TEST_ASSERT_EQUAL(_7SEG_INIT, data.state);
}

void test_init7SegmentHardware(void) {
  OpenSPI_Expect(SPI_FOSC_4, MODE_11, SMPEND);
  init7SegmentHardware();

  TEST_ASSERT_EQUAL(0, _7SEG_EN_TRIS);
  TEST_ASSERT_EQUAL(1, _7SEG_EN_PIN);
}

void test_sevenSegmentSM_given_state_in_7SEG_INIT_will_display_0(void) {
  SevenSegmentData data = {.state = _7SEG_INIT, .count = 0xff, .currentClock = 0};
  
  OpenSPI_Expect(SPI_FOSC_4, MODE_11, SMPEND);
  getClock_ExpectAndReturn(100);
  WriteSPI_ExpectAndReturn(0xee, 0xee);
  sevenSegmentSM(&data);

  TEST_ASSERT_EQUAL(0, _7SEG_EN_TRIS);
  TEST_ASSERT_EQUAL(1, _7SEG_EN_PIN);
  TEST_ASSERT_EQUAL(_7SEG_WAITING, data.state);
  TEST_ASSERT_EQUAL(0, data.count);
  TEST_ASSERT_EQUAL(100, data.currentClock);
}

void test_sevenSegmentSM_given_state_in_7SEG_WAITING_and_count_is_0x01_will_display_2(void) {
  SevenSegmentData data = {.state = _7SEG_WAITING, .count = 0x01, .currentClock = 100};
  
  getClock_ExpectAndReturn(300);
  WriteSPI_ExpectAndReturn(0xdc, 0xdc);
  getClock_ExpectAndReturn(300);
  sevenSegmentSM(&data);

  TEST_ASSERT_EQUAL(_7SEG_WAITING, data.state);
  TEST_ASSERT_EQUAL(0x02, data.count);
  TEST_ASSERT_EQUAL(300, data.currentClock);
}

void test_sevenSegmentSM_given_state_in_7SEG_WAITING_and_count_is_0x0f_will_display_0(void) {
  SevenSegmentData data = {.state = _7SEG_WAITING, .count = 0x0f, .currentClock = 100};
  
  getClock_ExpectAndReturn(300);
  WriteSPI_ExpectAndReturn(0xee, 0xee);
  getClock_ExpectAndReturn(300);
  sevenSegmentSM(&data);

  TEST_ASSERT_EQUAL(_7SEG_WAITING, data.state);
  TEST_ASSERT_EQUAL(0x00, data.count);
  TEST_ASSERT_EQUAL(300, data.currentClock);
}