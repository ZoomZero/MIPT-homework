#ifndef _AKINATOR_H_
#define _AKINATOR_H_

const int MAX_LINE = 20;

Node * Asker(Node * n)
{
  while (true)
  {
    if (n->left == NULL)
    {
      printf("Эй, эй, попридержи коней\n");
      printf("У меня есть информация, которая тебе нужна\n");
      printf("Я уверен, что это %s\n", n->word);
      return n;
    }

    printf("Это %s?\n", n->word);
    printf("[y] - да, [n] - нет\n");

    char ans = 0;
    scanf(" %c", &ans);

    if (ans == 'y') n = n->left;
    else if (ans == 'n') n = n->right;
    else
    {
      printf("Ненене, это так не работает\n");
      abort();
    }
  }
}

Node * NewMem(Node * n)
{
  assert(n);

  char * new_mem = (char*)calloc(MAX_LINE, sizeof(char));
  char * difference = (char*)calloc(MAX_LINE, sizeof(char));

  printf("Так, не понял. Кто же это?\n");
  scanf("%s", new_mem);

  printf("Чем отличается %s от %s?\n", new_mem, n->word);
  scanf(" %s", difference);

  Node * newm = calloc(1, sizeof(Node));
  Node * move = calloc(1, sizeof(Node));

  newm->parent = n;
  move->parent = n;
  n->left = newm;
  n->right = move;
  move->word = n->word;
  n->word = difference;
  newm->word = new_mem;

  newm->left = NULL;
  newm->right = NULL;
  move->left = NULL;
  move->right = NULL;
}

Node * TreeElemCtr(tree * name_tree, int * i, char * buffer)
{
  assert(name_tree);
  assert(i);
  assert(buffer);

  if (buffer[*i] == '{')
  {
    Node * node = (Node*)calloc(1, sizeof(Node));

    (*i) += (2 * sizeof(char));
    name_tree->size++;

    if (buffer[*i] == '{')
    {
      node->left = TreeElemCtr(name_tree, i, buffer);
      (node->left)->parent = node;
    }

    node->word = &buffer[*i];
    while (!(buffer[*i] == '{' || buffer[*i] == '}')) (*i)++;
    buffer[*i - 1] = '\0';
    node->word = strdup(node->word);

    if (buffer[*i] == '{')
    {
        node->right = TreeElemCtr(name_tree, i, buffer);
        (node->right)->parent = node;
    }

    if (buffer[*i] != '}')
    {
        printf("Проблема с буфером!\n");
        abort();
    }

    (*i) += (2 * sizeof(char));

    return node;
  }
  else
  {
    printf("Проблема с синтаксисом буфера!\n");
    abort();
  }

  assert_tree(name_tree);
}

int ReadTree(tree * Atree, char * filename)
{
  assert_tree(Atree);
  assert(filename);

  FILE * Etree = fopen(filename, "r");
  if (Etree == NULL)
  {
    printf("%s\n", "Error reading file");
    return false;
  }

  fseek(Etree, 0, SEEK_END);

  int pos = ftell(Etree);
  char * elems = (char*)calloc(pos + 1, sizeof(char));

  fseek(Etree, 0, SEEK_SET);
  fread(elems, sizeof(char), pos, Etree);
  fclose(Etree);

  int i = 0;
  Atree->root = TreeElemCtr(Atree, &i, elems);

  free(elems);
  assert_tree(Atree);
}

void visit(Node * n, char * obj, Node ** res)
{
 if (!n) return;

 if (strcmp(n->word, obj) == 0) *res = n;

 visit(n->left, obj, res);
 visit(n->right, obj, res);
}

void searcher(Node * n)
{
  printf( "+---------------------------------------+\n"
          "|\tА мне за это что? Ладно...\t|\n"
          "|\tКого тебе найти надобно?\t|\n"
          "+---------------------------------------+\n");

  char * mem = (char*)calloc(MAX_LINE, sizeof(char));
  scanf(" %s", mem);

  stack_t st;
  StackConstruct(&st, 4);

  Node * pos = NULL;
  visit(n, mem, &pos);

  if (pos == NULL)
  {
    printf("Таких не знаем\n");
    return;
  }

  while (pos != NULL)
  {
    StackPush(&st, pos->word);
    pos = (pos->parent);
  }

  pos = n;

  printf("Это ");
  while (st.size > 1)
  {
    if (strcmp(pos->left->word, st.data[st.size - 2]) == 0)
    {
      printf("%s, ", pos->word);
      pos = pos->left;
    }
    else
    {
      printf("не %s, ", pos->word);
      pos = pos->right;
    }
    StackPop(&st);
  }
  printf(".\n");
  StackDestruct(&st);
}

void root_graph(Node * n, FILE * f_dot)
{
  if (n->left != NULL)
  {
    fprintf(f_dot, "\t\"%s\"\n\t\t\"%s\"->\"%s\" [label = \"Yes\"]\n\n", n->word, n->word, n->left->word);
    root_graph(n->left, f_dot);
  }
  if (n->right != NULL)
  {
    fprintf(f_dot, "\t\"%s\"\n\t\t\"%s\"->\"%s\" [label = \"No\"]\n\n", n->word, n->word, n->right->word);
    root_graph(n->right, f_dot);
  }
}

void digraph(Node * n, char * filename)
{
  assert(n);
  assert(filename);

  FILE * f_dot = fopen(filename, "w+");
  assert(f_dot);

  fprintf(f_dot, "digraph {\n");
  fprintf(f_dot, "\t\tnode [shape=\"circle\", style=\"filled\", fillcolor=\"blue\", fontcolor=\"#FFFFFF\", margin=\"0.01\"];\n");
  fprintf(f_dot, "\t\tedge [style=\"dashed\"];\n\n");

  root_graph(n, f_dot);

  fprintf(f_dot, "}");
  fclose(f_dot);

  system("dot -Tjpg digraph -o tree.jpg");
}

#endif
