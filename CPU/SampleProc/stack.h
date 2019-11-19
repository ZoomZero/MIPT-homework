#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define VAR_NAME(var) #var
#define stack_t struct stack

#define assert_stack(stk) {\
  if (!(StackOk(stk)))\
  {\
    printf("|\tAssertion failed.\t|\n");\
    printf("|\twhat: StackOk(%s)\t|\n", #stk);\
    printf("|\tin: %s\t\t|\n", __FILE__);\
    printf("|\tfunction: %s\t|\n",  __PRETTY_FUNCTION__);\
    printf("|\ton: %d line\t\t|\n", __LINE__);\
    printf("\t%s\n", "!!!Look at Dump.txt!!!");\
    StackDump(stk);\
    abort();\
  }\
}\

#define assert_var(var) {\
  if (!isfinite((float)var))\
  {\
    printf("|\tAssertion failed.\t|\n");\
    printf("|\twhat: StackOk(%s)\t|\n", #var);\
    printf("|\tin: %s\t\t|\n", __FILE__);\
    printf("|\tfunction: %s\t|\n",  __PRETTY_FUNCTION__);\
    printf("|\ton: %d line\t\t|\n", __LINE__);\
    printf("\t%s\n", "!!!Look at Dump.txt!!!");\
    StackDump(stk);\
    abort();\
  }\
}\

const int CANN_VALUE1 = 0xF4321;
const int CANN_VALUE2 = 0xF1234;
const int MULTIPLIER = 2;
const char poison = 255;

enum STACK_ERRORS
{
  CONSTRUCT_ERROR = 12321,
  REALLOC_ERROR = 32423,
  DESTRUCT_ERROR = 56765
};

typedef int elem_t;

typedef enum
{
  false,
  true
} bool;

elem_t error_code = true;

struct stack
{
  int cannery1;
  int cannery2;
  int size;
  elem_t * data;
  int capacity;
  elem_t hash;
  int cannery3;
  int cannery4;
} st;

int StackConstruct(stack_t * stk, ...)
{
  assert(stk);

  va_list init_sz;
  int init_size = 0;
  va_start(init_sz, stk);
  init_size = va_arg(init_sz, int);
  va_end(init_sz);
  if(init_size < 0 || init_size > 20) init_size = 0;

  assert_var(init_size);

  if (init_size == 0)
  {
    stk->size = 0;
    stk->capacity = 0;;
    stk->hash = 0;
    stk->data = NULL;
    stk->cannery1 = stk->cannery4 = CANN_VALUE1;
    stk->cannery2 = stk->cannery3 = CANN_VALUE2;
  }
  else
  {
    stk->size = 0;
    stk->capacity = init_size;
    stk->hash = 0;
    stk->data = (elem_t*)calloc(init_size + 4, sizeof(elem_t));
    stk->cannery1 = stk->cannery4 = CANN_VALUE1;
    stk->cannery2 = stk->cannery3 = CANN_VALUE2;
    stk->data[0] = stk->data[init_size+3] = CANN_VALUE1;
    stk->data[1] = stk->data[init_size+2] = CANN_VALUE2;

    if (stk->data == NULL)
    {
      printf("ERROR! Can't initialize the Stack! Memory corruption!\n");
      error_code = CONSTRUCT_ERROR;
      StackDump(stk);
      return poison;
    }
  }

  assert_stack(stk);
  return true;
}

int StackPush(stack_t * stk, elem_t data)
{
  assert_stack(stk);
  assert_var(data);

  if(stk->size >= stk->capacity)
  {
    if(stk->data == NULL)
    {
      stk->data = (elem_t*)calloc(stk->capacity++ + 4, sizeof(elem_t));
      stk->data[0] = CANN_VALUE1;
      stk->data[1] = CANN_VALUE2;
    }
    else
    {
      stk->data[stk->capacity+2] = 0;
      stk->data[stk->capacity+3] = 0;
      stk->capacity *= MULTIPLIER;
      stk->data = (elem_t*)realloc(stk->data, (stk->capacity + 4) * sizeof(elem_t));
    }
    stk->data[stk->capacity+2] = CANN_VALUE2;
    stk->data[stk->capacity+3] = CANN_VALUE1;

    if (stk->data == NULL)
    {
      printf("ERROR! Can't reallocate the Stack! Memory corruption!\n");
      error_code = REALLOC_ERROR;
      StackDump(stk);
      return poison;
    }
  }

  stk->data[stk->size++ + 2] = data;
  stk->hash = murmur_hash(stk);

  assert_stack(stk);

  return true;
}

elem_t StackPop(stack_t * stk)
{
  assert_stack(stk);

  if(stk->size == 0)
  {
    printf("%s\n", "Error. Stack is empty");
    assert_stack(stk);
    return poison;
  }

  elem_t val = stk->data[--stk->size + 2];

  if (stk->size < stk->capacity/(MULTIPLIER*MULTIPLIER))
  {
    stk->capacity = stk->capacity/MULTIPLIER;
    stk->data = (elem_t*)realloc(stk->data, (stk->capacity + 4) * sizeof(elem_t));
    stk->data[stk->capacity+2] = CANN_VALUE2;
    stk->data[stk->capacity+3] = CANN_VALUE1;

    if (stk->data == NULL)
    {
      printf("ERROR! Can't reallocate the Stack! Memory corruption!\n");
      error_code = REALLOC_ERROR;
      StackDump(stk);
      return poison;
    }
  }

  stk->hash = murmur_hash(stk);

  assert_stack(stk);

  return val;
}

int StackOk(stack_t * stk)
{
  assert(stk);

  if (stk->data == NULL && stk->size != 0)                          return false;
  if (stk->cannery1 != CANN_VALUE1 || stk->cannery4 != CANN_VALUE1) return false;
  if (stk->cannery2 != CANN_VALUE2 || stk->cannery3 != CANN_VALUE2) return false;
  if (stk->data != NULL)
  {
    if(stk->data[0] != CANN_VALUE1 || stk->data[1] != CANN_VALUE2)  return false;
    if(stk->data[stk->capacity+2] != CANN_VALUE2)                   return false;
    if(stk->data[stk->capacity+3] != CANN_VALUE1)                   return false;
  }
  if (stk->capacity < 0 || stk->size < 0)                           return false;
  if (stk->capacity < stk->size)                                    return false;
  if (stk->size != 0) if (stk->hash != murmur_hash(stk))            return false;

  return true;
}

void StackClear(stack_t * stk)
{
  assert_stack(stk);

  if (stk->data != NULL)
  {
    memset(stk->data, poison, (stk->capacity + 4) * sizeof(elem_t));
    free(stk->data);
    stk->data = NULL;
  }

  stk->hash = 0;
  stk->capacity = 0;
  stk->size = 0;
}

int StackDestruct(stack_t * stk)
{
  assert_stack(stk);

  if (stk->data != NULL)
  {
    memset(stk->data, poison, (stk->capacity + 4) * sizeof(elem_t));
    free(stk->data);
    stk->data = NULL;
  }

  if (stk->data != NULL)
  {
    printf("ERROR! Can't destruct the Stack! Memory corruption!\n");
    error_code = DESTRUCT_ERROR;
    StackDump(stk);
    return poison;
  }

  stk->size = poison;
  stk->hash = poison;
  stk->capacity = poison;
  stk->cannery1 = poison;
  stk->cannery2 = poison;
  stk->cannery3 = poison;
  stk->cannery4 = poison;

  return true;
}

void StackDump(stack_t * stk)
{
  assert(stk);

  FILE * dump = fopen("Dump.txt", "w+");
  fprintf(dump, "%s\n", "-------------------------------------");
  fprintf(dump, "stack_t \"%s\" [%p]\n", VAR_NAME(stk), stk);
  fprintf(dump, "{\n");
  fprintf(dump, "\tcannery1 = %d\n", stk->cannery1);
  fprintf(dump, "\tcannery2 = %d\n", stk->cannery2);
  fprintf(dump, "\tsize = %d\n", stk->size);
  fprintf(dump, "\tcapacity = %d\n", stk->capacity);
  fprintf(dump, "\tdata [%p]\n\t{\n", stk->data);
  if (stk->data != NULL)
  {
    for (int i = 0; i < stk->capacity + 4; i++)
    {
      fprintf(dump, "\t\t*[%d] = %d", i, stk->data[i]);
      if (i == 0 || i == 1 || i == stk->capacity+2 || i == stk->capacity+3)
        fprintf(dump, "%s\n", " (cannery)");
      else if (stk->data[i] == poison) fprintf(dump, "%s\n", " (poison?)");
      else fprintf(dump, "\n");
    }
  }
  fprintf(dump, "\t}\n");
  fprintf(dump, "\thash = %d\n", stk->hash);
  fprintf(dump, "\tcannery3 = %d\n", stk->cannery3);
  fprintf(dump, "\tcannery4 = %d\n", stk->cannery4);
  fprintf(dump, "\tError code (%d)\n}\n", error_code);
  fprintf(dump, "%s\n", "-------------------------------------");
  fclose(dump);
}

int murmur_hash(stack_t * stk)
{
  assert(stk);

  const int m = 0xDED;
  const int r = 12;

  int h = 1;
  int k = 0;

  const elem_t * data = stk->data;
  int size = stk->size;

  while (size >= 4)
  {
    k = data[2];
    k |= data[3] << 8;
    k |= data[4] << 16;
    k |= data[5] << 24;

    k *= m;
    k ^= k >> r;
    k *= m;

    h *= m;
    h ^= k;

    data +=4;
    size -= 4;
  }

  switch (size)
  {
    case 3:
    h ^= data[4] << 16;
    case 2:
    h ^= data[3] << 8;
    case 1:
    h ^= data[2];
    h *= m;
  }

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}
