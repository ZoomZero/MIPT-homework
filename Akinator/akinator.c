#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include "Tree/tree.h"
#include "stack.h"
#include "akinator.h"

int main(int argc, char * argv[])
{
  printf( "+-------------------------------+\n"
          "|\tAкинатор-имбицил\t|\n"
          "|\tCоздано ZoomZero\t|\n"
          "|\tВерсия 0.2 (beta)\t|\n"
          "+-------------------------------+\n");

  printf( "+---------------------------------------+\n"
          "|\tДружок-пирожок!\t\t\t|\n"
          "|\tЯ хочу сыграть с тобой в игру\t|\n"
          "|\tТы готов?\t\t\t|\n"
          "|\t\t[y] - да, [n]- нет\t|\n"
          "+---------------------------------------+\n");

  char ans = 0;
  scanf("%c", &ans);

  if (ans == 'n')
  {
    printf("\nАривидерчи, ёпта\n");
    return 0;
  }

  if (ans != 'y')
  {
    printf("\nТы что-то попутал, дружок-пирожок\nКлуб кожевенного мастерства два блока вверх\n");
    return 0;
  }

  printf("\nНу что-ж, настало моё время\n\n");

  tree MyTree;
  TreeCtr(&MyTree);
  ReadTree(&MyTree, argv[1]);

  while(ans != 'q')
  {
    printf( "+---------------------------------------+\n"
            "|\tЛя, маслину поймал\t\t|\n"
            "|\tЧего тебе надобно то, а?\t|\n"
            "|\t[a] - поясни, [s]- объясни\t|\n"
            "+---------------------------------------+\n");

    scanf(" %c", &ans);

    if (ans == 'a')
    {
      printf("\n");
      Node * f_node = Asker(MyTree.root);

      printf("Я угадал, ежжи?\n");
      printf("[y] - да, [n] - нет\n");

      scanf(" %c", &ans);

      if (ans == 'y') printf("Всё для тебя, брат!\n");
      else if (ans == 'n') NewMem(f_node);
      else
      {
        printf("...\n");
        break;
      }
    }
    else if (ans == 's')
    {
      printf("Сначала поговорим о награде\n");
      printf("Кого тебе найти надобно?\n");

      searcher(MyTree);
    }
    else printf("И чего ты этим добиваешься?\n");

    printf( "+---------------------------------------+\n"
            "|\tCыграем ещё разок, сладенький?\t|\n"
            "|\t\t[y] - давай, [q]- нет\t|\n"
            "+---------------------------------------+\n");

    scanf(" %c", &ans);

    if (ans != 'y')
    {
      printf("Давай, давай, кидай\n");
      break;
    }
  }

  printf("Иди своей дорогой, путник...\n");

  FILE * out_tree = fopen(argv[1], "w+");
  assert(out_tree);

  PrintTree(MyTree.root, out_tree);
  fclose(out_tree);

  digraph(MyTree.root, "digraph");

  TreeDeleter(&MyTree);
  return 0;
}
