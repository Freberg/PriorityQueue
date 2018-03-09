#include<stdio.h>
#include<stdlib.h>
#include"linked_list.h"


static List * list;

Node* init_q(double key){
    list = (List *)malloc(sizeof(List));
    list -> size = 1;
    Node * node = (Node *) malloc(sizeof(Node));
    node -> key = key;
    list -> last = node;
    list -> first = node;
    return node;
}

void insert(double key){
  Node * node = (Node *) malloc(sizeof(Node));
  node -> key = key;
  if(list-> size = 0){
    list -> first = node;
    list -> last = node;
    list -> size = 1;
  }else if(key < ((list -> first -> key + list -> last -> key) / 2)){
    Node * current_node = list -> first;
    while(current_node && current_node -> key < key){
      current_node = current_node -> next;
    }
    Node * next = current_node -> next;
    current_node -> next = node;
    if(next) next -> previous = node;
    node -> next = next;
    node -> previous = current_node;
  }else{
    Node * current_node = list -> last;
    while(current_node && current_node -> key >= key){
      current_node = current_node -> previous;
    }
    Node * previous = current_node -> previous;
    current_node -> previous = node;
    if(previous) previous -> next = node;
    node -> next = current_node;
    node -> previous = previous;
  }
  if(list -> last -> next){
    list -> last = list -> last-> next;
  }
  if(list -> first -> previous){
    list -> first = list -> first -> previous;
  }
}

Node * get(double key){
  Node * current_node = list -> first;
  while(current_node && key != current_node -> key){
    current_node = current_node -> next;
  }
  if(current_node -> key == key){
    return current_node;
  }else{
    return NULL;
  }
}

Node * get_highest_prio(){
  return list->first;
}

void delete(double key){
  Node * current_node = list -> first;
  while(current_node && key != current_node -> key){
    current_node = current_node -> next;
  }
  if(current_node -> key == key){
    Node * next = current_node -> next;
    Node * previous = current_node -> previous;
    if(next) next -> previous = previous;
    if(previous) previous -> next = next;
    free(current_node);
  }else{
    return;
  }
}

void destroy(){
  Node * current_node = list -> first;
  while(current_node){
    current_node = current_node -> next;
    free(current_node->previous);
  }
  free(current_node);
  free(list);
}
