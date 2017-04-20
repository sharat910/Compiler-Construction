#include "codegen.h"
int cond;
FILE* ASM;
void bss(){

	fprintf(ASM,"section .bss\n");
	
	// traverseST(symbol_table);
	int i=0;
	
	for(i=0;i<10;i++){
		fprintf(ASM,"	buffer%d:	resb	8\n",i);
		}
}

//Initiates the data section
void data(){
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
	
	if(strcmp("ID",root->ptNode->NodeSymbol)==0){
		char* var=root->ptNode->lexemeCurrentNode;
		int index;
		if(strcmp(root->ptNode->sibling->NodeSymbol,"e")==0)
			fprintf(ASM,"	mov	rsi,[%s]\n",var);
		else {
			index=(int)root->ptNode->sibling->child->sibling->valueLfNumber;
			fprintf(ASM,"	mov	rsi,[%s+%d*8]\n",var,index);
		}
		fprintf(ASM,"	mov	rdi,putint\n");
		fprintf(ASM,"	call printf\n\n");
		
	}	
}

void while_gen(AST_NODE* root)
{
	fprintf(ASM, "loop%d:\n", cond);
	boolean_gen(root->array[0]);
	fprintf(ASM, "	cmp rax, 0\n");
    fprintf(ASM, "	je endloop%d\n", cond);
	root=root->array[1];
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
	fprintf(ASM,"mov 	rdi, %d*8\n",init);
	fprintf(ASM,"loop%d:\t",cond);
	if(root->array[2]==NULL)
		printf("FUCKkkk\n");
	AST_NODE* stmts = root->array[2];
	while(stmts!=NULL)
	{
		process(stmts);
		stmts=stmts->array[1];
	}
	fprintf(ASM, "cmp	rdi, 8*%d\n",end);
	fprintf(ASM, "jne	loop%d\n",cond );
    fflush(ASM);
	cond++;
}
void assignment_gen(AST_NODE* root)
{

}
void switch_gen(AST_NODE* root)
{
	
}
void boolean_gen(AST_NODE* root)
{

}
void process(AST_NODE* root)
{
	if(root==NULL)
		return;
	// printf("%s\n",root->name );
	if(strcmp(root->name,"<statements>")!=0)
		return;
	printf("%s\n",root->name );
	printf("ptNode:%s\n",root->array[0]->ptNode->NodeSymbol );
	
	if(strcmp("<assignmentStmt>",root->array[0]->ptNode->NodeSymbol)==0){
		printf("%s\n","Doing this" );
		root=root->array[0];
		char LHS[100];
		printf("%s\n",root->array[1]->name );
		fflush(stdout);
		printf("ARRAY LHS= %s\n",root->array[0]->name );
		if(strcmp(root->array[1]->name,"<lvalueARRStmt>" )==0)
		{
			
			if(root->array[1]->array[0]->type==2)
				sprintf(LHS,"%s+%d*8",root->array[0]->name,root->array[1]->array[0]->value);
			// else sprintf(LHS,"%s+%d*8",root->array[0]->name,root->array[1]->array[0]->value);

		}
		else sprintf(LHS,"%s",root->array[0]->name);
		assignment_gen(root);
		fprintf(ASM,"	mov [%s],rax\n",LHS);
		fprintf(ASM,"	pop rax\n\n");
		fflush(ASM);
		return;
	}
	else if(strcmp("<conditionalStmt>",root->array[0]->ptNode->NodeSymbol)==0)
	{
		root=root->array[0];
		switch_gen(root);
		return;
	}
	else if(strcmp("<iterativeStmt>",root->array[0]->ptNode->NodeSymbol)==0)
	{
		root=root->array[0];
		if(root->count==2)
		    while_gen(root);			
		else if(root->count==3)
			for_gen(root);
		fprintf(ASM,"%s\n","hello" );
		return;
	}
	// else if(strcmp("GET_VALUE",root->ptNode->parent->child->NodeSymbol)==0)
	// {
	// 	input(root);
	// 	return;
	// }
	// else if(strcmp("PRINT",root->ptNode->parent->child->NodeSymbol)==0)
	// {
	// 	output(root);
	// 	return;
	// }
	printf("GONE\n");
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
	 
	// else if (root->is_leaf)
	// {
	// 	printf("Line No. %d ", root->line_no);
	// 	print_ast_leaf(root);
	// }
	else
	{
		// // if(strcmp(root->name,"<statements>")==0)
		// // 	process(root);
		// int loop_count = root->count;
		// for (int i = 0; i < loop_count; i++)
		// {
		// 	if(root->ptNode!=NULL)
		// 		printf("LINE_NO%d ", root->ptNode->lineno);
		// 	printf("Printing nptr array entry %d of %s\n",i,root->name);
		// 	process(root->array[i]);
		// 	traverseAST(root->array[i++]);
		// }
		AST_NODE* stmts = root->array[2];
		while(stmts != NULL){
			printf("Calling process on %s\n",stmts->name);
			process(stmts);
			stmts=stmts->array[1];
		}
	}
}
void generate_code(AST_NODE* root)
{
	ASM=fopen("asm.txt","w");
	cond=0;
	bss();
	data();
	fflush(ASM);
	traverseAST(root);
}