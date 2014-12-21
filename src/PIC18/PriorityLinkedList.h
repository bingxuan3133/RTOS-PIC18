#ifndef PriorityLinkedList_H
#define PriorityLinkedList_H

#include "TaskControlBlock.h"

typedef struct Item Item;

struct Item {
  Item *next;
};

typedef struct PriorityLinkedList PriorityLinkedList;

struct PriorityLinkedList {
  Item *head;
  Item *tail;
};

void addPriorityLinkedList(PriorityLinkedList *list,
                           void *data,
                           int compare(void *, void *));
                           
void *removeFromHeadPriorityLinkedList(PriorityLinkedList *list);

#define addTCB(list, data)  addPriorityLinkedList(list,\
                                                  data,\
                                                  compareTCBPriority)

#define removeTCBFromHead(list) removeFromHeadPriorityLinkedList(list)

#endif // PriorityLinkedList_H