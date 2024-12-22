#include <stdio.h>
#include "memory.h"

// pool of memory
static struct record pool[POOL_SIZE]; // static because pool is strictly private
struct record * top=pool;  // a pointer variable for pool stack top.

void init_pool() // Initialize the pool; Use right instead of next!!!
{
  int i;
  struct record *r=pool;
  struct record *s;

  pool[POOL_SIZE-1].right=NULL;  

  for(i=1;i<POOL_SIZE;i++) {  
    s=r++;
    s->right=r;
  }
}

// Get a node from the pool. Returns NULL if pool is empty. (A BETTER DESIGN)
// When calling new(), make sure to check if it is NULL. 
struct record * new_node()  
{
  struct record *r;
  
  if(top==NULL) 
    return NULL;
    
  r=top;
  top=r->right;  // Again, right instead of next.
  return r;
}

// Push a node to the pool.
void free_node(struct record *r)
{
  r->right=top;  // Again, right instead of next.
  top=r;
}
