#ifndef SEMANTICH
#define SEMANTICH
#include "tree.h"

int semanticAnalyser(TREENODE *root);
void setTypes(TREENODE *node);
void checkDeclarations(void);
void checkIfVariableDeclared(TREENODE *node);
int verifyParams(TREENODE* node, TREENODE* function);
int getExpDataType(TREENODE *node);
void checkAllVariables(TREENODE * root);
int checkDataTypes (int firstType, int secType);

#endif
