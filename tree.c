#include "tree.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>



TREENODE* addChild(int type, HASHCELL *symbol, TREENODE *child1,TREENODE *child2,TREENODE *child3,TREENODE *child4)
{
  TREENODE *node = calloc(sizeof(TREENODE),1);
  node->type = type;
  node->symbol = symbol;
  node->child[0] = child1;
  node->child[1] = child2;
  node->child[2] = child3;
  node->child[3] = child4;
  return node;
  
}

void printTree(TREENODE *node)
{
    int numChild = 0;
    printf("(type id:%d",node->type);
    if(node->symbol!=NULL)
    {
      printf(" value: %s", node->symbol->key);
    }
    while(node->child[numChild]!=NULL && numChild<4)
      numChild++;
    int cursor=0;
    while(numChild>0)
    { 
      printf(", ");
      printTree(node->child[cursor]);
      numChild--;
      cursor++;
    }
    printf(")");
      
      
}