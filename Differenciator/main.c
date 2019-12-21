#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tree.h"
#include "descent.h"
#include "diff.h"

int main()
{
  int size;
  char * expression = readfile("exp", &size);
  tree Tree;
  tree diffTree;

  TreeCtr(&Tree);
  TreeCtr(&diffTree);
  Tree.root = GetG(&Tree, expression);
  TypeIdentify(&Tree, Tree.root);

  TeXPrint(NULL, NULL, TeX_start, 0);
  MoyaLubovKMatanu(StartDiff, 0);
  MoyaLubovKMatanu(InDiff, 0);

  diffTree.root = Differenciator(&diffTree, Tree.root->left);



  TeXPrint(NULL, NULL, TeX_finish, 0);
  FILE * pr = fopen("pr", "w+");
  PrintTree(Tree.root, pr);
  fclose(pr);
  //system("tex differ.tex");

  TreeDeleteElems(Tree.root);
  TreeDeleteElems(diffTree.root);
  TreeDeleter(&Tree);
  TreeDeleter(&diffTree);

  return 0;
}
