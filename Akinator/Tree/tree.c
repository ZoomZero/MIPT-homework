#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

typedef int data_t;
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

  //assert_tree(name_tree);
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
    //printf("-0-%d\n", n->word);
    return n;
  }

  if(branch == 'L')
  {
    n->parent = position;
    n->left = NULL;
    n->right = NULL;
    position->left = n;
    name_tree->size++;
    //printf("-L-%d\n", n->word);
    return n;
  }

  if (branch == 'R')
  {
    n->parent = position;
    n->left = NULL;
    n->right = NULL;
    position->right = n;
    name_tree->size++;
    //printf("-R-%d\n", n->word);
    return n;
  }

  //assert_tree(name_tree);
  return NULL;
}

void TreeDeleter(tree * name_tree)
{
  assert_tree(name_tree);

  name_tree->size = 0;
  name_tree->root = NULL;

  assert_tree(name_tree);
}

void PrintTree(Node * n)
{
  //assert(n);

  if (!n)
  {
    printf(")\n");
    return;
  }

  //if(n->left == NULL && n->right != NULL) printf("*");*/
  printf("(\n%d\n", n->word);
  PrintTree(n->left);
  PrintTree(n->right);
}

void TreeDeleteElems(Node * n)
{
  if (!n) return;

  TreeDeleteElems(n->left);
  TreeDeleteElems(n->right);

  n->parent = NULL;
  n->left = NULL;
  n->right = NULL;
  //free(n->word);
  n->word = poison;

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
  printf("%dtt%d\n", pos, name_tree->size);

  if(pos != name_tree->size)                                 return false;

  return true;
}

void visit(Node * n, int(*func)(Node * n), data_t pos, Node * result)
{
  assert(n);
  assert(func);

  //if (strcmp(n->word, pos) == 0)
  if (n->word == pos)
  {
    func(n);
    result = n;
    return;
  }
  else if (result == NULL)
  {
    visit(n->left, func(n), pos, result);
    visit(n->right, func(n), pos, result);
  }

  return;
}

void Printer(Node * n)
{
  if(!n) return;

  printf("%d\n", n->word);

  if()
}

int main()
{
  data_t elem;
  scanf("%d", &elem);
  tree MyTree;
  TreeCtr(&MyTree);
  node_creator(&MyTree, MyTree.root, elem, 'L');
  MyTree.current_pos = node_creator(&MyTree, MyTree.root, 2, 'L');
  MyTree.current_pos = node_creator(&MyTree, MyTree.root, 3, 'R');
  //PrintTree(MyTree.root);
  Node search;
  visit(MyTree.root, Printer, 4, &search);
  TreeDeleteElems(MyTree.root);
}

/*digraph Treee {

}*/
