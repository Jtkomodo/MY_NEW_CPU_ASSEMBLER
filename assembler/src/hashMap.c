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

void makeNode(Node* dest,const char* key,void* value,bool dynamic,int hash){
     dest->value=value;
     dest->dynamic_ptr=dynamic;
     dest->hash=hash;
     dest->Collisions=NULL;
     strcpy(dest->key,key);
 
}
bool addNode(HashMap* HashMap,const char *key,void* value,bool dynamic){ 
  bool returnB=false;
  uint32_t hash=(HashMap->func_prt(key,60));
  uint32_t i=hash%HashMap->capacity;
  if(HashMap->array[i]==NULL){
     Node* n=malloc(sizeof(Node));
     if(n==NULL){
       printf("HASH_MAP[ERROR]%s MALLOC FAILED",key);
       return false;
     }
     makeNode(n,key,value,dynamic,hash);
     HashMap->array[i]=n;
     returnB=true;
  
  }else{
    if(HashMap->array[i]->Collisions==NULL){
       Queue* Queue=initQueue();
       HashMap->array[i]->Collisions=Queue;
    }
    
      Node* n=malloc(sizeof(Node));
     if(n==NULL){
       printf("HASH_MAP[ERROR]%s MALLOC FAILED",key);
       return false;
     }
      makeNode(n,key,value,dynamic,hash);
      enQueue(HashMap->array[i]->Collisions,n,true);
      returnB=true;
  }


  return returnB;
}

void freeMap(HashMap *hashmap){
    for(int i=0;i<hashmap->capacity;i++){
       if(hashmap->array[i]!=NULL){
        Node n=*(Node*)(hashmap->array[i]);
       if(n.Collisions!=NULL){
         freeQueue(n.Collisions);
       }
       
        if(n.dynamic_ptr){
           free(n.value);
        }
       }
         free(hashmap->array[i]);
       
     
      
    }
    //free(hashmap->array);
    free(hashmap);
}

bool addNodes(HashMap* HashMap,Entry array[],int sizeOfArrray){
    for(int i=0;i<sizeOfArrray;i++){
       Entry n=array[i];
        if(!addNode(HashMap,n.key,n.value,n.dynamic_ptr)){
          return false;
        }
         

    }
   return true;

}
bool hasKey(HashMap* HashMap,const char *key){
 uint32_t hash=(HashMap->func_prt(key,60));
 uint32_t i=hash%HashMap->capacity;
 if(HashMap->array[i]!=NULL){
   uint32_t  oldhash=HashMap->array[i]->hash;
    if(hash==oldhash){
      return true;
    }else if(HashMap->array[i]->Collisions!=NULL){
      bool r=false;
       Queue* q=HashMap->array[i]->Collisions;  
       for (int index = 0; index <q->size; index++)
       {
         Node n=*(Node*)getValueAtIndex(HashMap->array[i]->Collisions,index);
        
         if(n.hash==hash){
             r=true;
            break;

         }
          
       }
       return r;
    }
 } else{
   return false;
 }    
}


void getValue(HashMap* HashMap,const char* key,void** dest){
 uint32_t hash=(HashMap->func_prt(key,60));
 uint32_t i=hash%HashMap->capacity;
 *dest=NULL;
  if(HashMap->array[i]!=NULL){
    if(HashMap->array[i]->hash==hash){
      Node n=*(Node*)(HashMap->array[i]);
      *(dest)=n.value;
    }else if(HashMap->array[i]->Collisions!=NULL){
       

       Queue* q=HashMap->array[i]->Collisions;  
       for (int index = 0; index <q->size; index++)
       {
         Node n=*(Node*)getValueAtIndex(HashMap->array[i]->Collisions,index);
        
         if(n.hash==hash){
           *(dest)=n.value;
            break;
         }
       }
       
    }
  }
 

}



uint32_t hash(const char *key, size_t len)
{
    uint32_t hash, i;
    if(strcmp(key,"r1")==0 || strcmp(key,"r2")==0){
       printf("hash");
    };
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




