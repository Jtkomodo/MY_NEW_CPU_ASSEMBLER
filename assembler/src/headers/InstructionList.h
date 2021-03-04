#ifndef LIST_H
#define LIST_H

#include "Instruction.h"
#include <stdbool.h>

typedef struct Node{
  void* value;
  struct node *nextNode;
} Node;



void Push(void* i);
void* pop();
void clear();
bool Empty();
#endif