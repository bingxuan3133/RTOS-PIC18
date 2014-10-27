#include "unity.h"
#include "Blinky.h"
#include "p18f4520.h"

void setUp(void) {}

void tearDown(void) {}

void test_configureLED_set_portc_pin0_as_output_OpenComport(void) {
  TRISCbits.RC0 = PIN_INPUT;
  configureLED();
  TEST_ASSERT_EQUAL(PIN_OUTPUT, TRISCbits.RC0);
}

void test_onLED_set_portc_pin0_to_high(void) {
  PORTCbits.RC0 = PIN_LOW;
  onLED();
  TEST_ASSERT_EQUAL(PIN_HIGH, PORTCbits.RC0);
}

void test_offLED_set_portc_pin0_to_high(void) {
  PORTCbits.RC0 = PIN_HIGH;
  offLED();
  TEST_ASSERT_EQUAL(PIN_LOW, PORTCbits.RC0);
}