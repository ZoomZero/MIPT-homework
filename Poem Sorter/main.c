#include "sorter.h"

int main()
{
  setlocale (LC_ALL, "UTF-8");

  long int pos = 0;

  char* infilename = (char*)calloc(MAX_NAME, sizeof(char));
  printf("%s\n", "Enter in file name");
  scanf("%s", infilename);

  char * text = size_and_buffer(infilename, &pos);
  int count = counter(text, pos);
  char **letter = linepointers(text, count, pos);

  qsort(letter, count, sizeof(char*), mystrcmp);

  char* outfilename = (char*)calloc(MAX_NAME, sizeof(char));
  printf("%s\n", "Enter out file name");
  scanf("%s", outfilename);

  filewrite(outfilename, letter, count);
  qsort(letter, count, sizeof(char*), backstrcmp);
  fileadder(outfilename, letter, count);
  filecopy(infilename, outfilename);

  free(text);
  free(letter);
  free(infilename);
  free(outfilename);
  return 0;
}
