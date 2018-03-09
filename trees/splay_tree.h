typedef struct Node {
  struct Node *parent, *left, *right;
  double key;
  struct Queue * queue;
} Node;

Node * create_node(Node *, double);
void insert(double);
Node * get(double);
Node* get_parent(Node *);
void delete(double);
void splay(Node*);
void traverse_tree(Node *);
double get_lowest_key_from(Node *);
double get_lowest_key();
void rotate_right(Node *);
void rotate_left(Node *);
Node* init_q(double);
Node* get_root();
Node * get_highest_prio();
void destroy();
