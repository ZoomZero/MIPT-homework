#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <float.h>

const int INF_ROOTS = -1;
const double eps = 0.0001;
const int MIN_COEF = -3;
const int MAX_COEF = 3;

int is_zero(double a);
int sqrtroots(double a, double b, double c, double *x1, double *x2);
int linear_eq(double b, double c, double *x1);
int unittest();

int main(void)
{
  unittest();
  return 0;
}

int unittest()
{
  double x1 = 0, x2 = 0, res1 = 0, res2 = 0;
  FILE * result = fopen("testresult.txt", "w+");
  for(int a = MIN_COEF; a <= MAX_COEF; a++)
    for(int b = MIN_COEF; b <= MAX_COEF; b++)
      for(int c = MIN_COEF; c <= MAX_COEF; c++)
      {
        int count = sqrtroots(a, b, c, &x1, &x2);
        if (count == 2)
        {
          res1 = a*x1*x1 + b*x1 + c;
          res2 = a*x2*x2 + b*x2 + c;
          if (is_zero(res1) && is_zero(res2))
            fprintf(result, "%s %d%s %d%s %d%s %lg%s %lg\n", "Test complited successfully with coef a =", a, ", coef b =", b, ", coef c =", c, " and first root =", x1, ", second root =", x2);
          else
            fprintf(result, "%s %d%s %d%s %d%s %lg%s %lg\n", "Test failed with coef a =", a, ", coef b =", b, ", coef c =", c, " and first root =", x1, ", second root =", x2);
        }
        if (count == 1)
        {
          res1 = a*x1*x1 + b*x1 + c;
          if (is_zero(res1))
            fprintf(result, "%s %d%s %d%s %d%s %lg\n", "Test complited successfully with coef a =", a, ", coef b =", b, ", coef c =", c, " and root =", x1);
          else
            fprintf(result, "%s %d%s %d%s %d%s %lg\n", "Test failed with coef a =", a, ", coef b =", b, ", coef c =", c, " and root =", x1);
        }
        if (count == INF_ROOTS)
        {
            if (is_zero(a) && is_zero(b) && is_zero(c))
            fprintf(result, "%s %d%s %d%s %d%s\n", "Test complited with coef a =", a, ", coef b =", b, ", coef c =", c, " and infinite number of roots");
          else
            fprintf(result, "%s %d%s %d%s %d%s\n", "Test failed with coef a =", a, ", coef b =", b, ", coef c =", c, " and infinite number of roots");
        }
        if (count == 0)
        {
          double high = -b * b;
          high /= 4 * a;
          high += c;
          if (is_zero(a) && is_zero(b))
            fprintf(result, "%s %d%s %d%s %d%s\n", "Test complited with coef a =", a, ", coef b =", b, ", coef c =", c, " and no roots");
          else if ((a > 0 && high > 0) || (a < 0 && high < 0))
                fprintf(result, "%s %d%s %d%s %d%s\n", "Test complited with coef a =", a, ", coef b =", b, ", coef c =", c, " and no roots");
              else
                fprintf(result, "%s %d%s %d%s %d%s\n", "Test failed with coef a =", a, ", coef b =", b, ", coef c =", c, " and no roots");
        }
      }
  fclose(result);
  return 0;
}

int sqrtroots(double a, double b, double c, double *x1, double *x2)
{
  assert(isfinite(a));
  assert(isfinite(b));
  assert(isfinite(c));
  assert(x1 != NULL);
  assert(x2 != NULL);
  assert(x1 != x2);

  if (is_zero(a))
      return linear_eq(b, c, x1);

  if (c == 0)
  {
    *x2 = 0;
    return linear_eq(a, b, x1) + 1;
  }

  double d = b*b - 4*a*c;
  if (d < 0)
      return 0;

  d = sqrt(d);

  if (is_zero(d))
  {
    *x1 = -b/(2*a);
    return 1;
  }

  *x1 = (-b + d)/(2*a);
  *x2 = (-b - d)/(2*a);
  return 2;
}

int linear_eq(double b, double c, double *x1)
{
  assert(x1);

  if (is_zero(b)) return (is_zero(c)) ? INF_ROOTS : 0;
  else
  {
    *x1 = -c/b;
                  return 1;
  }
}

int is_zero(double a)
{
  return ((labs(a)) < eps);
}
