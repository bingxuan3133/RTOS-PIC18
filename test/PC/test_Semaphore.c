#include "unity.h"
#include "Semaphore.h"
#include "PriorityLinkedList.h"
#include "TaskControlBlock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_upSemaphore_should_increase_semaphore_counter(void) {
  TCB task = {0};
  Semaphore semaphore = {.counter = 0, .maxCounter = 3};
  
  TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.tail);
  
  upSemaphore(&semaphore);
	TEST_ASSERT_EQUAL(1, semaphore.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.tail);
}

void test_upSemaphore_should_not_increase_semaphore_counter_if_reach_maxCounter(void) {
  TCB task = {0};
  Semaphore semaphore = {.counter = 3, .maxCounter = 3};
  
  TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.tail);
  
  upSemaphore(&semaphore);
	TEST_ASSERT_EQUAL(3, semaphore.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.tail);
}

void test_upSemaphore_should_increase_semaphore_counter_and_remove_waiting_task_from_waitingQueue(void) {
  TCB task = {0};
  // PriorityLinkedList queue = {.head = &task, .tail = &task};
  Semaphore semaphore = {.counter = 0, .maxCounter = 3, .waitingQueue = {.head = (Item *)&task, .tail = (Item *)&task}};
  
  TEST_ASSERT_EQUAL_PTR(&task, semaphore.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&task, semaphore.waitingQueue.tail);
  
  upSemaphore(&semaphore);
	TEST_ASSERT_EQUAL(1, semaphore.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.tail);
}

void test_downSemaphore_should_decrease_semaphore_counter(void) {
  TCB task = {0};
  Semaphore semaphore = {.counter = 3, .maxCounter = 3};
  
  TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.tail);
  
  downSemaphore(&task, &semaphore);
	TEST_ASSERT_EQUAL(2, semaphore.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.tail);
}

void test_downSemaphore_should_decrease_semaphore_counter_and_add_caller_task_to_waitingQueue(void) {
  TCB task = {0};
  Semaphore semaphore = {.counter = 0, .maxCounter = 3};
  
  TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.tail);
  
  downSemaphore(&task, &semaphore);
	TEST_ASSERT_EQUAL(-1, semaphore.counter);
	TEST_ASSERT_EQUAL_PTR(&task, semaphore.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&task, semaphore.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.head->next);
}

void test_downSemaphore(void) {
  TCB task = {0};
  runningTCB = &task;
  Semaphore empty = {.counter = 3, .maxCounter = 3};
  
  TEST_ASSERT_EQUAL_PTR(NULL, empty.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, empty.waitingQueue.tail);
  
  downSemaphore(runningTCB, &empty);
  downSemaphore(runningTCB, &empty);
  downSemaphore(runningTCB, &empty);
  
  TEST_ASSERT_EQUAL_PTR(NULL, empty.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, empty.waitingQueue.tail);
  
  downSemaphore(runningTCB, &empty);
  
  TEST_ASSERT_EQUAL_PTR(NULL, runningTCB);
  TEST_ASSERT_EQUAL_PTR(&task, empty.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&task, empty.waitingQueue.tail);
}

void test_upSemaphore(void) {
  TCB task = {0};
  runningTCB = &task;
  Semaphore item = {.counter = 3, .maxCounter = 3};
  
  TEST_ASSERT_EQUAL_PTR(NULL, item.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, item.waitingQueue.tail);
  
  downSemaphore(runningTCB, &item);
  downSemaphore(runningTCB, &item);
  downSemaphore(runningTCB, &item);
  
  TEST_ASSERT_EQUAL_PTR(NULL, item.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, item.waitingQueue.tail);
  
  downSemaphore(runningTCB, &item);
  
  TEST_ASSERT_EQUAL_PTR(NULL, runningTCB);
  TEST_ASSERT_EQUAL_PTR(&task, item.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&task, item.waitingQueue.tail);
}
