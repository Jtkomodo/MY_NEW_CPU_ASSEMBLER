#include <stdio.h>
#include "Instruction.h"
#include <stdbool.h>


#ifndef _POINTERHASH_H
#define _POINTERHASH_H
#define MAX_SIZE 10000
#define NULL_PTR 0xffff



typedef struct Label{
    char key[60]; 
    Pointer value;
} Label;
#endif


void initList();
bool addLabelToList(Label label);
bool getPointer(char* key,Pointer* dest);
void DeleteTable();
void printTable();



