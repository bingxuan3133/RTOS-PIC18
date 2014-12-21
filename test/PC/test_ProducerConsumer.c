#include "unity.h"
#include "ProducerConsumer.h"
#include "Semaphore.h"
#include "TaskControlBlock.h"
#include "PriorityLinkedList.h"

// Buffer status
int array0[] = {0, 0, 0};
int array1[] = {0x5A5A5A5A, 0, 0};
int array2[] = {0x5A5A5A5A, 0x5A5A5A5A, 0};
int array3[] = {0x5A5A5A5A, 0x5A5A5A5A, 0x5A5A5A5A};

// Test Counter
int testCount = 1;
  
void setUp(void) {
  printf("Test %d\n", testCount++);
  printf("------------------------\n");
}

void tearDown(void) {
  printf("========================\n");
}

void test_consumer_try_to_consume_item_when_buffer_is_empty_should_be_blocked(void) {
  TCB producerTask = {0};
  TCB consumerTask = {0};
  int yieldOnThese[] = {2, 5, 6};
  
  registerForYield(yieldOnThese, 3);
  initProducerConsumer();
  
  consumer(&consumerTask);
  
  TEST_ASSERT_EQUAL(-1, itemCount.counter);
  TEST_ASSERT_EQUAL(3, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(&consumerTask, itemCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&consumerTask, itemCount.waitingQueue.tail);
}

void test_producer_try_to_wake_consumer_up_from_waitingQueue(void) {
  TCB producerTask = {0};
  TCB consumerTask = {0};
  int yieldOnThese[] = {2, 5, 6};
  
  registerForYield(yieldOnThese, 3);
  initProducerConsumer();
  
  consumer(&consumerTask); // Blocked
  producer(&producerTask);
  
  TEST_ASSERT_EQUAL(0, itemCount.counter);
  TEST_ASSERT_EQUAL(2, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, itemCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, itemCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_INT_ARRAY(array1, itemBuffer, 3);
  
  consumer(&consumerTask);
  TEST_ASSERT_EQUAL(0, itemCount.counter);
  TEST_ASSERT_EQUAL(3, emptyCount.counter);
  TEST_ASSERT_EQUAL_INT_ARRAY(array0, itemBuffer, 3);
}


void test_multiple_producer_try_to_produce_items(void) {
  TCB producerTask1 = {0};
  TCB producerTask2 = {0};
  TCB producerTask3 = {0};
  TCB consumerTask = {0};
  int yieldOnThese[] = {1, 1, 5, 5, 5};
  
  registerForYield(yieldOnThese, 5);
  initProducerConsumer();

  producer(&producerTask1);
  
  TEST_ASSERT_EQUAL(0, itemCount.counter);
  TEST_ASSERT_EQUAL(2, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_INT_ARRAY(array0, itemBuffer, 3);

  producer(&producerTask2);
  
  TEST_ASSERT_EQUAL(0, itemCount.counter);
  TEST_ASSERT_EQUAL(1, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_INT_ARRAY(array0, itemBuffer, 3);

  producer(&producerTask3);
  
  TEST_ASSERT_EQUAL(1, itemCount.counter);
  TEST_ASSERT_EQUAL(0, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_INT_ARRAY(array1, itemBuffer, 3);
  
  producer(&producerTask2);
  
  TEST_ASSERT_EQUAL(2, itemCount.counter);
  TEST_ASSERT_EQUAL(0, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_INT_ARRAY(array2, itemBuffer, 3);
  
  producer(&producerTask1);
  
  TEST_ASSERT_EQUAL(3, itemCount.counter);
  TEST_ASSERT_EQUAL(0, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_INT_ARRAY(array3, itemBuffer, 3);  
}

void test_producer_try_to_produce_item_when_buffer_is_full_should_be_blocked(void) {
  TCB producerTask1 = {0};
  TCB producerTask2 = {0};
  TCB producerTask3 = {0};
  TCB consumerTask = {0};
  int yieldOnThese[] = {5, 5, 5, 1, 1};
  
  registerForYield(yieldOnThese, 5);
  initProducerConsumer();

  producer(&producerTask1);
  producer(&producerTask2);
  producer(&producerTask3);
  producer(&producerTask1);
  
  TEST_ASSERT_EQUAL(3, itemCount.counter);
  TEST_ASSERT_EQUAL(-1, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(&producerTask1, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&producerTask1, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_INT_ARRAY(array3, itemBuffer, 3);
  
  producer(&producerTask2);
  
  TEST_ASSERT_EQUAL(3, itemCount.counter);
  TEST_ASSERT_EQUAL(-2, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(&producerTask1, emptyCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&producerTask2, emptyCount.waitingQueue.head->next);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head->next->next);
	TEST_ASSERT_EQUAL_PTR(&producerTask2, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_INT_ARRAY(array3, itemBuffer, 3);
}

void test_consumer_try_to_wake_producer_up_from_waitingQueue(void) {
  TCB producerTask1 = {0};
  TCB producerTask2 = {0};
  TCB producerTask3 = {0};
  TCB consumerTask = {0};
  int yieldOnThese[] = {5, 5, 5, 1, 1, 6, 6, 5, 5};
  
  registerForYield(yieldOnThese, 9);
  initProducerConsumer();

  producer(&producerTask1);
  producer(&producerTask2);
  producer(&producerTask3);
  producer(&producerTask1); // Blocked
  producer(&producerTask2); // Blocked
  
  consumer(&consumerTask);
  TEST_ASSERT_EQUAL(2, itemCount.counter);
  TEST_ASSERT_EQUAL(-1, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(&producerTask2, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&producerTask2, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_INT_ARRAY(array2, itemBuffer, 3);
    
  consumer(&consumerTask);
  TEST_ASSERT_EQUAL(1, itemCount.counter);
  TEST_ASSERT_EQUAL(0, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_INT_ARRAY(array1, itemBuffer, 3);
}