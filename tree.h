#include "hash.h"
typedef struct treenode {
  int type;
  HASHCELL *hash;
  struct treenode *child[4];
}TREENODE; 

int addChild(TREENODE *parent, int childPos, TREENODE *child);
TREENODE* getChild(TREENODE *parent, int childPos);