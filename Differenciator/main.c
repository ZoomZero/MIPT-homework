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

  int rofl = 0;
  diffTree.root = Differenciator(&diffTree, Tree.root, &rofl);

  MoyaLubovKMatanu(PresentDiff, 1);
  TeXPrint(&Tree, Tree.root, TeX_print, diff);
  TeXPrint(&diffTree, diffTree.root, TeX_print, enddiff);
  MoyaLubovKMatanu(FinishDiff, 0);
  TeXPrint(&Tree, NULL, TeX_finish, 0);

  digraph(diffTree.root, "digraph");
  FILE * pr = fopen("tree_debug", "w+");
  PrintTree(diffTree.root, pr);
  fclose(pr);

  TreeDeleter(&Tree);
  TreeDeleter(&diffTree);

  return 0;
}
