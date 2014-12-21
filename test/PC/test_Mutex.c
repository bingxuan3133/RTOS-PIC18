#include "unity.h"
#include "Mutex.h"
#include "PriorityLinkedList.h"
#include "TaskControlBlock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_acquireMutex_given_counter_is_1_should_decrease_counter_to_0_and_remember_owner(void) {
  TCB task = {0};
  Mutex mutex = {.counter = 1, .owner = NULL};
  acquireMutex(&mutex, &task);
  TEST_ASSERT_EQUAL(0, mutex.counter);
  TEST_ASSERT_EQUAL_PTR(&task, mutex.owner);
}

void test_acquireMutex_given_counter_is_0_should_decrease_counter_to_neg_1(void) {
  TCB task = {0};
  Mutex mutex = {.counter = 0, .owner = &task};
  acquireMutex(&mutex, &task);
  TEST_ASSERT_EQUAL(-1, mutex.counter);
  TEST_ASSERT_EQUAL_PTR(&task, mutex.owner);
}

void test_acquireMutex_given_mutex_is_acquired_by_task1_should_not_be_acquired_by_task2(void) {
  TCB task1 = {0};
  TCB task2 = {0};
  Mutex mutex = {.counter = 0, .owner = &task1};
  acquireMutex(&mutex, &task2);
  TEST_ASSERT_EQUAL(0, mutex.counter);
  TEST_ASSERT_EQUAL_PTR(&task1, mutex.owner);
  TEST_ASSERT_EQUAL_PTR(&task2, mutex.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&task2, mutex.waitingQueue.tail);
}

void test_releaseMutex_given_counter_is_0_should_increase_counter_to_1_and_forget_owner(void) {
  TCB task = {0};
  Mutex mutex = {.counter = 0, .owner = &task};
  releaseMutex(&mutex, &task);
  TEST_ASSERT_EQUAL(1, mutex.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, mutex.owner);
}

void test_releaseMutex_given_counter_is_neg_1_should_increase_counter_to_0_and_not_forget_owner(void) {
  TCB task = {0};
  Mutex mutex = {.counter = -1, .owner = &task};
  releaseMutex(&mutex, &task);
  TEST_ASSERT_EQUAL(0, mutex.counter);
  TEST_ASSERT_EQUAL_PTR(&task, mutex.owner);
}

void test_releaseMutex_given_mutex_is_acquired_by_task1_should_not_be_released_by_task2(void) {
  TCB task1 = {0};
  TCB task2 = {0};
  Mutex mutex = {.counter = 0, .owner = &task1};
  releaseMutex(&mutex, &task2);
  TEST_ASSERT_EQUAL(0, mutex.counter);
  TEST_ASSERT_EQUAL_PTR(&task1, mutex.owner);
  TEST_ASSERT_EQUAL_PTR(&task2, mutex.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&task2, mutex.waitingQueue.tail);
}

void test_releaseMutex_given_mutex_is_released_by_task1_and_task2_is_blocked_should_unblock_task2(void) {
  TCB task1 = {0};
  TCB task2 = {0};
  Mutex mutex = {.counter = 0, .owner = &task1 , .waitingQueue= {.head = (Item *)&task2, .tail = (Item *)&task2}};
  
  releaseMutex(&mutex, &task1);
  TEST_ASSERT_EQUAL(0, mutex.counter);
  TEST_ASSERT_EQUAL_PTR(&task2, mutex.owner);
  TEST_ASSERT_EQUAL_PTR(NULL, mutex.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, mutex.waitingQueue.tail);
}

void test_releaseMutex_given_mutex_is_released_by_task1_and_task2_is_blocked_should_unblock_task2_and_task3(void) {
  TCB task1 = {0};
  TCB task2 = {0};
  TCB task3 = {0};
  Mutex mutex = {.counter = 0, .owner = &task1 , .waitingQueue= {.head = NULL, .tail = NULL}};
  addTCB(&mutex.waitingQueue, &task2);
  addTCB(&mutex.waitingQueue, &task3);
  TEST_ASSERT_EQUAL_PTR(&task2, mutex.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&task3, mutex.waitingQueue.tail); 
  
  releaseMutex(&mutex, &task1);
  TEST_ASSERT_EQUAL(0, mutex.counter);
  TEST_ASSERT_EQUAL_PTR(&task2, mutex.owner);
  TEST_ASSERT_EQUAL_PTR(&task3, mutex.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&task3, mutex.waitingQueue.tail); 
  
  releaseMutex(&mutex, &task2);
  TEST_ASSERT_EQUAL(0, mutex.counter);
  TEST_ASSERT_EQUAL_PTR(&task3, mutex.owner);
  TEST_ASSERT_EQUAL_PTR(NULL, mutex.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, mutex.waitingQueue.tail);
}