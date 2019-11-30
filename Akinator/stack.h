#ifndef _STACK_H_
#define _STACK_H_

#define VAR_NAME(var) #var
#define stack_t struct stack

const int MULTIPLIER = 2;

typedef char* elem_t;

struct stack
{
  int size;
  elem_t * data;
  int capacity;
} st;

int StackConstruct(stack_t * stk, int init_size)
{
  assert(stk);

  stk->size = 0;
  stk->capacity = init_size;
  stk->data = (elem_t*)calloc(init_size, sizeof(elem_t));

  if (stk->data == NULL)
  {
    printf("ERROR! Can't initialize the Stack! Memory corruption!\n");
    return false;
  }

  return true;
}

int StackPush(stack_t * stk, elem_t data)
{
  assert(stk);

  if(stk->size >= stk->capacity)
  {
    if(stk->data == NULL)
    {
      stk->data = (elem_t*)calloc(stk->capacity++, sizeof(elem_t));
    }
    else
    {
      stk->capacity *= MULTIPLIER;
      stk->data = (elem_t*)realloc(stk->data, stk->capacity * sizeof(elem_t));
    }

    if (stk->data == NULL)
    {
      printf("ERROR! Can't reallocate the Stack! Memory corruption!\n");
      return false;
    }
  }

  stk->data[stk->size++] = data;

  return true;
}

elem_t StackPop(stack_t * stk)
{
  assert(stk);

  if(stk->size == 0)
  {
    printf("%s\n", "Error. Stack is empty");
    return poison;
  }

  elem_t val = stk->data[--stk->size];
  //free(stk->data[stk->size + 1]);

  if (stk->size < stk->capacity/(MULTIPLIER*MULTIPLIER))
  {
    stk->capacity = stk->capacity/MULTIPLIER;
    stk->data = (elem_t*)realloc(stk->data, stk->capacity * sizeof(elem_t));

    if (stk->data == NULL)
    {
      printf("ERROR! Can't reallocate the Stack! Memory corruption!\n");
      return poison;
    }
  }

  return val;
}

void StackClear(stack_t * stk)
{
  assert(stk);

  if (stk->data != NULL)
  {
    memset(stk->data, poison, stk->capacity * sizeof(elem_t));
    free(stk->data);
    stk->data = NULL;
  }

  stk->capacity = 0;
  stk->size = 0;
}

int StackDestruct(stack_t * stk)
{
  assert(stk);

  if (stk->data != NULL)
  {
    memset(stk->data, poison, stk->capacity  * sizeof(elem_t));
    free(stk->data);
    stk->data = NULL;
  }

  if (stk->data != NULL)
  {
    printf("ERROR! Can't destruct the Stack! Memory corruption!\n");
    return false;
  }

  stk->size = poison;
  stk->capacity = poison;

  return true;
}

#endif
