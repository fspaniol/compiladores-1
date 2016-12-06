#include "tac.h"
#include "tree.h"
#include "hash.h"
#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int temp_count = 0;
int label_count = 0;


HASHCELL* hashVector;
int initVector = 0;
TAC* tac_create(int tac_code, HASHCELL *result, HASHCELL *op1, HASHCELL *op2){
    TAC *tc = (TAC*) calloc(sizeof(TAC),1);
    tc->next = NULL;
    tc->prev = NULL;
    tc->tac_code = tac_code;
    tc->op1 = op1;
    tc->op2 = op2;
    tc->result = result;
    return tc;
}

TAC* invert_tac_list(TAC *tc) {
    while(tc->prev!=NULL) {
        tc->prev->next = tc;
        tc = tc->prev;
    }
    return tc;
}

void print_tac_list(TAC *tc) {
    while(tc != NULL) {
        tac_print(tc);
        tc = tc->next;
    }
}

void tac_print(TAC * tac) {

  if (!tac) {
      printf("tac is null");
    return;
  }

  switch (tac->tac_code) {

  case TAC_SYMBOL       : return; //printf("TAC_SYMBOL : ");        break;
  case TAC_ATTR         : printf("TAC_MOVE : ");        break;
  case TAC_ADD          : printf("TAC_ADD : ");         break;
  case TAC_SUB          : printf("TAC_SUB : ");         break;
  case TAC_MUL          : printf("TAC_MUL : ");         break;
  case TAC_DIV          : printf("TAC_DIV : ");         break;
  case TAC_EQ           : printf("TAC_EQ : ");          break;
  case TAC_NE           : printf("TAC_NE : ");          break;
  case TAC_LE           : printf("TAC_LE : ");          break;
  case TAC_GE           : printf("TAC_GE : ");          break;
  case TAC_L             : printf("TAC_LESS : ");        break;
  case TAC_G          : printf("TAC_GREATER : ");     break;
  case TAC_AND          : printf("TAC_AND : ");         break;
  case TAC_OR           : printf("TAC_OR : ");          break;
  case TAC_LABEL        : printf("TAC_LABEL : ");       break;
  case TAC_BEGINFUNC     : printf("TAC_BEGIN_FUN : ");       break;
  case TAC_ENDFUNC       : printf("TAC_END_FUN : ");     break;
  case TAC_IFZ          : printf("TAC_IFZ : ");         break;
  case TAC_READ        : printf("TAC_READ : ");       break;
  case TAC_PRINT       : printf("TAC_PRINT : ");      break;
  case TAC_RETURN       : printf("TAC_RETURN : ");      break;
  case TAC_JUMP         : printf("TAC_JUMP : ");        break;
  case TAC_VARDEC       : printf("TAC_VARDEC : ");      break;
  case TAC_VECDEC       : printf("TAC_VECDEC : ");      break;
  case TAC_CALL         : printf("TAC_CALL : ");        break;
  case TAC_PUSH_ARGS      : printf("TAC_PUSH : ");        break;
  case TAC_POP_ARGS       : printf("TAC_POP : ");         break;
  case TAC_ATTR_SCALAR: printf("TAC_ATTR_SCALAR: ");break;
  case TAC_ATTR_VEC: printf("TAC_ATTR_VEC: ");break;
  default           : printf("TAC_%d <!!!> : ", tac->tac_code); break;
  }

  if (tac->result)
    printf(" %s, ", tac->result->key);
  else
    printf("__, ");

  if (tac->op1)
    printf("%s, ", tac->op1->key);
  else
    printf("__, ");

  if (tac->op2)
    printf("%s\n", tac->op2->key);
  else
    printf("__\n");


  return;

}

//concat two tacs
TAC* tac_join(TAC *list_a, TAC *list_b) {

    if(list_a == NULL)
        return list_b;
    if(list_b == NULL)
        return list_a;
    TAC *tpoint=list_b;
    while(tpoint->prev!= NULL) {
        tpoint = tpoint->prev;
    }
    tpoint->prev = list_a;
    return list_b;
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
    sprintf(num,"_temp%d", temp_count);
    temp_count++;
    HASHCELL *temp = addHash(num, SYMBOL_CODEGEN_TEMP_VAR);
    return temp;
}

TAC* gen_tac_exp_binary_op(TREENODE *node, TAC **children_tac_array) {
    int tac_op = -1;
    HASHCELL *temp;
    switch(node->child[1]->type) {
        case TREE_ADD:
            tac_op = TAC_ADD;
            break;
        case TREE_SUB:
            tac_op = TAC_SUB;
            break;
        case TREE_DIV:
            tac_op = TAC_DIV;
            break;
        case TREE_MUL:
            tac_op = TAC_MUL;
            break;
        case TREE_LE:
            tac_op = TAC_LE;
            break;
        case TREE_GE:
            tac_op = TAC_GE;
            break;
        case TREE_EQ:
            tac_op = TAC_EQ;
            break;
        case TREE_NE:
            tac_op = TAC_NE;
            break;
        case TREE_AND:
            tac_op = TAC_AND;
            break;
        case TREE_OR:
            tac_op = TAC_OR;
            break;
        case TREE_L:
            tac_op = TAC_L;
            break;
        case TREE_G:
            tac_op = TAC_G;
            break;
        default:
            tac_op = -1;
    }
    if(tac_op == -1){
        printf("Unknown tac operator");
        exit(5);
    }
    TAC *children_tacs = tac_join(children_tac_array[0],children_tac_array[2]);
    int datatype_op = checkDataTypes(children_tac_array[0]->result->datatype,children_tac_array[2]->result->datatype);
    if(datatype_op == -1 ) {
        printf("Error during tac creation. binary exp operands have incompatble types\n");
        printf("datatype 1 : %d\n",children_tac_array[0]->result->datatype);
        printf("datatype 1 : %d\n",children_tac_array[2]->result->datatype);
        printf("line:%d\n",node->linenumber);

        exit(-1);
    }
    if(datatype_op == 0)
        datatype_op =children_tac_array[0]->result->datatype;
    temp = make_temp();
    temp->datatype = datatype_op;
    TAC *tc = tac_create(tac_op, temp,
                         children_tac_array[0] != NULL ? children_tac_array[0]->result : NULL,
                         children_tac_array[2] != NULL ? children_tac_array[2]->result : NULL);
    return tac_join(children_tacs, tc);
}


/* generate tac  */
TAC* gen_tac(TREENODE *node) {
    HASHCELL* labelAux;
    HASHCELL* tempAux;
    HASHCELL *temp_var;
    char* buffer;

    TAC* children_tac[4];
    TAC* returnedTac;
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
        case TREE_DECLARATION: return tac_join(children_tac[0],children_tac[1]);

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

        case TREE_EXP_BRACKET_ENCLOSURE:
            return children_tac[0];

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


        /* Variable declarations: dont neet to create tacs*/
        case TREE_DECLARATION_SCALAR:

        break;
        case TREE_DECLARATION_VEC_LIT:
        case TREE_DECLARATION_VEC_NOLIT:
        case TREE_DEC_VAR_VEC_LIT_LIST_HEAD:
        case TREE_DEC_VAR_VEC_LIT_LIST_TAIL:
            break;

        /* type reserved words: does nothing */
        case TREE_KW_INTEGER:
        case TREE_KW_BOOL:
        case TREE_KW_CHAR:
        case TREE_KW_FLOAT:
            break;
        /* commands */
        case TREE_CMD_BLOCK:

            return children_tac[0];
        case TREE_CMD_READ:
            return tac_create(TAC_READ, children_tac[0]->result,NULL,NULL);
        case TREE_CMD_LIST_HEAD:
            return tac_join(children_tac[0], children_tac[1]);
        case TREE_CMD_LIST_TAIL:
            return children_tac[0];

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
        
        /* ELSE's and IF's */
        case TREE_CMD_IF:
            labelAux = make_label();
            return tac_join(children_tac[0],tac_join(tac_join(tac_create(TAC_IFZ,labelAux,children_tac[0]->result,0),
                                                              children_tac[1]),
                                                     tac_create(TAC_LABEL,labelAux,0,0)));
        case TREE_CMD_IF_ELSE:
            labelAux = make_label();
            tempAux  = make_label();
            return tac_join(children_tac[0],tac_join(tac_join(tac_create(TAC_IFZ,labelAux,children_tac[0]->result,0),
                                                              children_tac[1]),
                                                     tac_join(tac_join(tac_create(TAC_JUMP,tempAux,0,0),
                                                                       tac_create(TAC_LABEL,labelAux,0,0)),
                                                              tac_join(children_tac[2],
                                                                       tac_create(TAC_LABEL,tempAux,0,0)))));
        case TREE_CMD_FOR:
            labelAux = make_label();
            tempAux  = make_label();
                return tac_join(tac_create(TAC_LABEL,labelAux,0,0),
                                tac_join(tac_join(children_tac[0],
                                                  tac_create(TAC_IFZ,tempAux, children_tac[0]->result,0)),
                                         tac_join(children_tac[1],
                                                  tac_join(tac_create(TAC_JUMP,labelAux,0,0),
                                                           tac_create(TAC_LABEL,tempAux,0,0)))));
        case TREE_CMD_FOR_TO:
            labelAux = make_label();
            tempAux = make_label();
            temp_var = make_temp();
            return tac_join(tac_join(children_tac[1], tac_create(TAC_ATTR_SCALAR, children_tac[0]->result, children_tac[1]->result, 0)), tac_join(tac_create(TAC_LABEL,labelAux,0,0),
                                           tac_join( children_tac[2],
                                           tac_join( tac_create(TAC_L, temp_var,children_tac[0]->result, children_tac[2]->result),

                  tac_join(tac_create(TAC_IFZ,tempAux,temp_var,0), tac_join( children_tac[3], tac_join(tac_create(TAC_JUMP,labelAux,0,0),
                             tac_create(TAC_LABEL,tempAux,0,0))))))));


            break;







        /*Function calls */
        case TREE_EXP_FUNC_CALL:
            labelAux = make_label();
            tempAux  = make_temp();   
            return tac_join(children_tac[1],tac_join(tac_join(tac_create(TAC_CALL,node->child[0]->symbol,labelAux,0),tac_create(TAC_LABEL,labelAux,0,0)),
                                                      tac_create(TAC_POP_ARGS,tempAux,0,0)));

        case TREE_EXP_FUNC_CALL_ARG_LIST_HEAD:
            return tac_join(children_tac[0],tac_join(tac_create(TAC_PUSH_ARGS,children_tac[0]->result,0,0),children_tac[1]));
        case TREE_EXP_FUNC_CALL_ARG_LIST_TAIL:
            return tac_create(TAC_PUSH_ARGS, children_tac[0]->result,0,0);
        /* Function declaration */
        case TREE_DECLARATION_FUC:
            return tac_join(tac_create(TAC_BEGINFUNC,node->child[1]->symbol,0,0), tac_join(children_tac[2],
                           tac_join(children_tac[3],
                              tac_create(TAC_ENDFUNC, node->child[1]->symbol, 0, 0))));
        case TREE_DEC_FUC_PARAM_HEAD: //fprintf(stderr, "ASTREE_FUNC_DEC_PARAMS\n" );
            return tac_join(tac_create(TAC_POP_ARGS,node->child[1]->symbol,0,0),children_tac[2]);
        case TREE_DEC_FUC_PARAM_TAIL:
            return tac_create(TAC_POP_ARGS,node->child[1]->symbol,0,0);






        default:
            if(node != NULL) {
                printf("ERROR. Unknown TREE NODE %d.\n", node->type);

            } 

            break;
    }
    return NULL;
}


