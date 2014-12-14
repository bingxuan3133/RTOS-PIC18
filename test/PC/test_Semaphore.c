#include "unity.h"
#include "Semaphore.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_upSemaphore_should_increase_semaphore_counter(void) {
  Semaphore semaphore = {.counter = 0, .maxCounter = 3};
  
  upSemaphore(&semaphore);
	TEST_ASSERT_EQUAL(1, semaphore.counter);
}

void test_upSemaphore_should_not_increase_semaphore_counter_if_reach_maxCounter(void) {
  Semaphore semaphore = {.counter = 3, .maxCounter = 3};
  
  upSemaphore(&semaphore);
	TEST_ASSERT_EQUAL(3, semaphore.counter);
}

void test_downSemaphore_should_increase_semaphore_counter(void) {
  Semaphore semaphore = {.counter = 0, .maxCounter = 3};
  
  downSemaphore(&semaphore);
	TEST_ASSERT_EQUAL(-1, semaphore.counter);
}
