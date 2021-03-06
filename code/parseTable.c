// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#include "parseTable.h"

extern entry_map_nt map_nt[56];
extern entry_map_t map_t[59];


stack total_first(stack rhs,rule firsts[])
{
	stack ans;
	ans=*((stack* )malloc(sizeof(stack)));
	NODE top=rhs.top;
	
	if(isTerminal(top)){		
		ans=distinct_push(ans,top->str);
		return ans;
	}
	while(top!= NULL &&  !(isTerminal(top))&& 
		find_stack(&firsts[get_index_nt(top->str)].rhs,"e"))
	{
		ans=merge(ans,firsts[get_index_nt(top->str)].rhs);
		top=top->link;
	}
	if(top==NULL){
		return ans;
	}
	if (top!= NULL &&  !(isTerminal(top)))
		ans=merge(ans,firsts[get_index_nt(top->str)].rhs);

	if(isTerminal(top))
		ans=distinct_push(ans,top->str);
	fflush(stdout);
	return ans;
}

void fill_parseTable(grammar g,FirstAndFollow f,int parseTable[56][59])
{
	for(int i=1;i<109;i++)
	{

		int found=0;
		char * lhs=g.rules_back[i].lhs;
		stack rhs= g.rules_back[i].rhs;
		stack curr_firsts=total_first(rhs,f.firsts);
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
			stack curr_follows=f.follows[get_index_nt(lhs)].rhs;
			NODE top=curr_follows.top;
			while(top!=NULL)
			{
				if(isTerminal(top)){					
					parseTable[get_index_nt(lhs)][get_index_t(top->str)]=i;
				}
				top=top->link;				
			}
		}
	}
}