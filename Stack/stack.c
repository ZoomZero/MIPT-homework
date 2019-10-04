#include "stack.h"

int main()
{
  //всякие указатели
  elem_t elem = 0;

  StackConstruct(&st);

  printf("%s\n", "Enter stack element");
  scanf("%d", &elem);

  StackPush(&st, elem);

  printf("%d\n", StackPop(&st));

  //StackDestruct(&st);
}
