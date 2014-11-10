#ifndef PriorityLinkedList_H
#define PriorityLinkedList_H

typedef struct PriorityLinkedList PriorityLinkedList;

struct PriorityLinkedList {
  void *head;
  void *tail;
};

typedef struct Item Item;

struct Item {
  void *next;
};

void addPriorityLinkedList(PriorityLinkedList *list,
                           void *data,
                           int compare(void *, void *));
void removePriorityLinkedList(PriorityLinkedList *list,
                              void *data,
                              int compare(void *, void *));
#define addTCB(list, data)  addPriorityLinkedList(list,\
                                                  data,\
                                                  compareTCBPriority);

#define removeTCB()


#endif // PriorityLinkedList_H