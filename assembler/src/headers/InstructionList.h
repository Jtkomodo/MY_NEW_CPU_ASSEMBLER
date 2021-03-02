#include "Instruction.h"
#include <stdbool.h>
#ifndef LIST_H
#define LIST_H

typedef struct Node{
  void* value;
  struct node *nextNode;
} Node;


#endif
void Push(void* i);
void* pop();
void clear();
bool Empty();