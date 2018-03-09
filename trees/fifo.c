#include<stdlib.h>
#include<stdio.h>
#include"fifo.h"

void print_queue(Queue * queue){
  printf("size : %d\n", queue->size);
  if(queue->size > 0){;
    printf("first : %f\n", queue->first->key);
    printf("last : %f\n", queue->last->key);
  }
}

FifoNode * fifo_get(Queue * queue){
  FifoNode * node = queue->first;
  if(queue->first == queue->last){
    queue->last = queue->first->next;
  }
  queue->first = queue->first->next;
  queue->size --;
  return node;
}

void fifo_add(Queue * queue, double key){
  FifoNode * node = (FifoNode *)malloc(sizeof(FifoNode));
  node->key = key;
  if(queue->size == 0){
    queue->first = node;
  }else{
    queue->last->next = node;
  }
  queue->last = node;
  queue->size ++;
}

Queue * fifo_init(){
  Queue * queue = (Queue *)malloc(sizeof(Queue));
  queue->size = 0;
  return queue;
}
