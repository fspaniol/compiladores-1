#ifndef TAC_H
#define TAC_H

#include "hash.h"
#include "tree.h"
/* OP codes are defined here */
#define TAC_NOP 1
#define TAC_SYMBOL 2
#define TAC_MOVE 3

/* arithmetic and logical operators */
#define TAC_ADD 4
#define TAC_SUB 5
#define TAC_DIV 6
#define TAC_MUL 7
#define TAC_LE  8
#define TAC_GE  9
#define TAC_EQ  10
#define TAC_NE  11
#define TAC_AND 12
#define TAC_OR  13
#define TAC_L   14
#define TAC_G   15

//Commands 
#define TAC_ATTR_SCALAR 17
#define TAC_ATTR_VEC 	18
#define TAC_READ 		19
#define TAC_PRINT		20	
#define TAC_RETURN		21
#define TAC_IF 			22
#define TAC_IF_ELSE		23
#define TAC_FOR 		24
#define TAC_FOR_TO  	25

//Expressions 
#define TAC_PUSH_ARGS 26
#define TAC_POP_ARGS 27

#define TAC_LABEL 28
#define TAC_CALL 29

#define TAC_VARDEC 30
#define TAC_ATTR 31
#define TAC_VECDEC 32

#define TAC_IFZ 33
#define TAC_JUMP 34

#define TAC_BEGINFUNC 35
#define TAC_ENDFUNC 36

#define TAC_TO_VEC_MOVE 37



typedef struct tac {
    int tac_code;
    HASHCELL *result;
    HASHCELL *op1;
    HASHCELL *op2;
    struct tac *next;
    struct tac *prev;
} TAC;

TAC* tac_create(int tac_code, HASHCELL *result,HASHCELL *op1, HASHCELL *op2);
void print_tac_list(TAC *tc);
void tac_print(TAC * tac);
TAC* tac_join(TAC *dest, TAC *src);
TAC* gen_tac(TREENODE *node);
TAC* invert_tac_list(TAC *tc);

HASHCELL* make_label();
HASHCELL* make_temp();

#endif

