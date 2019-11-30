#include "stack.h"

struct Info
{
  int ax;
  int bx;
  int cx;
  int dx;
};

int * size_and_buffer(char * filename, long int *pos)
{
  assert(filename != NULL);
  assert(pos != NULL);

  FILE * file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("%s\n", "Error reading file int f. size_and_buffer");
    return NULL;
  }

  fseek(file, 0, SEEK_END);

  *pos = ftell(file);
  int * text = (int*)calloc(*pos + 1, sizeof(int));

  fseek(file, 0, SEEK_SET);
  fread(text, sizeof(int), *pos, file);
  fclose(file);
  return text;
}

int executor()
{
  #define DEF_CMD(name, number, spec, code) \
  case number: {\
    code;\
    break;\
  }\

    #include "../commands.h"


}

int main()
{
  int pos = 0;
  int pc = 0;

  char* filename = (char*)calloc(50, sizeof(char));
  printf("%s\n", "Enter in file name");
  scanf("%s", filename);

  int * code = size_and_buffer(filename, pos);
}
