

#ifndef _Instruction_H
#define _Instruction_H
#include <stdint.h>
#include "Queue.h"
#include "Error.h"
#define LABEL_MARKER "@"
#define MEMORY_MARKER "["
#define MEMORY_MARKER_END "]"
#define REGISTER_MARKER "&"
#define HEX_MARKER "0x"
#define BIN_MARKER "b"



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

typedef struct Instruction{
  TOKEN operation;
  TOKEN arg1;
  TOKEN arg2;


} Instruction;


typedef enum REGISTERS{
     r0,
     r1,
     r2,
     r3,
     A,
     B,
     EAX,
     XY,
     SP,
     BP
} REGISTERS;



typedef uint16_t Pointer;


typedef union CPU_ARG{
      struct{
          uint8_t a;
          uint8_t b;

      };
      uint16_t arg;

} CPU_ARG;

typedef struct CPU_INSTRUCTION
{
      uint8_t OPCODE;
      uint8_t extended_OP;
      CPU_ARG arrgument;
} CPU_INSTRUCTION;

TOKEN parseToToken(char* string,ERROR* error);

Instruction getInstructionFromTokens(TOKEN memoric,TOKEN arg,TOKEN arg2);

#endif







