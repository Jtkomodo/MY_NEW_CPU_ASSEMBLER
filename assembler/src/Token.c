#include "headers/Token.h"
#include "string.h"
#include <stdlib.h>
#include "headers/Error.h"
#include "headers/Error.h"
#include "headers/CAT.h"

char* TOKEN_TYPE_STRINGS[]={
       "NO",
       "POINTER",
       "REGISTER",
       "LABEL",
       "NUMBER",
       "MEMORIC",


};

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