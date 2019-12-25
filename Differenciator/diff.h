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
    printf("%s\n", "Error reading file int f. readfile");
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
  assert(n != NULL);

  Node * new_node = NodeAlloc(t);
  new_node->word = strdup(n->word);
  new_node->type = n->type;
  new_node->parent = top;

  if(top != NULL)
  {
    if(branch == 'L')
    {
      top->left = new_node;
    }
    else if (branch == 'R')
    {
      top->right = new_node;
    }
  }

  if (n->left != NULL) TreeCopy(t, new_node, n->left, 'L');
  if (n->right != NULL) TreeCopy(t, new_node, n->right, 'R');

  return new_node;
}

/*Node * TreeCopy(tree * t, Node * top, Node * n, char branch)
{
  assert(t != NULL);
  assert(n != NULL);

  if (top != NULL)
  {
    char * per = top->word;
  }

  return _TreeCopy(t, top, n, branch);
}*/

Node * TypeNode(tree * t, int type, char * data, Node * l, Node * r)
{
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

Node * PrintTexDescent(tree * t, Node * n, FILE * file_TeX, int status, int * rec)
{
  assert(t != NULL);
  assert(n != NULL);
  (*rec)++;

  if (status == diff) fprintf(file_TeX, "\\left( ");
  if (n->word[0] == '/') fprintf(file_TeX, "\\frac{");
  if (strcmp("log", n->word) == 0) fprintf(file_TeX, "\\log_");
  if ((n->word[0] == '+') || (n->word[0] == '-'))
    if (n->parent != NULL)
    {
      if (strcmp("sqrt", n->parent->word) != 0)  fprintf(file_TeX, "\\left( ");
    }
    else fprintf(file_TeX, "\\left( ");

  if (n->left != NULL)
  {
    if (strcmp("sqrt", n->word) == 0) fprintf(file_TeX, "\\%s {", n->word);
    if ((n->right == NULL) && (strcmp("sqrt", n->word) != 0)) fprintf(file_TeX, "%s \\left( ", n->word);

    fprintf(file_TeX, "{");
    PrintTexDescent(t, n->left, file_TeX, nodiff, rec);
    fprintf(file_TeX, "}");

    if (n->right != NULL)
    {
      if ((n->word[0] != '/') && (strcmp("log", n->word) != 0)) fprintf(file_TeX, "%s ", n->word);
    }
    else if (strcmp("sqrt", n->word) != 0) fprintf(file_TeX, "\\right) ");
         else fprintf(file_TeX, "} ");
  }

  if (n->word[0] == '/')  fprintf(file_TeX, "}{");

  if (n->right != NULL)
  {
    if (strcmp("log", n->word) == 0) fprintf(file_TeX, "\\left( ");

    fprintf(file_TeX, "{");
    PrintTexDescent(t, n->right, file_TeX, nodiff, rec);
    fprintf(file_TeX, "}");

    if (strcmp("log", n->word) == 0) fprintf(file_TeX, "\\right) ");
  }


  if ((n->left == NULL) && (n->right == NULL)) fprintf(file_TeX, "%s ", n->word);


  if (n->word[0] == '/') fprintf(file_TeX, "}");
  if ((n->word[0] == '+') || (n->word[0] == '-'))
    if (n->parent != NULL)
    {
        if (strcmp("sqrt", n->parent->word) != 0) fprintf(file_TeX, "\\right) ");
    }
    else fprintf(file_TeX, "\\right) ");

    if (status == diff) fprintf(file_TeX, "\\right)' ");

  return n;
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
      fprintf(file_TeX, "\\author{By Borisenkov Ivan} \n\\title{Differentiator \\LaTeX{}} \n\\date{\\today}");
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

          break;

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

Node * Differenciator (tree * t, Node * n, int * rofl)
{
  assert(t != NULL);
  assert(n != NULL);

  (*rofl)++;
  printf("1 -%d\n", (*rofl)%3);
  printf("2 -%d\n", (*rofl)%6);

  Node * indif = NULL;

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
      Variable(rofl);\
      TeXPrint(t, n, TeX_print, diff);\
      TeXPrint(t, indif, TeX_print, enddiff);\
    }

    #include "func.h"

    #undef DIFF_
  }

  return indif;
}

void Variable(int * rofl)
{
  if((*rofl)%3 == 0 && (*rofl) != 0)
  {
    printf("eban\n");
    MoyaLubovKMatanu(InDiff, bread);
    (*rofl) = 4;
  }
  else if((*rofl)%6 == 0 && (*rofl) != 0)
  {
    printf("kek\n");
    MoyaLubovKMatanu(InDiff, bread2);
    (*rofl) = 1;
  }
  else
  {
    MoyaLubovKMatanu(InDiff, nodiff);
    (*rofl) = 0;
  }
}

#endif
