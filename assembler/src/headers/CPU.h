#ifndef CPU_H
#define CPU_H
#include <stdint.h>
//conditions for jump this will be placed in extended op section


//2 control bits 6 flags
//11 on     flags    zero,sign  parity,hoverflow,carry,overflow
//10 0ff    flags    zero,sign  parity,hoverflow,carry,overflo


//examples:
//check if zero flag is on option=1110 0000 first 2 bits say we are checking if the flag is on rest tell which flags to check
//check if zero flag is off option=1010 0000
//check if carry and overflow is off=1000 

#define IF_EQUAL      0x70//11 10 0000 zf=on
#define IF_ NOT_EQUAL 0xa0//10 10 0000 zf=off
#define IF_GREATOR    0xb0//10 11 0000 zf=off sign=off
#define IF_LESS       0xd0//11 01 0000  sign=on 
//OPCODES
#define OP_MOV_R_N 0x03
#define OP_MOV_R_R 0x04
#define OP_MOVE_P_R 0x05
#define OP_MOVE_P_N 0x06
#define OP_ADD 0x72
#define OP_POP 0x90
#define OP_JMP 0x80


#define NUMBER_OF_REGISTERS 9

typedef enum REG_ID{
     r0,
     r1,
     r2,
     r3,
     A,
     B,
     EAX,
     SP,
     BP
} REG_ID;





typedef uint16_t Pointer;


typedef union CPU_ARG{
      struct{
          uint8_t b;
          uint8_t a;

      };
      uint16_t arg;

} CPU_ARG;

typedef struct CPU_INSTRUCTION
{
      uint8_t OPCODE;
      uint8_t extended_OP;
      CPU_ARG arrgument;
} CPU_INSTRUCTION;

#endif