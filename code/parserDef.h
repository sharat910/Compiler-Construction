#ifndef _parserDef
#define _parserDef


typedef struct 
{
	rule firsts[57];
	rule follows[57]; 
}FirstAndFollow;

typedef struct 
{
	int parseTable[53][59];
}table;

#endif