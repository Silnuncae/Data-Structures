#include <stdio.h>
#include "backend.h"

/****************************************
Implement Breadth-First Search on the graph constructed in "backend.c" and
use it in the find_path() below.

You can access functions and data structures constructed in "backend.c" via
"backend.h"
*****************************************/

int state[N][2]; // [N]에는 현재 노드, [N][0]에는 상태, [N][1]에는 부모 노드
// 상태 0 = undiscovered, 1 = discovered, 2 = processed

int shortest_path(char start[5], char goal[5])
{
    int Q[N]; // 큐에 넣어서 이제 
    int rear = 0;
    int front = 0; // rear, front
    int k;

    for (k = 0; k < N; k++) // 상태, 부모, 큐 초기화
    {
        state[k][0] = 0;
        state[k][1] = -1;
        Q[k] = -1;
    } 

    int i, j;

    i = search_index(start);
    j = search_index(goal);

    state[i][0] = 1; // 시작 노드는 discovered
    state[i][1] = -1; // 시작 노드의 부모에 -1
    Q[rear++] = i; //Q에 시작 노드의 인덱스 투입

    while (front < rear) // queue is not empty
    {
        int current = Q[front++]; // pop() // 처음 current는 start
       
        struct node *p = adj_list[current];

        while (p != NULL) // for each neighbor v of current
        {
        int next = p->index;

        if (state[next][0] == 0)
        {
                  state[next][0] = 1;
                    Q[rear++] = next;
                    state[next][1] = current;
                    if (j == next) // found t!
                    {
                        return 1;
                    }
        }
           p = p->next;
        }
        state[current][0] = 2;
    }
    return 0; // the traversal is complete without finding t
}

void print_path(char start[5], char goal[5]) // 다시 봐야할듯
{
    int i, j;

    i = search_index(start);
    j = search_index(goal);

    int path[N]; // long enough just to store the path
    int g = j;
    int r = 0;

    while (g != i) 
    {
        path[r++] = g;
        g = state[g][1];
    }
    path[r] = i;
    int p = 0;
    while (r >= 0)
    {
        printf("          %d ", p++);
        print_word(path[r--]);
        printf("\n");
    }
}


void find_path(char start[5], char goal[5])
{
    int i, j;
  
  i=search_index(start);
  j=search_index(goal);

  if (i<0) {
    printf("Sorry. ");
    print_five_chars(start);
    printf(" is not in the dicitonary.");
  }
  else if (j<0) {
    printf("Sorry. ");
    print_five_chars(goal);
    printf(" is not in the dicitonary.");
  }
  else 
  {
      int find = shortest_path(start, goal);
      if (find == 0)
      {
          printf("Sorry. There is no path from ");
          print_five_chars(start);
          printf(" to ");
          print_five_chars(goal);
          printf(".\n");
      }
      else
      {
          print_path(start, goal);
      }
  }
}
