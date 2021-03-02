#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/Instruction.h"
#include "headers/PointerhashTable.h"

#define ERROR_TO_MANY_ARGS 0x4
#define ERROR_TO_FEW_ARGS 0x6
#define ERROR_FILE_NOT_FOUND 0x404


int firstPass(FILE *File);
CPU_INSTRUCTION* secondPass(FILE *File);
void writeFIle();
int CheckIfProgramShouldRun(int argc,char *atgv[]);
void SyntaxCheck(const char* instruction,const char *arg1,const char arg2);
TOKEN getToken(const char* arg);

int main(int argc, char *argv[]){
    
    int ERROR_CODE=CheckIfProgramShouldRun(argc,argv);
    if(ERROR_CODE!=0){
        return ERROR_CODE;
    }
    char* file=argv[1];


    initList();

   FILE *filePointer;
   filePointer= fopen(file,"r");
   if(filePointer==NULL){
     printf("[ERROR] FILE NOT FOUD");
      exit(EXIT_FAILURE);
   }
  firstPass(filePointer);
  rewind(filePointer);
  secondPass(filePointer);
  fclose(filePointer);
  Pointer p;
  if(getPointer("@start",&p)){
     printf("%0x",p);
  }

  DeleteTable();
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




int firstPass(FILE *file){
  
   Pointer MEMLOCATION=0x90;
 char command[60];

   while(fgets(command, 60, file)!=NULL)
{
   char *MEMORRIC=strtok(command,";");
   MEMORRIC=strtok(MEMORRIC,"\n");
if(MEMORRIC!=NULL){
   //printf("%s\n",MEMORRIC);   

  //if label
  if(strstr(MEMORRIC,"@")==MEMORRIC){
       Label l;
       strcpy(l.key,MEMORRIC);
       l.value=MEMLOCATION;
       addLabelToList(l);
       continue;
   }
  // "command,arg1,arg2"  "command"


   char* Instruction=strtok(MEMORRIC," ");
   char* arg1=strtok(NULL,",");
   char* arg2=strtok(NULL,",");
   printf("%s,%s,%s\n",Instruction,arg1,arg2);
   
}


   }
   

}
void SyntaxCheck(const char* instruction,const char *arg1,const char arg2){
     
     
    
  
}

TOKEN getToken(const char* arg){

  
}

CPU_INSTRUCTION* secondPass(FILE *file){
 Pointer MEMLOCATION=0;
 char command[60];
  
  while(fgets(command, 60, file)!=NULL){
   char *MEMORRIC=strtok(command,";");
   MEMORRIC=strtok(MEMORRIC,"\n");

   
   



   }



}


