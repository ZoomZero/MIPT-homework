#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

const char poison = 255;
int p = 0;

#define label_t struct labels

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
  for(int i = 0, j = 0; i < comm_count - 1; i++)
  {
    char * comm_el = *commands + strlen(*commands) - 1;
    if(*comm_el == ':')
    {
      label[j].pos = i;
      label[j].name = (char*)calloc(strlen(*commands) - 1, sizeof(char));
      label[j].name = *commands;
      label[j].name[strlen(*commands) - 1] = '\0';
      //printf("%d\n", strcmp(label[j].name, "start"));
      printf("lb -%s -%d\n", label[j].name, label[j].pos);
      j++;
    }
    *(commands++);
  }
}

int translator(char * par, label_t label[], int label_cnt, char ** commands)
{
  //assert(commands != NULL);
  //assert(buffer != NULL);
  printf("beg par = %s\n", par);
  #define DEF_CMD(name, number, spec, code) if (strcmp(par, #name) == 0) { \
                                                spec; \
                                                printf("name in DEF_CMD = %s\n", #name); \
                                                return number; \
                                            }

  #include "../commands.h"

  #undef DEF_CMD

  /*for(int i = 0; i < comm_count; i++)
  {
    if(strcmp(commands[i], "push") == 0)
      if(strcmp(commands[i+1], "ax") == 0 || strcmp(commands[i+1], "ax") == 0 ||
        strcmp(commands[i+1], "ax") == 0 || strcmp(commands[i+1], "ax") == 0) buffer[i] = 12;
      else
      {
        buffer[i] = 1;
        //buffer[i++] = ...;
      }
    if(strcmp(commands[i], "pop") == 0)
    if(strcmp(commands[i+1], "ax") == 0 || strcmp(commands[i+1], "ax") == 0 ||
      strcmp(commands[i+1], "ax") == 0 || strcmp(commands[i+1], "ax") == 0) buffer[i] = 12;
    else
    {
      buffer[i] = 2;
      //buffer[i++] = ...;
    }
    if(strcmp(commands[i], "in") == 0) buffer[i] = 3;
    if(strcmp(commands[i], "out") == 0) buffer[i] = 4;
    if(strcmp(commands[i], "sum") == 0) buffer[i] = 5;
    if(strcmp(commands[i], "sub") == 0) buffer[i] = 6;
    if(strcmp(commands[i], "mul") == 0) buffer[i] = 7;
    if(strcmp(commands[i], "div") == 0) buffer[i] = 8;
    if(strcmp(commands[i], "sqrt") == 0) buffer[i] = 9;
    if(strcmp(commands[i], "end") == 0) buffer[i] = 10;
    if(strcmp(commands[i], "sin") == 0) buffer[i] = 11;
    if(strcmp(commands[i], "cos") == 0) buffer[i] = 12;
    if(strcmp(commands[i], "jmp") == 0) buffer[i] = 14;
    if(strcmp(commands[i], "ja") == 0) buffer[i] = 15;
    if(strcmp(commands[i], "jb") == 0) buffer[i] = 16;
    if(strcmp(commands[i], "je") == 0) buffer[i] = 17;
    for(int j = 0; j < label_cnt; j++)
    {
      //if(strcmp(buffer[i], label[j].name) == 0) buffer[i] = label[j].pos;
    }

  }*/

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
  //for(int i = 0; i < label_count; i++) printf("%s\n", label[i].name);
  int * binarycode = (int*)calloc(comm_count, sizeof(int));
  //printf("%s\n", commands[0]);
  /*printf("%s\n", *commands);
  *(commands++);
  printf("%s\n", *commands);*/
  //translator(commands, comm_count, binarycode, label_count);
  int t = 0;
  for( ; p < comm_count; p++)
  {
    int between = translator(commands[p], label, label_count, commands);
    printf("between = %d\n", between);
    if (between != -1 && between != 0)
    {
      binarycode[t] = between;
      t++;
    }
  }

  for(int k = 0; k < comm_count - label_count; k++) printf("%d\n", binarycode[k]);
  //code_to_file(binarycode, comm_count - label_count);

  //label_clner(label, label_count);*/
  free(input);
  free(commands);
  free(binarycode);
  return 0;
}
