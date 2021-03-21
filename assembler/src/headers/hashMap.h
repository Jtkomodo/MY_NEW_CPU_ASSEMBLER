

#ifndef HASH_TABLE
#define HASH_TABLE
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Node{
    char key[16];
    bool dynamic_ptr;
    void* value;
} Node;



typedef struct HashMap{
  Node** array;
  uint32_t (*func_prt)(const char*,size_t len);
  uint32_t capacity;
} HashMap;


HashMap* init(size_t capacity,uint32_t(*hash_func)(const char*,size_t len));
HashMap* init_with_values(size_t capacity,uint32_t(*hash_func)(const char*,size_t len));
bool addNode(HashMap* HashMap,const char *key,void* value,bool dynamic);
bool addNodes(HashMap* HashMap,Node array[],int sizeOfarray);
bool hasKey(HashMap* HashMap,const char *key);
void getValue(HashMap* HashMap,const char* key,void** dest);
void freeMap(HashMap *hashmap);

uint32_t hash(const char *key, size_t len);
#endif