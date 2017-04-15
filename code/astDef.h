// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _astDef
#define _astDef

typedef struct ast_node
{
	char val[20];
	char type[10];
	struct ast_node* parent;
	struct ast_node* child;
	struct ast_node* sibling;
	TREE_NODE_PTR parse_node;

}AST_NODE;

AST_NODE* AST_NODE_PTR;

#endif