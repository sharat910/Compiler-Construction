// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _parseTree
#define _parseTree

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
}TREE_NODE;

typedef TREE_NODE* TREE_NODE_PTR;

typedef struct {

	TREE_NODE begin;
}parseTree;
#endif