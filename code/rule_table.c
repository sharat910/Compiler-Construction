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
		sprintf()
	}
}
