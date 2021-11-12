#include "headers/Token.h"
#include "string.h"
#include <stdlib.h>
#include "headers/Error.h"
#include "headers/Error.h"
#include "headers/CAT.h"
#include "headers/hashMap.h"
#include "headers/CPU.h"

char* TOKEN_TYPE_STRINGS[]={
       "NO",
       "POINTER",
       "REGISTER",
       "LABEL",
       "NUMBER",
       "MEMORIC",


};

static int intReg[NUMBER_OF_REGISTERS]={
     r0,
     r1,
     r2,
     r3,
     A,
     B,
     EAX,
     SP,
     BP
};
static Entry REG_NODES[NUMBER_OF_REGISTERS]={
      {"&ro",false,&intReg[0]},
      {"&r1",false,&intReg[1]},
      {"&r2",false,&intReg[2]},
      {"&r3",false,&intReg[3]},
      {"&a",false,&intReg[4]},
      {"&b",false,&intReg[5]},
      {"&eax",false,&intReg[6]},
      {"&sp",false,&intReg[7]},
      {"&bp",false,&intReg[8]}

};


HashMap MAP_REG;
void InitTokens(){
     MAP_REG=*init(NUMBER_OF_REGISTERS*2,hash);
     addNodes(&MAP_REG,REG_NODES,NUMBER_OF_REGISTERS);
}
void freeTokens(){
    freeMap(&MAP_REG);
}



TOKEN* parseToToken(char* string,ERROR* error){
     TOKEN* t=(TOKEN*)malloc(sizeof(TOKEN));
    bool errors=false;
     if(string==NULL){
        t->string="NULL";
        t->type=NO;

     }
    
   

    else if(strstr(string,LABEL_MARKER)==string){
         t->string=malloc(strlen(string)+1);
         strcpy(t->string,string);
         t->type=LABEL;
        
     }else if(strstr(string,MEMORY_MARKER)==string){
         char* s=strtok(string,MEMORY_MARKER);
          s=strtok(s,MEMORY_MARKER_END);
         t->string=malloc(strlen(string)+1);
         strcpy(t->string,s);
         t->type=POINTER; 

     }else if(strstr(string,REGISTER_MARKER)==string){
         t->string=malloc(strlen(string)+1);
         strcpy(t->string,string);
         t->type=REGISTER;
         bool registerExist=hasKey(&MAP_REG,string);
         if(!registerExist){
            char* no="no such register \"";
            char* exist="\"exist!";
            int i=strlen(no)+strlen(exist)+strlen(string)+1;
            error->errorMessage=(char*)malloc(i);
            char* strings[3]={
                no,
                string,
                exist
            };
            CAT(error->errorMessage,strings,3);
            errors=true;
         }else{
            printf("register %s",string);
         }
         


     }else if(strstr(string,HEX_MARKER)==string){
           char* end; 
            strtol(string,&end,0);
          if(*end!='\0'){
             char* hex="Hex value \"";
             char* not_real="\" is not a real number";
             int i=strlen(hex)+strlen(string)+strlen(not_real)+1;
             error->errorMessage=(char*)malloc(i);
             char* strings[3]={
                  hex,
                  string,
                  not_real
             };
             CAT(error->errorMessage,strings,3);
             errors=true;
          }else{
             t->string=malloc(strlen(string)+1);
             strcpy(t->string,string);
             t->type=NUMBER; 
          }
     }else if(strstr(string,BIN_MARKER)!=0){
             char* end;
             char* s=strtok(string,BIN_MARKER);
              
            int a=strtol(s,&end,2);
          if(*end!='\0'){
           char* bin="Binary value \"";
             char* not_real="\" is not a real number";
             int i=strlen(bin)+strlen(string)+strlen(not_real)+1;
             error->errorMessage=(char*)malloc(i);
             char* strings[3]={
                  bin,
                  string,
                  not_real
             };
             CAT(error->errorMessage,strings,3);
             errors=true;
          }else{
          t->string=malloc(strlen(string)+1);
          strcpy(t->string,s);
          t->type=NUMBER; 
          }
     }else{
          char* end; 
            strtol(string,&end,0);
          if(*end!='\0'){
              error->errorMessage=(char*)malloc(sizeof(char)*28);
             strcpy(error->errorMessage,"value is not a real number\n");
             errors=true;
          }
         t->string=malloc(strlen(string)+1);
         strcpy(t->string,string);
          t->type=NUMBER; 



     }   
    if(errors){
           t->string="ERROR";
           t->type=NO;
    }else{
        error->errorMessage=NULL;
    }


       return t;
}