#include "unity.h"
#include "TaskControlBlock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_compareTCBPriority_given_task1_is_the_only_task_to_compare_should_return_1(void) {
  TCB task1 = {.priority = 1};
	int result = compareTCBPriority(&task1, NULL);
  
  TEST_ASSERT_EQUAL(1, result);
}

void test_compareTCBPriority_given_task1_has_higher_priority_than_task2_should_return_1(void) {
  TCB task1 = {.priority = 1};
  TCB task2 = {.priority = 3};
	int result = compareTCBPriority(&task1, &task2);
  
  TEST_ASSERT_EQUAL(1, result);
}

void test_compareTCBPriority_given_task1_has_lower_priority_than_task2_should_return_0(void) {
  TCB task1 = {.priority = 3};
  TCB task2 = {.priority = 2};
	int result = compareTCBPriority(&task1, &task2);
  
  TEST_ASSERT_EQUAL(0, result);
}

void test_compareTCBPriority_given_nothing_to_compare(void) {
  TCB task1 = {.priority = 3};
  TCB task2 = {.priority = 2};
	int result = compareTCBPriority(NULL, NULL);
  
  TEST_ASSERT_EQUAL(0, result);
}