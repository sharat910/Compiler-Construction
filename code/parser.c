#include "parser.h"
#include <stdio.h>
#include "index_nt.h"
#include "index_t.h"
#include <string.h>
#include <stdlib.h>

int isTerminal(NODE top)
{
	if(top->str[0]=='<')
		return 0;
	else return 1;	
}
rule follows[57];
rule firsts[57];

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
void fill_firsts(rule rules_back[100])
{
	fill_lhs(firsts);
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
						*b=merge_without_e(*b,*a);
					int final=(*b).stack_size;
					if(final>initial)
						flag=1;
					if(!find_stack(a,"e"))
						break;
					else{
						if(j==right.stack_size)
							*b=distinct_push(*b,"e");
					}
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

void fill_follows(rule rules_back[100]){
	fill_lhs(follows);
	int flag = 1;
	stack* b=&(follows[get_index_nt("<program>")].rhs);
	(*b)=push((*b),"$");
	while(flag){
		flag = 0;
		for(int i=1;i<99;i++)
		{
			char* lhs = rules_back[i].lhs;
			stack right=rules_back[i].rhs;
			NODE item = right.top;
			int j=1;
			while(item != NULL)
			{	
				if(isTerminal(item)==0)
				{
					stack item_follow_stack = get_follow_stack(item->str);
					int prev_size = item_follow_stack.stack_size;
					NODE next = item->link;
					while(next != NULL)
					{
						if(isTerminal(next))
						{
							
							item_follow_stack = distinct_push(item_follow_stack,next->str);
							
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

FirstAndFollow ComputeFirstAndFollowSets(grammar G)
{
	FirstAndFollow f;	
	fill_firsts(G.rules_back);
	for (int i = 0; i < 53; ++i)
	{
		sprintf(f.firsts[i].lhs,"%s",firsts[i].lhs);
		f.firsts[i].rhs = firsts[i].rhs;
	}		
	fill_follows(G.rules_back);
	for (int i = 0; i < 53; ++i)
	{
		sprintf(f.follows[i].lhs,"%s",follows[i].lhs);
		f.follows[i].rhs = follows[i].rhs;		
	}	
	return f;
}

parseTree  parseInputSourceCode(char *testcaseFile, table T,grammar G)
{
	parseTree programNode=*((parseTree* )malloc(sizeof(parseTree)));
	char str_top[25];
	removeComments(testcaseFile,"clean_code.txt");
	stack s=push(s,"$");
	s=push(s,"<program>");
	sprintf(programNode.begin.lexemeCurrentNode,"%s","----");
	programNode.begin.lineno=1;
	sprintf(programNode.begin.parentNodeSymbol,"%s","ROOT");
	programNode.begin.isLeafNode=0;
	sprintf(programNode.begin.NodeSymbol,"%s","<program>");
	tokenInfo curr;
	int read=1;
	int terminated=0;
	while(1)
	{		
		// if(terminated)
		if(read)
		{
			curr=getNextToken();
			if (strcmp(curr.token,"$")==0){
				// pop(&s);
				// break;
				read=0;
				terminated=1;
			}
			if(isEmptyStack(s))
				break;
			printf("NEW TOKEN: %s\n", curr.token);
			printf("%d %d\n",curr.line,curr.column );
		}
		NODE top=s.top;
		
		sprintf(str_top,"%s",top->str);
		printf("%s\n",str_top );
		printf("%s\n",curr.token);
		// printf("cool1");
		// printf("cool2");
		if(isTerminal(top))
		{
			printf("matching %s %s\n",str_top,curr.token);
			printf("\n");
			if(strcmp(curr.token,str_top)==0){
				// printf("Here\n");
				// fillnode();
				pop(&s);
				// printf("pop done\n");
				if(terminated)
					break;
				read=1;
				continue;
			}

			else if(strcmp(str_top,"e")==0){
				read=0;
				pop(&s);
				//fillnode()
			}
			else printf("error in matching\n");
			
		}
		else
		{
			pop(&s);
			printf("inside%s\n",str_top );
			printf("%d %d\n",get_index_nt(str_top), get_index_t(curr.token));
			int rule_num=T.parseTable[get_index_nt(str_top)][get_index_t(curr.token)];
			NODE populate=G.rules[rule_num].rhs.top;
			printf("%d\n",rule_num );
			printf("%d\n",G.rules[rule_num].rhs.stack_size );
			while(populate!=NULL)
			{
				s=push(s,populate->str);
				// fillnode();
				populate=populate->link;
			}
			printf("stack:\n");
			printStack(s);
			read=0;
		}
		printf("%s ", curr.token);	

	}
	
	if(s.top!=NULL)
		printf("wrong\n");
	if(s.top==NULL)
		printf("good\n");
	return programNode;
}

