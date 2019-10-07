#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <locale.h>

const int MAX_NAME = 15; //!< define max number of cymbols for filename

//------------------------------------------------------------------------
//! Compare lines by their ends
//!
//! @param [in] line1 first line
//! @param [in] line2 second line
//!
//! @return 1 if first line is bigger, -1 if second line is bigger and  0 if lines are equal
//------------------------------------------------------------------------
int mystrcmp(const void* line1, const void* line2)
{
  assert(line1 != NULL);
  assert(line2 != NULL);

  const char* s1 = *(char**) line1;
  const char* s2 = *(char**) line2;

  if (s1[0] == 0 && s2[0] == 0) return 0;
  if (s1[0] == 0) return -1;
  if (s2[0] == 0) return 1;

  const char* str1 = s1;
  const char* str2 = s2;

  for ( ; *(str1) && *(str2); str1++, str2++)
  {
    while (*str1 && !isalnum(*str1)) str1++;
    while (*str2 && !isalnum(*str2)) str2++;
    char c1 = tolower(*str1);
    char c2 = tolower(*str2);
    if (c1 > c2)
      return 1;
    else if (c1 < c2)
      return -1;
  }

  if(!*str1 &&  *str2) return -1;
  if(!*str2 &&  *str1) return 1;
  return 0;
}

//------------------------------------------------------------------------
//! Compare lines by their ends
//!
//! @param [in] line1 first line
//! @param [in] line2 second line
//!
//! @return 1 if first line is bigger, -1 if second line is bigger and  0 if lines are equal
//------------------------------------------------------------------------
int backstrcmp(const void* line1, const void* line2)
{
  assert(line1 != NULL);
  assert(line2 != NULL);

  const char* s1 = *(char**) line1;
  const char* s2 = *(char**) line2;

  if (s1[0] == 0 && s2[0] == 0) return 0;
  if (s1[0] == 0) return -1;
  if (s2[0] == 0) return 1;

  const char* str1 = s1 + strlen(s1) - 1;
  const char* str2 = s2 + strlen(s2) - 1;

  for ( ; *(str1) && *(str2); str1--, str2--)
  {
    while (*str1 && !isalnum(*str1)) str1--;
    while (*str2 && !isalnum(*str2)) str2--;
    char c1 = tolower(*str1);
    char c2 = tolower(*str2);
    if (c1 > c2)
      return 1;
    else if (c1 < c2)
      return -1;
  }

if(!*str1 &&  *str2) return -1;
if(!*str2 &&  *str1) return 1;
return 0;
}

//------------------------------------------------------------------------
//! Count number of lines in poem
//!
//! @param [in] text text of poem
//! @param [in] pos number of symbols in text
//!
//! @return number of lines in text
//!
//! @note If number of lines is 0 print File is empty and return 0
//------------------------------------------------------------------------
int counter(char text[], long int pos)
{
  assert(text != NULL);

  int count = 0;

  for (int i = 0; (i < pos) && (text [i] != '\0'); ++i)
  {
    if (text[i] == '\n')
    {
      while(text[i] == '\n')
        i++;
      ++count;
      i++;
    }
  }

  if (count == 1 && text[0] == '\n')
  {
    printf("%s\n", "File is empty");
    exit (1);
  }
  else return count;
}

//------------------------------------------------------------------------
//! Count number of symbols in file and creates array of text from file
//!
//! @param [in] filename name of input file
//! @param [out] pos number of symbols in text
//!
//! @return array of text
//------------------------------------------------------------------------
char* size_and_buffer(char * filename, long int *pos)
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
  char * text = (char*)calloc(*pos + 1, sizeof(char));

  fseek(file, 0, SEEK_SET);
  fread(text, sizeof(char), *pos, file);
  fclose(file);
  return text;
}

//------------------------------------------------------------------------
//! Create pointers on the start of the eash line on array and change \n to \0
//!
//! @param [in] text text of poem
//! @param [in] count number of lines in array
//! @param [in] pos number of symbols in text
//!
//! @return array of pointers
//------------------------------------------------------------------------
char** linepointers(char *text, int count, int pos)
{
  assert(text != NULL);

  char **letter = (char**)calloc(count + 5, sizeof(char*));

  for (int i = 0, j = 0; i < pos; i++)
  {
    if (text[i] == '\n')
    {
      text[i] = '\0';
      i++;
      while(text[i] == '\n')
        i++;
      letter[j] = &text[i];
      j++;
    }
  }
  return letter;
}

//------------------------------------------------------------------------
//! Write array in new file
//!
//! @param [in] filename name of output file
//! @param [in] letter array of text
//! @param [in] count number of lines in array
//!
//! @return nothing
//------------------------------------------------------------------------
void filewrite(char* filename, char** letter, int count)
{
  assert(filename != NULL);
  assert(letter != NULL);

  FILE * result = fopen(filename, "w+");
  for(int i = 0; i < count; i++)
  {
    if (*letter[i] == '\0') continue;
    fprintf(result, "%s\n", letter[i]);
  }
  fclose(result);
}

//------------------------------------------------------------------------
//! Adds new array in file
//!
//! @param [in] filename name of output file
//! @param [in] letter array of text
//! @param [in] count number of lines in array
//!
//! @return nothing
//------------------------------------------------------------------------
void fileadder(char* filename, char** letter, int count)
{
  assert(filename != NULL);
  assert(letter != NULL);

  FILE * result = fopen(filename, "a");
  fprintf(result, "\n");
  for(int i = 0; i < count; i++)
  {
    if (*letter[i] == '\0') continue;
    fprintf(result, "%s\n", letter[i]);
  }
  fprintf(result, "\n");
  fclose(result);
}

//------------------------------------------------------------------------
//! Copy test from file to another file
//!
//! @param [in] filename1 name of output file
//! @param [in] filename2 name of input file
//!
//! @return nothing
//------------------------------------------------------------------------
void filecopy(char* filename1, char* filename2)
{
  assert(filename1 != NULL);
  assert(filename2 != NULL);

  FILE * file = fopen(filename1, "r");

  assert(file != NULL);

  fseek(file, 0, SEEK_END);

  int pos = ftell(file);
  char * text = (char*)calloc(pos + 1, sizeof(char));

  fseek(file, 0, SEEK_SET);
  fread(text, sizeof(char), pos, file);
  free(text);
  fclose(file);

  FILE * result = fopen(filename2, "a");
  fputs(text, result);
  fclose(result);
}

//------------------------------------------------------------------------
//! Copy test from file to another file
//!
//! @param [in] filename1 name of output file
//! @param [in] filename2 name of input file
//!
//! @return nothing
//------------------------------------------------------------------------
void filecopy2(char* filename1, char* filename2)
{
  char * line = (char*)calloc(MAX_NAME*3, sizeof(char));
  line[0] = 'c';
  line[1] = 'a';
  line[2] = 't';
  line[3] = ' ';
  char oper[4] = {" >> "};
  strcat(line, filename1);
  printf("%s\n", line);
  strcat(line, oper);
  strcat(line, filename2);
  system(line);
  free(line);
}
