#include <stdio.h>
#include <ctype.h>
#include "map.h"
#include "index_nt.h"
#include "index_t.h"
#include "rule_table.h"
#include "ff.h"
#include "parseTable.h"
#include "lexer.h"
// #include "stackadt.h"
int line;
int column;
char last,ch;
FILE * fp;
extern entry lookup_table[40];
extern entry_map_nt map_nt[53];
extern entry_map_t map_t[59];
extern rule rules[100];
extern rule rules_back[100];
extern rule firsts[53];
extern rule follows[53];
extern int parseTable[53][59];
int main()
{
	init();
	init_map_t();
	init_map_nt();
	rule_table_init();
	fill_lhs();
	fill_firsts();
	fill_follows();
	fill_parseTable();
	for(int i=0;i<53;i++){
		for(int j=0;j<59;j++)
		{
			printf("%d ",parseTable[i][j] );
		}
		printf("\n");
	}
	for(int i=0;i<53;i++)
	{
		printf("%s \n",map_nt[i].incoming );
		printStack(firsts[i].rhs);
	}
	for(int i=0;i<53;i++)
	{
		printf("%s \n",map_nt[i].incoming );
		printStack(follows[i].rhs);
	}
	for(int i=1;i<99;i++)
	{
		printf("%s --> ",rules_back[i].lhs);
		printStack(rules_back[i].rhs);
	}

	for(int i=0;i<53;i++)
	{
		printf("%s ,%d\n",map_nt[i].incoming,map_nt[i].index);
	}
	
	fp=fopen( "code.txt", "r" );
	last=fgetc(fp);
	line=1;
	column=1;
	while(!feof(fp))
	{
		// printf("hello\n");
		tokenInfo curr;
		curr=getNextToken();
		
		printf("%s %d %d\n", curr.token,curr.line,curr.column);
	}
	
	
	fclose(fp);
}