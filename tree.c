#include "tree.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
TREENODE root;
int init = 0;
void initTree()
{
  if (init == 1)
    return;
  root.type=0;
  root.hash=NULL;
  root.child[0] = NULL;
  root.child[1] = NULL;
  root.child[2] = NULL;
  root.child[3] = NULL;
  init = 1;
}

void initNode(TREENODE *node)
{
  node->type=0;
  node->hash=NULL;
  node->child[0] = NULL;
  node->child[1] = NULL;
  node->child[2] = NULL;
  node->child[3] = NULL;
}
int addChild(TREENODE *parent, int childPos, TREENODE *child)
{
  if(!init)
    initTree();
  if(parent->child[childPos]!=NULL) {
    free(parent->child[childPos]);
  }
  parent->child[childPos] = child;
  
}

TREENODE* getChild(TREENODE *parent, int childPos)
{
  if (!init)
    initTree();
  return(parent->child[childPos]);
}