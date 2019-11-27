#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "tree.h"

int main()
{
  data_t elem;
  tree MyTree;
  TreeCtr(&MyTree);
  node_creator(&MyTree, MyTree.root, "yuppi", 'L');
  MyTree.current_pos = node_creator(&MyTree, MyTree.root, "da", 'L');
  node_creator(&MyTree, MyTree.current_pos, "manda", 'L');
  MyTree.current_pos = node_creator(&MyTree, MyTree.current_pos, "commenda", 'R');
  node_creator(&MyTree, MyTree.current_pos, "eshkere", 'R');
  MyTree.current_pos = node_creator(&MyTree, MyTree.root, "ejji", 'R');
  node_creator(&MyTree, MyTree.current_pos, "ti loh", 'R');
  PrintTree(MyTree.root, "rofl");
  //Node search;
  //visit(MyTree.root, Printer, 4, &search);
  TreeDeleteElems(MyTree.root);
}
