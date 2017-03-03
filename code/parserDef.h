// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _parserDef
#define _parserDef


typedef struct 
{
	rule firsts[57];
	rule follows[57]; 
}FirstAndFollow;

typedef struct 
{
	int parseTable[56][59];
}table;

#endif