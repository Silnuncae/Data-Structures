// record structure
struct record {
  char name[3];
  char number[4];
  struct record * next; // 다음 구조체 노드로 가는 포인터
};

void init_pool();
struct record * new_node();
void free_node(struct record *r);

#define POOL_SIZE 10

