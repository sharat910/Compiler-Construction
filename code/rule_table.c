#include "rule_table.h"
#include <stdio.h>
#include <stdlib.h>

rule rules[100];
rule rules_back[100];
void rule_table_init()
{
	char s[50];
	FILE* fp=fopen("line_sep_grammar.txt","r");
	while(fscanf(fp,"%s",s) != EOF)
	{
		int l=atoi(s);
		fscanf(fp,"%s",s);
		// printf("%s\n",s );
		sprintf(rules[l].lhs,s);
		fscanf(fp,"%s",s);
		int a=atoi(s);
		while(a--)
		{
			fscanf(fp,"%s",s);
			// printf("%s\n",s );
			rules[l].rhs=push(rules[l].rhs,s);
		}
	}

	FILE* fp=fopen("line_sep_grammar_back.txt","r");
	while(fscanf(fp,"%s",s) != EOF)
	{
		int l=atoi(s);
		fscanf(fp,"%s",s);
		// printf("%s\n",s );
		sprintf(rules_back[l].lhs,s);
		fscanf(fp,"%s",s);
		int a=atoi(s);
		while(a--)
		{
			fscanf(fp,"%s",s);
			// printf("%s\n",s );
			rules_back[l].rhs=push(rules_back[l].rhs,s);
		}
	}
}
