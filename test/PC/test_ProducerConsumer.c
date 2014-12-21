#include "unity.h"
#include "ProducerConsumer.h"
#include "Semaphore.h"
#include "Mutex.h"
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
  TCB producerTask = {.taskID = 1};
  TCB consumerTask = {.taskID = 1};
  int yieldOnThese[] = {2};
  
  registerForYield(yieldOnThese, 1);
  initProducerConsumer();
  
  consumer(&consumerTask);
  
  TEST_ASSERT_EQUAL(-1, itemCount.counter);
  TEST_ASSERT_EQUAL(3, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(&consumerTask, itemCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&consumerTask, itemCount.waitingQueue.tail);
}

void test_producer_try_to_wake_consumer_up_from_waitingQueue(void) {
  TCB producerTask = {.taskID = 1};
  TCB consumerTask = {.taskID = 1};
  int yieldOnThese[] = {2, 9, 10};
  
  registerForYield(yieldOnThese, 3);
  initProducerConsumer();
  
  consumer(&consumerTask); // Blocked
  producer(&producerTask);
  
  TEST_ASSERT_EQUAL(0, itemCount.counter);
  TEST_ASSERT_EQUAL(2, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, itemCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, itemCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array1, itemBuffer, 3);
  
  consumer(&consumerTask);
  TEST_ASSERT_EQUAL(0, itemCount.counter);
  TEST_ASSERT_EQUAL(3, emptyCount.counter);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array0, itemBuffer, 3);
}


void test_multiple_producers_p1_p2_has_not_acquireMutex_should_not_block_p3(void) {
  TCB producerTask1 = {.taskID = 1};
  TCB producerTask2 = {.taskID = 2};
  TCB producerTask3 = {.taskID = 3};
  TCB consumerTask = {.taskID = 1};
  int yieldOnThese[] = {1, 1, 9, 9, 9};
  
  registerForYield(yieldOnThese, 5);
  initProducerConsumer();

  producer(&producerTask1);
  
  TEST_ASSERT_EQUAL(0, itemCount.counter);
  TEST_ASSERT_EQUAL(2, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array0, itemBuffer, 3);

  producer(&producerTask2);
  
  TEST_ASSERT_EQUAL(0, itemCount.counter);
  TEST_ASSERT_EQUAL(1, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array0, itemBuffer, 3);

  producer(&producerTask3);
  
  TEST_ASSERT_EQUAL(1, itemCount.counter);
  TEST_ASSERT_EQUAL(0, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array1, itemBuffer, 3);
  
  producer(&producerTask2);
  
  TEST_ASSERT_EQUAL(2, itemCount.counter);
  TEST_ASSERT_EQUAL(0, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array2, itemBuffer, 3);
  
  producer(&producerTask1);
  
  TEST_ASSERT_EQUAL(3, itemCount.counter);
  TEST_ASSERT_EQUAL(0, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array3, itemBuffer, 3);  
}

void test_multiple_producers_p1_had_acquireMutex_should_block_p2_and_p3(void) {
  TCB producerTask1 = {.taskID = 1};
  TCB producerTask2 = {.taskID = 2};
  TCB producerTask3 = {.taskID = 3};
  TCB consumerTask = {.taskID = 1};
  int yieldOnThese[] = {3, 3, 3, 9, 9, 9};
  
  registerForYield(yieldOnThese, 6);
  initProducerConsumer();

  producer(&producerTask1);
  
  TEST_ASSERT_EQUAL(0, itemCount.counter);
  TEST_ASSERT_EQUAL(2, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, mutexBuffer.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, mutexBuffer.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array0, itemBuffer, 3);

  producer(&producerTask2);
  
  TEST_ASSERT_EQUAL(0, itemCount.counter);
  TEST_ASSERT_EQUAL(1, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(&producerTask2, mutexBuffer.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&producerTask2, mutexBuffer.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array0, itemBuffer, 3);

  producer(&producerTask3);
  
  TEST_ASSERT_EQUAL(0, itemCount.counter);
  TEST_ASSERT_EQUAL(0, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(&producerTask2, mutexBuffer.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&producerTask3, mutexBuffer.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array0, itemBuffer, 3);
  
  producer(&producerTask1);
  
  TEST_ASSERT_EQUAL(1, itemCount.counter);
  TEST_ASSERT_EQUAL(0, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(&producerTask3, mutexBuffer.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&producerTask3, mutexBuffer.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array1, itemBuffer, 3);
  
  producer(&producerTask2);
  
  TEST_ASSERT_EQUAL(2, itemCount.counter);
  TEST_ASSERT_EQUAL(0, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, mutexBuffer.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, mutexBuffer.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array2, itemBuffer, 3);    
  
  producer(&producerTask3);
  
  TEST_ASSERT_EQUAL(3, itemCount.counter);
  TEST_ASSERT_EQUAL(0, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, mutexBuffer.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, mutexBuffer.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array3, itemBuffer, 3);  
}

void test_producer_try_to_produce_item_when_buffer_is_full_should_be_blocked(void) {
  TCB producerTask1 = {.taskID = 1};
  TCB producerTask2 = {.taskID = 2};
  TCB producerTask3 = {.taskID = 3};
  TCB consumerTask = {.taskID = 1};
  int yieldOnThese[] = {9, 9, 9, 1, 1};
  
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
  TEST_ASSERT_EQUAL_HEX_ARRAY(array3, itemBuffer, 3);
  
  producer(&producerTask2);
  
  TEST_ASSERT_EQUAL(3, itemCount.counter);
  TEST_ASSERT_EQUAL(-2, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(&producerTask1, emptyCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&producerTask2, emptyCount.waitingQueue.head->next);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head->next->next);
	TEST_ASSERT_EQUAL_PTR(&producerTask2, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array3, itemBuffer, 3);
}

void test_consumer_try_to_wake_producer_up_from_waitingQueue(void) {
  TCB producerTask1 = {.taskID = 1};
  TCB producerTask2 = {.taskID = 2};
  TCB producerTask3 = {.taskID = 3};
  TCB consumerTask = {.taskID = 1};
  int yieldOnThese[] = {9, 9, 9, 1, 1, 10, 10, 9, 9};
  
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
  TEST_ASSERT_EQUAL_HEX_ARRAY(array2, itemBuffer, 3);
    
  consumer(&consumerTask);
  TEST_ASSERT_EQUAL(1, itemCount.counter);
  TEST_ASSERT_EQUAL(0, emptyCount.counter);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_HEX_ARRAY(array1, itemBuffer, 3);
}