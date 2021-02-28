#include <stdio.h>
#include "headers/Instruction.h"
#include "headers/PointerhashTable.h"

int firstPass();
CPU_INSTRUCTION* secondPass();
void writeFIle();


int main(){
    initList();
   
    firstPass();
    secondPass();
   



    DeleteTable();
 
}


int firstPass(){
    Pointer p=(uint16_t)0x10080;
    Label label1={"pots",p};
    Label label2={"stop",p};
    Label label3={"label3",p};
    addLabelToList(label1);
    addLabelToList(label2);
    addLabelToList(label3);

}

CPU_INSTRUCTION* secondPass(){
   Pointer p;

   
}

