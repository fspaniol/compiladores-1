#ifndef TAC_H
#define TAC_H

#include "hash.h"

/*OP codes are defined here*/
#define OP_NOP



typedef struct tac {
    int opcode;
    HASHCELL *addr[3];
    struct tac next;
} TAC;

TAC *create_tac();
void print_tac_list(TAC *tc);
int append_list(TAC *dest, TAC *src);

char* make_label();
char* make_temp();


#endif

