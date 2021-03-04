#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "headers/hashMap.h"


HashMap* init(size_t capacity,uint32_t(*hash_func)(const char*,size_t len)){
    HashMap *map=malloc(sizeof(HashMap));
    if(map!=NULL){
      map->array=malloc(sizeof(Node)*capacity);
      if(map->array==NULL){
         free(map);
         printf("[ERROR]HASHMAP INIT FAILED");
         return NULL;
      }
      map->capacity=capacity;
      map->func_prt=hash_func;
      for(int i=0;i<capacity;i++){
       map->array[i]=NULL;
      }
      return map;
    }else{
        printf("[ERROR]HASHMAP INIT FAILED");
        return NULL;
    }


}
bool addNode(HashMap* HashMap,const char *key,void* value){ 
  bool returnB=false;
  uint32_t i=(HashMap->func_prt(key,60))%HashMap->capacity;
  if(HashMap->array[i]==NULL){
     Node* n=malloc(sizeof(Node));
     if(n==NULL){
       printf("HASH_MAP[ERROR]%s MALLOC FAILED",key);
       return false;
     }
     n->value=value;
     strcpy(n->key,key);
     HashMap->array[i]=n;
     returnB=true;
     printf("array[%i]%s placed with address %0x\n",i,key,(n->value));
  }else{
    printf("HASH_MAP[ERROR]%s already exist use changeValue() instead\n",key);
  }


  return returnB;
}

void freeMap(HashMap *hashmap){
    for(int i=0;i<hashmap->capacity;i++){
      free(hashmap->array[i]);
      hashmap->array[i]=NULL;
      
    }
    free(hashmap);
}

void getValue(HashMap* HashMap,const char* key,void** dest){
 uint32_t i=(HashMap->func_prt(key,60))%HashMap->capacity;
  if(HashMap->array[i]!=NULL){
     Node n=*(Node*)(HashMap->array[i]);
     *(dest)=n.value;
     
  }else{
    printf("HASHMAP[ERROR]%s does not exist in the map",key);
    *(dest)= NULL;
  }

}



