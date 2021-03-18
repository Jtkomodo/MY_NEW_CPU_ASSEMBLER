
#include <stdint.h>



#ifndef _Instruction_H
#define _Instruction_H
//OPCODE
//N:real value;P:pointer;R:register
#define NOP           0x00
#define MOV_R_P       0x40
#define MOV_R_N       0x50
#define ADD16_REGA    0x16
#define ALU8          0X18
#define jump_P        0x20


//conditions for jump this will be placed in extended op section
#define IF_EQUAL     0
#define IF_GREATOR   1
#define IF_LESS      2

typedef enum TOKEN_TYPE{
       null,
       POINTER,
       REGISTER,
       LABEL,
       number
} TOKEN_TYPE;

typedef struct TOKEN{
  TOKEN_TYPE type;
  char* string

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



Instruction getInstructionFromTokens(TOKEN memoric,TOKEN arg,TOKEN arg2);

#endif







