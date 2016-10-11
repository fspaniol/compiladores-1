#ifndef SEMANTICH
#define SEMANTICH

int semanticAnalyser(TREENODE *root);
void setTypes(TREENODE *node);
void checkDeclarations(void);
#endif