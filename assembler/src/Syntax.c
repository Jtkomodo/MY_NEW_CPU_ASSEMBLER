#include "headers/Syntax.h"
#include <string.h>
#include "headers/CAT.h"
#include "headers/CPU.h"
#define AMOUNT_OF_KEY_WORDS 5
#define AMOUNT_OF_JE_RULES  2
#define AMOUNT_OF_MOV_RULES 5
#define AMOUNT_OF_ADD_RULES 1
#define AMOUNt_OF_JMP_RULES 2
#define AMOUNT_OF_POP_RULES 1


//opcodes for instructions





static  SYNTAX move_rules[AMOUNT_OF_MOV_RULES]={
    {REGISTER,NUMBER,OP_MOV_R_N,REG,1},
    {REGISTER,REGISTER,OP_MOV_R_R,REG,1},
    {POINTER,REGISTER,OP_MOVE_P_R,REG,1},
    {POINTER,NUMBER,OP_MOVE_P_N,GET_NEXT_ARG_FROM_RAM,2},
  
};
static  SYNTAX add_rules[AMOUNT_OF_ADD_RULES]={
    {REGISTER,NUMBER,OP_ADD,REG,1},

};
static  SYNTAX pop_rules[AMOUNT_OF_POP_RULES]={
    {REGISTER,NO,OP_POP,REG,1}
};

static  SYNTAX jmp_rules[AMOUNt_OF_JMP_RULES]={
    {LABEL,NO,OP_JMP,NONE,1},
    {POINTER,NO,OP_JMP,NONE,1},
};
static  SYNTAX je_rules[AMOUNT_OF_JE_RULES]={
    {LABEL,NO,OP_JMP,CONDITION,1},
    {POINTER,NO,OP_JMP,CONDITION,1},
};

static RULES move={
     move_rules,
     AMOUNT_OF_MOV_RULES
};

static RULES add={
      add_rules,
      AMOUNT_OF_ADD_RULES
};
static RULES jmp={
      jmp_rules,
      AMOUNt_OF_JMP_RULES

};

static RULES pop={
      pop_rules,
      AMOUNt_OF_JMP_RULES

};

static RULES je={
      je_rules,
      AMOUNT_OF_JE_RULES

};



static  Entry KeyWords[AMOUNT_OF_KEY_WORDS]={
       {"mov",false,&move},
       {"add",false,&add},
       {"jmp",false,&jmp},
       {"je",false,&je},
       {"pop",false,&pop},
};

HashMap h;

void initSyntax(){
    h=*init(AMOUNT_OF_KEY_WORDS*2,hash);
    addNodes(&h,KeyWords,AMOUNT_OF_KEY_WORDS);
  
}
void freeSyntax(){
    freeMap(&h);
    
}





SYNTAX* checkSyntax(char* keyword,TOKEN_TYPE a,TOKEN_TYPE b,ERROR* error){
      char* syntax_error="SYNTAX_ERROR ";
      char* a_tpye=TOKEN_TYPE_STRINGS[a]; 
      char* b_tpye=TOKEN_TYPE_STRINGS[b];   
      SYNTAX* syntax=NULL;
      RULES* rules;
      getValue(&h,keyword,(void**)&rules);

      if(rules!=NULL){
         for(int i=0;i<rules->amountOfRules-1;i++){
            SYNTAX* s=&(rules->syntaxRules[i]);
             if(s!=NULL){
                if((s->arg1==a)&&(s->arg2==b)){
                   syntax=malloc(sizeof(SYNTAX)*rules->amountOfRules);
                   syntax->arg1=s->arg1;
                   syntax->arg2=s->arg2;
                   syntax->opcode=s->opcode;
                   syntax->option=s->option;
                   syntax->size=s->size;
                break;
                }
             }
          
         }
         if(syntax==NULL){
            char* NO_RULES="NO RULES IN THE FORMAT (";
            char* COMMA=",";
            char* MEM=") exist for Memoric ";
              size_t i=strlen(syntax_error)+strlen(NO_RULES)+strlen(a_tpye)+strlen(COMMA)
              +strlen(b_tpye)+strlen(MEM)+strlen(keyword)+1;
                error->errorMessage=(char*)malloc(i);
                char* strings[7]={
                   syntax_error,
                   NO_RULES,
                   a_tpye,
                   COMMA,
                   b_tpye,
                   MEM,
                   keyword

                };
                CAT(error->errorMessage,strings,7);
         }
        
      }else{
        char* Memoric="Memoric \"";
        char* not_found="\" does not exist";
        size_t i=strlen(syntax_error)+strlen(Memoric)+strlen(keyword)+strlen(not_found)+1;
        error->errorMessage=(char*)malloc(i);
       
        char* strings[4]={
             syntax_error,
             Memoric,
             keyword,
             not_found
        };
       CAT(error->errorMessage,strings,4);
      }

      return syntax;
}

