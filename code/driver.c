// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "lexer.h"
#include "symbol_table.h"
#include "ast.h" 

int line;
int column;
char last,ch;
FILE * fp;
extern entry lookup_table[40];
extern entry_map_nt map_nt[56];
extern entry_map_t map_t[59];
int parseTable[56][59];
table T;
extern int main_seen;
int main(int argc, char* argv[])
{
	if( argc == 3 ) 
	{
		init();
		init_map_t();
		init_map_nt();

		grammar g = get_grammar();

		FirstAndFollow f = ComputeFirstAndFollowSets(g);
		printf("FIRSTS\n\n\n\n");
		for(int i=0;i<57;i++)
		{
			printf("%s\n",f.firsts[i].lhs );
			printStack(f.firsts[i].rhs);
		}
		printf("FOLLOWS\n\n\n\n");
		for(int i=0;i<57;i++)
		{
			printf("%s\n",f.follows[i].lhs );
			printStack(f.follows[i].rhs);


		}
		fflush(stdout);
		fill_parseTable(g,f,T.parseTable);
		parseTree programNode=*((parseTree* )malloc(sizeof(parseTree)));
		
		fp=fopen( "clean_code.txt", "r" );
		line=0;
		column=1;
		printf("-----FIRST AND FOLLOW AUTOMATED-----\n");
		int num=-1;
		
		while(1)
		{
			if(num==1){ 
				removeComments(argv[1],"clean_code.txt"); 
				FILE* clean_fp=fopen("clean_code.txt","r");
				char c;
				while((c=fgetc(clean_fp))!=EOF)
	       			printf("%c",c);
				num=-1; 
			}
			else if(num==2)
			{
				LexerOutput(argv[1]);
				fp=fopen( "clean_code.txt", "r" );
				line=0;
				column=1;
				num=-1;
			}
			else if (num==3)
			{
				programNode=parseInputSourceCode(argv[1],T,g,f);
				// fclose(fp);
				fp=fopen( "clean_code.txt", "r" );
				line=0;
				column=1;
				num=-1;
			}  
			else if(num==4)
			{
				FILE* out_fp=fopen(argv[2],"w");
				programNode=parseInputSourceCode(argv[1],T,g,f);
				programNode.begin.ASTparent=NULL;
				// createAST(&programNode.begin,((programNode.begin).child));
				parseTreePrint(&programNode.begin,NULL,out_fp);
				// fprintf(out_fp,"\n\n\n\n");
				// ASTPrint(&programNode.begin,out_fp);
				DFS(&programNode.begin,out_fp,-1,0,0);
				// printf("%d\n", get_func_hash_value("readArr"));
				// printf("hello%s\n",symbol_table[get_func_hash_value("readArr")].func_name );
				// if(symbol_table[get_func_hash_value("readArr")].scope.func_table[0][0].variables[0]->next==NULL)
				// 	printf("hello\n");
				fflush(stdout);
				fp=fopen( "clean_code.txt", "r" );
				num=-1;
				line=0;
				column=1;
			}  
			else if(num==-1){
				printf("\nPress:\n1=> For the clean code\n");
				printf("2=> For printing token generated by lexer\n");
				printf("3=> For verifying the syntactic correctness\n");
				printf("4=> For printing the parse tree\n");
				printf("5=> For Exiting\n");
				scanf(" %d",&num);
				if(num==-1)
					num=0;
			}
			else if(num==5)
				break;
			else{
				printf("Incorrect Input.\n");
				num=-1;
				break;
			}
		}
	}
	else if( argc > 3 ) {
	    printf("Too many arguments supplied.\n");
	}
	else{
	    printf("Insufficient arguments.\n");
	}

	// GenerateSymbolTable()
	// {
	// 	removeComments(testcaseFile,"clean_code.txt");
	// 	while(1)
	// 	{		
	// 		tokenInfo curr;
	// 		curr=getNextToken();
	// 		if (strcmp(curr.token,"$")==0)
	// 			break;
	// 		printf("%s %s %d \n",curr.lexeme,curr.token , curr.line);
	// 	}

	// }


	return 0;
}