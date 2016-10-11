#include "semantic.h"
#include "tree.h"


int semanticAnalyser(TREENODE *root) {

  
}


void setTypes(TREENODE *node){
	int i;
	if (!node) return;

	for(i = 0; i < 4; i++)
		setTypes(node->child[i]);
	
	if(node->type == TREE_DECLARATION_SCALAR){
		if(node->symbol->type != SYMBOL_LIT_IDENTIFIER){
			printf("ERRO");

		}
		else {
			node->symbol->type 		 = SYMBOL_SCALAR;
			node->symbol->lineNumber = getLineNumber();
		}
	}
	
	if(node->type == TREE_DECLARATION_FUC){
		if(node->symbol->type != SYMBOL_LIT_IDENTIFIER){
			printf("ERRO");

		}
		else {
			node->symbol->type 		 = SYMBOL_FUNCTION;
			node->symbol->lineNumber = getLineNumber();
		}
	}
}