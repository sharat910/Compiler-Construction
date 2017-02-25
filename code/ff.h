#ifndef _ff
#define _ff


#include "rule_table.h"

typedef struct 
{
	rule firsts[57];
	rule follows[57]; 
} FirstAndFollow;

int isTerminal(NODE top);
FirstAndFollow getFirstAndFollow(grammar G);

#endif