#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "hash.h"

TREENODE* createNode(int type, HASHCELL *symbol, TREENODE *child1,TREENODE *child2,TREENODE *child3,TREENODE *child4)
{
  TREENODE *node = calloc(sizeof(TREENODE),1);
  node->type = type;
  node->symbol = symbol;
  node->child[0] = child1;
  node->child[1] = child2;
  node->child[2] = child3;
  node->child[3] = child4;
  return node;
  
}

void printTree(TREENODE *node)
{
    int numChild = 0;
    printf("(type id:%d",node->type);
    if(node->symbol!=NULL)
    {
      printf(" value: %s", node->symbol->key);
    }
    while(node->child[numChild]!=NULL && numChild<4)
      numChild++;
    int cursor=0;
    while(numChild>0)
    { 
      printf(", ");
      printTree(node->child[cursor]);
      numChild--;
      cursor++;
    }
    printf(")");   
      
}

/* COlocar ; apenas nas variáveis globais e nas declarações de funções e também
dentro dos cmd_block */

void print_code(FILE *outFile,TREENODE *node){
  TREENODE *tmp;
  tmp = node;


  if(tmp != NULL) {
    switch(tmp->type) {
      case TREE_DECLARATION:
        print_code(outFile, tmp->child[0]);
        print_code(outFile, tmp->child[1]);
        break;

    case TREE_DECLARATION_SCALAR:
      print_code(outFile, tmp->child[0]);
      fprintf(outFile, " ");
      print_code(outFile, tmp->child[1]);
      fprintf(outFile, " : ");
      print_code(outFile, tmp->child[2]);
      fprintf(outFile, ";\n");
      break;


    case TREE_INTEGER:
    	fprintf(outFile, "%s", tmp->symbol->key);
    	break;
    case TREE_CHAR:
      fprintf(outFile, "%s",tmp->symbol->key);
      break;

	case TREE_IDENTIFIER:
    case TREE_STRING:
      fprintf(outFile, "%s",tmp->symbol->key);
      break;

    case TREE_CMD_ATTR_VAR_VEC:
      print_code(outFile, tmp->child[0]);
      fprintf(outFile, "[");
      print_code(outFile, tmp->child[1]);
      fprintf(outFile, "] =");
      print_code(outFile, tmp->child[2]);
      break;

    case TREE_DECLARATION_VEC_LIT:
      print_code(outFile, tmp->child[0]);
      fprintf(outFile, " ");
      print_code(outFile, tmp->child[1]);
      fprintf(outFile, " [");
      print_code(outFile, tmp->child[2]);
      fprintf(outFile, "] : ");
      print_code(outFile, tmp->child[3]);
      fprintf(outFile,";\n");
      break;
      
    case TREE_DECLARATION_VEC_NOLIT:
      print_code(outFile, tmp->child[0]);
      fprintf(outFile, " ");
      print_code(outFile, tmp->child[1]);
      fprintf(outFile, " [");
      print_code(outFile, tmp->child[2]);
      fprintf(outFile, "];\n");
      break;

    case TREE_DEC_VAR_VEC_LIT_LIST_HEAD:
      print_code(outFile, tmp->child[0]);
      fprintf(outFile, " ");
      print_code(outFile, tmp->child[1]);
      break;

    case TREE_DEC_VAR_VEC_LIT_LIST_TAIL:
      print_code(outFile, tmp->child[0]);
      break;

    case TREE_DECLARATION_FUC:
      print_code(outFile, tmp->child[0]);
      fprintf(outFile, " ");
      print_code(outFile, tmp->child[1]);
      fprintf(outFile, " (");
      print_code(outFile, tmp->child[2]);
      fprintf(outFile, ")");
      print_code(outFile, tmp->child[3]);
      fprintf(outFile, ";");
      break;

    case TREE_DEC_FUC_PARAM_HEAD:
      print_code(outFile, tmp->child[0]);
      fprintf(outFile, " ");
      print_code(outFile, tmp->child[1]);
      fprintf(outFile, ", ");
      print_code(outFile, tmp->child[2]);
      break;
    case TREE_DEC_FUC_PARAM_TAIL:
      print_code(outFile, tmp->child[0]);
      fprintf(outFile, " ");
      print_code(outFile, tmp->child[1]);
      break;

    case TREE_CMD_BLOCK:
      fprintf(outFile, "{ \n");
      print_code(outFile, tmp->child[0]);
      fprintf(outFile, "}");
      break;

    case TREE_CMD_LIST_HEAD:
      print_code(outFile, tmp->child[0]);
      fprintf(outFile, ";");
      print_code(outFile, tmp->child[1]);
      break;

    case TREE_CMD_LIST_TAIL:
      print_code(outFile, tmp->child[0]);
      fprintf(outFile, ";");
      break;

      case TREE_CMD_READ:
        fprintf(outFile, "read ");
        print_code(outFile, tmp->child[0]);
        break;

      case TREE_CMD_PRINT:
        fprintf(outFile, "print ");
        print_code(outFile, tmp->child[0]);
        break;

      case TREE_CMD_PRINT_LIST_HEAD:
        print_code(outFile, tmp->child[0]);
        fprintf(outFile," ");
        print_code(outFile, tmp->child[1]);
        break;

      case TREE_CMD_PRINT_LIST_TAIL:
        print_code(outFile, tmp->child[0]);
        fprintf(outFile,";\n");
        break;

      case TREE_CMD_RETURN:
        fprintf(outFile, "return ");
        print_code(outFile, tmp->child[0]);
        break;


    case TREE_CMD_FOR_TO:
      fprintf(outFile, "for (");
        print_code(outFile, tmp->child[0]);
        fprintf(outFile, " = ");
        print_code(outFile, tmp->child[1]);
        fprintf(outFile, " to ");
        print_code(outFile, tmp->child[2]);
        fprintf(outFile, ")\n");
        print_code(outFile, tmp->child[3]);
        break;

    case TREE_CMD_ATTR_VAR_SCALAR:
      print_code(outFile, tmp->child[0]);
        fprintf(outFile, " = ");
        print_code(outFile, tmp->child[1]);
        break;
    case TREE_CMD_FOR:
      fprintf(outFile, "for (");
       print_code(outFile, tmp->child[0]);
       fprintf(outFile, ")");
       print_code(outFile, tmp->child[1]);
       break;
    
    case TREE_EXP_BRACKET_ENCLOSURE:
      fprintf(outFile, "(");
       print_code(outFile, tmp->child[0]);
       fprintf(outFile, ")");
       break;

    case TREE_EXP_VEC_INDEX:
      print_code(outFile, tmp->child[0]);
       fprintf(outFile, "[");
       print_code(outFile, tmp->child[1]);
       fprintf(outFile, "]");
       break;

    case TREE_EXP_OP_BINARY:
      print_code(outFile, tmp->child[0]);
       fprintf(outFile, " ");
       print_code(outFile, tmp->child[1]);
       fprintf(outFile, " ");
       print_code(outFile, tmp->child[2]);
       break;
        

    case TREE_EXP_FUNC_CALL:
      print_code(outFile, tmp->child[0]);
      fprintf(outFile, "(");
      print_code(outFile, tmp->child[1]);
      fprintf(outFile, ");\n");
      break;

    case TREE_EXP_FUNC_CALL_ARG_LIST_TAIL:
      print_code(outFile, tmp->child[0]);
      break;

    case TREE_EXP_FUNC_CALL_ARG_LIST_HEAD:
      print_code(outFile, tmp->child[0]);
      fprintf(outFile, ", ");
      print_code(outFile, tmp->child[1]);
      break;

    case TREE_KW_INTEGER:  
      fprintf(outFile, "int");
      break;

    case TREE_KW_CHAR:       
      fprintf(outFile, "char");
      break;

    case TREE_KW_FLOAT: 
      fprintf(outFile, "float");
      break;

    case TREE_KW_BOOL: 
      fprintf(outFile, "bool");
      break;


     case TREE_CMD_IF: 
       fprintf (outFile, "\nif (");
       print_code(outFile, tmp->child[0]); 
       fprintf (outFile, ") then\n");
       print_code(outFile, tmp->child[1]); 
       break;

    case TREE_CMD_IF_ELSE:
      fprintf (outFile, "\nif (");
       print_code(outFile, tmp->child[0]); 
       fprintf (outFile, ") then\n");
       print_code(outFile, tmp->child[1]); 
       fprintf(outFile, "else");
       print_code(outFile, tmp->child[2]); 
       break;

    case TREE_ADD: 
      //print_code(outFile, tmp->child[0]); 
      fprintf (outFile, " + ");
      //print_code(outFile, tmp->child[1]); 
      break;

    case TREE_SUB: 
      //print_code(outFile, tmp->child[0]); 
      fprintf (outFile, " - ");
      //print_code(outFile, tmp->child[1]); 
      break;

    case TREE_MUL: 
      //print_code(outFile, tmp->child[0]); 
      fprintf (outFile, " * ");
      //print_code(outFile, tmp->child[1]); 
      break;

    case TREE_DIV: 
      //print_code(outFile, tmp->child[0]); 
      fprintf (outFile, " / ");
      //print_code(outFile, tmp->child[1]); 
      break;

    case TREE_LE: 
      //print_code(outFile, tmp->child[0]); 
      fprintf (outFile, " <= ");
      //print_code(outFile, tmp->child[1]); 
      break;

    case TREE_GE: 
      //print_code(outFile, tmp->child[0]); 
      fprintf (outFile, " >= ");
      //print_code(outFile, tmp->child[1]); 
      break;

    case TREE_EQ: 
      //print_code(outFile, tmp->child[0]); 
      fprintf (outFile, " == ");
      //print_code(outFile, tmp->child[1]); 
      break;

    case TREE_NE: 
      //print_code(outFile, tmp->child[0]); 
      fprintf (outFile, " != ");
      //print_code(outFile, tmp->child[1]); 
      break;

    case TREE_AND: 
      //print_code(outFile, tmp->child[0]); 
      fprintf (outFile, " && ");
      //print_code(outFile, tmp->child[1]); 
      break;

    case TREE_OR: 
      //print_code(outFile, tmp->child[0]); 
      fprintf (outFile, " || ");
      //print_code(outFile, tmp->child[1]); 
      break;

    case TREE_L: 
//       print_code(outFile, tmp->child[0]); 
      fprintf (outFile, " < ");
//       print_code(outFile, tmp->child[1]); 
      break;

    case TREE_G: 
//       print_code(outFile, tmp->child[0]); 
      fprintf (outFile, " > ");
//       print_code(outFile, tmp->child[1]); 
      break;
      
    case TREE_CMD_EMPTY:
    	break;

    default:
      fprintf(outFile,"\n");
      if(tmp->symbol != NULL)
	printf("erro : %s \n",tmp->symbol->key);
      exit(0);
      break;
  }}}
