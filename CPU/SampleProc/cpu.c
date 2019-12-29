#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "stack.h"
#include "cpu.h"

int main()
{
  int comm_count = 0;
  int pos_number = 0;
  int programme_status = 0;

  data_t * code = readfile("comm.bin", &comm_count);

  stack_t st;
  StackConstruct(&st, 4);

  CPU(&pos_number, &programme_status, comm_count, code, &st);

  free(code);
  StackDestruct(&st);
}
