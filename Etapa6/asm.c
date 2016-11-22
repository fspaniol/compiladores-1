#include <stdio.h>
#include "hash.h"
#include "tree.h"
#include <string.h>
#include <stdio.h>
FILE *fout;
//generates code for int global variable
int gen_scalar_var(HASHCELL *identifier) {
    fprintf(fout,"\t .glbol %s\n",identifier->key);
    fprintf(fout,"\t .data\n");
    if(identifier->datatype == DATATYPE_INT || identifier->datatype == DATATYPE_FLOAT)
        fprintf(fout, "\t .size\t%s, 4\n", node->key);
    if(identifier->datatype == DATATYPE_BOOL || identifier->datatype == DATATYPE_CHAR)
        fprintf(fout, "\t .size\t%s, 1\n", node->key);
    fprintf(fout, "%s:\n", node->key);


    if(node->datatype == DATATYPE_INT || node->datatype == DATATYPE_FLOAT) {
        char *init_value = node->declared_at->child[2]->symbol->key;
        fprintf(fout, "\t .long\t%s\n",init_value);
    }
    else if(node->datatype == DATATYPE_CHAR) {
        char *init_value = node->declared_at->child[2]->symbol->key;
        fprintf(fout, "\t .byte\t%d\n",init_value[0]);//to convert char to int
    }
    if(node->datatype == DATATYPE_BOOL)
        fprintf(fout, "\t .byte\t%d\n",node->declared_at->child[2]->type == TREE_TRUE ? 1 : 0);//to convert char to int
    fprintf(fout, "\n\n");
}




void gen_asm() {
    fout = fopen("asm.out","w");
    //generate variable declarations
    int hs_ind;
    HASHCELL *scan;
    for(hs_ind = 0; hs_ind < HASH_SIZE; hs_ind++) {
        scan = table[hs_ind];
        while(scan != NULL) {
            printf("scan!!\n");
            switch(scan->type) {

                case SYMBOL_IDENTIFIER_SCALAR:
                    printf("identifier symbol\n");
                    gen_identifier(scan);
                    break;
            }
            scan = scan->next;
        }
    }

}
