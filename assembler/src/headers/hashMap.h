#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef HASH_TABLE
#define HASH_TABLE
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
#endif

HashMap* init(size_t capacity,uint32_t(*hash_func)(const char*,size_t len));
bool addNode(HashMap* HashMap,const char *key,void* value,bool dynamic);
void getValue(HashMap* HashMap,const char* key,void** dest);
void freeMap(HashMap *hashmap);