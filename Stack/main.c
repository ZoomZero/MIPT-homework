#include "stack.h"

int main()
{
  elem_t elem = 0;

  StackConstruct(&st, 3);

  printf("%s\n", "Enter stack element");
  scanf("%d", &elem);

  StackPush(&st, elem);

  printf("%d\n", StackPop(&st));

  StackDestruct(&st);
}
