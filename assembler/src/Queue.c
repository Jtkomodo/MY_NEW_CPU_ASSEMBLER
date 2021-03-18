#include "headers/Queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void freeQUEUE_NODE(int i,Q_NODE* node);
void freeQueue(Queue* queue){
      printf("[QUEUE]Queue free started\n");
      if((queue->head!=NULL) &&(queue->tail!=NULL) ){
           
           freeQUEUE_NODE(1,queue->head);
      }else{
        printf(" [QUEUE]EMPTY\n");
      }
    
      free(queue);
       printf("[QUEUE]Queue freed\n");   
}
void freeQUEUE_NODE(int i,Q_NODE* node){
    
    if(node->next!=NULL){ 
        
        freeQUEUE_NODE(i+1,node->next);
    }
    if(node->dynamic_ptr && node->value!=NULL){
      free(node->value);
     printf(" [QUEUE]node[%i]value freed\n",i);    
    }
    free(node);
     printf(" [QUEUE]node[%i] freed\n",i);  

}
//q=[v2]<-[v1]
//    t     h
//bool added=enqueque(v3);
//q=[v3]<-[v2]<-[v1]
//   t     ot      h
bool enQueue(Queue* queue,void* value,bool dynamic_ptr){
  bool succsess=false;
  Q_NODE* node=(Q_NODE*)malloc(sizeof(Q_NODE));
  if(node!=NULL){
    node->value=value;
    node->dynamic_ptr=dynamic_ptr;
    if(queue->tail==NULL){//if empty just make both the tail and head point to the new value
      node->next=NULL;
      queue->head=node;
      queue->tail=node;
      succsess=true;
    }else{//if not empty make the node the new tail and point the old tail to the new tail
      Q_NODE* oldTail=queue->tail;
      oldTail->next=node;
      node->next=NULL;
      queue->tail=node;
      succsess=true;
    }
  }
  return succsess;
}

//q=[v3]<-[v2]<-[v1]
//   t            h
//void* value=dequeque();
//q=[v3]<-[v2]     value=[v1]
//   t     h              oh  
void* deQueue(Queue* queue){
   void* value=NULL;
    if(queue->head==NULL || queue->tail==NULL){//if queue is empty
    
       printf("[QUEUE]queue is empty\n");
    }else{//if queue is not empty make the node the head points to be the new head
       Q_NODE* oldhead=queue->head;//head
       value=oldhead->value;
       if(oldhead->next!=NULL){//if the head was not the only value in the queue
           queue->head=oldhead->next;
     }else{//else make the queue's tail and head point to null
           queue->head=NULL;
           queue->tail=NULL;
       }
      free(oldhead);
    //  printf("[QUEUE]value removed and node freed\n");
    }
   return value;

}



bool QueueIsEmpty(Queue* queue){
    return (queue->head==NULL)||(queue->tail==NULL);
}

Queue* initQueue(){
        Queue* q= (Queue*)malloc(sizeof(Queue));
        if(q!=NULL){
            q->head=NULL;
            q->tail=NULL;
        }

}