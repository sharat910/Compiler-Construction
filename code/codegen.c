#include "codegen.h"
int cond;
FILE* ASM;

int traverseST(AST_NODE* root)
{
	fflush(stdout);
	if(root == NULL){
		// printf("nptr is NULL\n");
		fflush(stdout);
		return 0;
	}
	if (root->ptNode != NULL)
	{
		// printf("NS: %s\n",root->ptNode->lexemeCurrentNode );
	}else
		// printf("Root ka ptNode null h\n");
	fflush(stdout);
	if(root->is_leaf && root->type==1 && strcmp(root->ptNode->parentNodeSymbol,"<idList>")==0 &&
	strcmp(root->ptNode->parent->parentNodeSymbol,"<moduleReuseStmt>")==0 )
		return 1;

	// printf("HERRERERE\n");
	fflush(stdout);

	// printf("IS LEAF %d\n",root->is_leaf);

	if (root->is_leaf)
	{

		VAR v=root->st_ptr;

		if(v!=NULL)
		{
			if((strcmp(root->ptNode->parentNodeSymbol,"<output_plist>")==0 ||
			strcmp(root->ptNode->parentNodeSymbol,"<output_plist_ex>")==0 ||
			strcmp(root->ptNode->parentNodeSymbol,"<input_plist>")==0 ||
			strcmp(root->ptNode->parentNodeSymbol,"<input_plist_ex>")==0 ||
			strcmp(root->ptNode->parentNodeSymbol,"<idList>")==0 ||
			strcmp(root->ptNode->parentNodeSymbol,"<idList_ex>")==0 ||
			strcmp(root->ptNode->parent->parentNodeSymbol,"<declareStmt>")==0) &&
			strcmp(root->ptNode->parent->parentNodeSymbol,"<optional>")!=0 &&
			strcmp(root->ptNode->parent->parentNodeSymbol,"<moduleReuseStmt>")!=0	)
			{
				// ne++;
				// int start=symbol_table[v->h].scope.func_table[v->n][v->o].start;
				// int end=symbol_table[v->h].scope.func_table[v->n][v->o].end;
				fprintf(ASM,"	%s:	resb %3d\n",v->var_name,v->size);

				fflush(ASM);
				// printf("%d\t%8s\t",num,v->var_name );
				// if(v->is_array)
				// 	printf("%5s(%d,%s)\t%5d to %d\t%7d\t%5d\t%d\n","array",v->e_range-v->s_range+1,v->type, start,end,v->n,v->size,v->m);
				// else printf("%10s\t%10d to %d\t%2d\t%5d\t%d\n",v->type, start,end,v->n,v->size,v->m);

			}
		}
		fflush(ASM);
		return 0;
	}
	
	// printf("HERRERERE2\n");
	fflush(stdout);

	int loop_count = root->count;
	for (int i = 0; i < loop_count; i++)
	{
		// printf("Printing nptr array entry %d of %s\n",i,root->name);
		fflush(stdout);
		if(traverseST(root->array[i]))
			break;
	}
	fflush(stdout);
	return 0;
}

void bss(AST_NODE* root){

	fprintf(ASM,"section .bss\n");
	traverseST(root);
}

//Initiates the data section
void data(AST_NODE* root){
	fprintf(ASM,"\nsection .data\n");
	fprintf(ASM,"	scanint:	dw \"%cd\", 0\n",37);
	fprintf(ASM,"	putint:	db \"%cd\", 10, 0\n",37);	
}
void input(AST_NODE *root){
	if(root==NULL) return;

	if(strcmp("ID",root->ptNode->NodeSymbol)==0){
		fprintf(ASM,"	mov	rsi,%s\n",root->ptNode->lexemeCurrentNode);
		fprintf(ASM,"	mov	rdi,scanint\n");
		fprintf(ASM,"	call scanf\n\n");
	}	

}

//generates the code for read operation.
void output(AST_NODE* root){
	if(root==NULL) return;
	AST_NODE* id = root->array[0];
	AST_NODE* whichid = root->array[1];
	if(whichid==NULL)
		fprintf(ASM,"	mov	rsi,[%s]\n",id->name);
	else {
		fprintf(ASM,"	push rax\n\n");
		fprintf(ASM,"	mov rax,[%s]\n",whichid->name);
		fprintf(ASM,"	shl rax, 1\n");
		fprintf(ASM,"	add rax,%s\n",id->name);
		fprintf(ASM,"	mov rsi,[rax]\n\n");
		fprintf(ASM,"	pop rax\n\n");
	}
	fprintf(ASM,"	mov	rdi,putint\n");
	fprintf(ASM,"	call printf\n\n");	
	fflush(ASM);	
}

void while_gen(AST_NODE* root)
{
	fprintf(ASM, "loop%d:\n", cond);
	boolean_gen(root->array[0]);
	root=root->array[1];
	// printf("ISSUE:%s\n",root->array[1]->name );
	if(root==NULL) return;
	while(root!=NULL)
	{
		process(root);
		root=root->array[1];
	}

    fprintf(ASM,"	jmp loop%d\n", cond);
    fprintf(ASM,"endloop%d:\n", cond);
    fflush(ASM);
    cond++;
}

void for_gen(AST_NODE* root)
{
	int init=root->array[1]->array[0]->value;
	int end=root->array[1]->array[1]->value;
	fprintf(ASM,"\tmov 	rdi, %d\n",init);
	fprintf(ASM,"loop%d:\n",cond);
	fprintf(ASM, "\tpush	rdi\n");
	
	AST_NODE* stmts = root->array[2];
	while(stmts!=NULL)
	{
		process(stmts);
		stmts=stmts->array[1];
	}
	fprintf(ASM, "\tpop	rdi\n");
	fprintf(ASM, "\tadd	rdi, 1\n");
	fprintf(ASM, "\tcmp	rdi, %d\n",end);
	fprintf(ASM, "\tjne	loop%d\n",cond );
    fflush(ASM);
	cond++;
}

void operate(AST_NODE* op){
	char op_symbol = op->name[0];
	// printf("%c\n",op_symbol );
	fprintf(ASM, "\t%s\n","pop rbx");
	fprintf(ASM, "\t%s\n","pop rax");
	switch(op_symbol){
		case '+':
		fprintf(ASM, "\t%s\n","add rax,rbx");		
		break;

		case '-':
		fprintf(ASM, "\t%s\n","sub rax,rbx");
		break;

		case '*':
		fprintf(ASM, "\t%s\n","mul rbx");
		break;

		case '/':
		fprintf(ASM, "\t%s\n","div rbx");
		break;
	}
	fprintf(ASM, "\t%s\n","push rax");
	return;
}

int N4(AST_NODE* n4)
{
	// printf("N4 called\n");
	if (n4 == NULL){
		// printf("N4 null\n");
		return 0;
	}
	// printf("N4 not null\n");
	// printf("Here\n");

	// if (n4->array[2] != NULL)
	// {
	term(n4->array[1]);
	int flag=N4(n4->array[2]);
	// 	if (flag)
	// 		operate(n4->array[0]);
	// }
	// else
	// 	term(n4->array[1]);
	if(flag )
	{
		// printf("Why\n");
		// printf("Operator %s\n",n4->array[2]->array[0]->name);
		operate(n4->array[2]->array[0]);
	}
	return 1;
}

int N5(AST_NODE* n5)
{
	// printf("N5 called\n");
	if (n5 == NULL){
		// printf("N5 null\n");
		return 0;
	}
	// printf("N5 not null\n");
	// printf("Here\n");
	factor(n5->array[1]);
	int flag=N5(n5->array[2]);
	if (flag )
	{
		// printf("Why\n");
		// printf("Operator %s\n",n5->array[2]->array[0]->name);
		operate(n5->array[2]->array[0]);
	}	
	return 1;
}

void negate_top(){
	fprintf(ASM, "\t%s\n","pop rax");
	fprintf(ASM, "\tmov rbx,-1\n");
	fprintf(ASM, "\t%s\n","mul rbx");
	fprintf(ASM, "\t%s\n","push rax");
}	

void AE(AST_NODE* ae,int flg)
{
	term(ae->array[0]);
	if (flg)
		negate_top();
	int flag = N4(ae->array[1]);
	if (flag)
		operate(ae->array[1]->array[0]);
}

void term(AST_NODE* term)
{
	// printf("Term ka naam %s\n",term->name);
	factor(term->array[0]);
	int flag = N5(term->array[1]);
	if (flag)
		operate(term->array[1]->array[0]);
}

void factor(AST_NODE* factor)
{	

	if (!factor->is_leaf && factor->array[0]->type == 1){
		fprintf(ASM, "\tmov rax,[%s]\n",factor->array[0]->name);
		fprintf(ASM, "\tpush rax\n");
		return;
	}
	//ID NUM case
	if (factor->is_leaf)
	{
		//NUM
		if (factor->type == 2)
		{
			fprintf(ASM, "\tmov rax,%d\n",factor->value);
			fprintf(ASM, "\tpush rax\n");
		}
	}
	else
		AE(factor,0);
}


void assignment_gen(AST_NODE* expr)
{

	if(strcmp(expr->name,"<AOBE>")==0)
	{
		AST_NODE* anyterm=expr->array[0];
		if(anyterm->array[1]==NULL)
			AE(anyterm->array[0],0);
	}
	else {
		int flag;
		// printf("Rule no %d\n",expr->ptNode->parent->rule_no);
		if(expr->ptNode->parent->rule_no==61)
			flag=1;
		else
			flag=0;
		// printf("Flag is %d\n",flag);
		AE(expr->array[1],flag);
		if(!flag)
		{
			fprintf(ASM, "\t%s\n","pop rax");
			fprintf(ASM, "\tmov rbx,-1\n");
			fprintf(ASM, "\t%s\n","mul rbx");
			fprintf(ASM, "\t%s\n","push rax");
		}
	}
}
void switch_gen(AST_NODE* root)
{
	if(root==NULL)
		return;
	fprintf(ASM, "\t%s\n","push rax");
	fprintf(ASM, "\tmov rax,%s\n",root->array[0]->name);
	AST_NODE* cases=root->array[1];
	int lol=cond;
	while(cases!=NULL)
	{
		fprintf(ASM, "loop%d:\n", cond);
		fprintf(ASM, "\tmov rbx,%s\n",cases->array[0]->name);
		fprintf(ASM,"	cmp rax,rbx\n");
		cond++;
		fprintf(ASM, "\tjne loop%d\n",cond);
		AST_NODE* stmts=cases->array[1];
		while(stmts!=NULL)
		{
			process(stmts);
			stmts=stmts->array[1];
		}
		cases=cases->array[2];
		fprintf(ASM, "\tjmp endloop%d\n",lol);
	}
	fprintf(ASM,"endloop%d:\n", lol);
	fprintf(ASM, "\t%s\n","pop rax");
	cond++;
	fflush(ASM);
}
void boolean_gen(AST_NODE* expr)
{
	if(strcmp(expr->name,"<AOBE>")==0)
	{
		AST_NODE* anyterm=expr->array[0];
		if(anyterm->array[1]!=NULL){
			AE(anyterm->array[0],0);
			AST_NODE* negpae=anyterm->array[1]->array[1];
			// printf("%s\n",anyterm->array[1]->array[1] );
			if(strcmp(negpae->name,"<arithmeticExpr>")==0)
				AE(negpae,0);
			else{
				int flag;
				// printf("%s\n",negpae->name );
				// printf("Rule no %d\n",negpae->array[1]->ptNode->parent->rule_no);
				if(expr->ptNode->parent->rule_no==61)
					flag=1;
				else
					flag=0;
				AE(negpae,flag);
				if(!flag)
				{
					fprintf(ASM, "\t%s\n","pop rax");
					fprintf(ASM, "\tmov rbx,-1\n");
					fprintf(ASM, "\t%s\n","mul rbx");
				}
			}
		}
		// else printf("CUlprit%s\n",anyterm->array[1]->name);
		fprintf(ASM,"	pop rbx\n");
		fprintf(ASM,"	pop rax\n");
		fprintf(ASM,"	cmp rax,rbx\n");
		char* relop=anyterm->array[1]->array[0]->ptNode->NodeSymbol;
		// printf("%s\n",relop );
		if(strcmp(relop,"LT")==0){
			fprintf(ASM, "	jge endloop%d\n",cond);
		}else if(strcmp(relop,"LE")==0){
			fprintf(ASM, "	jg endloop%d\n",cond);
		}else if(strcmp(relop,"EQ")==0){
			fprintf(ASM, "	jne endloop%d\n",cond);
		}else if(strcmp(relop,"GT")==0){
			fprintf(ASM, "	jle endloop%d\n",cond);
		}else if(strcmp(relop,"GE")==0){
			fprintf(ASM, "	jl endloop%d\n",cond);
		}else if(strcmp(relop,"NE")==0){
		}
	}
}
void process(AST_NODE* root)
{
	if(root==NULL)
		return;
	// printf("%s\n",root->name );
	if(strcmp(root->name,"<statements>")!=0)
		return;
	// printf("%s\n",root->name );
	// printf("ptNode:%s\n",root->array[0]->ptNode->NodeSymbol );
	
	if(strcmp("<assignmentStmt>",root->array[0]->ptNode->NodeSymbol)==0)
	{
		// printf("%s\n","Doing this" );
		fprintf(ASM,"	push rax\n\n");
		AST_NODE* assignmentStmt=root->array[0];
		char LHS[100];
		// printf("%s\n",assignmentStmt->array[1]->name );
		fflush(stdout);
		// printf("ARRAY LHS= %s\n",assignmentStmt->array[0]->name );
		if(strcmp(assignmentStmt->array[1]->name,"<lvalueARRStmt>" )==0)
		{
			
			if(assignmentStmt->array[1]->array[0]->type==2)
			{
				
				sprintf(LHS,"%s+%d*2",assignmentStmt->array[0]->name,assignmentStmt->array[1]->array[0]->value);
				assignment_gen(assignmentStmt->array[1]->array[1]);
			}
			else
				{ 
					assignment_gen(assignmentStmt->array[1]->array[1]);
					fprintf(ASM,"	mov rax,[%s]\n",assignmentStmt->array[1]->array[0]->name);
					fprintf(ASM,"	shl rax, 1\n");
					fprintf(ASM,"	add rax,%s\n",assignmentStmt->array[0]->name);
					fprintf(ASM,"	pop [rax]\n\n");
					fprintf(ASM,"	pop rax\n\n");
					fflush(ASM);
					return ;
				}
			
		}
		else {
			sprintf(LHS,"%s",assignmentStmt->array[0]->name);
			assignment_gen(assignmentStmt->array[1]);
		}
		fprintf(ASM,"	mov [%s],rax\n",LHS);
		fprintf(ASM,"	pop rax\n\n");
		fflush(ASM);
		return;
	}
	else if(strcmp("<conditionalStmt>",root->array[0]->ptNode->NodeSymbol)==0)
	{
		// printf("YOLO%s\n",root->name );
		switch_gen(root->array[0]);
		return;
	}
	else if(strcmp("<iterativeStmt>",root->array[0]->ptNode->NodeSymbol)==0)
	{
		AST_NODE* iter=root->array[0];
		if(iter->count==2)
		    while_gen(iter);			
		else if(iter->count==3)
			for_gen(iter);
		// fprintf(ASM,"%s\n","hello" );
		return;
	}
	else if(strcmp("<ioStmt>",root->array[0]->ptNode->NodeSymbol)==0)
	{
		// printf("I am IO not google just IO\n");
		AST_NODE* io=root->array[0]->array[0];
		// printf("%s\n", io->ptNode->NodeSymbol);
		if(strcmp("ID",io->ptNode->NodeSymbol)==0)
		{
			// printf("In ID\n");
			input(io);
			return;
		}
		if(strcmp("<var>",io->ptNode->NodeSymbol)==0)
		{
			// printf("In var\n");
			output(io);
			return;
		}
	}
	// printf("GONE\n");
	fflush(stdout);
	return;
}

void traverseAST(AST_NODE* root)
{
	if(root == NULL){
		// printf("nptr is NULL\n");
		fflush(stdout);
		return;
	}
	 
	else
	{
		AST_NODE* stmts = root->array[2];
		while(stmts != NULL){
			// printf("Calling process on %s\n",stmts->array[0]->name);
			// printf("%s\n",stmts->name );
			process(stmts);
			// printf("%s\n",stmts->name );
			stmts=stmts->array[1];
		}
	}
}
void generate_code(AST_NODE* root)
{
	ASM=fopen("assembly.asm","w");
	cond=0;
	fprintf(ASM,"extern printf\n");
	fprintf(ASM,"extern scanf\n\n");
	
	// treeNode *AST=PT->root; 
	bss(root);
	data(root);
	fprintf(ASM,"\nsection .text\n\n");
	fprintf(ASM,"global main\n");
	fprintf(ASM,"main:\n\n");
	fprintf(ASM,"\n	push rbp\n");
	traverseAST(root);
	fprintf(ASM,"\n	pop rbp\n");
	fprintf(ASM,"	ret\n");
	fflush(ASM);
}