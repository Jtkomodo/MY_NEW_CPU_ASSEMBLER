#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/Instruction.h"
#include "headers/hashMap.h"


#define ERROR_TO_MANY_ARGS 0x4
#define ERROR_TO_FEW_ARGS 0x6
#define ERROR_FILE_NOT_FOUND 0x404

uint32_t hash(const char *key, size_t len);
void t(HashMap* h);
int firstPass(HashMap* map,FILE *File);
CPU_INSTRUCTION* secondPass(FILE *File);
void writeFIle();
int CheckIfProgramShouldRun(int argc,char *atgv[]);
void SyntaxCheck(const char* instruction,const char *arg1,const char arg2);
TOKEN getToken(const char* arg);

int main(int argc, char *argv[]){
    
 

 HashMap h=*(init(100,hash));

t(&h);

float *po2;
getValue(&h,"s",(void**)&po2);
if(po2!=NULL){
printf("%f\n",*po2);
}

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

void t(HashMap* h){
   float *p=malloc(sizeof(float));
   *p=15.1f;
  addNode(h,"s",(void*)p,true);
}


int firstPass(HashMap* h,FILE *file){




}
void SyntaxCheck(const char* instruction,const char *arg1,const char arg2){
     
     
    
  
}

TOKEN getToken(const char* arg){

  
}

CPU_INSTRUCTION* secondPass(FILE *file){
 
   



   



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

