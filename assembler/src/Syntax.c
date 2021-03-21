#include "headers/Syntax.h"
#include <string.h>
#define AMOUNT_OF_KEY_WORDS 3
#define AMOUNT_OF_MOV_RULES 4
#define AMOUNT_OF_ADD_RULES 1
#define AMOUNR_OF_JMP_RULES 1
SYNTAX move_rules[AMOUNT_OF_MOV_RULES]={
    {REGISTER,NUMBER,0x02},
    {REGISTER,REGISTER,0x03},
    {POINTER,REGISTER,0x04},
    {POINTER,NUMBER,0x05}
};
SYNTAX add_rules[AMOUNT_OF_ADD_RULES]={
    {REGISTER,NUMBER,0x72},
};
SYNTAX jmp_rules[AMOUNR_OF_JMP_RULES]={
    {LABEL,NO,0x80},

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
      AMOUNR_OF_JMP_RULES

};


Node KeyWords[AMOUNT_OF_KEY_WORDS]={
       {"mov",false,&move},
       {"add",false,&add},
       {"jmp",false,&jmp},

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
      char* syntax_error="SYNTAX_ERROR";  
      SYNTAX* syntax=NULL;
      RULES* rules;
      getValue(&h,keyword,(void**)&rules);
      if(rules!=NULL){
         for(int i=0;i<rules->amountOfRules;i++){
            SYNTAX* s=&(rules->syntaxRules[i]);
             if(s!=NULL){
                if((s->arg1==a)&&(s->arg2==b)){
                   syntax=s;
                break;
                }
             }
          
         }
        
      }else{
        char* Memoric=" Memoric \"";
        char* not_found="\" does not exist";
        size_t i=strlen(syntax_error)+strlen(Memoric)+strlen(keyword)+strlen(not_found)+1;
        error->errorMessage=(char*)malloc(i);
        strcpy(error->errorMessage,syntax_error);
        char* strings[3]={
             Memoric,
             keyword,
             not_found
        };
      for(int i=0;i<3;i++){
       char* string=strings[i];
       strcat(error->errorMessage,string);
       }
   
      }

      return syntax;
}