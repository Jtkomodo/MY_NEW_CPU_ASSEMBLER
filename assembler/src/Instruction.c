#include "headers/Instruction.h"
#include "string.h"
#include <stdlib.h>
#include "headers/Error.h"
#include "headers/Error.h"

TOKEN parseToToken(char* string,ERROR* error){
     TOKEN t;
    bool errors=false;
     if(string==NULL){
        t.string="NULL";
        t.type=NO;

     }
    
   

    else if(strstr(string,LABEL_MARKER)==string){
      char* c=strstr(string,LABEL_MARKER);
         t.string=string;
         t.type=LABEL;
        
     }else if(strstr(string,MEMORY_MARKER)==string){
         char* s=strtok(string,MEMORY_MARKER);
         t.string=strtok(s,MEMORY_MARKER_END); 
         t.type=POINTER; 

     }else if(strstr(string,REGISTER_MARKER)==string){
         t.string=string;
         t.type=REGISTER;
     }else if(strstr(string,HEX_MARKER)==string){
           char* end; 
            strtol(string,&end,0);
          if(*end!='\0'){
       
             error->errorMessage=(char*)malloc(sizeof(char)*32);
             strcpy(error->errorMessage,"Hex value is not a real number\n");
             errors=true;
          }else{
             t.string=string;
             t.type=NUMBER; 
          }
     }else if(strstr(string,BIN_MARKER)!=0){
             char* end;
             char* s=strtok(string,BIN_MARKER);
              
            int a=strtol(s,&end,2);
          if(*end!='\0'){
            error->errorMessage=(char*)malloc(sizeof(char)*35);
            strcpy(error->errorMessage,"binary value is not a real number\n");
            errors=true;
          }else{
          t.string=s;
          t.type=NUMBER; 
          }
     }else{
          char* end; 
            strtol(string,&end,0);
          if(*end!='\0'){
              error->errorMessage=(char*)malloc(sizeof(char)*28);
             strcpy(error->errorMessage,"value is not a real number\n");
             errors=true;
          }
          t.string=string;
          t.type=NUMBER; 



     }   
    if(errors){
           t.string="ERROR";
           t.type=NO;
    }else{
        error->errorMessage=NULL;
    }


       return t;
}