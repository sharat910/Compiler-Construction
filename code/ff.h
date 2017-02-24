#ifndef _ff
#define _ff


#include "rule_table.h"

int isTerminal(NODE top);
void fill_lhs();
void fill_firsts();
void fill_follows();

#endif