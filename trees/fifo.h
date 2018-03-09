typedef struct FifoNode {
  struct FifoNode * next;
  double key;
} FifoNode;

typedef struct Queue {
  struct FifoNode * first;
  struct FifoNode * last;
  int size;
} Queue;

void fifo_add(Queue *, double);
Queue * fifo_init();
FifoNode * fifo_get(Queue *);
