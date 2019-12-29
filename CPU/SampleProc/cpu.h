#ifndef _CPU_H_
#define _CPU_H_

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

#endif
