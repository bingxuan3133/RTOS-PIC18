#include "PriorityLinkedList.h"
#include <stdio.h>

void addPriorityLinkedList(PriorityLinkedList *list,
                           void *data,
                           int compare(void *, void *)) {
  Item *itemPointer = list->head;
  Item *previousItem;
  
  if(compare(data, itemPointer) == 1) {
    list->head = data;
    if(itemPointer == NULL) // empty list
      list->tail = data;
    else  // data should be inserted as the first item
      ((Item *)data)->next = itemPointer;
    return;
  }
  
  while(1) {
    if(compare(data, itemPointer) == 1) { // insert
        previousItem->next = data;
        ((Item *)data)->next = itemPointer;
        if(itemPointer == NULL) // data should be insert at the last
          list->tail = data;
        break;
      } else { // do not insert
        previousItem = itemPointer;
        itemPointer = itemPointer->next;
      }
  }
}

void *removeFromHeadPriorityLinkedList(PriorityLinkedList *list) {
  Item *itemPointer = list->head;
  if(itemPointer != NULL) {
    list->head = itemPointer->next;
    if(itemPointer->next == NULL)
      list->tail = NULL;
  }
  return itemPointer;
}