#include "ff.h"
#include <stdio.h>
#include "index_nt.h"

int isTerminal(NODE top)
{
	if(top->str[0]=='<')
		return 0;
	else return 1;	
}

void fill_lhs(rule array[57])
{
	sprintf(array[0].lhs,"<AOBE>");
	sprintf(array[1].lhs,"<output_plist>");
	sprintf(array[2].lhs,"<idList>");
	sprintf(array[3].lhs,"<statement>");
	sprintf(array[4].lhs,"<whichStmt>");
	sprintf(array[5].lhs,"<WithLogOp>");
	sprintf(array[6].lhs,"<moduleReuseStmt>");
	sprintf(array[7].lhs,"<idList_ex>");
	sprintf(array[8].lhs,"<declareStmt>");
	sprintf(array[9].lhs,"<MultiCase>");
	sprintf(array[10].lhs,"<simpleStmt>");
	sprintf(array[11].lhs,"<expression>");
	sprintf(array[12].lhs,"<term>");
	sprintf(array[13].lhs,"<index>");
	sprintf(array[14].lhs,"<module>");
	sprintf(array[15].lhs,"<lvalueARRStmt>");
	sprintf(array[16].lhs,"<negOrPosAE>");
	sprintf(array[17].lhs,"<dataType>");
	sprintf(array[18].lhs,"<input_plist>");
	sprintf(array[19].lhs,"<var>");
	sprintf(array[20].lhs,"<op2>");
	sprintf(array[21].lhs,"<N4>");
	sprintf(array[22].lhs,"<output_plist_ex>");
	sprintf(array[23].lhs,"<driverModule>");
	sprintf(array[24].lhs,"<program>");
	sprintf(array[25].lhs,"<iterativeStmt>");
	sprintf(array[26].lhs,"<caseStmts>");
	sprintf(array[27].lhs,"<logicalOp>");
	sprintf(array[28].lhs,"<whichId>");
	sprintf(array[29].lhs,"<ioStmt>");
	sprintf(array[30].lhs,"<input_plist_ex>");
	sprintf(array[31].lhs,"<ret>");
	sprintf(array[32].lhs,"<WithRelOp>");
	sprintf(array[33].lhs,"<condionalStmt>");
	sprintf(array[34].lhs,"<optional>");
	sprintf(array[35].lhs,"<op1>");
	sprintf(array[36].lhs,"<range>");
	sprintf(array[37].lhs,"<relationalOp>");
	sprintf(array[38].lhs,"<BorNBAE>");
	sprintf(array[39].lhs,"<factor>");
	sprintf(array[40].lhs,"<value>");
	sprintf(array[41].lhs,"<moduleDeclarations>");
	sprintf(array[42].lhs,"<otherModules>");
	sprintf(array[43].lhs,"<type>");
	sprintf(array[44].lhs,"<moduleDeclaration>");
	sprintf(array[45].lhs,"<moduleDef>");
	sprintf(array[46].lhs,"<default>");
	sprintf(array[47].lhs,"<N5>");
	sprintf(array[48].lhs,"<assignmentStmt>");
	sprintf(array[49].lhs,"<lvalueIDStmt>");
	sprintf(array[50].lhs,"<statements>");
	sprintf(array[51].lhs,"<arithmeticExpr>");
	sprintf(array[52].lhs,"<AnyTerm>");
}
void fill_firsts(rule rules_back[100],FirstAndFollow f)
{
	fill_lhs(f.firsts);
	for(int i=1;i<99;i++)
	{
		if(isTerminal(rules_back[i].rhs.top))
		{
			stack* a=&(f.firsts[get_index_nt(rules_back[i].lhs)].rhs);
			*a=distinct_push(*a,rules_back[i].rhs.top->str);
		}
	}
	int flag=1;
	int out=0;
	while(flag==1)
	{
		flag=0;
		for(int i=1;i<99;i++)
		{
			out=0;
			stack right=rules_back[i].rhs;
			NODE top=right.top;
			for(int j=1;j<=right.stack_size;j++)
			{
				if(out)
					break;
				stack* b=&(f.firsts[get_index_nt(rules_back[i].lhs)].rhs);
				if(isTerminal(top)==0)
				{
					stack* a= &f.firsts[get_index_nt(top->str)].rhs;
					int initial=(*b).stack_size;
						*b=merge(*b,*a);
					int final=(*b).stack_size;
					if(final>initial)
						flag=1;
					if(!find_stack(a,"e"))
						break;
				}
				else {
					int initial=(*b).stack_size;
					*b=distinct_push(*b,top->str);
					int final=(*b).stack_size;
					if(final>initial)
						flag=1;
					break;
				}
				top=top->link;
			}	
		}
	}
}

stack get_follow_stack(char* non_terminal,FirstAndFollow f){
	return f.follows[get_index_nt(non_terminal)].rhs;
}

stack get_first_stack(char* non_terminal,FirstAndFollow f){
	return f.firsts[get_index_nt(non_terminal)].rhs;
}

void fill_follows(rule rules_back[100],FirstAndFollow f)
{
	//Initial follow
	fill_lhs(f.follows);
	int flag = 1;
	stack* b=&(f.follows[get_index_nt("<program>")].rhs);
	(*b)=push((*b),"$");
	while(flag){
		flag = 0;
		for(int i=1;i<99;i++)
		{
			char* lhs = rules_back[i].lhs;
			stack right=rules_back[i].rhs;
			// printf("\n");
			// printStack(right);
			NODE item = right.top;
			int j=1;
			// printf("%d ",right.stack_size);
			while(item != NULL)
			{	
				//printf("%d",j);
				if(isTerminal(item)==0)
				{
					//printf("Non-terminal: %s\n",item->str);
					stack item_follow_stack = get_follow_stack(item->str,f);
					int prev_size = item_follow_stack.stack_size;
					NODE next = item->link;
					while(next != NULL)
					{
						if(isTerminal(next))
						{
							
							item_follow_stack = distinct_push(item_follow_stack,next->str);
							
							// printf("Adding terminal: %s\n",next->str);
							// printStack(item_follow_stack);
							break;
						}else{
							stack next_ka_first_stack = get_first_stack(next->str,f);
							if (find_stack(&next_ka_first_stack,"e")){
								item_follow_stack = merge_without_e(item_follow_stack,next_ka_first_stack);
								next = next->link;
							}else{
								item_follow_stack = merge(item_follow_stack,next_ka_first_stack);
								break;
							}
						}

					}
					if (next == NULL)
						item_follow_stack = merge(item_follow_stack,get_follow_stack(lhs,f));
				
					int after_size = item_follow_stack.stack_size;
					if (after_size > prev_size)
						flag=1;
					f.follows[get_index_nt(item->str)].rhs = item_follow_stack;

				}
				item = item->link;
			}
		}
	}	
}


FirstAndFollow getFirstAndFollow(grammar G)
{
	FirstAndFollow f;
	fill_firsts(G.rules_back,f);
	fill_follows(G.rules_back,f);
	return f;
}

