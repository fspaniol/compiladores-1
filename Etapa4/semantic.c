#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "tree.h"
#include "y.tab.h"

TREENODE *raiz;

int semanticAnalyser(TREENODE *root) {
    int i;
    raiz = root;
    setTypes(root);
    
    return 1;
    
}

//checks compatibility of two datatypes
//if they are incompatible, returns -1
//if they are equivalent, returns 0
//if they are compatible but not equivalent (float, int) returns datatype
int checkDataTypes (int firstType, int secType) {
    
    if(firstType == secType)
        return 0;
    
    if(firstType == DATATYPE_INT) {
        switch(secType) {
            case DATATYPE_CHAR:
                return 0;
            case DATATYPE_FLOAT:
                return DATATYPE_FLOAT;
            default:
                return -1;
        }
    }
    else if (firstType == DATATYPE_CHAR) {
        switch(secType) {
            case DATATYPE_INT:
                return 0;
            case DATATYPE_FLOAT:
                return DATATYPE_FLOAT;
            default:
                return -1;
        }
    }
    else if (firstType == DATATYPE_FLOAT) {
        switch(secType) {
            case DATATYPE_INT:
            case DATATYPE_CHAR:
                return DATATYPE_FLOAT;
            default:
                return -1;
        }
    }
    
    else if (firstType == DATATYPE_BOOL)
        if(secType == DATATYPE_BOOL)
            return 0;
    return -1;
}


void checkIfVariableDeclared(TREENODE *node) {
    if(node == NULL) return;
    if (node->symbol == NULL) return;
    if(node->symbol->type == SYMBOL_IDENTIFIER) {
        //variable is not declared
        printf("Error. variable %s referenced before declaration on line %d\n", node->symbol->key, node->linenumber);
        exit(4);
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
//funçãozinha que é usada em vários lugares XD
int getDataTypeFromKW(int kw){
    switch(kw){
        case TREE_KW_INTEGER:
            return DATATYPE_INT;
        case TREE_KW_CHAR:
            return DATATYPE_CHAR;
        case TREE_KW_BOOL:
            return DATATYPE_BOOL;
        case TREE_KW_FLOAT:
            return DATATYPE_FLOAT;
            }
    return -1;
}


int verifyParams(TREENODE* node, TREENODE* function){
    if(node->type == TREE_DECLARATION_FUC && strcmp(node->child[1]->symbol->key,function->child[0]->symbol->key)==0){
        int returnDatatype;
        if (node->child[0] != NULL){
            returnDatatype = getDataTypeFromKW(node->child[0]->type);
        }
        else
            returnDatatype = -1;
        int declaredType, calledType;
        TREENODE *decList = node->child[2];
        TREENODE *callList = function->child[1];
        // Se são os dois void, está certo
        if(decList == NULL && callList==NULL) return returnDatatype;

        if(decList == NULL || callList==NULL) return -1; // quantidade de variaveis diferente
        
        // Testa os parâmetros um a um

        while(decList->type == TREE_DEC_FUC_PARAM_HEAD && callList ->type == TREE_EXP_FUNC_CALL_ARG_LIST_HEAD){
            
            declaredType = getDataTypeFromKW(decList->child[0]->type);
            calledType = getExpDataType(callList->child[0]);
            if (checkDataTypes(calledType, declaredType) == -1) return -1;
            decList = decList->child[2];
            callList = callList->child[1];
        }
        // Testa se um é tail e o outro não
        if ((decList->type == TREE_DEC_FUC_PARAM_HEAD) && (callList ->type == TREE_EXP_FUNC_CALL_ARG_LIST_TAIL)) return -1;
        if ((decList->type == TREE_DEC_FUC_PARAM_TAIL) && (callList ->type == TREE_EXP_FUNC_CALL_ARG_LIST_HEAD)) return -1;
        
        
        //Testa se as tails são iguais
        
        declaredType = getDataTypeFromKW(decList->child[0]->type);
        calledType = getExpDataType(callList->child[0]);
        if (checkDataTypes(calledType, declaredType) == -1) return -1;
        
        return returnDatatype;
        
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
    else if(node->type == TREE_INTEGER)
        return(DATATYPE_INT);
    else if(node->type == TREE_EXP_VEC_INDEX) {
        //expression is vector[exp]
        //check if variable is declared
        checkIfVariableDeclared(node->child[0]);
        //check if variable is a vector
        if(node->child[0]->symbol->type != SYMBOL_IDENTIFIER_VECTOR) {
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
        return(node->child[0]->symbol->datatype);
        
    }
    else if (node->type == TREE_FALSE || node->type == TREE_TRUE)
        return DATATYPE_BOOL;
    
    else if ((node->type == TREE_EXP_OP_BINARY) && (node->child[1] != NULL)) {
        int datatype = checkDataTypes(getExpDataType(node->child[0]), getExpDataType(node->child[2]));
        switch(node->child[1]->type){
            case TREE_ADD:
            case TREE_SUB:
            case TREE_DIV:
            case TREE_MUL:
                if (datatype == 0 )
                    return(getExpDataType(node->child[0]));
                else if (datatype > 0)
                    return datatype;
                else {
                    printf("ERROR: Incompatible datatypes on line %d.\n", node->linenumber);
                    exit(4);
                }
                
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
        
    } else if (node->type == TREE_EXP_BRACKET_ENCLOSURE) {
        return getExpDataType(node->child[0]);
    } else if (node->type == TREE_EXP_FUNC_CALL){
        int returnVerify = verifyParams(raiz, node);
        
        if(returnVerify == -4) {
            printf("ERROR: Function %s called at line %d is not declared.\n", node->child[0]->symbol->key, node->linenumber);
            exit(4);
        }
        if (returnVerify == -1){
            printf("ERROR: Function %s at line %d is called with the wrong parameters\n", node->child[0]->symbol->key, node->linenumber);
            exit(4);
        }
        return returnVerify;
    }
    
    return -1;
}




int check_print_list(TREENODE *node) {
    int type;
    if(node->type == TREE_CMD_PRINT_LIST_HEAD || node->type == TREE_CMD_PRINT_LIST_TAIL) {
        if(node->child[0]->type != TREE_STRING) {
            //it must be an arithmetical expression
            type = getExpDataType(node->child[0]);
            
            if(type != DATATYPE_INT && type != DATATYPE_CHAR && type != DATATYPE_FLOAT) {
                //invalid expression type
                printf("ERROR: Invalid expression type on print command on line %d. type is %d\n", node->linenumber, type);
                exit(4);
            }
        }
    }
    if(node->type == TREE_CMD_PRINT_LIST_HEAD) {
        //the list continues. recurse function
        return check_print_list(node->child[1]);
    }
    return 1;
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
    int expDataType;
    //test empty command
    if (node == NULL)
        return 1;
    
    TREENODE *listHead;
    //unwraps command block
    if (node->type == TREE_CMD_BLOCK) {
        listHead = node->child[0];
        checkCommand(listHead, funcType);
    }
    
    //unwraps list
    if(node->type == TREE_CMD_LIST_HEAD || node->type == TREE_CMD_LIST_TAIL) {
        if(checkCommand(node->child[0], funcType) != 1)
            return -1;
        if(node->type == TREE_CMD_LIST_HEAD && node->child[1] != NULL)
            checkCommand(node->child[1], funcType);
    }
    
    //print command
    if(node->type == TREE_CMD_PRINT) {
        return check_print_list(node->child[0]);
        
    }
    
    //attribution operations
    ///scalar
    if(node->type == TREE_CMD_ATTR_VAR_SCALAR) {
        if(node->child[0]->type != TREE_IDENTIFIER) {
            printf("Error: Left hand side of attribution operator is not an identifier on line %d.\n", node->linenumber);
            exit(4);
        }
        if(node->child[0]->symbol->type != SYMBOL_IDENTIFIER_SCALAR) {
            printf("Error: Left hand side of attribution operator is a unindexed vector on line %d.\n", node->linenumber);
            exit(4);
        }
        
        int rhs_datatype = getExpDataType(node->child[1]);
        if(rhs_datatype == -1) {
            printf("Error: right hand side of attribution operator is not an expression on line %d.\n", node->linenumber);
            exit(4);
        }

        int result_datatype = checkDataTypes(node->child[0]->symbol->datatype, rhs_datatype);
        if(result_datatype == 0 || result_datatype == node->child[0]->symbol->datatype)
            return 1;
        else {
            printf("Error: right hand side of attribution operator has incompatible data type on line %d.\n", node->linenumber);
            exit(4);
        }
        
    }
    
    ///vector
    if(node->type == TREE_CMD_ATTR_VAR_VEC) {
        if(node->child[0]->type != TREE_IDENTIFIER) {
            printf("Error: Left hand side of attribution operator is not an identifier on line %d.\n", node->linenumber);
            exit(4);
        }
        if(node->child[0]->symbol->type != SYMBOL_IDENTIFIER_VECTOR) {
            printf("Error: Left hand side of attribution operator is not a vector on line %d.\n", node->linenumber);
            exit(4);
        }
        
        //checks is index is an integer
        if(checkDataTypes(DATATYPE_INT, getExpDataType(node->child[1])) != 0) {
            printf("Error: vector on left hand side of operator on line %d is not indexed with an integer value.\n", node->linenumber);
            printf("check data types result.%d\n",checkDataTypes(DATATYPE_INT, getExpDataType(node->child[1])));
            printf("index data type:%d\n.", getExpDataType(node->child[1]));
            exit(4);
        }
        
        int rhs_datatype = getExpDataType(node->child[2]);
        if(rhs_datatype == -1) {
            printf("Error: right hand side of attribution operator is not an expression on line %d.\n", node->linenumber);
            exit(4);
        }
        int result_datatype = checkDataTypes(node->child[0]->symbol->datatype, rhs_datatype);
        if(result_datatype == 0 || result_datatype == node->child[0]->symbol->datatype)
            return 1;
        else {
            printf("Error: right hand side of attribution operator has incompatible data type on line %d.\n", node->linenumber);
            exit(4);
        }
        
        
    }
    //Cuida dos comandos dentro dos FOR's e IFS e ElSE
    if ((node->type == TREE_CMD_IF) || (node->type == TREE_CMD_FOR))
        checkCommand(node->child[1], funcType);
    else if (node->type == TREE_CMD_IF_ELSE) {
        checkCommand(node->child[1], funcType);
        checkCommand(node->child[2], funcType);
    }
    else if (node->type == TREE_CMD_FOR_TO)
        checkCommand(node->child[3], funcType);
    
    
    
    //if commands check : test if exp is boolean
    //checks nested commands
    if(node->type == TREE_CMD_IF || node->type == TREE_CMD_IF_ELSE) {
        if(getExpDataType(node->child[0])!= DATATYPE_BOOL) {
            printf("ERROR: Conditional expression on if command must be of type Boolean. Line  %d .\n", node->linenumber);
            exit(4);
        }
        checkCommand(node->child[1], funcType);
    }
    if(node->type == TREE_CMD_IF_ELSE) {
        checkCommand(node->child[2], funcType);
    }
    
    TREENODE* cmd = node;
    //tests if return type is correct
    if(cmd->type == TREE_CMD_RETURN){
        int returnType = checkDataTypes(getExpDataType(cmd->child[0]), funcType);
        if(returnType != 0 && returnType!=funcType){
            printf("ERROR: Return type on line  %d is invalid.\n", cmd->linenumber);
            exit(4);
        }
    }
    
    return 1;
    
}



void setTypes(TREENODE *node) {
    int i;
    if(node == NULL) return;
    
    if(node->type == TREE_DECLARATION) {
        setTypes(node->child[0]);
        setTypes(node->child[1]);
    }
    
    
    //check scalar declarations
    if(node->type == TREE_DECLARATION_SCALAR) {
        //first child of TREE_DECLARATION_SCALAR is datatype, second is identifier
        //checks if identifies has already been declared
        if(node->child[1]->symbol->type != SYMBOL_IDENTIFIER) {
            printf("ERRO: Redeclaração de \" %s \", na linha %d. Declarada na linha %d", node->child[1]->symbol->key, node->linenumber, node->child[1]->symbol->lineNumber);
            exit(4);
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
            
            if(node->child[0]->type == TREE_KW_INTEGER) {
                node->child[1]->symbol->datatype = DATATYPE_INT;

            }
            else if (node->child[0]->type == TREE_KW_CHAR) {
                node->child[1]->symbol->datatype = DATATYPE_CHAR;

            }
            else if (node->child[0]->type == TREE_KW_FLOAT) {
                node->child[1]->symbol->datatype = DATATYPE_FLOAT;

            }
            else if (node->child[0]->type == TREE_KW_BOOL) {
                node->child[1]->symbol->datatype = DATATYPE_BOOL;

            }
            setTypes(node->child[2]);
            checkCommand(node->child[3], node->child[1]->symbol->datatype);
        }
    }
    //check function parameters
    if ((node->type == TREE_DEC_FUC_PARAM_HEAD) || (node->type == TREE_DEC_FUC_PARAM_TAIL)){
        node->child[1]->symbol->lineNumber = node->linenumber;
        
        if(node->child[0]->type == TREE_KW_INTEGER) {
            node->child[1]->symbol->datatype = DATATYPE_INT;
            node->child[1]->symbol->type = SYMBOL_IDENTIFIER_SCALAR;
        }
        else if (node->child[0]->type == TREE_KW_CHAR) {
            node->child[1]->symbol->datatype = DATATYPE_CHAR;
            node->child[1]->symbol->type = SYMBOL_IDENTIFIER_SCALAR;}
        else if (node->child[0]->type == TREE_KW_FLOAT){
            node->child[1]->symbol->datatype = DATATYPE_FLOAT;
            node->child[1]->symbol->type = SYMBOL_IDENTIFIER_SCALAR;}
        else if (node->child[0]->type == TREE_KW_BOOL){
            node->child[1]->symbol->datatype = DATATYPE_BOOL;
            node->child[1]->symbol->type = SYMBOL_IDENTIFIER_SCALAR;}

        if (node->type == TREE_DEC_FUC_PARAM_HEAD)
            setTypes(node->child[2]);
    }
    
}


