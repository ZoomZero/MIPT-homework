#ifndef _TREE_H_
#define _TREE_H_

#define assert_tree(name_tree) {\
  if (!(TreeOk(name_tree)))\
  {\
    printf("|\tAssertion failed.\t|\n");\
    printf("|\twhat: TreeOk(%s)\t|\n", #name_tree);\
    printf("|\tin: %s\t\t|\n", __FILE__);\
    printf("|\tfunction: %s\t|\n",  __PRETTY_FUNCTION__);\
    printf("|\ton: %d line\t\t|\n", __LINE__);\
    abort();\
  }\
}\

typedef enum
{
  false,
  true
} bool;

typedef char* data_t;
const char poison = 255;

#define Node struct Node_t
#define tree struct TreeInfo

struct Node_t
{
  data_t word;
  Node * parent;
  Node * left;
  Node * right;
};

struct TreeInfo
{
  int size;
  Node * current_pos;
  Node * root;
};

int TreeCtr(tree * name_tree)
{
  assert(name_tree);

  name_tree->size = 0;
  name_tree->root = NULL;
  name_tree->current_pos = NULL;

  assert_tree(name_tree);
  return true;
}

Node * node_creator(tree * name_tree, Node * position, data_t info, char branch)
{
  assert_tree(name_tree);

  Node * n = (Node*)calloc(1, sizeof(Node));
  n->word = info;

  if (name_tree->size == 0)
  {
    name_tree->root = n;
    name_tree->size++;
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    return n;
  }

  if(branch == 'L')
  {
    n->parent = position;
    n->left = NULL;
    n->right = NULL;
    position->left = n;
    name_tree->size++;
    return n;
  }

  if (branch == 'R')
  {
    n->parent = position;
    n->left = NULL;
    n->right = NULL;
    position->right = n;
    name_tree->size++;
    return n;
  }

  assert_tree(name_tree);
  return NULL;
}

void TreeDeleter(tree * name_tree)
{
  assert_tree(name_tree);

  name_tree->size = 0;
  name_tree->root = NULL;

  assert_tree(name_tree);
}

void PrintTree(Node * n, FILE * out_tree)
{
  if (!n) return;

  fprintf(out_tree, "{\n");
  PrintTree(n->left, out_tree);

  fprintf(out_tree, "%s\n", n->word);
  PrintTree(n->right, out_tree);

  fprintf(out_tree, "}\n");
}

void TreeDeleteElems(Node * n)
{
  if (!n) return;

  TreeDeleteElems(n->left);
  TreeDeleteElems(n->right);

  n->parent = NULL;
  n->left = NULL;
  n->right = NULL;
  free(n->word);
  //n->word = poison;

  free(n);
}

void TreeElemOk(Node * n, int * i)
{
  if (n == NULL) return;
  assert(i);

  TreeElemOk(n->left, i);
  TreeElemOk(n->right, i);

  (*i)++;
}

int TreeOk(tree * name_tree)
{
  if (!name_tree)                                            return false;
  if (name_tree->size == 0 && name_tree->root ==  NULL)      return true;
  else if (name_tree->size == 0 || name_tree->root == NULL)  return false;

  int pos = 0;
  TreeElemOk(name_tree->root, &pos);

  if(pos != name_tree->size)                                 return false;

  return true;
}

#endif _TREE_H_
