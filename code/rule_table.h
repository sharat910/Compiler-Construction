// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _rule_table
#define _rule_table

#include "stackadt.h"


typedef struct{
	char lhs[50];
	stack rhs;
}rule;

typedef struct 
{
	rule rules[110];
	rule rules_back[110];	
} grammar;

extern grammar get_grammar();
#endif