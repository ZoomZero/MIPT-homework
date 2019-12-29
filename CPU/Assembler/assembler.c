#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "assembler.h"

int main(int argc, char const * argv[])
{
  if (argc < 2)
  {
    printf("%s\n", "No commands");
    return 1;
  }

  int pos = 0;
  char * input = fileread(argv[1], &pos);

  int comm_count = 0;
  int label_count = 0;
  char ** commands = command_separator(input, pos, &comm_count, &label_count);

  label_t label[label_count];
  label_creator(label, label_count, commands, comm_count);

  int * binarycode = (int*)calloc(comm_count - label_count, sizeof(int));

  translator(commands, label, label_count, binarycode, comm_count);
  for(int k = 0; k < comm_count - label_count; k++) printf("%d %d\n", k, binarycode[k]);
  code_to_file(binarycode, comm_count - label_count);

  label_clner(label, label_count);
  free(input);
  free(commands);
  free(binarycode);
  return 0;
}
