#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/Token.h"
#include "headers/hashMap.h"
#include "headers/Queue.h"
#include "headers/Error.h"
#include "headers/Syntax.h"
#include "headers/CAT.h"
#include "headers/CPU.h"

#define ERROR_TO_MANY_ARGS 0x4
#define ERROR_TO_FEW_ARGS 0x6
#define ERROR_FILE_NOT_FOUND 0x404
char* DEFAULTbinfileName="D:\\VsProject\\MY_NEW_CPU_ASSEMBLER\\assembler\\program.bin";
typedef struct Label_entry{
    char* string;
    int lineNumber;
} Label_entry;




void inits();
void frees();
int firstPass(Queue* instructions,HashMap* h,FILE *file);
int secondPass(Queue* instruction,HashMap* labels,Queue* cpu_instructions);
void writeBinFIle(Queue* cpu_instructions,char* binfileLocation);
int CheckIfProgramShouldRun(int argc,char *atgv[]);

int main(int argc, char *argv[]){
   int ERROR_CODE=CheckIfProgramShouldRun(argc,argv);
   if(ERROR_CODE!=0){
        return ERROR_CODE;
    }
    
 HashMap labels=*init(100,hash);
 Queue instuctions=*initQueue();
 Queue cpu_instuctions=*initQueue();
 inits();
 
 char* asmfile=argv[1];
 char * binfile;
 if(argc>2){
    binfile=argv[2];  
 }else{
    binfile=DEFAULTbinfileName;
 }
  FILE * ASM_FILE;
    ASM_FILE= fopen(asmfile,"r");
   if(ASM_FILE==NULL){
     printf("[ERROR] FILE NOT FOUD");
      exit(EXIT_FAILURE);
   }
  int errors; 
  errors=firstPass(&instuctions,&labels,ASM_FILE);
  if(errors==0){
  errors=secondPass(&instuctions,&labels,&cpu_instuctions);
  }
  if(errors==0){
    writeBinFIle(&cpu_instuctions,binfile);
  }
  fclose(ASM_FILE);


  frees();
  freeQueue(&instuctions);
  freeQueue(&cpu_instuctions);
  freeMap(&labels);
  exit(0);
}

int CheckIfProgramShouldRun(int argc,char *atgv[]){
      if(argc>3){
        return ERROR_TO_MANY_ARGS;
      }else if(argc<2){
        return ERROR_TO_FEW_ARGS;
      }
    
    return 0;
}
void frees(){
  freeSyntax();
  freeTokens();  
}

void inits(){
    InitTokens();
    initSyntax();

}


int firstPass(Queue* instructions,HashMap* h,FILE *file){
  
//this is where we will get all the tokens and replace labels with the correct memory location
   int errors=0;
  Queue labelsDefinedLater=*initQueue();
  Queue errorList=*initQueue();
  Queue* p=&errorList;
  int line=0;
  Pointer MEMLOCATION=0x00;
  char command[60];

   while(fgets(command, 60, file)!=NULL){ 
   line++;
   char *memoric=strtok(command,";");
   memoric=strtok(memoric,"\n");
   char* Ins=strtok(memoric," ");
   char* arg1=strtok(NULL,",");
   char* arg2=strtok(NULL," ,");
   char* arg3=strtok(NULL," ,");
  if(Ins!=NULL){
     if(arg3!=NULL){
       ERROR* e=(ERROR*)malloc(sizeof(ERROR));
        e->errorMessage=(char*)malloc(sizeof(char)*36);
        strcpy(e->errorMessage,"To many arguments ony 2 are allowed");
        e->lineNumber=line;
        enQueue(&errorList,e,true);
        continue;
     }
     printf("%i--%s,%s,%s;\n",line,Ins,arg1,arg2);





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
       
        Pointer* m=(Pointer*)malloc(sizeof(Pointer));
        *m=MEMLOCATION;
        if(!hasKey(h,memoric)){
          addNode(h,memoric,m,true);
          printf("Label %s defined with memmory location 0x%X\n",memoric,*m);

        }else{
          
          char* Label="Label \"";
          char* already="\" already defined at memory location 0x";
          int* value;
          getValue(h,memoric,(void**)&value);
          size_t size=sizeof(char)*sizeof(Pointer)+1;
          char* lineNumber=(char*)malloc(size);
          itoa(*(Pointer*)value,lineNumber,16);
          size_t i=strlen(Label)+strlen(memoric)+strlen(already)+strlen(lineNumber)+1;
           ERROR* e=(ERROR*)malloc(sizeof(ERROR));
          e->errorMessage=(char*)malloc(i);
          char* strings[4]={
            Label,
            memoric,
            already,
            lineNumber
          };

         
         CAT(e->errorMessage,strings,4);
          e->lineNumber=line;
          enQueue(&errorList,e,true);
          free(lineNumber);
        }
        continue;
   }else{
      ERROR* e=malloc(sizeof(ERROR));
      ERROR* e2=malloc(sizeof(ERROR));
      TOKEN* a=parseToToken(arg1,e);
       if(e->errorMessage!=NULL){
            e->lineNumber=line;
            enQueue(&errorList,e,true);
            continue;
       }else{
           free(e);
        }
     

      TOKEN* b=parseToToken(arg2,e2);
       if(e2->errorMessage!=NULL){
            e2->lineNumber=line;
            enQueue(&errorList,e2,true);
            continue;
       }else{
        free(e2);
       }

      ERROR* e3=malloc(sizeof(ERROR));
       SYNTAX* s=checkSyntax(Ins,a->type,b->type,e3);
       if(s!=NULL){
          free(e3);
          Instruction* i=(Instruction*)malloc(sizeof(Instruction));
           TOKEN* t=(TOKEN*)malloc(sizeof(TOKEN));
           t->string=malloc(strlen(Ins)+1);
           strcpy(t->string,Ins);
           t->type=MEMORIC;
          
            i->operation=t;
            i->arg1=a;
            i->arg2=b;
            i->syntax=s;
            Pointer p=s->size;
            MEMLOCATION+=p;
           
        if(a->type==LABEL){
          if(!hasKey(h,a->string)){
           Label_entry l=*(Label_entry*)malloc(sizeof(Label_entry));
           l.string=malloc(sizeof(a->string));
           strcpy(l.string,a->string);
           l.lineNumber=line; 
           enQueue(&labelsDefinedLater,&l,true);
           continue;
          }
        }
        if(b->type==LABEL){
           if(!hasKey(h,b->string)){
            Label_entry l=*(Label_entry*)malloc(sizeof(Label_entry));
            l.string=malloc(sizeof(b->string));
            strcpy(l.string,b->string);
            l.lineNumber=line; 
            enQueue(&labelsDefinedLater,&l,true);
            continue;
          }
        }



           enQueue(instructions,i,true);
        
       }else{
        e3->lineNumber=line;
        enQueue(&errorList,e3,true);
        continue;
       }

       

   }
   




  



  
   }}



//check to see if any label was not defined

//check errors
while(!QueueIsEmpty(&labelsDefinedLater)){
    Label_entry* label=deQueue(&labelsDefinedLater);
    if(!hasKey(h,label->string)){
       ERROR* e=(ERROR*)malloc(sizeof(ERROR));
       char* l="Label ";
       char* not_defined=" not defined";
       size_t i=strlen(l)+strlen(label->string)+strlen(not_defined)+1;
       e->errorMessage=(char*)malloc(i);
       char* strings[3]={
          l,
          label->string,
          not_defined,
       };


       CAT(e->errorMessage,strings,3);

        
       e->lineNumber=label->lineNumber;
       enQueue(&errorList,e,true);
     
    }
  // free(label->string);
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
printf("ERRORS %i\n",errors);

freeQueue(&labelsDefinedLater);
freeQueue(p);
return errors;
}



int secondPass(Queue* instructions,HashMap* labels,Queue* cpu_instructions){
   int errors=0;
   while(!QueueIsEmpty(instructions)){
      Instruction* i=(Instruction*)deQueue(instructions);
      
      TOKEN* Memoric=i->operation;
      TOKEN* ARG1=i->arg1;
      TOKEN* ARG2=i->arg2;
      SYNTAX* s=i->syntax;



      char* arg1=TOKEN_TYPE_STRINGS[s->arg1];
      char * arg2=TOKEN_TYPE_STRINGS[s->arg2];
      printf("(%s)0x%02X %s(%s),%s(%s)\n",i->operation->string,s->opcode,arg1,i->arg1->string,arg2,i->arg2->string);
      CPU_INSTRUCTION* cpu_instruction=(CPU_INSTRUCTION*)malloc(sizeof(CPU_INSTRUCTION)); 
      cpu_instruction->arrgument.arg=0x0000;
      cpu_instruction->OPCODE=s->opcode;

     
      if(s->option==CONDITION){
        if(strcmp(Memoric->string,"je")==0){
           cpu_instruction->extended_OP=IF_EQUAL;
        }else
        if(strcmp(Memoric->string,"jg")==0){
           cpu_instruction->extended_OP=IF_GREATOR;
        }else
         if(strcmp(Memoric->string,"jl")==0){
           cpu_instruction->extended_OP=IF_LESS;
        }
      }else{
         cpu_instruction->extended_OP=0x00;
      } 
      printf("aType=%d bType=%d\n",s->arg1,s->arg2);
      if(s->arg1==NUMBER){
         char* numberToParse=i->arg1->string;
         if(numberToParse!=NULL){
            if(strstr(numberToParse,"0x")==numberToParse){
             int a=strtol(numberToParse,NULL,16);
             cpu_instruction->arrgument.a=a;
            }else{
                int a=atoi(numberToParse);
                cpu_instruction->arrgument.a=a;
            }
             
         }


      }
      if(s->arg2==NUMBER){
         char* numberToParse=i->arg2->string;
         if(numberToParse!=NULL){
          if(strstr(numberToParse,"0x")==numberToParse){
             int b=strtol(numberToParse,NULL,16);
             cpu_instruction->arrgument.b=b;
            }else{
                int b=atoi(numberToParse);
                cpu_instruction->arrgument.b=b;
            }
       }
    

      }
        if(s->arg1==LABEL){
         char* labeltogetMemLocation=i->arg1->string;
         Pointer* m;
         getValue(labels,labeltogetMemLocation,(void**)&m);
         printf("LABEL %s changed to memory location 0x%X",labeltogetMemLocation,*m);
         cpu_instruction->arrgument.arg=*m;
      }
      
      




    
      enQueue(cpu_instructions,cpu_instruction,true);
   
      
      free(i->arg1->string);
      free(i->arg1);
      free(i->arg2->string);
      free(i->arg2);
      free(i->operation->string);
      free(i->operation);
      free(i->syntax);
      free(i);
   
     
   }

return errors;

   



}
void writeBinFIle(Queue* cpu_instructions,char* binfileLocation){
   FILE* BIN_FILE;
      BIN_FILE= fopen(binfileLocation,"w");
   if(BIN_FILE==NULL){
     printf("[ERROR] FILE NOT WRITTEN");
   }else{
   
   while(!QueueIsEmpty(cpu_instructions)){
      CPU_INSTRUCTION* instruction=(CPU_INSTRUCTION*)deQueue(cpu_instructions);
      uint8_t byte1=instruction->OPCODE;
      uint8_t byte2=instruction->extended_OP;
      uint8_t byte3=instruction->arrgument.a;
      uint8_t byte4=instruction->arrgument.b;
      
      
      free(instruction);
      fprintf(BIN_FILE," %02x%02x%02x%02x",byte1,byte2,byte3,byte4);
   }
}
   fclose(BIN_FILE);
}
