#include "equationsolver.h"

int main(void)
{
  double a = 0, b = 0, c = 0;

  printf("%s", "Enter the coefficients: ");
  scanf("%lg %lg %lg", &a, &b, &c);

  double x1 = 0, x2 = 0;
  int solution = sqrtroots(a, b, c, &x1, &x2);

  switch (solution)
  {
    case 0:
      printf("%s\n", "Equation doesn't have roots");
      break;

    case 1:
      printf("%s %lg\n", "Equation has one root:", x1);
      break;

    case 2:
      printf("%s %lg %s %lg\n", "Equation has two roots:", x1, "and", x2);
      break;

    case INF_ROOTS:
      printf("%s\n", "Number of solutions is infinite");
      break;

    default:
      printf("%s\n", "Error");
      return 1;
  }
  return 0;
}
