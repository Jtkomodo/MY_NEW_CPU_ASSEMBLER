#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/Instruction.h"
#include "headers/hashMap.h"
#include "headers/Queue.h"
#include "headers/Error.h"
#include "headers/Syntax.h"

#define ERROR_TO_MANY_ARGS 0x4
#define ERROR_TO_FEW_ARGS 0x6
#define ERROR_FILE_NOT_FOUND 0x404


typedef struct Label_entry{
    char* string;
    int lineNumber;
} Label_entry;

int firstPass(Queue* instructions,HashMap* h,FILE *file);
CPU_INSTRUCTION* secondPass(Queue* instructions);
void writeFIle();
int CheckIfProgramShouldRun(int argc,char *atgv[]);
TOKEN getToken(const char* arg);

int main(int argc, char *argv[]){
   int ERROR_CODE=CheckIfProgramShouldRun(argc,argv);
   if(ERROR_CODE!=0){
        return ERROR_CODE;
    }
 HashMap h=*init(100,hash);
 Queue q=*initQueue();
 
 char* file=argv[1];
 
  FILE *filePointer;
   filePointer= fopen(file,"r");
   if(filePointer==NULL){
     printf("[ERROR] FILE NOT FOUD");
      exit(EXIT_FAILURE);
   }

   initSyntax();
  firstPass(&q,&h,filePointer);
  secondPass(&q);
  fclose(filePointer);


  freeSyntax();
  freeQueue(&q);
  freeMap(&h);
  exit(0);
}

int CheckIfProgramShouldRun(int argc,char *atgv[]){
      if(argc>2){
        return ERROR_TO_MANY_ARGS;
      }else if(argc<2){
        return ERROR_TO_FEW_ARGS;
      }
    
    return 0;
}




int firstPass(Queue* instructions,HashMap* h,FILE *file){
//this is where we will get all the tokens and replace labels with the correct memory location
   int errors=0;
  Queue labelsDefinedLater=*initQueue();
  Queue errorList=*initQueue();
  int line=0;
  Pointer MEMLOCATION=0x00;
  char command[60];

   while(fgets(command, 60, file)!=NULL){ 
   line++;
   char *memoric=strtok(command,";");
   memoric=strtok(memoric,"\n");
   char* Ins=strtok(memoric," ");
   char* arg1=strtok(NULL,",");
   char* arg2=strtok(NULL," ");
  if(Ins!=NULL){
     printf("%s,%s,%s;\n",Ins,arg1,arg2);





     //addd label to hashmap with the correct memloaction
     if(strstr(memoric,LABEL_MARKER)==Ins){

        if(arg1!=NULL || arg2!=NULL){
        ERROR* e=(ERROR*)malloc(sizeof(ERROR));
        e->errorMessage=(char*)malloc(sizeof(char)*32);
        strcpy(e->errorMessage,"Label should not have a agument");
        e->lineNumber=line;
        enQueue(&errorList,e,true);
          continue;
       }
       
        Pointer m=*(Pointer*)malloc(sizeof(Pointer));
        m=MEMLOCATION;
        addNode(h,memoric,&m,true);
        continue;
   }else{
      ERROR* e=malloc(sizeof(ERROR));
      ERROR* e2=malloc(sizeof(ERROR));
      TOKEN a=parseToToken(arg1,e);
       if(e->errorMessage!=NULL){
            e->lineNumber=line;
            enQueue(&errorList,e,true);
            continue;
       }else{
           free(e);
        }
     

      TOKEN b=parseToToken(arg2,e2);
       if(e2->errorMessage!=NULL){
            e2->lineNumber=line;
            enQueue(&errorList,e2,true);
            continue;
       }else{
        free(e2);
       }

      ERROR* e3=malloc(sizeof(ERROR));
       if(checkSyntax(Ins,a.type,b.type,e3)!=NULL){
          free(e3);
          Instruction i=*(Instruction*)malloc(sizeof(Instruction));
           TOKEN t;
           t.string=Ins;
           t.type=MEMORIC;
          
            i.operation=t;
            i.arg1=a;
            i.arg2=b;
        if(a.type==LABEL){
          if(!hasKey(h,a.string)){
           Label_entry l=*(Label_entry*)malloc(sizeof(Label_entry));
           l.string=malloc(sizeof(a.string));
           strcpy(l.string,a.string);
           l.lineNumber=line; 
           enQueue(&labelsDefinedLater,&l,true);
           continue;
          }
        }
        if(b.type==LABEL){
           if(!hasKey(h,b.string)){
            Label_entry l=*(Label_entry*)malloc(sizeof(Label_entry));
            l.string=malloc(sizeof(b.string));
            strcpy(l.string,b.string);
            l.lineNumber=line; 
            enQueue(&labelsDefinedLater,&l,true);
            continue;
          }
        }



           enQueue(instructions,&i,true);
        
       }else{
        e3->lineNumber=line;
        enQueue(&errorList,e3,true);
        continue;
       }

       

   }
   




  



   MEMLOCATION++;
   }}



//check to see if any label was not defined

//check errors
while(!QueueIsEmpty(&labelsDefinedLater)){
    Label_entry* label=deQueue(&labelsDefinedLater);
    if(!hasKey(h,label->string)){
       ERROR* e=(ERROR*)malloc(sizeof(ERROR));
        e->errorMessage=(char*)malloc(sizeof(char)*32);
        strcpy(e->errorMessage,"Label not defined");
        e->lineNumber=label->lineNumber;
        enQueue(&errorList,e,true);
     
    }
   free(label->string);
   free(label); 
}


while(!QueueIsEmpty(&errorList)){
    ERROR* error=(ERROR*)deQueue(&errorList);
    if(error!=NULL){
        printf("[Error]Line %i %s\n",error->lineNumber,error->errorMessage);
        free(error->errorMessage);
        free(error);
        errors++;
    }
      
}

printf("ERRORS %i",errors);

freeQueue(&labelsDefinedLater);
freeQueue(&errorList);
return errors;
}
TOKEN getToken(const char* arg){

  
}

CPU_INSTRUCTION* secondPass(Queue* instructions){
 
   



   



}

