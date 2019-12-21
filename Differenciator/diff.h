#ifndef _DIFF_H_
#define _DIFF_H_

enum TeXPos
{
  TeX_start = 1,
  TeX_print = 2,
  TeX_finish = 3
};

enum DiffStatus
{
  diff = 1,
  nodiff = 2,
  enddiff = 3,
  bread = 4,
  bread2 = 5
};

enum TeXPhrase
{
  StartDiff = 1,
  FinishDiff = 2,
  ShortDiff = 3,
  PresentDiff = 4,
  InDiff = 5
};

enum NodeTypes
{
  symbol_t = 1,
  value_t = 2,
  op_t = 3,
  const_t = 4
};

char * readfile(char * filename, int * pos)
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

Node * TreeCopy(tree * t, Node * top, Node * n, char branch)
{
  assert(t != NULL);
  assert(top != NULL);

  printf("going to alloc in TreeCopy\n");
  Node * new_node = NodeAlloc(t);
  new_node->word = strdup(n->word);
  new_node->type = n->type;
  new_node->parent = top;

  if(top!= NULL)
  {
    if(branch == 'L') top->left = new_node;
    else if (branch == 'R') top->right = new_node;
  }

  if (n->left != NULL) TreeCopy(t, new_node, n->left, 'L');
  if (n->right != NULL) TreeCopy(t, new_node, n->right, 'R');

  printf("copying...\n");
  Printtt(new_node);

  return new_node;
}

Node * TypeNode(tree * t, int type, char * data, Node * l, Node * r)
{
  printf("data in node %s\n", data);
  printf("goint to alloc in TypeNode\n");
  Node * n = NodeAlloc(t);

  if(type == op_t)
  {
    n->left = l;
    n->right = r;

    if(l != NULL) l->parent = n;
    if(r != NULL) r->parent = n;

    n->type = op_t;
    n->word = strdup(data);
  }
  else
  {
    n->left = NULL;
    n->right = NULL;
    n->type = type;
    n->word = strdup(data);
  }

  return n;
}

void PrintTexDescent(tree * t, Node * n, FILE * file_TeX, int status, int * rec)
{

}

void TeXPrint(tree * t, Node * n, int pos, int status)
{
  switch (pos)
  {
    case TeX_start:
    {
      FILE * file_TeX = fopen("differ.tex","w+");
      assert(file_TeX != NULL);

      fprintf(file_TeX, "\\documentclass[a4paper,12pt]{article}\n");
      fprintf(file_TeX, "\\usepackage[T2A]{fontenc}\n\\usepackage[utf8]{inputenc}\n\\usepackage[english,russian]{babel}\n");
      fprintf(file_TeX, "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools}\n");
      fprintf(file_TeX, "\\author{By Ivan Borisenkov} \n\\title{Differentiator \\LaTeX{}} \n\\date{\\today}");
      fprintf(file_TeX, "\\begin{document}\n\\maketitle\n\\newpage");
      fclose(file_TeX);

      break;
    }
    case TeX_print:
    {
      assert(t != NULL);
      assert(n != NULL);

      int recurs = 0;
      FILE * file_TeX = fopen("differ.tex", "a+");
      assert(file_TeX != NULL);

      fprintf(file_TeX, "\\begin{equation}\n");
      PrintTexDescent(t, n, file_TeX, status, &recurs);

      if (status != enddiff) fprintf(file_TeX, "=");

      fprintf(file_TeX, "\n\\end{equation}\n");
      fclose(file_TeX);

      break;
    }
    case TeX_finish:
    {
      FILE *file_TeX = fopen("differ.tex", "a+");
      assert(file_TeX != NULL);

      fprintf(file_TeX, "\\end{document}\n");
      fclose(file_TeX);

      break;
    }

    default:  break;
  }
}

void MoyaLubovKMatanu(int phrase, int status)
{
  FILE * file_TeX = fopen("differ.tex", "a+");
  assert(file_TeX != NULL);

  switch (phrase)
  {
    case StartDiff:
      fprintf(file_TeX, "\nПрезренный, тебе что, неизвестно, как найти такую производную?\n");
      fprintf(file_TeX, "Так уж и быть, я найду её для тебя. Слишком изи фор ми.\n");

      break;

    case FinishDiff:
      fprintf(file_TeX, "Видишь, презренный. Я же говорил, что это проще простого.\n");
      fprintf(file_TeX, "А теперь вон с глаз моих!\n");

      break;

    case InDiff:
      if(status == 0) fprintf(file_TeX, "Чтобы ты хотя бы что-то понял, я рассмотрю производные функции по частям\n");
      else switch (status)
      {
        case diff:
          fprintf(file_TeX, "Понимаешь ли ты, что это изи. Состатб+лежатб, ща всё сделаем\n");

          break;

        case nodiff:
          fprintf(file_TeX, "Очевидно, что,\n");

          break;

        case enddiff:
          fprintf(file_TeX, "Оставив некоторые преобразования на додумку читателю, запишем,\n");

          break;

        case bread:
          fprintf(file_TeX, "Как же мне надоело заниматься такой фигнёй. Какие блин производные я создан для чего-то большего!\n");

        case bread2:
          fprintf(file_TeX, "Кстати, а я рассказвал тебе сказку о паравозике, который смог?\n");

          break;

        default: break;
      }

      break;

    case ShortDiff:
      fprintf(file_TeX, "Произведём элементарные преобразования.\n");

      break;

    case PresentDiff:
      fprintf(file_TeX, "Вот так это выглядит, презренный.\n");

      break;

    default: break;
  }

  fclose(file_TeX);
}

void TypeIdentify(tree * diffTree, Node * n)
{
  if (!n) return;

  bool not_finished = true;

  #define DIFF_(Name, Type, Declaration)\
  if (strcmp(#Name, n->word) == 0) {\
    n->type = Type;\
    not_finished = false;\
  }

  #include "func.h"

  #undef DIFF_

  if (not_finished)
  {
    if ('0' <= (n->word[0]) && (n->word[0]) <= '9')
    {
      n->type = value_t;
    }
    else if ((strcmp("pi", n->word) == 0) || (strcmp("e", n->word) == 0) || (strcmp("π", n->word) == 0))
    {
      n->type = const_t;
    }
    else
    {
      n->type = symbol_t;
    }
  }


  TypeIdentify(diffTree, n->left);
  TypeIdentify(diffTree, n->right);
}

Node * Differenciator (tree * t, Node * n)
{
  assert(t != NULL);
  assert(n != NULL);

  printf("word in n %s\n", n->word);
  Printtt(n);
  printf("\n");
  Node * indif; //= NULL;

  if (n->type == value_t || n->type == const_t)
  {
    char * dc = (char*)calloc(2, sizeof(char));
    assert(dc != NULL);

    memcpy(dc, "0", 2);

    indif = TypeNode(t, value_t, dc, NULL, NULL);
    assert(indif != NULL);
  }

  if(n->type == symbol_t)
  {
    char * dx = (char*)calloc(2, sizeof(char));
    assert(dx != NULL);

    memcpy(dx, "1", 2);

    indif = TypeNode(t, value_t, dx, NULL, NULL);
    assert(indif != NULL);
  }

  if(n->type == op_t)
  {
    #define DIFF_(Name, Type, Declaration)\
    if (strcmp(#Name, n->word) == 0) {\
      indif = Declaration;\
      assert(indif != NULL);\
      MoyaLubovKMatanu(InDiff, nodiff);\
      TeXPrint(t, n, TeX_print, diff);\
      TeXPrint(t, indif, TeX_print, enddiff);\
    }

    #include "func.h"

    #undef DIFF_
  }

  return indif;
}

#endif
