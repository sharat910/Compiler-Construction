#ifndef _ff
#define _ff


#include "rule_table.h"

extern rule rules[100];
int isTerminal(stack s);
void fill_lhs();
void fill_firsts(rule rules[100]);


#endif