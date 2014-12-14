#include "unity.h"
#include "PriorityLinkedList.h"
#include "TaskControlBlock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_addTCB_given_empty_list_should_add_newTCB_at_1st_position(void) {
  TCB newTCB = {.next = NULL};
  PriorityLinkedList list = {.head = NULL, .tail = NULL};
	addTCB(&list, &newTCB);
  TEST_ASSERT_EQUAL_PTR(&newTCB, list.head);
  TEST_ASSERT_EQUAL_PTR(&newTCB, list.tail);
}

void test_addTCB_given_a_high_priority_TCB_in_list_should_add_newTCB_at_2nd_position(void) {
  TCB newTCB = {.next = NULL, .priority = 2};
  TCB TCBInList = {.next = NULL, .priority = 1};
  PriorityLinkedList list = {.head = &TCBInList, .tail = &TCBInList};

	addTCB(&list, &newTCB);
  TEST_ASSERT_EQUAL_PTR(&TCBInList, list.head);
  TEST_ASSERT_EQUAL_PTR(&newTCB, TCBInList.next);
  TEST_ASSERT_EQUAL_PTR(&newTCB, list.tail);
}

void test_addTCB_given_a_low_priority_TCB_in_list_should_add_newTCB_at_1nd_position(void) {
  TCB newTCB = {.next = NULL, .priority = 1};
  TCB TCBInList = {.next = NULL, .priority = 2};
  PriorityLinkedList list = {.head = &TCBInList, .tail = &TCBInList};

	addTCB(&list, &newTCB);
  TEST_ASSERT_EQUAL_PTR(&newTCB, list.head);
  TEST_ASSERT_EQUAL_PTR(&TCBInList, newTCB.next);
  TEST_ASSERT_EQUAL_PTR(&TCBInList, list.tail);
}

void test_addTCB_given_2_higher_priority_TCBs_in_list_should_add_newTCB_at_3rd_position(void) {
  TCB newTCB = {.next = NULL, .priority = 5};
  TCB TCBInList2 = {.next = NULL, .priority = 3};
  TCB TCBInList1 = {.next = &TCBInList2, .priority = 1};
  PriorityLinkedList list = {.head = &TCBInList1, .tail = &TCBInList2};

	addTCB(&list, &newTCB);
  TEST_ASSERT_EQUAL_PTR(&TCBInList1, list.head);
  TEST_ASSERT_EQUAL_PTR(&TCBInList2, TCBInList1.next);
  TEST_ASSERT_EQUAL_PTR(&newTCB, TCBInList2.next);
  TEST_ASSERT_EQUAL_PTR(&newTCB, list.tail);
}

void test_addTCB_given_a_higher_priority_TCB_and_a_lower_priority_TCB_in_list_should_add_newTCB_at_2nd_position(void) {
  TCB newTCB = {.next = NULL, .priority = 2};
  TCB TCBInList2 = {.next = NULL, .priority = 3};
  TCB TCBInList1 = {.next = &TCBInList2, .priority = 1};
  PriorityLinkedList list = {.head = &TCBInList1, .tail = &TCBInList2};

	addTCB(&list, &newTCB);
  TEST_ASSERT_EQUAL_PTR(&TCBInList1, list.head);
  TEST_ASSERT_EQUAL_PTR(&newTCB, TCBInList1.next);
  TEST_ASSERT_EQUAL_PTR(&TCBInList2, list.tail);
}

void test_addTCB_given_priority_1_3_5_TCBs_in_listshould_add_newTCBs_at_2nd_and_4th_position(void) {
  TCB newTCB1 = {.next = NULL, .priority = 2};
  TCB newTCB2 = {.next = NULL, .priority = 4};
  TCB TCBInList3 = {.next = NULL, .priority = 5};
  TCB TCBInList2 = {.next = &TCBInList3, .priority = 3};
  TCB TCBInList1 = {.next = &TCBInList2, .priority = 1};
  PriorityLinkedList list = {.head = &TCBInList1, .tail = &TCBInList3};

	addTCB(&list, &newTCB1);
  TEST_ASSERT_EQUAL_PTR(&TCBInList1, list.head);
  TEST_ASSERT_EQUAL_PTR(&newTCB1, TCBInList1.next);
  TEST_ASSERT_EQUAL_PTR(&TCBInList2, newTCB1.next);
  TEST_ASSERT_EQUAL_PTR(&TCBInList3, TCBInList2.next);
  TEST_ASSERT_EQUAL_PTR(&TCBInList3, list.tail);

	addTCB(&list, &newTCB2);
  TEST_ASSERT_EQUAL_PTR(&TCBInList1, list.head);
  TEST_ASSERT_EQUAL_PTR(&newTCB1, TCBInList1.next);
  TEST_ASSERT_EQUAL_PTR(&TCBInList2, newTCB1.next);
  TEST_ASSERT_EQUAL_PTR(&newTCB2, TCBInList2.next);
  TEST_ASSERT_EQUAL_PTR(&TCBInList3, newTCB2.next);
  TEST_ASSERT_EQUAL_PTR(&TCBInList3, list.tail);
}

void test_removeTCBFromHead_given_empty_list_should_return_NULL(void) {
  TCB *removedTCB;
  PriorityLinkedList list = {.head = NULL, .tail = NULL};
	removedTCB = removeTCBFromHead(&list);
  TEST_ASSERT_EQUAL_PTR(NULL, list.head);
  TEST_ASSERT_EQUAL_PTR(NULL, list.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, removedTCB);
}

void test_removeTCBFromHead_given_1_TCB_in_list_should_return_that_TCB(void) {
  TCB *removedTCB;
  TCB newTCB = {.next = NULL, .priority = 1};
  PriorityLinkedList list = {.head = &newTCB, .tail = &newTCB};
	removedTCB = removeTCBFromHead(&list);
  TEST_ASSERT_EQUAL_PTR(NULL, list.head);
  TEST_ASSERT_EQUAL_PTR(NULL, list.tail);
  TEST_ASSERT_EQUAL_PTR(&newTCB, removedTCB);
}

void test_removeTCBFromHead_given_2_TCBs_in_list_should_return_the_first_TCB(void) {
  TCB *removedTCB;
  TCB newTCB2 = {.next = NULL, .priority = 2};
  TCB newTCB1 = {.next = &newTCB2, .priority = 1};
  PriorityLinkedList list = {.head = &newTCB1, .tail = &newTCB2};
	removedTCB = removeTCBFromHead(&list);
  TEST_ASSERT_EQUAL_PTR(&newTCB2, list.head);
  TEST_ASSERT_EQUAL_PTR(&newTCB2, list.tail);
  TEST_ASSERT_EQUAL_PTR(&newTCB1, removedTCB);
}