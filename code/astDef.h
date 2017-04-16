// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _astDef
#define _astDef
#include "symbolTableDef.h"
struct ast_node;
typedef struct tree_node
{
	char lexemeCurrentNode[25];
	int lineno;
	char token[25];
	float valueLfNumber;
	char parentNodeSymbol[25];
	int isLeafNode;
	char NodeSymbol[25];
	struct tree_node* parent;
	struct tree_node* child;
	struct tree_node* sibling;
	int hash_value;
	int nesting;
	int offset;
	
	int rule_no;
	struct ast_node* nptr;
	char* type;

	struct tree_node *ASTparent;
    struct tree_node *ASTchild;
    struct tree_node *ASTsibling;

}TREE_NODE;

typedef TREE_NODE* TREE_NODE_PTR;

typedef struct {
	TREE_NODE begin;
}parseTree;



typedef struct ast_node{
	int is_leaf;
	
	char name[30];
	VAR st_ptr;
	int value;
	int type;
	int line_no;
	TREE_NODE_PTR ptNode;
	struct ast_node* array[6];
	int count;

}AST_NODE;

#endif