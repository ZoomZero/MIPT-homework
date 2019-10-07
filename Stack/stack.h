#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

const int CANN_VALUE = 1010101;
const int INIT_SIZE = 4;
const int MULTIPLIER = 2;

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

typedef struct stk
{
  int cannery1;
  int cannery2;
  int size;
  elem_t * data;
  int cannery3;
  int cannery4;
} stack_t;

typedef
{
  false;
  true;
} bool;

struct stack
{
  int cannery1;
  int cannery2;
  int size;
  elem_t * data;
  elem capacity;
  int cannery3;
  int cannery4;
} st;

void StackConstruct(stack_t * stk)
{
  assert(stk);

  stk->size = 0;
  stk->data = (elem_t*)calloc(INIT_SIZE + 4, sizeof(elem_t));
  stk->data[0] = stk->data[1] = stk->data[INIT_SIZE+2] = stk->data[INIT_SIZE+3] = CANN_VALUE;
  stk->cannery1 = stk->cannery2 = stk->cannery3 = stk->cannery4 = CANN_VALUE;
  stk->capacity = INIT_SIZE;

  assert(StackOk(stk));
}

void StackPush(stack_t * stk, elem_t data)
{
  assert(StackOk(stk));

  if(stk->size >= stk->capacity)
  {
    capacity = capacity*MULTIPLIER;
    stk->data = (elem_t*)realloc(data, (capacity+4) * sizeof(elem_t));
    stk->data[capacity+2] = stk->data[capacity+3] = CANN_VALUE;
  }

  stk->data[2+stk->size++] = elem;

  assert(StackOk(stk));
}

elem_t StackPop(stack_t * stk)
{
  assert(StackOk(stk));

  if(stk.size = 0) printf("%s\n", "Error. Stack is empty");;

  elem_t val = stk->data[2+stk->size--];

  if(stk->size <= (capacity-4)/MULTIPLIER)
  {
    capacity = (capacity-4)/MULTIPLIER;
    stk->data = (elem_t*)realloc(data, (capacity+4) * sizeof(elem_t));
  }

  assert(StackOk(stk));

  return val;
}

bool StackDestruct(stack_t * stk)
{
    assert(StackOk(stk));

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
