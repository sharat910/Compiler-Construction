#ifndef _rule_table
#define _rule_table

#include "stackadt.h"


typedef struct{
	char lhs[50];
	stack rhs;
}rule;

extern void rule_table_init();

#endif