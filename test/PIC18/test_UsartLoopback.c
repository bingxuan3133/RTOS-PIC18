#include "unity.h"
#include "UsartLoopback.h"
#include "mock_usart.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_usartLoopbackSM_given_WAIT_DATA_should_stay_in_the_same_state(void) {
	LoopbackData loopbackData = {.state = WAIT_DATA};
  DataRdyUSART_ExpectAndReturn(0);
  usartLoopbackSM(&loopbackData);
  TEST_ASSERT_EQUAL(WAIT_DATA, loopbackData.state);
}

void test_usartLoopbackSM_given_WAIT_DATA_and_byte_arrive_should_read_and_transition_to_WAIT_TO_TX(void) {
	LoopbackData loopbackData = {.state = WAIT_DATA, .dataByte = 0x5a};
  DataRdyUSART_ExpectAndReturn(1);
  ReadUSART_ExpectAndReturn(0x5a);
  usartLoopbackSM(&loopbackData);
  TEST_ASSERT_EQUAL(WAIT_TO_TX, loopbackData.state);
  TEST_ASSERT_EQUAL(0x5a, loopbackData.dataByte);
}

void test_usartLoopbackSM_given_WAIT_TO_TX_should_stay_in_the_same_state(void) {
	LoopbackData loopbackData = {.state = WAIT_TO_TX};
  BusyUSART_ExpectAndReturn(1);
  usartLoopbackSM(&loopbackData);
  TEST_ASSERT_EQUAL(WAIT_TO_TX, loopbackData.state);
}

void test_usartLoopbackSM_given_WAIT_TO_TX_and_tx_buffer_empty_should_send_back_same_byte_and_transition_to_WAIT_DATA(void) {
	LoopbackData loopbackData = {.state = WAIT_TO_TX, .dataByte = 0x5a};
  BusyUSART_ExpectAndReturn(0);
  WriteUSART_Expect(0x5a);
  usartLoopbackSM(&loopbackData);
  TEST_ASSERT_EQUAL(WAIT_DATA, loopbackData.state);
  TEST_ASSERT_EQUAL(0x5a, loopbackData.dataByte);
}
