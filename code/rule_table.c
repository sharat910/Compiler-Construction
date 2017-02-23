#include "rule_table.h"
#include <stdio.h>

rule rules[100];

void rule_table_init()
{
	char str[50];
	FILE* fp=fopen("grammer.txt","r");
	while(fscanf(fp,"%s",str) != EOF)
	{
		int l=atoi(s);
		fscanf(fp,"%s",str);
		sprintf(rule[l].lhs,str);
		int a=atoi(fscanf(fp,"%s",str));
		while(a--)
		{
			rule[l].rhs.push(rule[l].rhs,str);
		}
	}
}
