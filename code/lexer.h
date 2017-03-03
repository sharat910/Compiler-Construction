// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _lexer
#define _lexer
#include<stdio.h>
#include "lexerDef.h"
typedef struct 
{
	char token[25];
	int line;
	int column;
	char lexeme[25];

}tokenInfo;

FILE* getStream(FILE* fp);
tokenInfo getNextToken();
void removeComments(char *testcaseFile, char *cleanFile);
void init();
void init_map_nt();
void init_map_t();

#endif