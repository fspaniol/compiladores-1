#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "tree.h"
#include "y.tab.h"

int semanticAnalyser(TREENODE *root) {
    int i;
    setTypes(root);

  return 1;

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
    return -1;
}


void checkIfVariableDeclared(TREENODE *node) {
    if(node == NULL) return;
    if (node->symbol == NULL) return;
    if(node->symbol->type == SYMBOL_IDENTIFIER) {
        //variable is not declared
        printf("Error. variable %s referenced before declaration on line %d\n", node->symbol->key, node->linenumber);
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
  exit(4);

}

int verifyParams(TREENODE* node, TREENODE* function){
    if(node->type == TREE_DECLARATION_FUC && strcmp(node->child[1]->symbol->key,function->child[0]->symbol->key)==0){
        int declaredType, calledType;
        TREENODE *decList = node->child[2];
        TREENODE *callList = function->child[1];
        // Se são os dois void, está certo
        if(decList == NULL && callList==NULL) return 1;
        if(decList == NULL || callList==NULL) return -1; // quantidade de variaveis diferente
        if(decList->type != callList->type) return -1; //Pode ser head ou tail

        // Testa os parâmetros um a um
        while(decList->type == TREE_DEC_FUC_PARAM_HEAD && callList ->type == TREE_DEC_FUC_PARAM_HEAD){
            declaredType = getLiteralType(decList->child[0]);
            calledType = getExpDataType(callList->child[0]);
            if (checkDataTypes(calledType, declaredType) == -1) return -1;
            decList = decList->child[2];
            callList = callList->child[1];
        }
        // Testa se um é tail e o outro não
        if(decList->type != callList->type) return -1;

        //Testa se as tails são iguais
        declaredType = getLiteralType(decList->child[0]);
        calledType = getExpDataType(callList->child[0]);
        if (checkDataTypes(calledType, declaredType) == -1) return -1;
        return 1;

    }
    else {
       int childs = 0;
       for(childs=0;childs<4;childs++) {
            if(node->child[childs]!=NULL) {
                int value = verifyParams(node->child[childs],function); // recursão pros 4 filhos
                if(value != -4) return value; // vai retornando da recursão o tipo
            }
        }
    }
    return -4; //se não achou retorna -4

}

//returns -1 if node is not an expression.
int getExpDataType(TREENODE *node) {
    if(node->type == TREE_IDENTIFIER) {
        //vectors have to indexed
        if(node->symbol->type == SYMBOL_IDENTIFIER_VECTOR) {
            printf("Error. Vectors reference must be indexed. Line %d\n", node->linenumber);
            exit(4);
        }
        //functions must be called
        if(node->symbol->type == SYMBOL_IDENTIFIER_FUNCTION) {
            printf("Error. Function reference must be function call. Line %d\n", node->linenumber);
            exit(4);
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
            exit(4);
        }
        //check if index is an expression
        int datatype = getExpDataType(node->child[1]);
        if(datatype != DATATYPE_INT) {
            //not an expression
            printf("Error. vector has to be indexed by integer. Line %d\n", node->linenumber);
            exit(4);
        }
        return(node->symbol->datatype);

    } 
    
    else if ((node->type == TREE_EXP_OP_BINARY) && (node->child[1] != NULL)) {
        
        switch(node->child[1]->type){
            case TREE_ADD:
            case TREE_SUB:
            case TREE_DIV: 
            case TREE_MUL:
                if (checkDataTypes(getExpDataType(node->child[0]), getExpDataType(node->child[2])) == 0 )
                    return getExpDataType(node->child[0]);
                else if (checkDataTypes(getExpDataType(node->child[0]), getExpDataType(node->child[2])) > 0)
                    return checkDataTypes(getExpDataType(node->child[0]), getExpDataType(node->child[2]));
            case TREE_LE:
            case TREE_GE:
            case TREE_EQ:
            case TREE_NE:
            case TREE_AND: 
            case TREE_OR:
            case TREE_L:
            case TREE_G:
                return DATATYPE_BOOL;
        } 
        
    } 
    return -1;
} 

    /*: KW_READ identifier { $$ = createNode(TREE_CMD_READ, NULL, $2, NULL,NULL, NULL);}
    | KW_PRINT print_list { $$ = createNode(TREE_CMD_PRINT, NULL, $2, NULL,NULL, NULL);}
    | cmdblock      { $$ = $1;}
    | identifier OPERATOR_ATTR exp { $$ = createNode(TREE_CMD_ATTR_VAR_SCALAR, NULL, $1, $3,NULL, NULL);}
    | identifier '[' exp ']' OPERATOR_ATTR exp { $$ = createNode(TREE_CMD_ATTR_VAR_VEC, NULL, $1, $3, $6, NULL);}
    | KW_IF '(' exp ')' KW_THEN cmd { $$ = createNode(TREE_CMD_IF, NULL, $3, $6, NULL, NULL);}
    | KW_IF '(' exp ')' KW_THEN cmd KW_ELSE cmd { $$ = createNode(TREE_CMD_IF_ELSE, NULL, $3, $6, $8, NULL);}
    | KW_FOR '(' exp ')' cmd { $$ = createNode(TREE_CMD_FOR, NULL, $3, $5, NULL, NULL);}
    | KW_FOR '(' identifier OPERATOR_ATTR exp KW_TO exp ')' cmd { $$ = createNode(TREE_CMD_FOR_TO, NULL, $3, $5, $7, $9);} */




// retorna 1 se tudo certo, incluindo o retorno da função
int checkCommand(TREENODE *node, int funcType){
    if (node == NULL) return 1;
    TREENODE *listHead;
    //unwraps command block
    if (node->type == TREE_CMD_BLOCK) {
      listHead = node->child[0];
      checkCommand(listHead, funcType);
    }

    //unwraps list
    if(node->type == TREE_CMD_LIST_HEAD || node->type == TREE_CMD_LIST_HEAD) {
      if(checkCommand(listHead->child[0], funcType) != 1)
	return -1;
      if(node->child[1] != NULL)
	checkCommand(node->child[1], funcType);
    }
    
    
    TREENODE* cmd = cmdList;
    //tests if return type is correct
    if(cmd->type == TREE_CMD_RETURN){
        int returnType = checkDataTypes(getExpDataType(cmd->child[0]), funcType);
        if(returnType < 0){
            printf("ERRO: Retorno da função na linha %d é inválido.\n", cmd->linenumber);
            exit(4);
        }
    }

    // Atribuições de escalares
    /*if (cmd->type == TREE_CMD_ATTR_VAR_SCALAR){
        setTypes(cmd->child[0]);
        if(checkDataTypes(cmd->child[0]->symbol->datatype, getExpDataType(cmd->child[1])) == -1){
            printf("Atr errada: %d,  %d\n", cmd->child[0]->symbol->datatype, getExpDataType(cmd->child[1]));
            printf("ERRO: Atribuição com tipos de dados incompatíveis na linha %d", cmd->linenumber);
            exit(4);
        }
    } */

    return 1;

}



void setTypes(TREENODE *node) {
    int i;
    if(node == NULL) return;

     for(i = 0; i < 4; i++)
       if(node->type == TREE_DECLARATION)
     if(node->child[i] != NULL)
       setTypes(node->child[i]);

    //check scalar declarations
    if(node->type == TREE_DECLARATION_SCALAR) {
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
    }
    //check vector declarations
    if((node->type == TREE_DECLARATION_VEC_LIT) || (node->type == TREE_DECLARATION_VEC_NOLIT)) {
        if(node->child[1]->symbol->type != SYMBOL_IDENTIFIER) {
            printf("ERRO: Redeclaração de \" %s \", na linha %d. Declarada na linha %d\n", node->child[1]->symbol->key, node->linenumber, node->child[1]->symbol->lineNumber);
            exit(4);
        }
        else {
        if(getLiteralType(node->child[2]) != DATATYPE_INT) {
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
    }
    //check function declarations
      if(node->type == TREE_DECLARATION_FUC) {
        if(node->child[1]->symbol->type != SYMBOL_IDENTIFIER) {
            printf("ERRO SEMÂNTICO: Redeclaração de \" %s \", na linha %d. Declarada na linha %d\n", node->child[1]->symbol->key, node->linenumber, node->child[1]->symbol->lineNumber);
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

            checkCommandlist(node->child[3], node->child[1]->symbol->datatype);
        }
    }



}


