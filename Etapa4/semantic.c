#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"
#include "tree.h"
#include "y.tab.h"

int semanticAnalyser(TREENODE *root) {
    setTypes(root);

}

//checks compatibility of two datatypes 
//if they are incompatible, returns -1
//if they are equivalent, returns 0 
//if they are compatible but not equivalent (float, int) returns datatype
int checkDataTypes (int firstType, int secType) {

    if(firstType == secType)
        return firstType;

    if(firstType == DATATYPE_INT) {
        switch(secType) {
        case DATATYPE_CHAR:
            return 0;
        case DATATYPE_FLOAT:
            return DATATYPE_FLOAT;
        default:
            return 0;
        }
    }
    else if (firstType == DATATYPE_CHAR) {
        switch(secType) {
        case DATATYPE_INT:
            return 0;
        case DATATYPE_FLOAT:
            return DATATYPE_FLOAT;
        default:
            return 0;
        }
    }
    else if (firstType == DATATYPE_FLOAT) {
        switch(secType) {
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

void checkIfVariableDeclared(TREENODE *node) {
    if(node->symbol->type == SYMBOL_IDENTIFIER) {
        //variable is not declared
        printf("Error. variable %s referenced before declaration on line %d", node->symbol->key, node->linenumber );
        exit(-4);
    }

}

int getLiteralType(TREENODE *node) {
  if(node->type == TREE_CHAR)
    return(DATATYPE_CHAR);
  if(node->type == TREE_INTEGER)
    return(DATATYPE_INT);
  if(node->type == TREE_TRUE || node->type == TREE_FALSE)
    return(DATATYPE_BOOL);
  printf("Unknown literal datatype: node type: %d\n", node->type);
  exit(-4);
  
}

//returns -1 if node is not an expression.
int getExpDataType(TREENODE *node) {
    if(node->type == TREE_IDENTIFIER) {
        //vectors have to indexed
        if(node->symbol->type == SYMBOL_IDENTIFIER_VECTOR) {
            printf("Error. Vectors reference must be indexed. Line %d\n", node->linenumber);
            exit(-4);
        }
        //functions must be called
        if(node->symbol->type == SYMBOL_IDENTIFIER_FUNCTION) {
            printf("Error. Function reference must be function call. Line %d\n", node->linenumber);
            exit(-4);
        }
        return(node->symbol->datatype);
    } else if(node->type == TREE_CHAR)
        return(DATATYPE_CHAR);
    else if(node->type == LIT_INTEGER)
        return(DATATYPE_INT);
    else if(node->type == TREE_EXP_VEC_INDEX) {
        //expression is vector[exp]
        //check if variable is declared
        checkIfVariableDeclared(node->child[0]);
        //check if variable is a vector
        if(node->symbol->type != SYMBOL_IDENTIFIER_VECTOR) {
            printf("Error. Only vectors can be indexed. Line %d\n", node->linenumber);
            exit(-4);
        }
        //check if index is an expression
        int datatype = getExpDataType(node->child[1]);
        if(datatype != DATATYPE_INT ) {
            //not an expression
            printf("Error. vector has to be indexed by integer. Line %d\n", node->linenumber);
            exit(-4);
        }
        return(node->symbol->datatype);

    }




    //exp->type ==  || TREE_EXP_OP_BINARY || TREE_EXP_BRACKET_ENCLOSURE || TREE_EXP_FUNC_CALL )
}



void setTypes(TREENODE *node) {
    int i;
    if(node == NULL)
      printf("node is null\n");
    printf("node type = %d\n", node->type);
  
    for(i = 0; i < 4; i++)
      if(node->type == TREE_DECLARATION)
	if(node->child[i] != NULL)
	  setTypes(node->child[i]);
    

    //check scalar declarations
    if(node->type == TREE_DECLARATION_SCALAR) {
      printf("startsca\n");
	//first child of TREE_DECLARATION_SCALAR is datatype, second is identifier
	//checks if identifies has already been declared
        if(node->child[1]->symbol->type != SYMBOL_IDENTIFIER) {
            printf("ERRO: Redeclaração de \" %s \", na linha %d. Declarada na linha %d", node->child[1]->symbol->key, node->linenumber, node->child[1]->symbol->lineNumber);
            exit(-4);
        }
        else {
            node->child[1]->symbol->type = SYMBOL_IDENTIFIER_SCALAR;
            node->child[1]->symbol->lineNumber = node->linenumber;
            if(node->child[0]->type == TREE_KW_INTEGER)
                node->child[1]->symbol->datatype = DATATYPE_INT;
            else if (node->child[0]->type == TREE_KW_CHAR)
                node->child[1]->symbol->datatype = DATATYPE_CHAR;
            else if (node->child[0]->type == TREE_KW_FLOAT)
                node->child[1]->symbol->datatype = DATATYPE_FLOAT;
            else if (node->child[0]->type == TREE_KW_BOOL)
                node->child[1]->symbol->datatype = DATATYPE_BOOL;
        }
        
        //checks data type of the initialized value
        int datatype = checkDataTypes(node->child[1]->symbol->datatype, getLiteralType(node->child[2]));
        if(datatype < 0) {
	  //initialized with the incompatible
	  printf("Error incompatible types on line %d\n", node->linenumber);
	  
	}
        printf("endsca\n");
    }
    //check vector declarations
    if((node->type == TREE_DECLARATION_VEC_LIT) || (node->type == TREE_DECLARATION_VEC_NOLIT)) {
      printf("startvec\n");
        if(node->child[1]->symbol->type != SYMBOL_IDENTIFIER) {
            printf("ERRO: Redeclaração de \" %s \", na linha %d. Declarada na linha %d", node->child[1]->symbol->key, node->linenumber, node->child[1]->symbol->lineNumber);
            exit(4);
        }
        else {
	    if(getLiteralType(node->child[2])!= DATATYPE_INT) {
	      printf("ERROR Vector cannot be initialized with an index of type diffent than Integer. Line %d\n", node->linenumber);
	    }
            node->child[1]->symbol->type = SYMBOL_IDENTIFIER_VECTOR;
            node->child[1]->symbol->lineNumber = node->linenumber;
            if(node->child[0]->type == TREE_KW_INTEGER)
                node->child[1]->symbol->datatype = DATATYPE_INT;
            else if (node->child[0]->type == TREE_KW_CHAR)
                node->child[1]->symbol->datatype = DATATYPE_CHAR;
            else if (node->child[0]->type == TREE_KW_FLOAT)
                node->child[1]->symbol->datatype = DATATYPE_FLOAT;
            else if (node->child[0]->type == TREE_KW_BOOL)
                node->child[1]->symbol->datatype = DATATYPE_BOOL;
        }
        printf("endvec\n");
    }
    //check function declarations
    if(node->type == TREE_DECLARATION_FUC) {
	printf("startfuc\n");
        if(node->child[1]->symbol->type != SYMBOL_IDENTIFIER) {
            printf("ERRO: Redeclaração de \" %s \", na linha %d. Declarada na linha %d", node->child[1]->symbol->key, node->linenumber, node->child[1]->symbol->lineNumber);
            exit(4);
        }
        else {
            node->child[1]->symbol->type = SYMBOL_IDENTIFIER_FUNCTION;
            node->child[1]->symbol->lineNumber = node->linenumber;
            if(node->child[0]->type == TREE_KW_INTEGER)
                node->child[1]->symbol->datatype = DATATYPE_INT;
            else if (node->child[0]->type == TREE_KW_CHAR)
                node->child[1]->symbol->datatype = DATATYPE_CHAR;
            else if (node->child[0]->type == TREE_KW_FLOAT)
                node->child[1]->symbol->datatype = DATATYPE_FLOAT;
            else if (node->child[0]->type == TREE_KW_BOOL)
                node->child[1]->symbol->datatype = DATATYPE_BOOL;
        }
        printf("endfuc\n");
    }



}
