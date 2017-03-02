#ifndef _rule_table
#define _rule_table

#include "stackadt.h"


typedef struct{
	char lhs[50];
	stack rhs;
}rule;

typedef struct 
{
	rule rules[109];
	rule rules_back[109];	
} grammar;

extern grammar get_grammar();
#endif