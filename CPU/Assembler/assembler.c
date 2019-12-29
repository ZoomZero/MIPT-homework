#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

const char poison = 255;

char * fileread(const char * filename, int * pos)
{
  assert(filename != NULL);
  assert(pos != NULL);

  FILE * file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("%s\n", "Error reading file");
    return NULL;
  }

  fseek(file, 0, SEEK_END);

  *pos = ftell(file);
  char * text = (char*)calloc(*pos + 1, sizeof(char));

  fseek(file, 0, SEEK_SET);
  fread(text, sizeof(char), *pos, file);
  fclose(file);

  return text;
}

char ** command_separator(char * text, int pos, int * count, int * label_cnt)
{
  assert(text != NULL);
  assert(count != NULL);
  //printf("%d %d\n", *count, *label_cnt);
  for(int i = 0; i < pos; i++)
  {
    if(text[i] == '\n' || text[i] == ' ') (*count)++;
    if(text[i] == ':') (*label_cnt)++;
  }
  //printf("%d %d\n", *count, *label_cnt);
  char ** commands = (char**)calloc(*count + 1, sizeof(char*));

  commands[0] = &text[0];
  for (int i = 0, j = 1; i < pos; i++)
  {
    if (text[i] == '\n'  || text[i] == ' ')
    {
      text[i] = '\0';
      /*while(text[i] == '\n' || text[i] == ' ')
        i++;*/
      commands[j] = &text[++i];
      j++;
    }
  }
  return commands;
}

#define label_t struct labels

struct labels
{
  int pos;
  char * name;
};

void label_creator(label_t * label, int label_cnt, char ** commands, int comm_count)
{
  assert(label != NULL);
  assert(commands != NULL);
  //char * comm_el = *commands;
  //printf("%c", *comm_el);
  //const char* str1 = s1 + strlen(s1) - 1;
  for(int i = 0, j = 0; i < comm_count - 2; i++)
  {
    char * comm_el = *commands + strlen(*commands) - 1;
    //printf("%c", *comm_el);
    if(*comm_el == ':')
    {
      label[j].pos = i;
      label[j].name = strdup(*commands);
      label[j].name[strlen(*commands) - 1] = '\0';
      //printf("%d\n", strcmp(label[j].name, "start"));
      printf("lb -%s -%d\n", label[j].name, label[j].pos);
      j++;
      if(j != 0) i--;
    }
    *(commands++);
  }
}

int translator(char ** par, label_t label[], int label_cnt, int * binarycode, int comm_count)
{
  assert(par != NULL);
  assert(binarycode != NULL);

  for(int i = 0, p = 0; i < comm_count; i++)
  {
    printf("beg par = %s, p = %d\n", par[i], p);
    #define DEF_CMD(name, number, spec, code) if (strcmp(par[i], #name) == 0) { \
                                                  printf("camed\n");\
                                                  spec; \
                                                  printf("name in DEF_CMD = %s\n", #name); \
                                                  binarycode[p] = number;\
                                                  printf("%d\n", binarycode[p]);\
                                                  p++;\
                                              }

  #define DEF_LABEL {\
    for (int j = 0; j < label_cnt; j++) { \
                            if(strcmp(par[i], label[j].name) == 0) {\
                              binarycode[p] = label[j].pos;\
                              printf("camed lbl %s\n", label[j].name);\
                              p++;\
                         }\
                       }\
                       continue;\
                     }


  #define DEF_REG(name, number_reg, number) \
  if(strcmp(#name, par[i+1]) == 0) {\
    binarycode[p] = number;\
    p++;\
    binarycode[p] = number_reg;\
    printf("p-1 %d %d\np   %d %d\n", p-1, binarycode[p-1], p, binarycode[p]);\
    p++;\
    continue;\
  }


  #define SPEC(number) {\
    DEF_REG(ax, 1, number)\
    DEF_REG(bx, 2, number)\
    DEF_REG(cx, 3, number)\
    DEF_REG(dx, 4, number)\
    binarycode[p] = number - 1;\
    p++;\
    binarycode[p] = atoi(par[i+1]);\
    printf("p-1 %d %d\np   %d %d\n", p-1, binarycode[p-1], p, binarycode[p]);\
    p++;\
    continue;\
  }

    #include "../commands.h"

    #undef DEF_CMD
    #undef DEF_LABEL
    #undef DEF_REG
    #undef SPEC

  }

  return poison;
}

void label_clner(label_t * label, int label_cnt)
{
  for(int i = 0; i < label_cnt; i++) free(label[i].name);
}

void code_to_file(int * code, int count)
{
  FILE * result = fopen("comm.bin", "w");
  fwrite(code, sizeof(int), count, result);
  fclose(result);
}

int main(int argc, char const *argv[])
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
  struct labels label[label_count];

  label_creator(label, label_count, commands, comm_count);
  //for(int i = 0; i < comm_count; i++) printf("%s\n", commands[i]);
  //for(int i = 0; i < label_count; i++) printf("%s\n", label[i].name);
  int * binarycode = (int*)calloc(comm_count-label_count, sizeof(int));
  //printf("%s\n", commands[0]);
  /*printf("%s\n", *commands);
  *(commands++);
  printf("%s\n", *commands);*/
  translator(commands, label, label_count, binarycode, comm_count);


  for(int k = 0; k < comm_count - label_count; k++) printf("%d %d\n", k, binarycode[k]);
  code_to_file(binarycode, comm_count - label_count);

  label_clner(label, label_count);
  free(input);
  free(commands);
  free(binarycode);
  return 0;
}
