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
}
void fill_firsts()
{
	fill_lhs();
	for(int i=1;i<99;i++)
	{
		// if(isTerminal((*(r+i*sizeof(rule))).rhs))
		// {
		// 	stack curr=firsts[get_index_nt((*(r+i*sizeof(rule))).lhs)].rhs;
		// 	curr=distinct_push(curr,((*(r+i*sizeof(rule))).rhs.top)->str);
		// }
		// printf("%s\n", rules[i].lhs);
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
			// printf("%s\n", rules_back[i].lhs);
			// printStack(right);

			NODE top=right.top;
			// printf("%d\n", right.stack_size);
			for(int j=1;j<=right.stack_size;j++)
			{
				if(out)
					break;
				// printf("%s\n", top->str);
				
				if(isTerminal(top)==0)
				{
					// printf("%s\n",firsts[get_index_nt(top->str)].lhs );
					stack* a= &firsts[get_index_nt(top->str)].rhs;
					// printStack((*a));

					stack* b=&(firsts[get_index_nt(rules_back[i].lhs)].rhs);
					int initial=(*b).stack_size;
						*b=merge(*b,*a);
					int final=(*b).stack_size;
					if(final>initial)
						flag=1;
					if(!find_stack(a,"e"))
						break;
						
					// else {
					
					// stack* b=&(firsts[get_index_nt(rules_back[i].lhs)].rhs);
					// *b=merge(*b,*a);
				}
				else {
					stack* b=&(firsts[get_index_nt(rules_back[i].lhs)].rhs);
					int initial=(*b).stack_size;
					*b=distinct_push(*b,top->str);
					int final=(*b).stack_size;
					if(final>initial)
						flag=1;
					break;
				}
				top=top->link;
			}	
			printf("%s :::", (firsts[get_index_nt(rules_back[i].lhs)].lhs));
			printStack((firsts[get_index_nt(rules_back[i].lhs)].rhs));
			printf("\n");
		}
	}
}