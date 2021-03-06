// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _parser
#define _parser

#include "rule_table.h"
#include "parseTable.h"
#include "lexer.h"
#include "astDef.h"
#include "parserDef.h"
#include "stack_ptr.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isTerminal(NODE top);

FirstAndFollow  ComputeFirstAndFollowSets(grammar G);
void createParseTable(grammar G,FirstAndFollow  F, table T);
parseTree  parseInputSourceCode(char *testcaseFile, table T,grammar G,FirstAndFollow  F);
void printParseTree(parseTree  PT, char *outfile);
void LexerOutput(char *testcaseFile);
void parseTreePrint(TREE_NODE_PTR root,TREE_NODE_PTR parent);
void ASTPrint(TREE_NODE_PTR root);
void assignParents(TREE_NODE_PTR root,TREE_NODE_PTR parent);

#endif