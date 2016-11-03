#ifndef TAC_H
#define TAC_H

#include "hash.h"
#include "tree.h"
/* OP codes are defined here */
#define TAC_NOP 1
#define TAC_SYMBOL 2
#define TAC_MOVE 3

/* arithmetic operators */
#define TAC_ADD 4

typedef struct tac {
    int tac_code;
    HASHCELL *result;
    HASHCELL *op1;
    HASHCELL *op2;
    struct tac *next;
} TAC;

TAC* tac_create(int tac_code, HASHCELL *result,HASHCELL *op1, HASHCELL *op2);
void print_tac_list(TAC *tc);
TAC* tac_join(TAC *dest, TAC *src);
TAC* gen_tac(TREENODE *node);

HASHCELL* make_label();
HASHCELL* make_temp();

#endif

