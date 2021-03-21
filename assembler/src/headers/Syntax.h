#ifndef KEYWORD_H
#define KEYWORD_H
#include "hashMap.h"
#include "instruction.h"
#include "Queue.h"

//OPCODE
//N:real value;P:pointer;R:register


//conditions for jump this will be placed in extended op section

#define IF_EQUAL     0
#define IF_GREATOR   1
#define IF_LESS      2

typedef struct SYNTAX
{
    TOKEN_TYPE arg1;
    TOKEN_TYPE arg2;
    uint8_t opcode; 
} SYNTAX;
//syntax for each memmoric
typedef struct RULES{
    SYNTAX* syntaxRules;
    int amountOfRules;

} RULES;



void initSyntax();
SYNTAX* checkSyntax(char* keyword,TOKEN_TYPE a,TOKEN_TYPE b,ERROR* error);

void freeSyntax();

#endif

