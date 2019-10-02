#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h> //connect necessary libaries

const int INF_ROOTS = -1; //!< define special constant
const double eps = 0.0001; //!< define second special constant

//-----------------------------------------------------------------------
//! Solution of square equation ax^2+bx+c=0
//!
//! @param [in] a coefficient-a
//! @param [in] b coefficient-b
//! @param [in] c coefficient-c
//! @param [out] x1 first root
//! @param [out] x2 second root
//!
//! @return Number of roots
//!
//! @note If number of solutions is infinite the function returns INF_ROOTS
//------------------------------------------------------------------------

int sqrtroots(double a, double b, double c, double *x1, double *x2) // function counts roots and their quantity
{
  assert(isfinite(a)); //check if a enters class of double
  assert(isfinite(b)); //check if b enters class of double
  assert(isfinite(c)); //check if c enters class of double
  assert(x1 != NULL); //check if x1 has an adress in memory
  assert(x2 != NULL); //check if x2 has an adress in memory
  assert(x1 != x2); //check if adresses of x1 and x2 are not equal

  if (is_zero(a))
      return linear_eq(b, c, x1);

  if (is_zero(c))
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

//---------------------------------------------------------------------
//! Count root of linar euation
//!
//! @param [in] b coefficient-b or coefficient-a
//! @param [in] c coefficient-c or coefficient-c
//! @param [out] x1 root
//!
//! @return Number of roots
//!
//! @note If number of solutions is infinite the function returns INF_ROOTS
//---------------------------------------------------------------------
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

//----------------------------------------------------------------------
//! Compares variable of double class and zero
//!
//! @param [in] a variable of double class
//!
//! @return 1 if variable is equal to zero and 0 it variable is not equal
//----------------------------------------------------------------------
int is_zero(double a)
{
  return ((labs(a)) < eps);
}
