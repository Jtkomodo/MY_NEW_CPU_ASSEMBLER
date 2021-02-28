#include "headers/PointerhashTable.h"
#include <stdlib.h>
#include <string.h>
static uint32_t hash(const char *key, size_t len);

Label* table[MAX_SIZE];

void initList(){

   for(int i=0;i<MAX_SIZE;i++){
       table[i]=NULL;
   }

}
void printTable(){
   for(int i=0;i<MAX_SIZE;i++){
      
       if(table[i]!=NULL){
           Label *l=table[i];
           printf("[%i]--------%s,%0x\n",i,l->key,l->value);
       }
   }

}

bool addLabelToList(Label label){
     uint32_t i=hash(label.key,60)%MAX_SIZE;
     if(table[i]==NULL)
     {
         Label *l=malloc(sizeof(label));
         strcpy(l->key,label.key);
         l->value=label.value;
         table[i]=l;
       printf("[%i]--------%s,%0x\n",i,l->key,l->value);
         return true;
     }   

      printf("[ERROR]]%s NOT added to list\n",label.key);
     return false;
}

void DeleteTable(){
 for(int i=0;i<MAX_SIZE;i++){
    if(table[i]!=NULL){
        free(table[i]);
        table[i]=NULL;
    }
}
}

bool getPointer(char* key,Pointer* dest){

    uint32_t i=hash(key,60)%MAX_SIZE;
     if(table[i]!=NULL){
        dest=&(table[i]->value);
        return true;
     }
    printf("[ERROR]]%s NOT in list\n",key);
    return false;
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

