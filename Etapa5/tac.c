#include "tac.h"

TAC *create_tac() {
    TAC *tc =(TAC*) calloc(sizeof(TAC),1);
    tc->next = NULL;
    tc->opcode = OP_NOP;
    tc->addr[0] = NULL;
    tc->addr[1] = NULL;
    tc->addr[2] = NULL;
    return tc;
}

void print_tac_list(TAC *tc) {
    while(tc != NULL) {
        printf("OPCODE: %d \n", tc->opcode);
        tc = tc->next;
    }
}


int append_list(TAC *dest, TAC *src) {
    if(dest == NULL)
        return -1;
    if(src == NULL)
        return 0;
    while(dest->next != NULL)
        dest = dest->next;
    dest->next = src;
    return 0;
}
