// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "lexer.h"
#include "symbolTable.h"
#include "ast.h" 
#include "codegen.h"
#include "semantic_checker.h"

extern int line;
extern int column;
extern char last;
char ch;
extern FILE * fp;
extern entry lookup_table[40];
extern entry_map_nt map_nt[56];
extern entry_map_t map_t[59];
extern int ast_node_count;
extern int parse_tree_node_count;
extern int parse_error_cnt;
extern int semantic_error_cnt;
extern int type_error_cnt;
int parseTable[56][59];
table T;
extern int main_seen;
int main(int argc, char* argv[])
{
	parse_error_cnt=0;
	semantic_error_cnt=0;
	type_error_cnt=0;
	if( argc == 2 ) 
	{
		init();
		init_map_t();
		init_map_nt();

		grammar g = get_grammar();
		FirstAndFollow f = ComputeFirstAndFollowSets(g);
		fill_parseTable(g,f,T.parseTable);
		parseTree programNode=*((parseTree* )malloc(sizeof(parseTree)));
		
		fp=fopen( "clean_code.txt", "r" );
		line=0;
		column=1;
		// printf("-----FIRST AND FOLLOW AUTOMATED-----\n");
		int num=-1;
		
		num=-1; 
		while(1)
		{
			if(num==1){ 
				removeComments(argv[1],"clean_code.txt"); 
				FILE* clean_fp=fopen("clean_code.txt","r");
				char c;
				while((c=fgetc(clean_fp))!=EOF)
		   			printf("%c",c);
				LexerOutput(argv[1]);
				fp=fopen( "clean_code.txt", "r" );
				line=0;
				column=1;
				num=8;	
			}
			else if(num==2)
			{
				removeComments(argv[1],"clean_code.txt"); 

				LexerOutput(argv[1]);
				fp=fopen( "clean_code.txt", "r" );
				line=0;
				column=1;
				programNode=parseInputSourceCode(argv[1],T,g,f);
				programNode.begin.ASTparent=NULL;
				if (!parse_error_cnt){
					assignParents(&programNode.begin,NULL);
					printf("\n\n*****************ParseTree****************\n\n");
					parseTreePrint(&programNode.begin,NULL);
					printf("%s\n","Correct Syntax. Parsing Successful.");
				}
				else
					printf("Kindly correct the syntax errors before request for Print Parse Tree\n");
				fp=fopen( "clean_code.txt", "r" );
				line=0;
				column=1;
				num=8;
			}
			else if (num==3)
			{
				removeComments(argv[1],"clean_code.txt"); 

				LexerOutput(argv[1]);
				fp=fopen( "clean_code.txt", "r" );
				line=0;
				column=1;
				programNode=parseInputSourceCode(argv[1],T,g,f);
				programNode.begin.ASTparent=NULL;
				if (!parse_error_cnt){
					assignParents(&programNode.begin,NULL);
					construct2AST(&programNode.begin);
					printf("\n\n*****************AST****************\n\n");
			        printf("\nAST is:\n");
					printf("%-20s%-20s%-20s%-20s%-20s%-20s%-20s\n",
						"lexemeCurrentNode","lineno","token","valueIfNumber",
						"parentNodeSymbol","isLeafNode(yes/no)","NodeSymbol");
					if(type_error_cnt)
					{
						printf("Type Errors in code please fix them.\n");
					}
					else print2AST(&programNode.begin);
				}				
				else
					printf("Kindly correct the syntax errors before request for Print AST\n");
				
				fp=fopen( "clean_code.txt", "r" );
				line=0;
				column=1;
				num=8;
				
			}  
			else if(num==4)
			{
				/*
				Parse tree     Number of nodes = 150 Allocated Memory = 1024 Bytes
				AST               Number of nodes = 30 Allocated Memory = 200 Bytes
				Compression percentage = ((1024‐200)/1024)*100
				*/
				removeComments(argv[1],"clean_code.txt"); 

				LexerOutput(argv[1]);
				fp=fopen( "clean_code.txt", "r" );
				line=0;
				column=1;
				programNode=parseInputSourceCode(argv[1],T,g,f);
				programNode.begin.ASTparent=NULL;
				if (!parse_error_cnt){
					assignParents(&programNode.begin,NULL);
					construct2AST(&programNode.begin);
					count_AST_Nodes(&programNode.begin);
					count_Parse_Tree_Nodes(&programNode.begin);
					int p_mem = sizeof(TREE_NODE)*parse_tree_node_count;
					int a_mem = sizeof(AST_NODE)*ast_node_count;
					if(type_error_cnt)
					{
						printf("Type Errors in code please fix them.\n");
					}
					else{
						printf("Parse tree\tNumber of nodes = %d\tAllocated Memory = %dBytes\n",parse_tree_node_count,p_mem);
						printf("AST       \tNumber of nodes = %d\tAllocated Memory = %dBytes\n",ast_node_count,a_mem);
						float cp = (p_mem - a_mem) / (float)p_mem;
						printf("Compression percentage = ((%d‐%d)/%d)*100 = %f\n",p_mem,a_mem,p_mem,cp);
					}
				}
				else
					printf("Kindly correct the syntax errors before request for Compression Percentage\n");
				num=8;
			}
			else if(num==5){
				removeComments(argv[1],"clean_code.txt"); 

				LexerOutput(argv[1]);
				fp=fopen( "clean_code.txt", "r" );
				line=0;
				column=1;
				programNode=parseInputSourceCode(argv[1],T,g,f);
				programNode.begin.ASTparent=NULL;	
				if (!parse_error_cnt){
					assignParents(&programNode.begin,NULL);
					constructSymbolTable(&programNode.begin,-1,0,0);
					constructAST(&programNode.begin);
					if(type_error_cnt){
						printf("\n\n*****************SymbolTable****************\n\n");
						printSymbolTable(programNode.begin.nptr,1);
						printf("Type errors exist. Please fix them.\n");
					}
					else {
						printf("\n\n*****************SymbolTable****************\n\n");
						printSymbolTable(programNode.begin.nptr,1);
					}
				}else
					printf("Kindly correct the syntax errors before request for Symbol Table\n");
				fp=fopen( "clean_code.txt", "r" );
				num=8;
				line=0;
				column=1;
			} 				
			else if(num==6){
				removeComments(argv[1],"clean_code.txt"); 

				LexerOutput(argv[1]);
				fp=fopen( "clean_code.txt", "r" );
				line=0;
				column=1;
				programNode=parseInputSourceCode(argv[1],T,g,f);
				programNode.begin.ASTparent=NULL;
				if (!parse_error_cnt){
					assignParents(&programNode.begin,NULL);
					constructSymbolTable(&programNode.begin,-1,0,0);
					constructAST(&programNode.begin);

					if(type_error_cnt)
					{
						printf("Type Errors in code please fix them.\n");
					}
					else{
						semantic_check(programNode.begin.nptr);
						if(semantic_error_cnt)
						{
							printf("Semantic Errors in code please fix them.\n");
						}
						else{
							printf("Code compiles successfully.........\n");
						}
					}
				}else
					printf("Kindly correct the syntax errors before request for Compression Percentage\n");
				fp=fopen( "clean_code.txt", "r" );
				num=8;
				line=0;
				column=1;
			} 	
			else if(num==7){
				removeComments(argv[1],"clean_code.txt"); 

				LexerOutput(argv[1]);
				fp=fopen( "clean_code.txt", "r" );
				line=0;
				column=1;
				programNode=parseInputSourceCode(argv[1],T,g,f);
				programNode.begin.ASTparent=NULL;
				if (!parse_error_cnt){
					assignParents(&programNode.begin,NULL);
					constructSymbolTable(&programNode.begin,-1,0,0);
					constructAST(&programNode.begin);
					if(type_error_cnt)
					{
						printf("Type Errors in code please fix them.\n");
					}
					else{
						if(semantic_error_cnt)
							printf("Semantic Errors in code please fix them.\n");
						else{
							semantic_check(programNode.begin.nptr);
							generate_code(programNode.begin.nptr);	
							printf("Code compiles successfully.........\n");
							printf("\n\nAssembly code produced in assembly.asm\n\n" );	
						}
					}
				}
				else
					printf("Kindly correct the syntax errors before request for Code Generation\n");	
				fp=fopen( "clean_code.txt", "r" );
				num=8;
				line=0;
				column=1;
			} 	
			else if(num==-1){
				printf("\n\n---------------LEVEL 4----------------\n\n");
				printf("To run generated assembly code use:\n");
				printf("nasm -felf64 assembly.asm && gcc assembly.o && ./a.out \n");
				printf("\nPress:\n1=> For token list generated by the lexer \n");
				printf("2=>  For parsing to verify the syntactic correctness of the input source code and to produce parse tree\n");
				printf("3=> For printing the Abstract Syntax Tree in appropriate format\n");
				printf("4=>  For displaying the amount of allocated memory and number of nodes to each of parse tree and abstract syntax tree for the test case used\n");
				printf("5=> For printing the Symbol Table in appropriate format showing all relevant information\n");
				printf("6=> For compiling to verify the syntactic and semantic correctness of the input source code\n");
				printf("7=> For producing assembly code\n");
				printf("8=> For exiting\n");
				scanf(" %d",&num);
				if(num==-1)
					num=0;
			}
			else if(num==8)
				break;
			else{
				printf("Incorrect Input.\n");
				num=-1;
				break;
			}
		}
	}
	else if( argc > 2 ) {
	    printf("Too many arguments supplied.\n");
	}
	else{
	    printf("Insufficient arguments.\n");
	}

	return 0;
}