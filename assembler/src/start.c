#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/Instruction.h"
#include "headers/hashMap.h"
#include "headers/Queue.h"

#define ERROR_TO_MANY_ARGS 0x4
#define ERROR_TO_FEW_ARGS 0x6
#define ERROR_FILE_NOT_FOUND 0x404
typedef struct ERROR{
     char* errorMessage;
     int lineNumber;
} ERROR;



uint32_t hash(const char *key, size_t len);
int firstPass(Queue* tokens,HashMap* h,FILE *file);
CPU_INSTRUCTION* secondPass(Queue* tokens);
void writeFIle();
int CheckIfProgramShouldRun(int argc,char *atgv[]);
void SyntaxCheck(const char* instruction,const char *arg1,const char arg2);
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


  firstPass(&q,&h,filePointer);
  secondPass(&q);
  fclose(filePointer);



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




int firstPass(Queue* tokens,HashMap* h,FILE *file){
//this is where we will get all the tokens and replace labels with the correct memory location
  Queue labelsDefinedLater=*initQueue();
  Queue errorList=*initQueue();
  int errors=0;
  int line=0;
  Pointer MEMLOCATION=0x00;
  char command[60];

   while(fgets(command, 60, file)!=NULL){ 
   line++;
   char *MEMORRIC=strtok(command,";");
   MEMORRIC=strtok(MEMORRIC,"\n");
   char* Instruction=strtok(MEMORRIC," ");
   char* arg1=strtok(NULL,",");
   char* arg2=strtok(NULL,",");
   printf("%s,%s,%s\n",Instruction,arg1,arg2);
   if(Instruction!=NULL){
     if(strstr(Instruction,"@")==Instruction){
        if(arg1!=NULL || arg2!=NULL){
        ERROR* e=(ERROR*)malloc(sizeof(ERROR));
        e->errorMessage=(char*)malloc(sizeof(char)*32);
        strcpy(e->errorMessage,"Label should not have a agument");
        e->lineNumber=line;
        enQueue(&errorList,e,true);
        errors++;
        printf("error thrown");
        continue;
       }
       
        Pointer m=*(Pointer*)malloc(sizeof(Pointer));
        m=MEMLOCATION;
        addNode(h,MEMORRIC,&m,true);
        continue;
   }
   MEMLOCATION++;
   }}
while(!QueueIsEmpty(&errorList)){
    ERROR* error=(ERROR*)deQueue(&errorList);
    if(error!=NULL){
        printf("[Error]Line %i %s",error->lineNumber,error->errorMessage);
        free(error->errorMessage);
        free(error);
    }

}


freeQueue(&labelsDefinedLater);
return errors;
}
TOKEN getToken(const char* arg){

  
}

CPU_INSTRUCTION* secondPass(Queue* tokens){
 
   



   



}


uint32_t hash(const char *key, size_t len)
{
    uint32_t hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        if(key[i]=='\0'){
           break;
        }
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

