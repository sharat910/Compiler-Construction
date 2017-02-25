#include "rule_table.h"
#include <stdio.h>
#include <stdlib.h>

rule rules[100];
rule rules_back[100];
void rule_table_init()
{
	char s[50];
	FILE* fp=fopen("line_numbered_grammar_normal.txt","r");
	while(fscanf(fp,"%s",s) != EOF)
	{
		int l=atoi(s);
		fscanf(fp,"%s",s);
		// printf("%s\n",s );
		sprintf(rules[l].lhs,"%s",s);
		fscanf(fp,"%s",s);
		int a=atoi(s);
		while(a--)
		{
			fscanf(fp,"%s",s);
			// printf("%s\n",s );
			rules[l].rhs=push(rules[l].rhs,s);
		}
	}

	FILE* fp2=fopen("line_numbered_grammar_reverse.txt","r");
	while(fscanf(fp2,"%s",s) != EOF)
	{
		int l=atoi(s);
		fscanf(fp2,"%s",s);
		// printf("%s\n",s );
		sprintf(rules_back[l].lhs,"%s",s);
		fscanf(fp2,"%s",s);
		int a=atoi(s);
		while(a--)
		{
			fscanf(fp2,"%s",s);
			// printf("%s\n",s );
			rules_back[l].rhs=push(rules_back[l].rhs,s);
		}
	}
}
