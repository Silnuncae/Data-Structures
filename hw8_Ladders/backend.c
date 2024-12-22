#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for delay()

#define N 5757

// words of 5 letters
char word[N][5];

// adjacency matrix
char adj_mat[N][N];


// Function declarations
void print_word();
void init_data();
void init_adj_mat();



/********* For adjacency list and queue,
           we need node structure and its memory pool.
********************************************/
// record structure
struct node {
  int index;
  struct node * next;
};

#define POOL_SIZE 6*5757  // What is an appropriate size?  The average degree
			  // is about 5.  So this must be enough.

// pool of memory
struct node pool[POOL_SIZE];
struct node * top=pool;  // a pointer variable for stack top.

// Still use the same memory management.
void init_pool() // Initialize the pool.
{
  int i;
  struct node *r=pool;
  struct node *s;

  pool[POOL_SIZE-1].next=NULL;

  for(i=1;i<POOL_SIZE;i++) {
    s=r++;
    s->next=r;
  }
}

// When calling new_node(), make sure to check if it returns NULL.
struct node * new_node()
{
  struct node *r;

  if(top==NULL)
    return NULL;

  r=top;
  top=r->next;
  return r;
}

// Push a node to the pool.
void free_node(struct node *r)
{
  r->next=top;
  top=r;
}

/***************** End of Memory Mananagement *********************/






/***************** adjacency list *******************/
struct node * adj_list[N];

void init_adj_list() // �׷��� ����Ʈ�� ����� �Լ�
{
  int i,j;
  struct node *p;

  for (i=0; i<N; i++)
    adj_list[i]=NULL;

  for (i=0; i<N; i++)
    for (j=N-1; j>=0; j--)    // a new node is put in front.  To make the
			      // list in ascending order, we check the
			      // vertices in reverse order.
      if (adj_mat[i][j]) {
	p=new_node();
	p->index=j;
	p->next=adj_list[i];
	adj_list[i]=p;
      }
  printf("Adjacency list was successfully constructed!\n");
}



void init_data() // �ܾ �׷��� �迭�� �����ϴ� �Լ�
{
  int i;
  FILE *f;

  if ((f=fopen("words.dat", "r")) == NULL)
    printf("Sorry, I can't open words.dat.\n");

  // skip the first four lines
  for (i=1; i<=4; i++) {
    while (getc(f)!='\n');
  }

  // start reading data
  for (i=0; i<N; i++) {
    fscanf(f, "%5c", word[i]);
    while (getc(f)!='\n');
  }

  printf("All the words were successfully read!\n");
  fclose(f);
}

int adjacent(char u[5], char v[5]) // �� �ܾ ���� �������� �Ǵ��ϴ� �Լ�
{
  int i, check=0;

  for (i=0; i<5; i++)
    if (u[i]!=v[i]) check++;

  if (check==1)
    return 1;
  else
    return 0;
}

void init_adj_mat()
{
  int i,j,l;

  for (i=0;i<N;i++)
    for (j=0;j<N;j++)
      adj_mat[i][j]=adjacent(word[i],word[j]);

  printf("Adjacency matrix was successfully constructed!\n");
}


void print_word(int k)
{
  int i;
  if(0<=k && k<N) {
    for (i=0; i<5; i++)
      putchar(word[k][i]);
  }
  else
    printf("ERROR: print_word() received a k=%d which is out of bound!\n", k);
}




/* u-v */
int compare(char u[5], char v[5])
{
  return strncmp(u, v, 5);
}

// Sequential search.
// Returns the index of the found record. (between 0 and N-1)
// Returns -1, if not found.
int search_index(char key[5])
{
  int i;

  for (i=0; i<N; i++) {
    if(compare(key,word[i])==0)
      return i;
  }
  return -1;
}

//***********************************************************************

/********** Homework 8 *****************/
void hw8()
{
    printf("\n");

    //******************Number(1)*********************

    printf("Number (1)\n");

    char words[2][6] = { "hello", "graph" }; // �˻��� �ܾ��
    for (int i = 0; i < 2; i++) 
    {
        char* current_word = words[i];
        int index = search_index(current_word); // �ܾ��� �ε��� ã��

        struct node* p = adj_list[index]; // ���� ����Ʈ���� �ش� �ε����� ù ��° ���
        int degree = 0;

        printf("Case of '%s'\n", current_word);
        printf("Adjacency words of '%s':\n", current_word);
        while (p != NULL) {
            print_word(p->index); // ������ �ܾ� ���
            printf("\n");
            degree++; // ���� ����
            p = p->next; // ���� ���� �̵�
        }
        printf("Degree of '%s': %d\n\n", current_word, degree);
    }

    //******************Number(2)*********************

    printf("Number (2)\n");
    int degree_count[N] = { 0 };  // ��� ������ ������ ������ �迭 �ʱ�ȭ
    int max_degree = 0;  // �ִ� ������ ����

    // �� �ܾ��� ���� ���
    for (int i = 0; i < N; i++) 
    {
        struct node* current = adj_list[i];
        int degree = 0;
        while (current != NULL) 
        {
            degree++;
            current = current->next;
        }
        if (degree > max_degree) 
        {
            max_degree = degree;  // �ִ� ���� ������Ʈ
        }
        degree_count[degree]++;  // �ش� ������ ī��Ʈ ����
    }

    // ���� ���� ���̺� ���
    printf("Degree distribution table:\n");
    for (int i = 0; i <= max_degree; i++) 
    {
        if (degree_count[i] > 0) 
        {
            printf("%d: %d\n", i, degree_count[i]);
        }
    }
    printf("\n");

    //******************Number(3)*********************

    printf("Number (3)\n");
    max_degree = 0;
    struct node* p;
    int degree;

    for (int i = 0; i < N; i++) // �ִ� ���� ���
    {
        degree = 0;
        for (p = adj_list[i]; p != NULL; p = p->next) 
        {
            degree++;
        }
        if (degree > max_degree) 
        {
            max_degree = degree;
        }
    }
    printf("Maximum degree: %d", max_degree); // �ִ� ���� ���

    //******************Number(4)*********************

    printf("\n");
    printf("Number (4)\n");
    printf("Words having maximum degree:\n"); // �ִ� ������ ���� �ܾ��

    for (int i = 0; i < N; i++) 
    {
        degree = 0;
        for (p = adj_list[i]; p != NULL; p = p->next) // �ִ� ������ ���� �ܾ� ã��
        {
            degree++;
        }

        if (degree == max_degree) // �ִ� ������ ���� ������ ���� �ܾ� ���
        {
            print_word(i);
            printf("\n");
        }
    }

    printf("\n");

    //******************Number(5)*********************

    printf("Number (5)\n");
    int total_degree = 0;
    double average_degree;

    for (int i = 0; i < N; i++) 
    {
        degree = 0;  
        for (p = adj_list[i]; p != NULL; p = p->next) 
        {
            degree++;
        }
        total_degree += degree;  // ������ ���տ� ���� �ܾ��� ���� ���ϱ�
    }

    if (N > 0)
    {
       average_degree = (double)total_degree / N;
    }      
    else
    {
        average_degree = 0.0;
    }

    printf("Total degree: % d\n", total_degree); // �� ���� ���
    printf("Average degree: %.2f\n", average_degree); // ��� ���� ���
    printf("\n");

    //******************Number(6)*********************

    printf("Number (6)\n");
    int total_nodes = 0;
    for (int i = 0; i < N; i++) // ����� ���� = ������ ���� �ƴѰ�?
    {
        int node_count = 0;
        struct node* current = adj_list[i];
        while (current != NULL) 
        {
            node_count++;
            current = current->next;
        }
        total_nodes += node_count;
    }
    printf("Number of total nodes in adjacency list: %d\n", total_nodes); // ���� ����Ʈ�� ����� �� ���� = �� ������ ���� �ʳ�?
    printf("\n");

    //******************Number(7)*********************

    printf("Number (7)\n");
    printf("Minimum possible size of POOL_SIZE: %d\n", total_nodes); // �ּ� ���� POOL_SIZE�� ������� ����� ������ ���� �ʳ�?
    printf("\n");
}


// All the initializations
void init()
{
  init_data();
  init_adj_mat();
  init_pool();
  init_adj_list();
  hw8();
}


void find_path(char start[5], char goal[5])
{
  int i,j,k,l;

  i=search_index(start);
  j=search_index(goal);

  if (i<0) printf("Sorry. %5s is not in the dictionary.", start);
  else if (j<0) printf("Sorry. %5s is not in the dictionary.", goal);
  else {
      printf("Hmm... I am trying to figure out the shortest path from ");
      print_word(i); printf(" to "); print_word(j); printf(".\n");
      for (l = 0; l < 150; l++) 
      {
          for (k = 0; k < N; k++) 
          {
              printf("Considering about ");
              print_word(k);
              printf("\r"); fflush(stdout);
          }
      }
  }

}


//int search_index(char key[5]) 
//{
//    int l = 0;
//    int h = N - 1;
//    int m;
//
//    while (l <= h) 
//    {
//        m = l + (h - l) / 2; // �߰� �ε��� ���
//
//        int result = compare(key, word[m]);
//        if (result == 0) 
//        {
//            return m; // key�� �߰� �ε����� �ܾ�� ��ġ�� ���
//        }
//        else if (result < 0) 
//        {
//            h = m - 1; // key�� �߰� �ܾ�� �տ� ���� ���
//        }
//        else 
//        {
//            l = m + 1; // key�� �߰� �ܾ�� �ڿ� ���� ���
//        }
//    }
//    return -1; // ã�� ���� ���
//}
