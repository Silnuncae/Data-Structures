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

void init_adj_list() // 그래프 리스트를 만드는 함수
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



void init_data() // 단어를 그래프 배열에 저장하는 함수
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

int adjacent(char u[5], char v[5]) // 두 단어가 서로 인접한지 판단하는 함수
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

    char words[2][6] = { "hello", "graph" }; // 검사할 단어들
    for (int i = 0; i < 2; i++) 
    {
        char* current_word = words[i];
        int index = search_index(current_word); // 단어의 인덱스 찾기

        struct node* p = adj_list[index]; // 인접 리스트에서 해당 인덱스의 첫 번째 노드
        int degree = 0;

        printf("Case of '%s'\n", current_word);
        printf("Adjacency words of '%s':\n", current_word);
        while (p != NULL) {
            print_word(p->index); // 인접한 단어 출력
            printf("\n");
            degree++; // 차수 증가
            p = p->next; // 다음 노드로 이동
        }
        printf("Degree of '%s': %d\n\n", current_word, degree);
    }

    //******************Number(2)*********************

    printf("Number (2)\n");
    int degree_count[N] = { 0 };  // 모든 가능한 차수를 저장할 배열 초기화
    int max_degree = 0;  // 최대 차수를 추적

    // 각 단어의 차수 계산
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
            max_degree = degree;  // 최대 차수 업데이트
        }
        degree_count[degree]++;  // 해당 차수의 카운트 증가
    }

    // 차수 분포 테이블 출력
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

    for (int i = 0; i < N; i++) // 최대 차수 계산
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
    printf("Maximum degree: %d", max_degree); // 최대 차수 출력

    //******************Number(4)*********************

    printf("\n");
    printf("Number (4)\n");
    printf("Words having maximum degree:\n"); // 최대 차수를 가진 단어는

    for (int i = 0; i < N; i++) 
    {
        degree = 0;
        for (p = adj_list[i]; p != NULL; p = p->next) // 최대 차수를 가진 단어 찾기
        {
            degree++;
        }

        if (degree == max_degree) // 최대 차수와 같은 차수를 가진 단어 출력
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
        total_degree += degree;  // 차수의 총합에 현재 단어의 차수 더하기
    }

    if (N > 0)
    {
       average_degree = (double)total_degree / N;
    }      
    else
    {
        average_degree = 0.0;
    }

    printf("Total degree: % d\n", total_degree); // 총 차수 출력
    printf("Average degree: %.2f\n", average_degree); // 평균 차수 출력
    printf("\n");

    //******************Number(6)*********************

    printf("Number (6)\n");
    int total_nodes = 0;
    for (int i = 0; i < N; i++) // 노드의 갯수 = 차수의 갯수 아닌가?
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
    printf("Number of total nodes in adjacency list: %d\n", total_nodes); // 인접 리스트의 노드의 총 갯수 = 총 차수랑 같지 않나?
    printf("\n");

    //******************Number(7)*********************

    printf("Number (7)\n");
    printf("Minimum possible size of POOL_SIZE: %d\n", total_nodes); // 최속 가능 POOL_SIZE는 사용중인 노드의 갯수와 같지 않나?
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
//        m = l + (h - l) / 2; // 중간 인덱스 계산
//
//        int result = compare(key, word[m]);
//        if (result == 0) 
//        {
//            return m; // key가 중간 인덱스의 단어와 일치할 경우
//        }
//        else if (result < 0) 
//        {
//            h = m - 1; // key가 중간 단어보다 앞에 있을 경우
//        }
//        else 
//        {
//            l = m + 1; // key가 중간 단어보다 뒤에 있을 경우
//        }
//    }
//    return -1; // 찾지 못한 경우
//}
