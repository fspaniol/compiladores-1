#include "tac.h"
#include "tree.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int temp_count = 0;
int label_count = 0;

TAC* tac_create(int tac_code, HASHCELL *result, HASHCELL *op1, HASHCELL *op2){
    printf("entered tac create\n");
    TAC *tc = (TAC*) calloc(sizeof(TAC),1);
    tc->next = NULL;
    tc->tac_code = tac_code;
    tc->op1 = op1;
    tc->op2 = op2;
    tc->result = result;
    return tc;
}

void print_tac_list(TAC *tc) {
    while(tc != NULL) {
        printf("OPCODE: %d \n", tc->tac_code);
        tc = tc->next;
    }
}

//concat two tacs
TAC* tac_join(TAC *dest, TAC *src) {

    if(dest == NULL)
        return src;
    if(src == NULL)
        return dest;
    printf("joinbegin\n");
    while(dest->next != NULL) {
        printf("while");
        dest = dest->next;
    }
    dest->next = src;
    printf("join end\n");
    return dest;
}

HASHCELL *make_label()
{
    char num[100];
    sprintf(num, "_label%d", label_count);
    label_count++;
    return addHash(num, SYMBOL_CODEGEN_LABEL);
}

HASHCELL *make_temp()
{
    char num[100];
    printf("creating temp var:\n",num);
    sprintf(num,"_temp%d", temp_count);
    temp_count++;
    HASHCELL *temp = addHash(num, SYMBOL_CODEGEN_TEMP_VAR);
    printf("finished\n");
    return temp;
}

TAC* gen_tac_exp_binary_op(TREENODE *node, TAC **children_tac_array) {
    int tac_op = -1;
    switch(node->child[1]->type) {
        case TREE_ADD:
            tac_op = TAC_ADD;
    }

    TAC *children_tacs = tac_join(children_tac_array[0],children_tac_array[2]);
    printf("Creating tac \n");
    TAC *tc = tac_create(tac_op, make_temp(),
                         children_tac_array[0] != NULL ? children_tac_array[0]->result : NULL,
                         children_tac_array[2] != NULL ? children_tac_array[2]->result : NULL);
    printf("tac created. joining \n");
    make_label();
    return tac_join(children_tacs, tc);
}


/* generate tac  */
TAC* gen_tac(TREENODE *node) {

    TAC* children_tac[4];
    int counter;

    if(node == NULL)
        return NULL;
    //depth first(left to right) algorithm
    /////considerar exceçoes
    for(counter = 0;counter < 4; counter++) {
        children_tac[counter] = gen_tac(node->child[counter]);
    }

    TAC *tc = (TAC*)calloc(sizeof(TAC),1);
    switch(node->type) {

        /* symbol and identifier nodes */
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
        case TREE_CMD_BLOCK:
            return children_tac[0];
        case TREE_CMD_READ:
            return tac_create(TAC_READ, NULL, children_tac[0]->result,NULL);

        /* print command*/
        case TREE_CMD_PRINT:
            return children_tac[0];

        case TREE_CMD_PRINT_LIST_HEAD:
            return tac_join(tac_join(children_tac[0],
                                tac_create(TAC_PRINT, NULL, children_tac[0]->result, NULL)),
                            children_tac[1]);
        case TREE_CMD_PRINT_LIST_TAIL:
            return tac_join(children_tac[0], tac_create(TAC_PRINT, NULL, children_tac[0]->result, NULL));
        /* return command */
        case TREE_CMD_RETURN:
            return tac_join(children_tac[0],tac_create(TAC_RETURN, NULL, children_tac[0]->result,NULL));

        /* attribution command */
        case TREE_CMD_ATTR_VAR_SCALAR:
            return tac_join(children_tac[1], tac_create(TAC_ATTR_SCALAR, children_tac[0]->result, children_tac[1]->result, 0));
        case TREE_CMD_ATTR_VAR_VEC:
            return tac_join(tac_join(children_tac[1], children_tac[2]), tac_create(TAC_ATTR_VEC, node->child[0]->symbol, children_tac[1]->result, children_tac[2]->result));




        default:
            if(node != NULL) {
                printf("ERROR. Unknown TREE NODE %d.\n", node->type);

            }

            break;
    }
    return NULL;
}


