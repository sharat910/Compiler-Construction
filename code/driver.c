#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "index_nt.h"
#include "index_t.h"
#include "rule_table.h"
#include "parseTable.h"
#include "parser.h"
#include "lexer.h"
#include "parseTree.h"
// #include "stackadt.h"
int line;
int column;
char last,ch;
FILE * fp;
extern entry lookup_table[40];
extern entry_map_nt map_nt[53];
extern entry_map_t map_t[59];
int parseTable[53][59];
table T;
int main()
{
	// printf("ele");
	init();
	init_map_t();
	init_map_nt();
	// printf("Adele");
	// fflush(stdout);
	grammar g = get_grammar();

	for(int i=1;i<99;i++)
	{
		printf("%s --> ",g.rules_back[i].lhs);
		printStack(g.rules_back[i].rhs);
		fflush(stdout);
	}

	// printf("hello\n");
	FirstAndFollow f = ComputeFirstAndFollowSets(g);
	printf("it's me");
	for(int i=0;i<53;i++)
	{
		printf("%s \n",map_nt[i].incoming );
		printStack(f.firsts[i].rhs);
	}
	for(int i=0;i<53;i++)
	{
		printf("%s \n",map_nt[i].incoming );
		printStack(f.follows[i].rhs);
	}

	

	fill_parseTable(g,f,T.parseTable);
	for(int i=0;i<53;i++){
		for(int j=0;j<59;j++)
		{

			printf("%d ",T.parseTable[i][j] );
		}
		printf("\n");
	}
	printf("over\n");
	for(int i=1;i<101;i++)
	{
		printf("%s --> ",g.rules_back[i].lhs);
		printStack(g.rules_back[i].rhs);
	}

	// for(int i=0;i<53;i++)
	// {
	// 	printf("%s ,%d\n",map_nt[i].incoming,map_nt[i].index);
	// }
	parseTree programNode=*((parseTree* )malloc(sizeof(parseTree)));
	
	
	fp=fopen( "clean_code.txt", "r" );
	line=0;
	column=1;
	// LexerOutput("code.txt");    
	programNode=parseInputSourceCode("code.txt",T,g,f);
	// printf("%s\n",programNode.begin.parentNodeSymbol );
	parseTreePrint(&programNode.begin);
	// printf("Program End\n");
}