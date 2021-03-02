#include <stdint.h>



#ifndef _Instruction_H
#define _Instruction_H

#define NOP     0x00
#define MOVRAM 0x010
#define MOVREG 0x020
#define ADD16   0x11
#define ADD8    0X08



typedef enum TOKEN_TYPE{
       null,
       MEM_LOCATION,
       REGISTER,
       LABEL,
       HEX_VALUE,
       REAL_VALUE
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
      uint8_t reg;
      CPU_ARG arrgument;
} CPU_INSTRUCTION;
#endif







