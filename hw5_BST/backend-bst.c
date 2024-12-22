#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend-bst.h"
#include "memory.h"

void print_name(struct record *);
void print_number(struct record *);

// comparison function for records
int compare(char key[3], struct record *);

// data
struct record * data = NULL; // Initially NULL.

/***********************
Address Book by binary search tree
**************************/

void init()
{
  init_pool();
}


void search(char name[3])  
{
  struct record *r; // Pointer to record being compared.
                    //data or left/right field of a node.
  int result;
  r=data;

  while (r!=NULL) {
    if ((result=compare(name,r))<0)
      r=r->left;
    else if (result==0) {
      print_name(r);
      printf(" : ");
      print_number(r);
      printf(" was found.\n");
      return;
    }
    else // case >0
      r=r->right;
  }
  printf("Couldn't find the name.\n");
}


void add(char *name, char *number)
{
    struct record* new = new_node();

    if (new == NULL)
    {
        printf("Can't add. The pool is empty!\n");
        return;
    }

    new->name[0] = name[0];
    new->name[1] = name[1];
    new->name[2] = name[2];
    new->number[0] = number[0];
    new->number[1] = number[1];
    new->number[2] = number[2];
    new->number[3] = number[3];
    new->left = NULL;
    new->right = NULL;

    struct record* r; // Pointer to record being compared.
    //data or left/right field of a node.
    struct record* before = NULL;
    int result;
    r = data;

    if (data == NULL)
    {
        data = new;
    }
    else
    {
    while (r != NULL) 
    {
        if ((result = compare(new->name, r)) <= 0)
        {
            before = r;
            r = r->left;
        }
        else // case >0
        {
            before = r;
            r = r->right;
        }
    }
    if ((result = compare(new->name, before)) <= 0)
    {
        before->left = new;
    }
    else // case >0
    {
        before->right = new;
    }
    }
    printf("The name was successfully added!\n");
  // Messages to print
  //  printf("Can't add.  The pool is empty!\n");
  //  printf("The name was successfully added!\n");
}


// The most complicated.
void delete(char name[3])
{
    struct record* r; // Pointer to record being compared.
    //data or left/right field of a node.
    struct record* before = NULL;
    struct record* delete = NULL;
    int result;
    r = data;

    while (r != NULL)
    {
        if ((result = compare(name, r)) < 0)
        {
            before = r;
            r = r->left;
        }
        else if ((result = compare(name, r)) > 0)
        {
            before = r;
            r = r->right;
        }
        else // 비교한 노드가 삭제한 노드인 경우
        {

            if (r->left == NULL && r->right == NULL) // 삭제할 노드의 자식 노드가 없는 경우
            {
                if (before == NULL)
                {
                    data = NULL;
                }
                else if (before->left == r)
                {
                    before->left = NULL;
                }
                else
                {
                    before->right = NULL;
                }
                free_node(r);
                printf("The name was deleted.\n");
                return;
            }

            if (r->left == NULL && r->right != NULL) // 삭제할 노드에 자식 노드가 오른쪽 하나인 경우
            {
                if (before == NULL)
                {
                    data = r->right;
                }
                else if (before->right == r) // 삭제할 노드의 전 노드의 오른쪽이 삭제할 노드인 경우
                {
                    before->right = r->right; // 삭제할 노드의 오른쪽 자식 노드의 주소를 전 노드의 오른쪽에 전달
                }
                else // 삭제할 노드의 전 노드의 왼쪽이 삭제할 노드인 경우
                {
                    before->left = r->right; // 삭제할 노드의 오른쪽 자식 노드의 주소를 전 노드의 왼쪽에 전달
                }
                free_node(r);
                printf("The name was deleted.\n");
                return;
            }

            if (r->left != NULL && r->right == NULL) // 삭제할 노드에 자식 노드가 왼쪽 하나인 경우
            {
                if (before == NULL)
                {
                    data = r->left;
                }
                else if (before->right == r) // 삭제할 노드의 전 노드의 오른쪽이 삭제할 노드인 경우
                {
                    before->right = r->left; // 삭제할 노드의 왼쪽 자식 노드의 주소를 전 노드의 오른쪽에 전달
                }
                else // 삭제할 노드의 전 노드의 왼쪽이 삭제할 노드인 경우
                {
                    before->left = r->left; // 삭제할 노드의 왼쪽 자식 노드의 주소를 전 노드의 왼쪽에 전달
                }
                free_node(r);
                printf("The name was deleted.\n");
                return;
            }

            if (r->left != NULL && r->right != NULL) // 삭제할 노드에 자식 노드가 둘 다 있는 경우
            {
                struct record* predessor = r->left; // 삭제할 노드의 왼쪽 자식 노드
                struct record* predessorB = NULL;
                while (predessor->right != NULL) // 프레데쎄서를 찾는 루틴
                {
                    predessorB = predessor;
                    predessor = predessor->right;
                }

                if (before == NULL) // 삭제하려는 노드가 헤드인 경우
                {
                    if (predessorB == NULL)
                    {
                        predessor->right = r->right;
                        data = predessor;
                    }
                    else
                    {
                        predessorB->right = predessor->left;
                        predessor->right = r->right;
                        predessor->left = r->left;
                        data = predessor;                       
                    }
                }
                else if (before->right == r)
                {
                    predessorB->right = predessor->left;
                    before->right = predessor;
                    predessor->left = r->left;

                }
                else
                {
                    predessorB->right = predessor->left;
                    before->left = predessor;
                    predessor->left = r->left;

                }
                free_node(r);
                printf("The name was deleted.\n");
                return;         
            }
        }
    }
    printf("Couldn't find the name.\n");
}
  // Messages to print
  //  printf("The name was deleted.\n");  
  //  printf("Couldn't find the name.\n");


/* Just a wrapper of strncmp().
Regard strncmp(a,b) as a-b.
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
    return strncmp(key, r->name, 3);
}


void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_name(struct record *r)
{
  print_data(r->name, 3);
}

void print_number(struct record *r)
{
  print_data(r->number, 4);
}

void print_inorder(struct record *t)
{
    if (t == NULL) return;

    print_inorder(t->left);
    print_name(t);
    printf(" : ");
    print_number(t);
    printf("\n");
    print_inorder(t->right);
}

void print_list()  
{
  print_inorder(data);
}


// returns the height of the BST.
int height(struct record *t) // 다시 보자 헤드 삭제시 왼쪽 자식이 하나만 있는 경우 자식이 올라가는데 가비지값이 주소로 담김
{
    int l, r;
    if (t == NULL)
    {
        return -1;
    }
    if ((l = (height(t->left))) < (r = (height(t->right))))
    {
        return r + 1;
    }
    else
    {
        return l + 1;
    }
}

void print_height()  
{
  printf("The Address Book BST's height is %d.\n", height(data));
}
