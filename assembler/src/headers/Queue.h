#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>

typedef struct Q_NODE{
    struct Q_NODE* next;
    void* value;
    bool dynamic_ptr; 
    
}Q_NODE;

typedef struct Queue
{
    Q_NODE* head;
    Q_NODE* tail;
    int size;
} Queue;


void freeQueue(Queue* queue);
bool enQueue(Queue* queue,void* value,bool dynamiic_ptr);
void* deQueue(Queue* queue);
void* getValueAtIndex(Queue* Queue,int index);
Queue* initQueue();
bool QueueIsEmpty(Queue* Queue);

#endif
