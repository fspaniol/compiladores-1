#include "tac.h"
#include "tree.h"
#include <stdio.h>
int temp_count = 0;
int label_count = 0;

TAC* tac_create(int tac_code, HASHCELL *result, HASHCELL *op1, HASHCELL *op2){
    TAC *tc =(TAC*) calloc(sizeof(TAC),1);
    tc->next = NULL;
    tc->opcode = tac_code;
    tc->op1 = op1;
    tc->op2 = op2;
    tc->result = result;
    return tc;
}

void print_tac_list(TAC *tc) {
    while(tc != NULL) {
        printf("OPCODE: %d \n", tc->opcode);
        tc = tc->next;
    }
}


TAC* tac_join(TAC *dest, TAC *src) {
    if(dest == NULL)
        return src;
    if(src == NULL)
        return dest;
    while(dest->next != NULL)
        dest = dest->next;
    dest->next = src;
    return dest;
}

char *make_label()
{
    char num[100];
    sprintf("_label%d", label_count);
    label_count++;
    char *out = calloc(sizeof(char), strlen(num));
    strncpy(out, num, strlen(num));
    return out;
}

char *make_temp()
{
    char num[100];
    sprintf("_temp%d", temp_count);
    temp_count++;
    char *out = calloc(sizeof(char), strlen(num));
    strncpy(out, num, strlen(num));
    return out;
}

/* generate tac  */
TAC* gen_tac(TREENODE *node) {

    TAC children_tac[4];
    int counter;

    if(node == NULL)
        return NULL;
    //depth first(left to right) algorithm
    /////considerar exceçoes
    for(counter = 0;counter < 4; counter++) {
        children_tac[count] = gen_tac(node->child[count]);
    }

    TAC *tc = (TAC*)calloc(sizeof(TAC),1);
    switch(node->type) {

        /* symbol nodes */
        case TREE_INTEGER:
        case TREE_TRUE:
        case TREE_FALSE:
        case TREE_CHAR:
        case TREE_STRING:
        case TREE_IDENTIFIER:
        case TREE_FLOAT:
            return tac_create(TAC_SYMBOL, node->symbol, NULL, NULL);


        /* expressions */
        case TREE_EXP_OP_BINARY:
            return gen_tac_exp_binary_op(node, children_tac);

        /* arithmetic/logical operators. handled at
         * gen_tac_exp_binary_op. can ignore*/
        case TREE_ADD:
        case TREE_SUB:
        case TREE_DIV:
        case TREE_MUL:
        case TREE_LE:
        case TREE_GE:
        case TREE_EQ:
        case TREE_NE:
        case TREE_AND:
        case TREE_OR:
        case TREE_L:
        case TREE_G:
            break;


        /* commands */


        default:
    }
}

TAC* gen_tac_exp_binary_op(TREENODE *node, TAC *children_tac_array) {
    int tac_op = -1;
    switch(node->child[1]) {
        case TREE_ADD:
            tac_op = TAC_ADD
    }
    TAC *children_tacs = tac_join(children_tac_array[0],children_tac_array[2]);
    return tac_join(children_tacs,
                tac_create(tap_op, make_temp(),
                    children_tac_array[0] ? children_tac_array[0].result : NULL,
                    children_tac_array[2] ? children_tac_array[2].result : NULL)
                );

    }

