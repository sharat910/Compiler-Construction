// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _ast
#define _ast

#include "parseTree.h"
#include <string.h>
extern int non_term_to_remove(char *non_terminal);
extern int to_eps(char *non_terminal);
extern int term_to_remove(char *terminal);
extern void createAST(TREE_NODE_PTR parent, TREE_NODE_PTR child);

#endif