#ifndef _lexer
#define _lexer
#include<stdio.h>
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

#endif