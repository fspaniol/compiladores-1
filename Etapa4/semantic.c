#include "semantic.h"
#include "tree.h"


int semanticAnalyser(TREENODE *root) {

  
}

// Dado dois tipos de dado, retorna 0 se não são compatíveis.
// Se são, retorna o tipo de dado (por ex: float e int = float)
int checkDataTypes (int firstType, int secType){

	if(firstType == secType) 
		return firstType;

	if(firstType == DATATYPE_INT){
		switch(secType){
			case DATATYPE_CHAR:
				return DATATYPE_INT;
			case DATATYPE_FLOAT:
				return DATATYPE_FLOAT;
			default:
				return 0;
		}
	}
	else if (firstType == DATATYPE_CHAR){
		switch(secType){
			case DATATYPE_INT:
				return DATATYPE_INT;
			case DATATYPE_FLOAT:
				return DATATYPE_FLOAT;
			default:
				return 0;
		}
	}
	else if (firstType == DATATYPE_FLOAT){
		switch(secType){
			case DATATYPE_INT:
			case DATATYPE_CHAR:
				return DATATYPE_FLOAT;
			default:
				return 0;
		}
	}
	
	else if (firstType == DATATYPE_BOOL)
		return 0;
}

//Verifica o tipo de retorno de uma expressão
int checkExpType(TREENODE *exp){
	switch(exp->type){
		  	case TREE_EXP_OP_BINARY:
  				return checkExpType()
	}
}




//TEM QUE TESTAR... mas tá igual à do Professor
void checkDeclaractions(){
	int i = 0;
	HASHCELL *cell;
	for (i = 0; i < HASH_SIZE; i++)
		for(cell = table[i]; node; node = node->next)
			if(node->type == SYMBOL_IDENTIFIER)
				printf("ERRO: Variável %s não declarada!", node->key);
}

void setTypes(TREENODE *node){
	int i;
	if (!node) return;

	for(i = 0; i < 4; i++)
		setTypes(node->child[i]);
	
	if(node->type == TREE_DECLARATION_SCALAR){
		if(node->symbol->type != SYMBOL_IDENTIFIER){
			printf("ERRO: Redeclaração de \" %s \", na linha %d. Declarada na linha %d", node->symbol->key, getLineNumber(), node->symbol->lineNumber);
			exit(4);
		}
		else {
			node->symbol->type 		 = SYMBOL_SCALAR;
			node->symbol->lineNumber = getLineNumber();
		}
	}

	if((node->type == TREE_DECLARATION_VEC_LIT) || (node->type == TREE_DECLARATION_VEC_NOLIT)){
		if(node->symbol->type != SYMBOL_IDENTIFIER){
			printf("ERRO: Redeclaração de \" %s \", na linha %d. Declarada na linha %d", node->symbol->key, getLineNumber(), node->symbol->lineNumber);
			exit(4);
		}
		else {
			node->symbol->type  	 = SYMBOL_VECTOR;
			node->symbol->lineNumber = getLineNumber();
		}
	}

	if(node->type == TREE_DECLARATION_FUC){
		if(node->symbol->type != SYMBOL_IDENTIFIER){
			printf("ERRO: Redeclaração de \" %s \", na linha %d. Declarada na linha %d", node->symbol->key, getLineNumber(), node->symbol->lineNumber);
			exit(4);
		}
		else {
			node->symbol->type 		 = SYMBOL_FUNCTION;
			node->symbol->lineNumber = getLineNumber();
		}
	}
}


