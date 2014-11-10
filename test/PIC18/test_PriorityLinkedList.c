#include "unity.h"
#include "PriorityLinkedList.h"
#include "TaskControlBlock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_addTCB_given_empty_list_should_add_newTCB_at_first_position(void) {
  TCB newTCB = {.next = NULL};
  PriorityLinkedList list = {.head = NULL, .tail = NULL};

	addTCB(&list, &newTCB);
  TEST_ASSERT_EQUAL_PTR(&newTCB, list.head);
  TEST_ASSERT_EQUAL_PTR(&newTCB, list.tail);
}

void test_addTCB_given_a_high_priority_TCB_in_list_should_add_newTCB_at_second_position(void) {
  TCB newTCB = {.next = NULL, .priority = 2};
  TCB TCBInList = {.next = NULL, .priority = 1};
  PriorityLinkedList list = {.head = &TCBInList, .tail = &TCBInList};

	addTCB(&list, &newTCB);
  TEST_ASSERT_EQUAL_PTR(&TCBInList, list.head);
  TEST_ASSERT_EQUAL_PTR(&newTCB, TCBInList.next);
  TEST_ASSERT_EQUAL_PTR(&newTCB, list.tail);
}