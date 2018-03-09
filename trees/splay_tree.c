#include<stdio.h>
#include<stdlib.h>
#include"splay_tree.h"
#include"fifo.h"

#define true 1
#define false 0

static Node * root;

Node * create_node(Node * parent, double key){
  Node * node = (Node *)malloc(sizeof(Node));
  node -> left = NULL;
	node -> right = NULL;
	node -> parent = parent;
	node -> key = key;
  return node;
}

Node* init_q(double key){
  root = (Node*)malloc(sizeof(Node));
  root -> key = key;
  root -> queue = fifo_init();
  fifo_add(root -> queue, key);
  return root;
}

Node* get_root(){
  return root;
}

void printNode(Node * node){
  if(node->queue){
    printf("%dX%f, ", node->queue->size + 1, node -> key);
  }else{
    printf("1X%f, ", node -> key);
  }
}

void left_rotate( Node *x ) {
  Node *y = x->right;
  if(y) {
    x->right = y->left;
    if( y->left ) y->left->parent = x;
    y->parent = x->parent;
  }

  if( !x->parent ) root = y;
  else if( x == x->parent->left ) x->parent->left = y;
  else x->parent->right = y;
  if(y) y->left = x;
  x->parent = y;
}

void right_rotate( Node *x ) {
  Node *y = x->left;
  if(y) {
    x->left = y->right;
    if( y->right ) y->right->parent = x;
    y->parent = x->parent;
  }
  if( !x->parent ) root = y;
  else if( x == x->parent->left ) x->parent->left = y;
  else x->parent->right = y;
  if(y) y->right = x;
  x->parent = y;
}

void splay(Node *x ) {
  while( x->parent ) {
    if( !x->parent->parent ) {
      if( x->parent->left == x ) right_rotate( x->parent );
      else left_rotate( x->parent );
    } else if( x->parent->left == x && x->parent->parent->left == x->parent ) {
      right_rotate( x->parent->parent );
      right_rotate( x->parent );
    } else if( x->parent->right == x && x->parent->parent->right == x->parent ) {
      left_rotate( x->parent->parent );
      left_rotate( x->parent );
    } else if( x->parent->left == x && x->parent->parent->right == x->parent ) {
      right_rotate( x->parent );
      left_rotate( x->parent );
    } else {
      left_rotate( x->parent );
      right_rotate( x->parent );
    }
  }
}

Node* get( double key) {
    Node *z = root;
    while( z ) {
      if(z->key < key) z = z->right;
      else if(key < z->key) z = z->left;
      else return z;
    }
    return NULL;
  }

void replace(Node * node, Node * node1) {
  if(!node->parent) root = node1;
  else if(node == node->parent->left) node->parent->left = node1;
  else node->parent->right = node1;
  if(node1) node1->parent = node->parent;
}

Node* subtree_minimum(Node * node) {
  while(node->left ) node = node -> left;
  return node;
}

Node* subtree_maximum(Node * node) {
  while(node->right) node = node->right;
  return node;
}

void insert(double key ) {
    Node * current_node = root;
    Node * parent = NULL;
    while(current_node) {
      parent = current_node;
      if(current_node->key > key){
        current_node = current_node->left;
      }
      else if(current_node->key < key){
        current_node = current_node->right;
      }
      else{
        fifo_add(current_node->queue, key);
        splay(current_node);
        return;
      }
    }
    current_node = create_node(parent, key);
    current_node->queue = fifo_init();
    fifo_add(current_node->queue, key);

    if(!parent) root = current_node;
    else if(parent->key < current_node->key) parent->right = current_node;
    else parent->left = current_node;
    splay(current_node);
}

  void delete(double key) {
    Node * node = get(key);
    if(!node) return;

    splay(node);
    if(node->queue){
      FifoNode * fn = fifo_get(node -> queue);
      free(fn);
      if(node->queue->size > 0){
        return;
      }
    }
    if(!node->left) replace(node, node->right );
    else if(!node->right) replace(node, node->left );
    else {
      Node *y = subtree_minimum(node->right);
      if(y->parent != node) {
        replace(y, y->right );
        y->right = node->right;
        y->right->parent = y;
      }
      replace(node, y );
      y->left = node->left;
      y->left->parent = y;
    }
    free(node->queue);
    free(node);
  }

void traverse_tree(Node * node){
  if(!node){
    return;
  }
  printf("[");
  printNode(node);
  traverse_tree(node -> left);
  traverse_tree(node -> right);
  printf("]\n");
}
Node * get_highest_prio(){
  return get(get_lowest_key());
}
double get_lowest_key_from(Node * root){
  Node * current_node = root;
  while(current_node -> left){
    current_node = current_node -> left;
  }
  return current_node -> key;
}

double get_lowest_key(){
  return get_lowest_key_from(get_root());
}

void destroy_from(Node * node){
  if(node){
    destroy_from(node -> left);
    destroy_from(node -> right);
  }
  free(node);
}

void destroy(){
  destroy_from(root);
}
