// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#include "parser.h"
#include "parseTree.h"
int cnt;
int offset_arr[100];
int isTerminal(NODE top)
{
	if(top->str[0]=='<')
		return 0;
	else return 1;	
}

int isTerminalLexeme(char* a)
{
	if(a[0]=='<')
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
	sprintf(array[53].lhs,"<all_ops>");	
	sprintf(array[54].lhs,"<alpha>");
	sprintf(array[55].lhs,"<AnyTerm2>");
}
void fill_firsts(rule rules_back[109])
{
	fill_lhs(firsts);
	for(int i=1;i<109;i++)
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
		for(int i=1;i<109;i++)
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
		for(int i=1;i<109;i++)
		{
			char* lhs = rules_back[i].lhs;
			stack right=rules_back[i].rhs;
			NODE item = right.top;
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
	for (int i = 0; i < 56; ++i)
	{
		sprintf(f.firsts[i].lhs,"%s",firsts[i].lhs);
		f.firsts[i].rhs = firsts[i].rhs;
	}		
	fill_follows(G.rules_back);
	for (int i = 0; i < 56; ++i)
	{
		sprintf(f.follows[i].lhs,"%s",follows[i].lhs);
		f.follows[i].rhs = follows[i].rhs;		
	}	
	return f;
}

TREE_NODE_PTR fillnode(TREE_NODE_PTR* parent_curr,ptr ts,tokenInfo curr,char* a)
{
	
	TREE_NODE_PTR temp;
	temp=(TREE_NODE_PTR) malloc(sizeof(TREE_NODE));
	temp->parent=*parent_curr;
	// printf("\n%s %s",a,temp->parent->NodeSymbol);
	temp->child=NULL;
	if(a[0]!='<')
	{
		sprintf(temp->lexemeCurrentNode,"%s",curr.lexeme);
		temp->lineno=curr.line;
		sprintf(temp->token,"%s",curr.token);
		sprintf(temp->NodeSymbol,"%s",a);
		temp->isLeafNode=1;
		sprintf(temp->parentNodeSymbol,"%s",ts.node_info->NodeSymbol);
		if(strcmp(curr.token,"NUM")==0)
			temp->valueLfNumber=(int)atoi(curr.lexeme);
		else if(strcmp(curr.token,"RNUM")==0)
			temp->valueLfNumber=atof(curr.lexeme);
	}
	else{
		sprintf(temp->lexemeCurrentNode,"%s","----");
		temp->lineno=curr.line;
		sprintf(temp->token,"%s","----");
		sprintf(temp->NodeSymbol,"%s",a);
		temp->isLeafNode=0;
		sprintf(temp->parentNodeSymbol,"%s",ts.node_info->NodeSymbol);
	}
	temp->ASTparent=NULL;
	temp->ASTchild=NULL;
	temp->ASTsibling=NULL;
	return temp;
}

parseTree parseInputSourceCode(char *testcaseFile, table T,grammar G,FirstAndFollow F)
{	
	cnt=0;
	parseTree programNode=*((parseTree* )malloc(sizeof(parseTree)));
	char str_top[25];
	removeComments(testcaseFile,"clean_code.txt");
	stack s=push(s,"$");
	s=push(s,"<program>");
	sprintf(programNode.begin.lexemeCurrentNode,"%s","----");
	sprintf(programNode.begin.token,"%s","----");
	programNode.begin.lineno=1;
	sprintf(programNode.begin.parentNodeSymbol,"%s","ROOT");
	programNode.begin.isLeafNode=0;
	sprintf(programNode.begin.NodeSymbol,"%s","<program>");
	ptr_stack ts=push_ptr_stack(ts,&(programNode.begin));
	tokenInfo curr;
	int read=1;
	int terminated=0;
	while(1)
	{	
		if(read)
		{
			curr=getNextToken();
			if (strcmp(curr.token,"$")==0){
				read=0;
				terminated=1;
			}
			if(isEmptyStack(s))
				break;
		}
		NODE top=s.top;
		
		sprintf(str_top,"%s",top->str);
		if(isTerminal(top))
		{
			if(strcmp(curr.token,str_top)==0 && strcmp("$",curr.token)){
				
				pop(&s);
				
				sprintf(ts.top->node_info->lexemeCurrentNode,"%s",curr.lexeme);
				ts.top->node_info->lineno=curr.line;
				sprintf(ts.top->node_info->token,"%s",curr.token);
				ts.top->node_info->isLeafNode=1;
				if(strcmp(curr.token,"NUM")==0)
					ts.top->node_info->valueLfNumber=(int)atoi(curr.lexeme);
				else if(strcmp(curr.token,"RNUM")==0)
					ts.top->node_info->valueLfNumber=atof(curr.lexeme);
				pop_ptr_stack(&ts);

				if(terminated)
					break;
				read=1;
				continue;
			}
			if(strcmp(curr.token,str_top)==0 && strcmp("$",curr.token)==0){
				pop(&s);
				break;
			}

			else if(strcmp(str_top,"e")==0){
				read=0;
				sprintf(ts.top->node_info->lexemeCurrentNode,"%s","----");
				sprintf(ts.top->node_info->token,"%s","----");
				ts.top->node_info->isLeafNode=1;
				pop(&s);
				pop_ptr_stack(&ts);
			}
			else {
				if(strcmp(curr.token,"$")==0)
						break;
				printf("The token %s for lexeme %s does not match at line %d. ",curr.token,curr.lexeme,curr.line);
				printf("The expected token here is %s.\n\n",str_top );
				cnt++;
				read=1;
				
				continue;
			}
			
		}
		else
		{
			ptr curr_st=*(ts.top);
			TREE_NODE_PTR* parent_curr=&((ts.top)->node_info);
			int rule_num=T.parseTable[get_index_nt(str_top)][get_index_t(curr.token)];
			if(rule_num !=0)
			{
				curr_st.node_info->rule_no = rule_num;
				pop(&s);				
				pop_ptr_stack(&ts);
			}
			else
			{
				stack follows = F.follows[get_index_nt(str_top)].rhs;
				if(find_stack(&follows,curr.token)){
					sprintf(ts.top->node_info->lexemeCurrentNode,"%s","----");
					sprintf(ts.top->node_info->token,"%s","----");
					sprintf(ts.top->node_info->NodeSymbol,"%s",str_top);
					ts.top->node_info->isLeafNode=1;
					pop(&s);
					pop_ptr_stack(&ts);
					read=1;
					continue;
				}
				else{
					printf("Syntactic structure incorrect in line no. %d: rule not for Non-terminal: %s and Terminal: %s\n",curr.line,str_top,curr.token);
					cnt++;
					read=1;
					if(strcmp(curr.token,"$")==0)
						break;
					continue;
				}					

			}
			NODE populate=G.rules[rule_num].rhs.top;
			TREE_NODE_PTR prev=(TREE_NODE_PTR)malloc(sizeof(TREE_NODE));
			prev=NULL;
			while(populate!=NULL)
			{	
				

				s=push(s,populate->str);
				ts=push_ptr_stack(ts,fillnode(parent_curr,curr_st,curr,populate->str));
				
					(ts.top)->node_info->sibling=prev;
					if(!isEmpty_ptr_stack(ts)){

					prev=ts.top->node_info;
					fflush(stdout);
					}
				if(populate->link==NULL){
					curr_st.node_info->child=(ts.top)->node_info;
				} 
				populate=populate->link;
			}
			read=0;
		}

	}
	if(cnt>0){
		printf("\n\nIncorrect Syntax.\n\n\n");
		return programNode;
	}
	if(s.top!=NULL)
		printf("\n\nIncorrect Syntax.\n\n\n");
	if(s.top==NULL)
		printf("\n\nCorrect Syntax.\n\n\n");
	return programNode;
}
void LexerOutput(char *testcaseFile)
{
	removeComments(testcaseFile,"clean_code.txt");
	while(1)
	{		
		tokenInfo curr;
		curr=getNextToken();
		if (strcmp(curr.token,"$")==0)
			break;
		printf("%s %s %d \n",curr.lexeme,curr.token , curr.line);
	}
}
void parseTreePrint(TREE_NODE_PTR root,TREE_NODE_PTR parent,FILE* out_fp)
{
	
	while(root== NULL)
		return;
	if(parent!=NULL)
		root->parent=parent;
	if(root->child !=NULL)
		parseTreePrint(root->child,root,out_fp);

	// if(strcmp(root->token,"NUM")!=0 && strcmp(root->token,"RNUM")!=0)
	// 	fprintf(out_fp,"%s\t%d\t%s\t%s\t%s\t%d\t%s\n",root->lexemeCurrentNode,root->lineno,root->token," N/A ",root->parentNodeSymbol,root->isLeafNode,root->NodeSymbol);
	// else
	// fprintf(out_fp,"%s\t%d\t%s\t%lf\t%s\t%d\t%s\n",root->lexemeCurrentNode,root->lineno,root->token,root->valueLfNumber,root->parentNodeSymbol,root->isLeafNode,root->NodeSymbol);
	

	if(root->child !=NULL){
		if((root->child)->sibling !=NULL){
			TREE_NODE_PTR temp=(root->child)->sibling;
			while(temp!=NULL)
			{
				parseTreePrint(temp,root,out_fp);
				temp=temp->sibling;
			}
		}
	}		
}

void ASTPrint(TREE_NODE_PTR root,FILE* out_fp)
{

	while(root== NULL)
		return;

	if(root->ASTparent==NULL){
		root->ASTparent=(TREE_NODE_PTR) malloc(sizeof(TREE_NODE));
		sprintf(root->ASTparent->NodeSymbol,"%s","ROOT");
	}

	if(strcmp(root->token,"NUM")!=0 && strcmp(root->token,"RNUM")!=0)
		fprintf(out_fp,"%s\t%d\t%s\t%s\t%s\t%d\t%s\n",root->lexemeCurrentNode,root->lineno,root->token," N/A ",root->ASTparent->NodeSymbol,root->isLeafNode,root->NodeSymbol);
	else
	fprintf(out_fp,"%s\t%d\t%s\t%lf\t%s\t%d\t%s\n",root->lexemeCurrentNode,root->lineno,root->token,root->valueLfNumber,root->ASTparent->NodeSymbol,root->isLeafNode,root->NodeSymbol);
		ASTPrint(root->ASTchild,out_fp);
		ASTPrint(root->ASTsibling,out_fp);	
}

