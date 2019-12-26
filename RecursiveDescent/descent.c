#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//---------------------------------
// G::= E#
// E::= T{[+-]T}*
// T::= S{[*/]S}*
// P::= '('E')' | N
// N::= [0-9]+
//---------------------------------

char * s;
const int MAX_NAME = 15;

int GetG();
int GetE();
int GetT();
int GetP();
int GetN();

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

int GetG(char * str)
{
  s = str;
  printf("in G %c\n", *s);
  int val = GetE();
  assert(*s == '#');
  return val;
}

int GetN()
{
  int val = 0;
  printf("in N %c\n", *s);
  if (*s >= '0' && *s <= '9')
  {
    val = *s - '0';
    s++;
  }
  printf("val in N = %d\n", val);
  printf("in N %c\n", *s);
  return val;
}

int GetP()
{
  printf("in P %c\n", *s);
  if (*s == '(')
  {
    *s++;
    int val = GetE();
    if (*s == ')') s++;
    return val;
  }
  else return GetN();
}

int GetT()
{
  printf("in T %c\n", *s);
  int val = 0;
  val = GetP(s);
  while (*s == '*' || *s == '/')
  {
    char op = *s;
    s++;
    int val2 = GetP();
    if (op == '*') val *= val2;
    else val /= val2;
  }
  return val;
}

int GetE()
{
  printf("in E %c\n", *s);
  int val = 0;
  val = GetT();
  printf("in E 2 %c\n", *s);
  printf("val in E = %d\n", val);
  while (*s == '+' || *s == '-')
  {
    printf("camed\n");
    char op = *s;
    s++;
    int val2 = GetT();
    if (op == '+') val += val2;
    else val -= val2;
  }
  return val;
}

int main()
{
  char * name = (char*)calloc(MAX_NAME, sizeof(char));
  scanf("%s", name);
  int pos = 0;
  char * expression = fileread(name , &pos);
  printf("%d\n", GetG(expression));
  return 0;
}
