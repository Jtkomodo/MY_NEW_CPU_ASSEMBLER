#ifndef _POINTERHASH_H
#define _POINTERHASH_H
#include "Instruction.h"
#include <stdbool.h>



#define MAX_SIZE 1000
#define NULL_PTR 0xffff



typedef struct Label{
    char key[60]; 
    Pointer value;
} Label;


bool isListEmpty();
void initList();
bool addLabelToList(Label label);
void changeLabelValue(char *key,Pointer value);
bool getPointer(char* key,Pointer* dest);
void DeleteTable();
void printTable();
#endif


