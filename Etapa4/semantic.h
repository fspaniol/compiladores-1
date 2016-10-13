#ifndef SEMANTICH
#define SEMANTICH
#include "tree.h"

int semanticAnalyser(TREENODE *root);
void setTypes(TREENODE *node);
void checkDeclarations(void);
#endif
