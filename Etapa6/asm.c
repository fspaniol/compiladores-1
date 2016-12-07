#include <stdio.h>
#include "hash.h"
#include "tree.h"
#include "tac.h"
#include <string.h>
#include <stdlib.h>
FILE *fout;
char *filename;
int data_flag_set = 0;

//generates code for int global variable
int gen_scalar_var(HASHCELL *identifier) {
    if(!data_flag_set) {
        fprintf(fout,"\t .data\n");
        data_flag_set = 1;
    }
    char buf[10];
    int size;
    if(identifier->datatype == DATATYPE_INT || identifier->datatype == DATATYPE_FLOAT || identifier->datatype == DATATYPE_BOOL)
        size = 4;
    if(identifier->datatype == DATATYPE_CHAR)
        size = 1;
    fprintf(fout, "\t .globl\t%s\n", identifier->key);
    fprintf(fout, "\t .align %d\n", size);
    fprintf(fout, "\t .type\t%s, @object\n", identifier->key);
    fprintf(fout, "\t .size\t%s, %d\n", identifier->key,size);
    fprintf(fout, "%s:\n", identifier->key);
    char *init_value;
    if(identifier->type == SYMBOL_CONST) {
        init_value = calloc(1,20);
        sscanf(identifier->key,"_const%s", init_value);
    } else {
        if(identifier->declared_at != NULL && identifier->declared_at->child[2]->symbol != NULL){
            //var initialized with constant removing constant tag
            init_value = &(identifier->declared_at->child[2]->symbol->key[6]);
        }
        else {
            buf[0] = '0';
            buf[1] = '\0';
            init_value = buf;
        }
    }

    if(identifier->datatype == DATATYPE_INT || identifier->datatype == DATATYPE_FLOAT) {
        fprintf(fout, "\t .long\t%s\n",init_value);
    }
    else if(identifier->datatype == DATATYPE_CHAR) {
        fprintf(fout, "\t .byte\t%d\n",init_value[0]);//to convert char to int
    }
    if(identifier->datatype == DATATYPE_BOOL)
        fprintf(fout, "\t .long\t%d\n",identifier->declared_at->child[2]->type == TREE_TRUE ? 1 : 0);//to convert char to int
    fprintf(fout, "\n\n");
}
int gen_vec_var(HASHCELL *identifier) {
    TREENODE *declaration = identifier->declared_at;
    TREENODE *list, *list_element;
    HASHCELL *symbol;
    int size;
    if(identifier->datatype == DATATYPE_INT || identifier->datatype == DATATYPE_FLOAT)
        size = 4;
    if(identifier->datatype == DATATYPE_BOOL || identifier->datatype == DATATYPE_CHAR)
        size = 1;
    int length = atoi(declaration->child[2]->symbol->key);
    if(declaration->type == TREE_DECLARATION_VEC_NOLIT) {
        fprintf(fout, "\t.comm %s,%d,%d\n", identifier->key, length*size, size);
    } else if (declaration->type == TREE_DECLARATION_VEC_LIT) {
        //fprintf(fout,"\t .glbol %s\n",identifier->key);
        //fprintf(fout,"\t .data\n");
        fprintf(fout, "\t .align %d\n", size);
        fprintf(fout, "\t .size\t%s, %d\n", identifier->key,size*length);
        fprintf(fout, "%s:\n", identifier->key);
        list = declaration->child[3];
        while(list != NULL) {
            list_element = list->child[0];

            if(list_element->type == TREE_INTEGER) {
                char *init_value = list_element->symbol->key;
                fprintf(fout, "\t .long\t%s\n",init_value);
            } else if(list_element->type == TREE_CHAR) {
                char *init_value = symbol->key;
                fprintf(fout, "\t .byte\t%d\n",init_value[0]);//to convert char to int
            } else if(list_element->type == TREE_TRUE) {
                fprintf(fout, "\t .byte\t%d\n",1);//to convert char to int
            } else if(list_element->type == TREE_FALSE) {
                fprintf(fout, "\t .byte\t%d\n",0);//to convert char to int
            }
            list = list->child[1];
        }


    }
}

void gen_asm_comp(TAC *next_tac){
    fprintf(fout, "\tmovl    %s(%%rip), %%edx\n", next_tac->op1->key);
    fprintf(fout, "\tmovl    %s(%%rip), %%eax\n", next_tac->op2->key);
    fprintf(fout, "\tcmpl    %%eax, %%edx\n");
    switch(next_tac->tac_code){
        case TAC_GE:
            fprintf(fout, "\tsetge    %%al\n");
            break;
        case TAC_G:
            fprintf(fout, "\tsetg    %%al\n");
            break;
        case TAC_LE:
            fprintf(fout, "\tsetle    %%al\n");
            break;
        case TAC_L:
            fprintf(fout, "\tsetl    %%al\n");
            break;
        case TAC_EQ:
            fprintf(fout, "\tsete    %%al\n");
            break;
        case TAC_NE:
            fprintf(fout, "\tsetne    %%al\n");
            break;
        default:
            printf("unknown comparator\n");
    }
    fprintf(fout, "\tmovzbl  %%al, %%eax\n");
    fprintf(fout, "\tmovl    %%eax, %s(%%rip)\n", next_tac->result->key);
}

void gen_asm(TAC *tac_list) {
    char *name;
    name = calloc(sizeof(char), strlen(filename)+3);
    sprintf(name,"%s.s", filename);
    fout = fopen(name,"w");
    int hs_ind;
    HASHCELL *scan;
    for(hs_ind = 0; hs_ind < HASH_SIZE; hs_ind++) {
        scan = table[hs_ind];
        while(scan != NULL) {
            switch(scan->type) {
                case SYMBOL_IDENTIFIER_SCALAR:
                    gen_scalar_var(scan);
                    break;
                case SYMBOL_IDENTIFIER_VECTOR:
                    gen_vec_var(scan);
                    break;
                case SYMBOL_CODEGEN_TEMP_VAR://temporary vars
                    gen_scalar_var(scan);
                    break;
                case SYMBOL_CONST:
                    gen_scalar_var(scan);
                    break;
            }
            scan = scan->next;
        }
    }
    //read TAC
    int tac_index = 0;
    TAC *next_tac = tac_list;
    while(next_tac!= NULL) {
        switch(next_tac->tac_code) {
            case TAC_BEGINFUNC:
                fprintf(fout,"\t.globl %s\n", next_tac->result->key);
                fprintf(fout,"\t.type   %s, @function\n", next_tac->result->key);
                fprintf(fout, "%s:\n",next_tac->result->key);
                fprintf(fout, "\tpushq   %%rbp\n");
                fprintf(fout, "\tmovq    %%rsp, %%rbp\n");
                break;
            case TAC_ENDFUNC:
                break;//probably nothing to do here
            case TAC_RETURN:
                if(next_tac->op1->type == SYMBOL_LIT_INT || next_tac->op1->type == SYMBOL_LIT_FLOAT || next_tac->op1->type == SYMBOL_LIT_CHAR)
                    fprintf(fout, "\tmovl    $%s, %%eax\n",next_tac->op1->key);
                else
                    fprintf(fout, "\tmovl    %s(%%rip), %%eax\n",next_tac->op1->key);

                fprintf(fout, "\tpopq    %%rbp\n");
                fprintf(fout, "\tret\n");
                break;
            //arith ops
            case TAC_ADD:
                fprintf(fout, "\tmovl    %s(%%rip), %%eax\n",next_tac->op1->key);
                fprintf(fout, "\tmovl    %s(%%rip), %%edx\n",next_tac->op2->key);
                fprintf(fout, "\taddl    %%edx, %%eax\n");
                fprintf(fout, "\tmovl    %%eax, %s(%%rip)\n",next_tac->result->key);
                break;
            case TAC_SUB:
                fprintf(fout, "\tmovl    %s(%%rip), %%eax\n",next_tac->op1->key);
                fprintf(fout, "\tmovl    %s(%%rip), %%edx\n",next_tac->op2->key);
                fprintf(fout, "\tsubl    %%edx, %%eax\n");
                fprintf(fout, "\tmovl    %%eax, %s(%%rip)\n",next_tac->result->key);
                break;
            case TAC_MUL:
                fprintf(fout, "\tmovl    %s(%%rip), %%eax\n",next_tac->op1->key);
                fprintf(fout, "\tmovl    %s(%%rip), %%edx\n",next_tac->op2->key);
                fprintf(fout, "\timul    %%edx,%%eax\n");
                fprintf(fout, "\tmovl    %%eax, %s(%%rip)\n",next_tac->result->key);
                break;
            case TAC_ATTR_SCALAR:
                fprintf(fout, "\tmovl    %s(%%rip), %%eax\n",next_tac->op1->key);
                fprintf(fout, "\tmovl    %%eax, %s(%%rip)\n",next_tac->result->key);
                break;
            case TAC_LABEL:
                fprintf(fout, "%s:\n",next_tac->result->key);
                break;
            case TAC_IFZ:
                fprintf(fout, "\tmovl    %s(%%rip), %%eax\n", next_tac->op1->key);
                fprintf(fout, "\ttestl    %%eax, %%eax\n");
                fprintf(fout, "\tje    %s\n", next_tac->result->key);
                break;
            case TAC_JUMP:
                fprintf(fout, "\tjmp %s\n", next_tac->result->key);
                break;

            case TAC_GE:
            case TAC_G:
            case TAC_LE:
            case TAC_L:
            case TAC_EQ:
            case TAC_NE:
                  gen_asm_comp(next_tac);
                  break;
            case TAC_AND:
                fprintf(fout, "\tmovl    %s(%%rip), %%edx\n", next_tac->op1->key);
                fprintf(fout, "\tmovl    %s(%%rip), %%eax\n", next_tac->op2->key);
                fprintf(fout, "\tandl    %%edx, %%eax\n");
                fprintf(fout, "\tmovl    %%eax, %s(%%rip)\n", next_tac->result->key);
                break;


            default:
                printf("LOST TAC number %d\n", next_tac->tac_code);
                break;
        }
        next_tac = next_tac->next;
    }


}
