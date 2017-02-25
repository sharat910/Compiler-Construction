#ifndef _rule_table
#define _rule_table

#include "stackadt.h"


typedef struct{
	char lhs[50];
	stack rhs;
}rule;

typedef struct 
{
	rule rules[100];
	rule rules_back[100];	
} grammar;

extern grammar rule_table_init();

#endif