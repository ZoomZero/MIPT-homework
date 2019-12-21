#ifndef _DESCENT_H_
#define _DESCENT_H_

Node * GetF(tree * t, const char * s, int * pos);
Node * GetN(tree * t, const char * s, int * pos);
Node * GetP(tree * t, const char * s, int * pos);
Node * GetS(tree * t, const char * s, int * pos);
Node * GetT(tree * t, const char * s, int * pos);
Node * GetE(tree * t, const char * s, int * pos);
Node * GetG(tree * t, const char * s);
Node * NodeCompile(tree * t, Node * n, Node * c, Node * p, char * s);

//---------------------------------
// G::= E#
// E::= T{[+-]E}*
// T::= S{[*/]T}*
// S::= P{[^]S}*
// P::= '('E')' | F | N
// F::= func
// N::= [0-9]+
//---------------------------------

Node * GetG(tree * t, const char * str)
{
  int pos = 0;
  Node * node = GetE(t, str, &pos);

  assert(node != NULL);
  printf("%c\n", str[pos]);
  assert(str[pos] == '\n');

  return node;
}

Node * GetF(tree * t, const char * s, int * pos)
{
  int i = 0;
  char str[WORD_LENGTH];

  while ('a' <= s[*pos] && s[*pos] <= 'z' && s[*pos] != '(')
  {
    str[i] = s[*pos];
    i++;
    (*pos)++;
  }
  str[i] = '\0';

  char * data = (char*)calloc(WORD_LENGTH, sizeof(char));
  memcpy(data, str, strlen(str));

  Node * n = NodeAlloc(t);
  n->word = data;

  return n;
}

Node * GetN(tree * t, const char * s, int * pos)
{
  int i = 0;
  char str[WORD_LENGTH];

  while ('0' <= s[*pos] && s[*pos] <= '9')
  {
    str[i] = s[*pos];
    i++;
    (*pos)++;
  }

  if (s[*pos] == '.')
  {
    str[i] = '.';
    i++;
    (*pos)++;
    while ('0' <= s[*pos] && s[*pos] <= '9')
    {
      str[i] = s[*pos];
      i++;
      (*pos)++;
    }
  }
  str[i] = '\0';

  char * data = (char*)calloc(WORD_LENGTH, sizeof(char));
  memcpy(data, str, strlen(str));

  Node * n = NodeAlloc(t);
  n->word = data;

  return n;
}

Node * GetP(tree * t, const char * s, int * pos)
{
  if (s[*pos] == '(')
  {
    (*pos)++;

    Node * n = GetE(t, s, pos);

    assert(s[*pos] == ')');
    (*pos)++;

    return n;
  }
  else if ('a' <= s[*pos] && s[*pos] <= 'z')
  {
    Node * n = GetF(t, s, pos);
    assert(n != NULL);

    if (s[*pos] == '(')
    {
      (*pos)++;

      n->left = GetE(t, s, pos);
      assert(s[*pos] == ')');

      (*pos)++;
      n->left->parent = n;
    }

    return n;
  }
  else return GetN(t, s, pos);
}

Node * GetS(tree * t, const char *s, int * pos)
{
  Node * node1 = GetP(t, s, pos);
  Node * node2 = NULL;
  Node * node3 = node1;

  char * op = (char*)calloc(2, sizeof(char));

  assert(node1);

  if (s[*pos] == '^')
  {
    op[0] = s[*pos];
    op[1] = '\0';
    (*pos)++;

    node2 = GetS(t, s, pos);

    assert(node2);

    node3 = NodeCompile(t, node1, node2, node3, op);
  }

  return node3;
}

Node * GetT(tree * t, const char * s, int * pos)
{
  Node * node1 = GetS(t, s, pos);
  Node * node2 = NULL;
  Node * node3 = node1;

  char * op = (char*)calloc(2, sizeof(char));

  if (s[*pos] == '*' || s[*pos] == '/')
  {
    op[0] = s[*pos];
    op[1] = '\0';
    (*pos)++;

    node2 = GetT(t, s, pos);

    assert(node2);

    node3 = NodeCompile(t, node1, node2, node3, op);
  }

  return node3;
}

Node * GetE(tree * t, const char * s, int * pos)
{
  Node * node1 = GetT(t, s, pos);
  Node * node2 = NULL;
  Node * node3 = node1;

  char * op = (char*)calloc(2, sizeof(char));

  if (s[*pos] == '+' || s[*pos] == '-')
  {
    op[0] = s[*pos];
    op[1] = '\0';
    (*pos)++;

    node2 = GetE(t, s, pos);

    assert(node2);

    node3 = NodeCompile(t, node1, node2, node3, op);
  }

  return node3;
}

Node * NodeCompile (tree * t, Node * n1, Node * n2, Node * n3, char * s)
{
  assert(t != NULL);
  assert(s != NULL);

  n3 = NodeAlloc(t);
  n3->word = s;
  n3->left = n1;
  n3->right = n2;
  n3->left->parent = n3;
  n3->right->parent = n3;

  return n3;
}

#endif
