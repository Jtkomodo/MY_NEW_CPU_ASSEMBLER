#include <stdio.h>
#include <stdint.h>



#ifndef _Instruction_H
#define _Instruction_H

#define NOP     0x00
#define LOADRAM 0x010
#define LOADREG 0x020
#define ADD16   0x11
#define ADD8    0X08

typedef uint16_t Pointer;
typedef union CPU_ARG{
      union{
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







