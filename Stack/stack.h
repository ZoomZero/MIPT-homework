#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

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
}

elem_t StackPop(stack_t * stk)
{
  assert(stk);

  node * prev = NULL;
  elem_t val = 0;

  prev = stk->last_elem;
  val = prev->value;
  stk->last_elem = stk->last_elem->next;

  free(prev);

  return val;
}

/*bool StackDestruct(stack_t * stk)
{

}

bool StackOk(const stack_t stk)
{
  return true;
}

void StackDump()
{
  printf("%s\n", "DUMPED");
}*/
