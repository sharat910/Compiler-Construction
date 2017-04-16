// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _ast
#define _ast
#include "astDef.h"
#include "parseTree.h"
#include <string.h>
extern int is_terminal(TREE_NODE_PTR node);
extern int is_non_terminal(TREE_NODE_PTR node);
extern AST_NODE* make_ast_leaf(TREE_NODE_PTR node, int type, int value);
extern AST_NODE* make_ast_node(TREE_NODE_PTR node);
extern TREE_NODE_PTR find_first_nt(TREE_NODE_PTR node);
extern AST_NODE* find_id_ka_nptr(TREE_NODE_PTR node);
extern void magic_function(TREE_NODE_PTR node);
extern void recursive_function(TREE_NODE_PTR node);
extern void constructAST(TREE_NODE_PTR root);
extern void printAST(AST_NODE* root);
#endif