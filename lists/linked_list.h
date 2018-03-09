typedef struct Node {
  struct Node *next, *previous;
  double key;
} Node;

typedef struct List {
  struct Node * first;
  struct Node * last;
  int size;
} List;

Node * get(double);
Node * get_highest_prio();
void insert(double);
void delete(double);
Node* init_q(double);
void destroy();
