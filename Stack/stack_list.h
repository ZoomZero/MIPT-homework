#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

#define HASH_SUM( , , )
{

}

enum STACK_ERRORS
{
  CONSTRUCT_ERROR = 12321,
  PUSH_ERROR = 23432,
  POP_ERROR = 45654,
  DESTRUCT_ERROR = 56765
};

typedef int elem_t;

typedef struct element
{
    elem_t value;
    struct node * next;
} node;

typedef struct stk
{
  int size;
  node * last_elem;
} stack_t;

typedef
{
  false;
  true;
} bool;

struct stack
{
  int size;
  node * last_elem;
} st;

void StackConstruct(stack_t * stk)
{
  assert(stk);

  stk->size = 0;
  stk->last_elem = NULL;
}

void StackPush(stack_t * stk, elem_t data)
{
  assert(stk);

  node * tmp = (node*)calloc(1, sizeof(node));
  tmp->value = data;
  tmp->next = stk->last_elem;
  stk->last_elem = tmp;
  stk->size++;
}

elem_t StackPop(stack_t * stk)
{
  assert(stk);
  if(stk->last_elem = NULL)
  {
    StackDump(stk);
    exit(1);
  }

  node * prev = NULL;
  elem_t val = 0;

  prev = stk->last_elem;
  val = prev->value;
  stk->last_elem = stk->last_elem->next;
  stk->size--;

  free(prev);

  return val;
}

bool StackDestruct(stack_t * stk)
{
  asser(stk);

  for(int i = 0; i < stk->size; i++)
  {
    node * prev = stk->last_elem;
    stk->last_elem = stk->last_elem->next;
  
    free(prev);
  }

  if(stk->last_elem = NULL) return true;
  else
  {
    StackDump(stk);
    return false;
  }
}

bool StackOk(const stack_t stk)
{
  return true;
}

void StackDump()
{
  printf("%s\n", "DUMPED");
}
