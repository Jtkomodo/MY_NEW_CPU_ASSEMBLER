#ifndef _TOKEN_H
#define _TOKEN_H
#include "Queue.h"
#include "Error.h"


#define LABEL_MARKER "@"
#define MEMORY_MARKER "["
#define MEMORY_MARKER_END "]"
#define REGISTER_MARKER "&"
#define HEX_MARKER "0x"
#define BIN_MARKER "b"


extern char* TOKEN_TYPE_STRINGS[6];
typedef enum TOKEN_TYPE{
       NO,
       POINTER,
       REGISTER,
       LABEL,
       NUMBER,
       MEMORIC
} TOKEN_TYPE;

typedef struct TOKEN{
  TOKEN_TYPE type;
  char* string;

} TOKEN;


void InitTokens();
void freeTokens();
TOKEN* parseToToken(char* string,ERROR* error);

#endif







