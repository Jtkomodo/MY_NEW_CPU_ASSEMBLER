#include "headers\test.h"




void test(HashMap* map){
   float *p;
   getValue(map,"s",(void**)&p);
    float f=0;
   if(p!=NULL){
      f=*p;
   }
   printf("V=%f",f);
}