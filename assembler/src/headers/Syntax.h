#ifndef KEYWORD_H
#define KEYWORD_H
#include "hashMap.h"
#include "Token.h"
#include "Queue.h"

//OPCODE
//N:real value;P:pointer;R:register







typedef enum OPTION_TYPE{
     NONE,
     GET_NEXT_ARG_FROM_RAM,
     CONDITION,
     REG
} OPTION_TYPE;




typedef struct SYNTAX
{
    TOKEN_TYPE arg1;
    TOKEN_TYPE arg2;
    uint8_t opcode; 
    OPTION_TYPE option;
    uint16_t size;
} SYNTAX;
//syntax for each memmoric
typedef struct RULES{
    SYNTAX* syntaxRules;
    int amountOfRules;

} RULES;
typedef struct Instruction{
     TOKEN* operation;
     TOKEN* arg1;
     TOKEN* arg2;
     SYNTAX* syntax;


} Instruction;



void initSyntax();
SYNTAX* checkSyntax(char* keyword,TOKEN_TYPE a,TOKEN_TYPE b,ERROR* error);

void freeSyntax();

#endif

