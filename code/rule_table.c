#include "rule_table.h"
#include <stdio.h>
#include <stdlib.h>

rule rules[109];
rule rules_back[109];
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
			// printStack(rules[l].rhs);
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

grammar get_grammar()
{
	rule_table_init();
	grammar g;
	for (int i = 1; i < 109; ++i)
	{

		sprintf(g.rules[i].lhs,"%s",rules[i].lhs);
		g.rules[i].rhs = rules[i].rhs;
		sprintf(g.rules_back[i].lhs,"%s",rules_back[i].lhs);
		g.rules_back[i].rhs = rules_back[i].rhs;
	}
	return g;
}
