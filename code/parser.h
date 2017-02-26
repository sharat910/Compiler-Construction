#ifndef _parser
#define _parser

#include "rule_table.h"
#include "parseTable.h"
#include "parseTree.h"
#include "parserDef.h"

int isTerminal(NODE top);

FirstAndFollow  ComputeFirstAndFollowSets(grammar G);
void createParseTable(grammar G,FirstAndFollow  F, table T);
parseTree  parseInputSourceCode(char *testcaseFile, table T);
void printParseTree(parseTree  PT, char *outfile);

#endif