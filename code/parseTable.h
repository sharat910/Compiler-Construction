#ifndef _parseTable
#define _parseTable

#include "rule_table.h"
#include "parserDef.h"
#include "parseTable.h"
#include <stdio.h>
#include "stackadt.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>

extern void fill_parseTable(grammar g,FirstAndFollow f,int parseTable[54][59]);

#endif