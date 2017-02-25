#include "parseTable.h"
#include <stdio.h>
#include "index_nt.h"
#include "index_t.h"
#include "rule_table.h"
#include "stackadt.h"
#include "ff.h"
#include <string.h>

// extern entry lookup_table[40];
extern entry_map_nt map_nt[53];
extern entry_map_t map_t[59];
extern rule rules[100];
extern rule rules_back[100];
extern rule firsts[53];
extern rule follows[53];
int parseTable[53][59];

stack total_first(stack rhs)
{
	stack ans;
	NODE top=rhs.top;
	while(top!= NULL && find_stack(&firsts[get_index_nt(top->str)].rhs,"e"))
	{
		ans=merge(ans,firsts[get_index_nt(top->str)].rhs);
		top=top->link;
	}
	return ans;
}

void fill_parseTable()
{
	for(int i=1;i<99;i++)
	{
		int found=0;
		char * lhs=rules[i].lhs;
		stack rhs= rules[i].rhs;
		stack curr_firsts=total_first(rhs);
		NODE top=curr_firsts.top;
		while(top!=NULL)
		{
			if(strcmp(top->str,"e")==0)
				found=1;
			parseTable[get_index_nt(lhs)][get_index_t(top->str)]=i;
			top=top->link;
		}

		if(found)
		{
			stack curr_follows=follows[get_index_nt(lhs)].rhs;
			NODE top=curr_follows.top;
			while(top!=NULL)
			{
				if(strcmp(top->str,"$")==0)
					found=2;
				if(isTerminal(top))

					parseTable[get_index_nt(lhs)][get_index_t(top->str)]=i;
				top=top->link;
			}
			if(found==2)
				parseTable[get_index_nt(lhs)][get_index_t("$")]=i;
		}
	}
}