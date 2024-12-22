#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"
#include "memory.h"

void print_name(struct record *);
void print_number(struct record *);
void print_data(char *, int); 

// data
struct record * data = NULL; // Initially NULL. // 헤더를 가르키는 포인터

void init()
{
  init_pool();
}


void add(char *name, char *number) // new->name[] = name[] 이런식으로 newnode를 불러야한다. p->name[] = name[] 보조변수 p는 구조체로. p=newnode가 끝나고 p를 리턴할때 오버플로우인지 고려해야한다.
{
    struct record* new = new_node();

    if (new == NULL)
    {
        printf("Can't add.  The address book is full!\n");

        return;
    }

    new->name[0] = name[0];
    new->name[1] = name[1];
    new->name[2] = name[2];
    new->number[0] = number[0];
    new->number[1] = number[1];
    new->number[2] = number[2];
    new->number[3] = number[3];

    new->next = data;
    data = new;

  // Error Message for overflow:
  // printf("Can't add.  The address book is full!\n");
}


/* Just a wrapper of strncmp(), except for the case r is NULL.
Regard strncmp(a,b) as a-b, that is,
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
  if (r==NULL)
    return -1;
  else
    return strncmp(key, r->name, 3);
}


void search(char name[3])
{
  struct record *r=data;
  int result;

  while(r!=NULL && (result=compare(name,r))!=0)
    r=r->next;
  if(r==NULL)
    printf("Couldn't find the name.\n");
  else {
    print_name(r);
    printf(" : ");
    print_number(r);
    printf(" was found.\n");
  }
}


void delete(char name[3]) // 삭제되는 노드와 삭제되는 노드 앞 노드를 가르키는 상태에서 삭제를 하고 노드를 연결시켜줘야한다. search함수를 잘 이용할것. 예외적인 상황이 있다. 꼭 고려하기
{
    struct record* current = data;
    struct record* before = NULL;
    int result;

    if(current == NULL)
    {
        printf("Couldn't find the name.\n");
    }
    else
    {
        while (current != NULL && (result = compare(name, current)) != 0)
        {
            before = current;
            current = current->next;
        }
        if (before == NULL)
        {
            data = current->next;
        }
        else
        {
            before->next = current->next;
        }
        free_node(current);
        printf("The name was deleted.\n");

    }

  // Error Message:
  // printf("Couldn't find the name.\n");
}


// Prints ith name.
void print_name(struct record *r)
{
  print_data(r->name, 3);
}

// Prints ith number.
void print_number(struct record *r)
{
  print_data(r->number, 4);
}

void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_list() // search에 거의 다 답이 있다. 단축키P
{
   struct record* current = data;
   while (current != NULL)
   {
       print_name(current);
       printf(" : ");
       print_number(current);
       printf("\n");
       current = current->next;
   }

}
