#include "headers/Syntax.h"
#include <string.h>
#include "headers/CAT.h"
#define AMOUNT_OF_KEY_WORDS 4
#define AMOUNT_OF_MOV_RULES 5
#define AMOUNT_OF_ADD_RULES 1
#define AMOUNt_OF_JMP_RULES 1
#define AMOUNT_OF_POP_RULES 1


SYNTAX move_rules[AMOUNT_OF_MOV_RULES]={
    {REGISTER,NUMBER,0x02,REG,(uint16_t)1},
    {REGISTER,REGISTER,0x03,REG,(uint16_t)1},
    {POINTER,REGISTER,0x04,REG,(uint16_t)1},
    {POINTER,NUMBER,0x05,GET_NEXT_ARG_FROM_RAM,(uint16_t)2},
    {POINTER,POINTER,0x05,GET_NEXT_ARG_FROM_RAM,(uint16_t)2}
};
SYNTAX add_rules[AMOUNT_OF_ADD_RULES]={
    {REGISTER,NUMBER,0x72,REG,(uint16_t)1},
};
SYNTAX pop_rules[AMOUNT_OF_POP_RULES]={
    {REGISTER,NO,0x90,REG,(uint16_t)1}
};

SYNTAX jmp_rules[AMOUNt_OF_JMP_RULES]={
    {LABEL,NO,0x80,NONE,(uint16_t)1},

};

RULES move={
     move_rules,
     AMOUNT_OF_MOV_RULES
};

RULES add={
      add_rules,
      AMOUNT_OF_ADD_RULES
};
RULES jmp={
      jmp_rules,
      AMOUNt_OF_JMP_RULES

};

RULES pop={
      pop_rules,
      AMOUNt_OF_JMP_RULES

};


Node KeyWords[AMOUNT_OF_KEY_WORDS]={
       {"mov",false,&move},
       {"add",false,&add},
       {"jmp",false,&jmp},
       {"pop",false,&pop},
};

HashMap h;
void initSyntax(){
    h=*init(AMOUNT_OF_KEY_WORDS+200,hash);
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
         for(int i=0;i<rules->amountOfRules;i++){
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

