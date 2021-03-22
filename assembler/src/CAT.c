#include "headers/CAT.h"
#include <string.h>


void CAT(char* destination,char** strings,int amountOfStrings){
 
   strcpy(destination,"");
   for(int i=0;i<amountOfStrings;i++){
       char* string=strings[i];
       strcat(destination,string);
       }



}