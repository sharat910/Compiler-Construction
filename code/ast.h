// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _ast
#define _ast
#include "astDef.h"
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
extern int printSymbolTable(AST_NODE* root,int num);
extern int non_term_to_remove(char *non_terminal);
extern int to_eps(char *non_terminal);
extern int term_to_remove(char *terminal);
extern void create2AST(TREE_NODE_PTR parent, TREE_NODE_PTR child);
extern void construct2AST(TREE_NODE_PTR PT);
extern void print2AST(TREE_NODE_PTR root);
extern void count_AST_Nodes(TREE_NODE_PTR root);
extern void count_Parse_Tree_Nodes(TREE_NODE_PTR  t);
#endif