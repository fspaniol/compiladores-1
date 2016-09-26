#ifndef TREEH
#define TREEH

#include "hash.h"

#define TREE_ADD 1
#define TREE_SUB 2
#define TREE_DIV 3
#define TREE_MUL 4
#define TREE_LE  5
#define TREE_GE  6
#define TREE_EQ  7
#define TREE_NE  8
#define TREE_AND 9 
#define TREE_OR  10
#define TREE_L   11
#define TREE_G   12
#define TREE_ATTR 13

//datatypes
#define TREE_KW_INTEGER  15
#define TREE_KW_BOOL      16
#define TREE_KW_CHAR      17
#define TREE_KW_FLOAT      18
//SYMBOL types
#define TREE_INTEGER 19
#define TREE_TRUE 20
#define TREE_FALSE 21
#define TREE_CHAR 22
#define TREE_STRING 23
#define TREE_IDENTIFIER 14
//declarations
#define TREE_DECLARATION 24
#define TREE_DECLARATION_SCALAR 25
#define TREE_DECLARATION_VEC_LIT 26
#define TREE_DECLARATION_VEC_NOLIT 27
#define TREE_DECLARATION_FUC 28
#define TREE_DEC_FUC_PARAM_HEAD 29
#define TREE_DEC_FUC_PARAM_TAIL 30
//commands
#define TREE_CMD_READ 31
#define TREE_CMD_PRINT 32
#define TREE_CMD_PRINT_LIST_HEAD 33
#define TREE_CMD_PRINT_LIST_TAIL 34
#define TREE_CMD_RETURN 35
#define TREE_CMD_LIST_HEAD 36
#define TREE_CMD_LIST_TAIL 37
#define TREE_CMD_BLOCK 38
#define TREE_CMD_ATTR_VAR_SCALAR 39
#define TREE_CMD_ATTR_VAR_VEC 40
#define TREE_CMD_IF 41
#define TREE_CMD_IF_ELSE 42
#define TREE_CMD_FOR 43
#define TREE_CMD_FOR_TO 44

//variable declarations<
#define TREE_DEC_VAR_VEC_LIT_LIST_HEAD 45
#define TREE_DEC_VAR_VEC_LIT_LIST_TAIL 46
#define TREE_DEC_VAR_VEC_NO_LIT 47
#define TREE_DEC_VAR_SCALAR 48
//expressions
#define TREE_EXP_VEC_INDEX 49 
#define TREE_EXP_OP_BINARY 50
#define TREE_EXP_BRACKET_ENCLOSURE 51
#define TREE_EXP_FUNC_CALL 52
#define TREE_EXP_FUNC_CALL_ARG_LIST_HEAD 53
#define TREE_EXP_FUNC_CALL_ARG_LIST_TAIL 54

typedef struct treenode {
  int type;
  HASHCELL *symbol;
  struct treenode *child[4];
}TREENODE; 

TREENODE* createNode(int type, HASHCELL *symbol, TREENODE *child1,TREENODE *child2,TREENODE *child3,TREENODE *child4);
void printTree(TREENODE *node);
void print_code(FILE *outFile,TREENODE *node);
#endif