// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _ast2
#define _ast2

#include "astDef.h"
#include <string.h>
extern int non_term_to_remove(char *non_terminal);
extern int to_eps(char *non_terminal);
extern int term_to_remove(char *terminal);
extern void create2AST(TREE_NODE_PTR parent, TREE_NODE_PTR child);
void construct2AST(TREE_NODE_PTR PT);
void print2AST(TREE_NODE_PTR root);

#endif