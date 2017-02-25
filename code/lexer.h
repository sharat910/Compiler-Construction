#ifndef _lexer
#define _lexer
typedef struct 
{
	char token[25];
	int line;
	int column;

}tokenInfo;



extern tokenInfo getNextToken();
// extern void removeComments(char *testcaseFile, char *cleanFile);

#endif