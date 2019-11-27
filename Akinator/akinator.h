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
  scanf("%s\n", difference);

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
  //assert_tree(name_tree);

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
    while (!(buffer[*i] == '{' || buffer[*i] == '}') ) (*i)++;
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

#endif _AKINATOR_H_
