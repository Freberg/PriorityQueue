#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/resource.h>

#ifdef LIST
  #include "lists/linked_list.h"
#else
  #include "trees/splay_tree.h"
#endif

#ifdef INITIAL_TREE_SIZE
  static int const tree_size = INITIAL_TREE_SIZE;
#else
  static int const tree_size = 10;
#endif

#ifdef MAX_PRIORITIY
  static int const max_priority = MAX_PRIORITIY;
#else
  static int const max_priority = 50;
#endif

#ifdef SIM_SIZE
  static int const sim_size = SIM_SIZE;
#else
  static int const sim_size = 1000;
#endif

#ifdef N
  static int const num_new_nodes = N;
#else
  static int const num_new_nodes = 1;
#endif

static int const primeSeeds[100] = {10007, 10009, 10037, 10039, 10061, 10067, 10069, 10079, 10091, 10093,
                      10099, 10103, 10111, 10133, 10139, 10141, 10151, 10159, 10163, 10169,
                      10177, 10181, 10193, 10211, 10223, 10243, 10247, 10253, 10259, 10267,
                      10271, 10273, 10289, 10301, 10303, 10313, 10321, 10331, 10333, 10337,
                      10343, 10357, 10369, 10391, 10399, 10427, 10429, 10433, 10453, 10457,
                      10459, 10463, 10477, 10487, 10499, 10501, 10513, 10529, 10531, 10559,
                      10567, 10589, 10597, 10601, 10607, 10613, 10627, 10631, 10639, 10651,
                      10657, 10663, 10667, 10687, 10691, 10709, 10711, 10723, 10729, 10733,
                      10739, 10753, 10771, 10781, 10789, 10799, 10831, 10837, 10847, 10853,
                      10859, 10861, 10867, 10883, 10889, 10891, 10903, 10909, 10937, 10939};

static int const numSeeds = 100;

static int const distSize = 10000;

static int normDist[10000] = {0};

typedef int bool;
#define true 1
#define false 0

void init_normDist(){
  int i;
  for(i = 0; i < distSize; i++){
    normDist[i] = (rand() % (max_priority/2) + 1) + (rand() % (max_priority/2) + 1);
  }
}
/*
best case for both splay tree and list is where the same key is added
all the time; Both are then fifo queues.
*/
void best_sim(bool isProc){
  int i, j;
  Node *root = init_q(1);
  for(i = 0; i < tree_size; i++){
    insert(1);
  }
  for(i = 0; i < sim_size; i++){
    Node* node = get_highest_prio();
    delete(node -> key);
    if(isProc){
      insert(1);
    }else{
      for(j = 0; j < num_new_nodes; j++){
        insert(node -> key);
      }
    }
  }
}
void worst_sim(bool isProc){
  int i, j;
  int c = 2;
  Node *root = init_q(1);
  for(i = 0; i < tree_size; i++){
    #ifdef LIST
       if(i > 0){
         insert(2);
       }else{
         insert(max_priority);
       }
    #else
       insert(c % max_priority + 1);
    #endif
    c++;
  }
  for(i = 0; i < sim_size; i++){
    Node* node = get_highest_prio();
    delete(node -> key);
    if(isProc){
      insert(c % max_priority + 1);
      c++;
    }else{
      for(j = 0; j < num_new_nodes; j++){
        #ifdef LIST
           insert(2);
        #else
          insert(c % max_priority + 1);
          c++;
        #endif
      }
    }
  }
}

/*
avg case is the same for both splay tree and list, keys are taken from a
normal distribution or binomial distribution;
*/
void avg_sim(bool isProc){
  int i, j;
  int c = 2;
  Node *root = init_q(1);
  for(i = 0; i < tree_size; i++){
    insert(normDist[c]);
    c++;
  }
  for(i = 0; i < sim_size; i++){
    Node* node = get_highest_prio();
    delete(node -> key);

    if(isProc){
      insert(normDist[c]);
      c++;
    }else{
      for(j = 0; j < num_new_nodes; j++){
        insert(node -> key + normDist[c]);
        c++;
      }
    }
  }
}

int main(){
  #ifdef LIST
     printf("Using linked list\n");
  #else
     printf("Using splay tree\n");
  #endif

  int i = 0;
  clock_t start, end;
  struct rusage r_usage;
  for(i = 0; i < 1000; i++){
    srand(primeSeeds[i % numSeeds]);
    init_normDist();
    getrusage(RUSAGE_SELF,&r_usage);
    start = clock();
    avg_sim(true);
    end = clock();
    printf("%f\n", ((double)(end - start)) / CLOCKS_PER_SEC);
  }
  return 0;
}
