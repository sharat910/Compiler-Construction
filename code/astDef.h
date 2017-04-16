// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _astDef
#define _astDef
#include "symbolTableDef.h"

typedef struct ast_node{
	int is_leaf;
	
	char name[30];
	VAR st_ptr;
	int value;
	int type;
	int line_no;
	struct ast_node* array[6];
	int count;

}AST_NODE;

#endif