#define POOL_SIZE 10

// record structure
struct record {
  char name[3];
  char number[4];
  struct record * left;
  struct record * right;
};

void init_pool();
struct record * new_node();
void free_node(struct record *r);
