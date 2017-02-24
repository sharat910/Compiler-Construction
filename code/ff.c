#include "ff.h"
#include <stdio.h>
#include "index_nt.h"

rule firsts[57];
rule follows[57];
int isTerminal(NODE top)
{
	if(top->str[0]=='<')
		return 0;
	else return 1;	
}
extern rule rules_back[100];
void fill_lhs()
{
	sprintf(firsts[0].lhs,"<AOBE>");
	sprintf(firsts[1].lhs,"<output_plist>");
	sprintf(firsts[2].lhs,"<idList>");
	sprintf(firsts[3].lhs,"<statement>");
	sprintf(firsts[4].lhs,"<whichStmt>");
	sprintf(firsts[5].lhs,"<WithLogOp>");
	sprintf(firsts[6].lhs,"<moduleReuseStmt>");
	sprintf(firsts[7].lhs,"<idList_ex>");
	sprintf(firsts[8].lhs,"<declareStmt>");
	sprintf(firsts[9].lhs,"<MultiCase>");
	sprintf(firsts[10].lhs,"<simpleStmt>");
	sprintf(firsts[11].lhs,"<expression>");
	sprintf(firsts[12].lhs,"<term>");
	sprintf(firsts[13].lhs,"<index>");
	sprintf(firsts[14].lhs,"<module>");
	sprintf(firsts[15].lhs,"<lvalueARRStmt>");
	sprintf(firsts[16].lhs,"<negOrPosAE>");
	sprintf(firsts[17].lhs,"<dataType>");
	sprintf(firsts[18].lhs,"<input_plist>");
	sprintf(firsts[19].lhs,"<var>");
	sprintf(firsts[20].lhs,"<op2>");
	sprintf(firsts[21].lhs,"<N4>");
	sprintf(firsts[22].lhs,"<output_plist_ex>");
	sprintf(firsts[23].lhs,"<driverModule>");
	sprintf(firsts[24].lhs,"<program>");
	sprintf(firsts[25].lhs,"<iterativeStmt>");
	sprintf(firsts[26].lhs,"<caseStmts>");
	sprintf(firsts[27].lhs,"<logicalOp>");
	sprintf(firsts[28].lhs,"<whichId>");
	sprintf(firsts[29].lhs,"<ioStmt>");
	sprintf(firsts[30].lhs,"<input_plist_ex>");
	sprintf(firsts[31].lhs,"<ret>");
	sprintf(firsts[32].lhs,"<WithRelOp>");
	sprintf(firsts[33].lhs,"<condionalStmt>");
	sprintf(firsts[34].lhs,"<optional>");
	sprintf(firsts[35].lhs,"<op1>");
	sprintf(firsts[36].lhs,"<range>");
	sprintf(firsts[37].lhs,"<relationalOp>");
	sprintf(firsts[38].lhs,"<BorNBAE>");
	sprintf(firsts[39].lhs,"<factor>");
	sprintf(firsts[40].lhs,"<value>");
	sprintf(firsts[41].lhs,"<moduleDeclarations>");
	sprintf(firsts[42].lhs,"<otherModules>");
	sprintf(firsts[43].lhs,"<type>");
	sprintf(firsts[44].lhs,"<moduleDeclaration>");
	sprintf(firsts[45].lhs,"<moduleDef>");
	sprintf(firsts[46].lhs,"<default>");
	sprintf(firsts[47].lhs,"<N5>");
	sprintf(firsts[48].lhs,"<assignmentStmt>");
	sprintf(firsts[49].lhs,"<lvalueIDStmt>");
	sprintf(firsts[50].lhs,"<statements>");
	sprintf(firsts[51].lhs,"<arithmeticExpr>");
	sprintf(firsts[52].lhs,"<AnyTerm>");
	sprintf(follows[0].lhs,"<AOBE>");
	sprintf(follows[1].lhs,"<output_plist>");
	sprintf(follows[2].lhs,"<idList>");
	sprintf(follows[3].lhs,"<statement>");
	sprintf(follows[4].lhs,"<whichStmt>");
	sprintf(follows[5].lhs,"<WithLogOp>");
	sprintf(follows[6].lhs,"<moduleReuseStmt>");
	sprintf(follows[7].lhs,"<idList_ex>");
	sprintf(follows[8].lhs,"<declareStmt>");
	sprintf(follows[9].lhs,"<MultiCase>");
	sprintf(follows[10].lhs,"<simpleStmt>");
	sprintf(follows[11].lhs,"<expression>");
	sprintf(follows[12].lhs,"<term>");
	sprintf(follows[13].lhs,"<index>");
	sprintf(follows[14].lhs,"<module>");
	sprintf(follows[15].lhs,"<lvalueARRStmt>");
	sprintf(follows[16].lhs,"<negOrPosAE>");
	sprintf(follows[17].lhs,"<dataType>");
	sprintf(follows[18].lhs,"<input_plist>");
	sprintf(follows[19].lhs,"<var>");
	sprintf(follows[20].lhs,"<op2>");
	sprintf(follows[21].lhs,"<N4>");
	sprintf(follows[22].lhs,"<output_plist_ex>");
	sprintf(follows[23].lhs,"<driverModule>");
	sprintf(follows[24].lhs,"<program>");
	sprintf(follows[25].lhs,"<iterativeStmt>");
	sprintf(follows[26].lhs,"<caseStmts>");
	sprintf(follows[27].lhs,"<logicalOp>");
	sprintf(follows[28].lhs,"<whichId>");
	sprintf(follows[29].lhs,"<ioStmt>");
	sprintf(follows[30].lhs,"<input_plist_ex>");
	sprintf(follows[31].lhs,"<ret>");
	sprintf(follows[32].lhs,"<WithRelOp>");
	sprintf(follows[33].lhs,"<condionalStmt>");
	sprintf(follows[34].lhs,"<optional>");
	sprintf(follows[35].lhs,"<op1>");
	sprintf(follows[36].lhs,"<range>");
	sprintf(follows[37].lhs,"<relationalOp>");
	sprintf(follows[38].lhs,"<BorNBAE>");
	sprintf(follows[39].lhs,"<factor>");
	sprintf(follows[40].lhs,"<value>");
	sprintf(follows[41].lhs,"<moduleDeclarations>");
	sprintf(follows[42].lhs,"<otherModules>");
	sprintf(follows[43].lhs,"<type>");
	sprintf(follows[44].lhs,"<moduleDeclaration>");
	sprintf(follows[45].lhs,"<moduleDef>");
	sprintf(follows[46].lhs,"<default>");
	sprintf(follows[47].lhs,"<N5>");
	sprintf(follows[48].lhs,"<assignmentStmt>");
	sprintf(follows[49].lhs,"<lvalueIDStmt>");
	sprintf(follows[50].lhs,"<statements>");
	sprintf(follows[51].lhs,"<arithmeticExpr>");
	sprintf(follows[52].lhs,"<AnyTerm>");
}
void fill_firsts()
{
	for(int i=1;i<99;i++)
	{
		if(isTerminal(rules_back[i].rhs.top))
		{
			stack* a=&(firsts[get_index_nt(rules_back[i].lhs)].rhs);
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
				stack* b=&(firsts[get_index_nt(rules_back[i].lhs)].rhs);
				if(isTerminal(top)==0)
				{
					stack* a= &firsts[get_index_nt(top->str)].rhs;
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

stack get_follow_stack(char* non_terminal){
	return follows[get_index_nt(non_terminal)].rhs;
}

stack get_first_stack(char* non_terminal){
	return firsts[get_index_nt(non_terminal)].rhs;
}

void fill_follows(){
	//Initial follow
	int flag = 1;
	stack* b=&(follows[get_index_nt("<program>")].rhs);
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
					stack item_follow_stack = get_follow_stack(item->str);
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
							stack next_ka_first_stack = get_first_stack(next->str);
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
						item_follow_stack = merge(item_follow_stack,get_follow_stack(lhs));
				
					int after_size = item_follow_stack.stack_size;
					if (after_size > prev_size)
						flag=1;
					follows[get_index_nt(item->str)].rhs = item_follow_stack;

				}
				item = item->link;
			}
		}
	}
	
}