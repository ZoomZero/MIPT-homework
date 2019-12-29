#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "stack.h"

#define DEF_LABEL

#define DEF_CMD(name, number, spec, code) \
case number: {\
  code;\
  break;\
}\

enum ProgramStatus
{
    StartProgram = 0,
    EndProgram = 1,
    ErrorProgram = 2
};

typedef int data_t;

data_t reg[4] = {};

data_t * readfile(char * filename, int *pos)
{
  assert(filename != NULL);
  assert(pos != NULL);

  FILE * file = fopen(filename, "rb");
  if (file == NULL)
  {
    printf("%s\n", "Error reading file int f. readfile");
    return NULL;
  }

  fseek(file, 0, SEEK_END);

  *pos = ftell(file);
  data_t * text = (data_t*)calloc(*pos + 1, sizeof(data_t));

  fseek(file, 0, SEEK_SET);
  fread(text, sizeof(data_t), *pos, file);
  fclose(file);

  return text;
}

int Executor(int * pos_number, int * programme_status, data_t * command, stack_t * stk)
{
  FILE * log_file = fopen("Log.txt", "a+");
  fprintf(log_file, "~~~Command~~~\n");
  fprintf(log_file, "Position: %d\n", *pos_number);
  fprintf(log_file, "Command[%i] = %d\n", *pos_number, command[*pos_number]);
  fprintf(log_file, "~~~~~~~~~~~~~~\n");
  fclose(log_file);

  printf("pos = %d com = %d\n", *pos_number, command[*pos_number]);
  switch (command[*pos_number]) {

      #include "../commands.h"

  }
}

int CPU(int * pos_number, int * programme_status, int comm_count, data_t * command, stack_t * stk)
{
  assert(pos_number != NULL);
  assert(command != NULL);
  assert(stk != NULL);

  int status = 0;

  FILE * log_file = fopen("Log.txt", "w+");
  fclose(log_file);

  while(*pos_number < comm_count)
  {
    status = Executor(pos_number, programme_status, command, stk);

    if(status == EndProgram) return 0;
    if(status == ErrorProgram)
    {
      printf("Syntax error!!\nPosition [%d]\n", *pos_number);
      return ErrorProgram;
    }

    (*pos_number)++;
  }

  return poison;
}

int main()
{
  int comm_count = 0;
  int pos_number = 0;
  int programme_status = 0;

  /*char * filename = (char*)calloc(50, sizeof(char));
  printf("%s\n", "Enter in file name");
  scanf("%s", filename);*/

  data_t * code = readfile("comm.bin", &comm_count);
  //for(int i = 0; i < pos; i++) printf("%d\n", code[i]);

  stack_t st;
  StackConstruct(&st, 4);
  //StackDump(&st);
  int exit_code = CPU(&pos_number, &programme_status, comm_count, code, &st);

  free(code);
  StackDestruct(&st);
}
