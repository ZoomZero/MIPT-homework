#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define struct List list_t;
typedef int elem_t;
const char poison = 255;

#define assert_list(lst) {\
  if (!(ListOk(stk)))\
  {\
    printf("|\tAssertion failed.\t|\n");\
    printf("|\twhat: ListOk(%s)\t|\n", #lst);\
    printf("|\tin: %s\t\t|\n", __FILE__);\
    printf("|\tfunction: %s\t|\n",  __PRETTY_FUNCTION__);\
    printf("|\ton: %d line\t\t|\n", __LINE__);\
    printf("\t%s\n", "!!!Look at Dump.txt!!!");\
    StackDump(lst);\
    abort();\
  }\
}\

#define assert_var(var) {\
  if (!isfinite((float)var))\
  {\
    printf("|\tAssertion failed.\t|\n");\
    printf("|\twhat: ListOk(%s)\t|\n", #var);\
    printf("|\tin: %s\t\t|\n", __FILE__);\
    printf("|\tfunction: %s\t|\n",  __PRETTY_FUNCTION__);\
    printf("|\ton: %d line\t\t|\n", __LINE__);\
    printf("\t%s\n", "!!!Look at Dump.txt!!!");\
    StackDump(lst);\
    abort();\
  }\
}\

struct List
{
  elem_t * data;
  int * next;
  int head;
  int size;
  int * prev;
  int tail;
};

void ListCtr(list_t * lst, int size)
{
  assert(lst);

  lst->data = (elem_t*)calloc(size, sizeof(elem_t));
  lst->next = (int*)calloc(size, sizeof(int));
  memset(lst->next, -1, size*sizeof(int));
  lst->next[0] = 0;
  lst->head = 1;
  lst->size = size;
  lst->prev = (int*)calloc(size, sizeof(int));
  memset(lst->prev, -1, size*sizeof(int));
  lst->prev[0] = 0;
  lst->tail = 1;

  assert_list(lst);
}

void InsertAfter(list_t * lst, int pos)
{
  assert_list(lst);


}

int main()
{

}
