
# include "type_checker.h"


# define ID_TYPE 1
# define NUM_RNUM_TYPE 2
# define OP_TYPE 3
# define BOOL_TYPE 4

int is_terminal(TREE_NODE_PTR node)
{
	return node->isLeafNode;
}

int is_non_terminal(TREE_NODE_PTR node)
{
	return !node->isLeafNode;
}

AST_NODE* make_ast_leaf(TREE_NODE_PTR node, int type, int value){
	char identifier[25];
	sprintf(identifier,"%s",node->lexemeCurrentNode);
	// VAR st_entryptr = get_symbol_table_var_entry(node);
	AST_NODE* leaf = (AST_NODE*)malloc(sizeof(AST_NODE));
	leaf->ptNode = node;
	leaf->line_no=node->lineno;
	leaf->is_leaf = 1;
	sprintf(leaf->name,"%s", identifier);
	leaf->st_ptr = NULL;
	leaf->value = -99999;
	leaf->type=type;
	switch (type){
		case ID_TYPE:
			// printf("Function hash:%d Nest:%d Offset:%d\n",node->hash_value,node->nesting,node->offset );
			leaf->st_ptr = get_symbol_table_var_entry(node);
			break;
		
		case NUM_RNUM_TYPE:
			leaf->value = value;
			break;
		
		// Nothing to be done for BOOL NUM RNUM

		// default:
		// 	printf("Unidentified type \"%d\" in make_ast_leaf\n",type);
	}
	// printf("Creating leaf for %s whose type is %d\n",identifier,type);
	return leaf;	
}

AST_NODE* make_ast_node(TREE_NODE_PTR node){
	AST_NODE* ast_node = (AST_NODE*)malloc(sizeof(AST_NODE));
	sprintf(ast_node->name,"%s",node->NodeSymbol);
	ast_node->is_leaf = 0;
	TREE_NODE_PTR temp = node->child;
	int i=0;
	while(temp!=NULL){
		if ( (strcmp(temp->NodeSymbol,"ID") == 0) || is_non_terminal(temp)){
			ast_node->array[i] = (AST_NODE*)malloc(sizeof(AST_NODE));
			ast_node->array[i] = temp->nptr;
			i++;
		}
		temp = temp->sibling;
	}

	ast_node->count = i;
	ast_node->ptNode = node;
	// printf("Creating ast node for %s with count %d\n",node->NodeSymbol,ast_node->count);
	return ast_node;
}

void print_ast_leaf(AST_NODE* leaf){
		switch(leaf->type){
			case ID_TYPE:
			printf("ID_TYPE Name: %s | ST_PTR %s\n",leaf->name,leaf->st_ptr->var_name);
			break;

			case NUM_RNUM_TYPE:
			printf("NUM_RNUM_TYPE Name: %s | Value: %d\n",leaf->name,leaf->value);
			break;

			case BOOL_TYPE:
			printf("BOOL_TYPE Name: %s\n",leaf->name);
			break;

			case OP_TYPE:
			printf("OP_TYPE Name: %s\n",leaf->name);
			break;
		}
}

TREE_NODE_PTR find_first_nt(TREE_NODE_PTR node){
	TREE_NODE_PTR temp = node->child;
	while(temp!=NULL && is_terminal(temp)){
		// printf("%s\n", );
		temp=temp->sibling;
	}
	return temp;
}


AST_NODE* find_id_ka_nptr(TREE_NODE_PTR node){
	TREE_NODE_PTR temp = node->child;
	while(temp != NULL)
	{
		if (strcmp(temp->NodeSymbol,"ID") == 0){
			return temp->nptr;
		} 
		temp = temp->sibling;
	}
	return NULL;
}

AST_NODE* get_nptr_range(TREE_NODE_PTR node){
	AST_NODE* num1;
	num1 = make_ast_leaf(node->child,NUM_RNUM_TYPE,node->child->valueLfNumber);
	AST_NODE* num2;
	num2 = make_ast_leaf(node->child->sibling->sibling,NUM_RNUM_TYPE,node->child->sibling->sibling->valueLfNumber);
	AST_NODE* new_ast_node;
	new_ast_node = (AST_NODE*) malloc(sizeof(AST_NODE));
	new_ast_node->is_leaf = 0;
	new_ast_node->array[0] = num1;
	new_ast_node->array[1] = num2;
	new_ast_node->count = 2;
	new_ast_node->ptNode = node;
	return new_ast_node;
}

void magic_function(TREE_NODE_PTR node)
{
	int rule_no = node->rule_no;
	// printf("Rule %d\n",rule_no);
	// printf("Line no. %d ",node->lineno );
	if (is_non_terminal(node))
		switch(rule_no){
			// Just make a new node
			case 1:
			case 2:
			case 5:
			case 8:
			case 9:
			case 11:
			case 12:
			case 14:
			case 15:
			case 25:
			case 32:
			case 33:
			case 53:
			case 54:
			case 105:
			node->nptr = make_ast_node(node);
			break;


			case 76:
			case 79:			
			//Typecheck
			type_check(node);			
			node->nptr = make_ast_node(node);
			node->type = node->child->type;
			break;

			case 43:
			case 50:
			case 63:
			case 68:
			case 70:
			case 77:
			case 80:
			case 96:
			case 97:
			case 98:
			case 106:
			type_check(node);
			node->nptr = make_ast_node(node);
			break;

			// Datatype statements
			case 17:
			case 18:
			case 19:
			case 21:
			case 22:
			case 23:
			node->nptr = NULL;
			node->type=node->child->lexemeCurrentNode;
			break;

			// <var> → ID <whichId>
			case 34:
			node->nptr = make_ast_node(node);
			type_check(node);
			node->type = node->child->type;
			break;
			
			// Inherit child's nptr and type
			case 35:
			case 36:
			case 37:
			case 38:
			case 44:
			case 45:
			case 48:
			case 49:
			case 56:
			case 59:
			case 61:
			case 67:
			case 82:
			case 100:
			case 101:
			case 102:
			node->nptr = node->child->nptr;
			node->type = node->child->type;
			break;

			case 46:
			case 60:
			case 66:
			node->nptr = find_first_nt(node)->nptr;
			node->type = find_first_nt(node)->type;
			break;

			case 57:
			case 108:
			type_check(node);
			node->nptr = find_first_nt(node)->nptr;
			node->type = find_first_nt(node)->type;
			break;

			// <negOrPosAE> → MINUS <BorNBAE>
			case 58:
			type_check(node);
			;AST_NODE* ast_node = (AST_NODE*)malloc(sizeof(AST_NODE));
			sprintf(ast_node->name,"%s",node->NodeSymbol);
			ast_node->is_leaf = 0;
			ast_node->ptNode = node;
			ast_node->array[0] = make_ast_leaf(node->child,OP_TYPE,0);
			ast_node->array[1] = find_first_nt(node)->nptr;
			ast_node->count = 2;
			node->type = find_first_nt(node)->type;
			break;

			// <dataType> → ARRAY SQBO <range> SQBC OF <type>
			case 20:
			node->nptr=make_ast_node(node);
			node->type = node->child->sibling->sibling->sibling->sibling->sibling->lexemeCurrentNode;
			break;

			// <lvalueARRStmt> → SQBO <index> SQBC ASSIGNOP <expression> SEMICOL
			case 47:
			node->nptr = make_ast_node(node);
			node->type = node->child->sibling->sibling->sibling->sibling->type;
			break;

			// One non-terminal in child
			case 24:
			case 51:
			case 7:

			// Only one child which is non_terminal
			case 27:
			case 28:
			case 29:
			case 30:
			case 31:
			case 41:
			case 42:
			case 72:
			case 73:
			case 74:
			case 75:			
			case 103:
			node->nptr = find_first_nt(node)->nptr;
			break;

			//<AOBE> → <AnyTerm> <WithLogOp>
			//<AnyTerm> → <arithmeticExpr> <WithRelOp>
			case 62:
			case 65:
			node->nptr = make_ast_node(node);

			if (node->child->sibling->nptr != NULL)
				node->type = "BOOLEAN";
			else
				node->type = node->child->type;
			break;

			
			// case 70:
			// //Typecheck
			// type_check(node);
			// node->nptr = make_ast_node(node);
			// TREE_NODE_PTR alpha = node->child->sibling->sibling->sibling;
			// if (alpha->nptr != NULL)
			// 	if (strcmp(alpha->child->child->NodeSymbol,"<relationalOp>")==0)
			// 		node->type = "BOOLEAN";
			// 	else
			// 		node->type = node->child->sibling->type;
			// else					
			// 	node->type = node->child->sibling->type;
			// break;

			// <declareStmt> → DECLARE <idList> COLON <dataType> SEMICOL
			case 95:
			node->nptr = make_ast_node(node);
			TREE_NODE_PTR idList = node->child->sibling;
			TREE_NODE_PTR dataType = idList->sibling->sibling;
			idList->type = dataType->type;
			break;

			//<range> → NUM​1​ RANGEOP NUM​2
			case 107:
			node->nptr = get_nptr_range(node);
            break;

			//All Op cases
			case 83:
			case 84:
			case 85:
			case 86:
			case 87:
			case 88:
			case 89:
			case 90:
			case 91:
			case 92:
			case 93:
			case 94:
			node->nptr = make_ast_leaf(node->child,OP_TYPE,0);
			break;

			// All epsilon rule cases
			case 3:
			case 6:
			case 10:
			case 13:
			case 16:
			case 26:
			case 40:
			case 52:
			case 55:
			case 64:
			case 69:
			case 71:
			case 78:
			case 81:
			case 99:
			case 104:
			node->nptr = NULL;
			break;

			case 4:
			case 39:
			node->nptr = find_id_ka_nptr(node);
			break;

		}

	else if (strcmp(node->NodeSymbol,"ID") == 0)
	{
		node->nptr = make_ast_leaf(node,ID_TYPE,0);
		VAR st_entry = get_symbol_table_var_entry(node);
		if (st_entry != NULL){
			node->type = st_entry->type;
			}
		else{
			node->type = (char*) malloc(sizeof(char)*10);
			sprintf(node->type,"%s","DUMMY");
		}
	}
	else if (strcmp(node->NodeSymbol,"NUM") == 0){
		node->nptr = make_ast_leaf(node,NUM_RNUM_TYPE,node->valueLfNumber);

		node->type = (char*) malloc(sizeof(char)*10);
		sprintf(node->type,"%s","INTEGER");
		node->nptr->st_ptr = NULL;
	}
		
	else if	(strcmp(node->NodeSymbol,"RNUM") == 0)
	{
		node->nptr = make_ast_leaf(node,NUM_RNUM_TYPE,node->valueLfNumber);

		node->type = (char*) malloc(sizeof(char)*10);
		sprintf(node->type,"%s","REAL");
		node->nptr->st_ptr = NULL;
	}
	else if ((strcmp(node->NodeSymbol,"TRUE") == 0) || 
		(strcmp(node->NodeSymbol,"FALSE") == 0))
	{
		node->nptr = make_ast_leaf(node,BOOL_TYPE,0);

		node->type = (char*) malloc(sizeof(char)*10);
		sprintf(node->type,"%s","BOOLEAN");
		node->nptr->st_ptr = NULL;

	}
	else{
		// node->nptr->ptNode = node;
	}
}


void recursive_function(TREE_NODE_PTR node)
{
	if (node->child != NULL)
		recursive_function(node->child);
	// printf("Line no. %d ",node->lineno);
	// printf("Calling magic_function on %s\n",node->NodeSymbol);
	magic_function(node);
	fflush(stdout);
	if (node->sibling != NULL)
		recursive_function(node->sibling);
}

void constructAST(TREE_NODE_PTR root)
{
	recursive_function(root);
}

void printAST(AST_NODE* root)
{
	if(root == NULL){
		// printf("nptr is NULL\n");
		fflush(stdout);
		return;
	}
	 
	else if (root->is_leaf)
	{
		// printf("Line No. %d ", root->line_no);
		print_ast_leaf(root);
	}
	else
	{
		int loop_count = root->count;
		for (int i = 0; i < loop_count; i++)
		{
			// printf("Printing nptr array entry %d of %s\n",i,root->name);
			printAST(root->array[i]);
		}
	}
}

void print_AST_element(AST_NODE* elem, int is_leaf)
{
	if (is_leaf)
		printf("\tLEAF\t%s\t%d\t-\n",elem->name,elem->type);
	else
		printf("\tNODE\t%s\t-\t%d\n",elem->name,elem->count);
}

void printAST2(AST_NODE* root)
{
	if(root == NULL){
		return;
	}
	 
	else if (root->is_leaf)
	{
		print_AST_element(root,root->is_leaf);
	}
	else
	{
		print_AST_element(root,root->is_leaf);
		int loop_count = root->count;
		for (int i = 0; i < loop_count; i++)
		{
			// printf("Printing nptr array entry %d of %s\n",i,root->name);
			printAST2(root->array[i]);
		}
	}
}

int ne=1;
int printSymbolTable(AST_NODE* root,int num)
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
	if(root->is_leaf && root->type==ID_TYPE && strcmp(root->ptNode->parentNodeSymbol,"<idList>")==0 &&
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
				ne++;
				int start=symbol_table[v->h].scope.func_table[v->n][v->o].start;
				int end=symbol_table[v->h].scope.func_table[v->n][v->o].end;
				printf("%d\t%8s\t",num,v->var_name );
				if(v->is_array)
					printf("%5s(%d,%s)\t%5d to %d\t%7d\t%5d\t%d\n","array",v->e_range-v->s_range+1,v->type, start,end,v->n,v->size,v->m);
				else printf("%10s\t%10d to %d\t%2d\t%5d\t%d\n",v->type, start,end,v->n,v->size,v->m);

			}
		}
		fflush(stdout);
		return 0;
	}
	
	// printf("HERRERERE2\n");
	fflush(stdout);

	int loop_count = root->count;
	for (int i = 0; i < loop_count; i++)
	{
		// printf("Printing nptr array entry %d of %s\n",i,root->name);
		fflush(stdout);
		if(printSymbolTable(root->array[i],ne))
			break;
	}
	fflush(stdout);
	return 0;
}

int non_term_to_remove(char *non_terminal){  

	if( 
	(strcmp(non_terminal, "<moduleDeclarations>") == 0) || 
	(strcmp(non_terminal, "<otherModules>") == 0) || 
	(strcmp(non_terminal, "<fieldDefinitions>") == 0) || 
	(strcmp(non_terminal, "<moduleDeclaration>") == 0) || 	
	(strcmp(non_terminal, "<input_plist>") == 0) || 	
	(strcmp(non_terminal, "<output_plist>") == 0) ||
	(strcmp(non_terminal, "<ret>") == 0) || 
	(strcmp(non_terminal, "<input_plist_ex>") == 0) ||
	(strcmp(non_terminal, "<onput_plist_ex>") == 0) ||
	(strcmp(non_terminal, "<dataType>") == 0) || 
	(strcmp(non_terminal, "<statements>") == 0) ||
	(strcmp(non_terminal, "<type>") == 0) ||
	(strcmp(non_terminal, "<range>") == 0) ||
	(strcmp(non_terminal, "<moduleDef>") == 0) ||
	(strcmp(non_terminal, "<statement>") == 0) ||
	(strcmp(non_terminal, "<var>") == 0) ||
	(strcmp(non_terminal, "<whichId>") == 0) ||
    (strcmp(non_terminal, "<simpleStmt>") == 0) ||
    (strcmp(non_terminal, "<whichStmt>") == 0) ||
	(strcmp(non_terminal, "<expression>") == 0) ||
	(strcmp(non_terminal, "<index>") == 0) ||
	(strcmp(non_terminal, "<optional>") == 0) ||
	(strcmp(non_terminal, "<AOBE>") == 0) ||
	(strcmp(non_terminal, "<negOrPosAE>") == 0) ||
	(strcmp(non_terminal, "<AnyTerm>") == 0) ||
	(strcmp(non_terminal, "<WithLogOp>") == 0) ||
	(strcmp(non_terminal, "<logicalOp>") == 0) ||
	(strcmp(non_terminal, "<AnyTerm2>") == 0) ||
	(strcmp(non_terminal, "<WithRelOp>") == 0) ||
	(strcmp(non_terminal, "<alpha>") == 0) ||
	(strcmp(non_terminal, "<all_ops>") == 0) ||
	(strcmp(non_terminal, "<op1>") == 0) ||
	(strcmp(non_terminal, "<op2>") == 0) ||
	(strcmp(non_terminal, "<N4>") == 0) ||
	(strcmp(non_terminal, "<N5>") == 0) ||	
	(strcmp(non_terminal, "<idList_ex>") == 0) ||
	(strcmp(non_terminal, "<factor>") == 0) ||
	(strcmp(non_terminal, "<relationalOp>") == 0) ||
	(strcmp(non_terminal, "<BorNBAE>") == 0) ) return 1;
	else return 0;	
}

//Terminals which are pointing to epsilon.
int to_eps(char *non_terminal){

	if( (strcmp(non_terminal, "<moduleDeclarations>") == 0) || 
		(strcmp(non_terminal, "<otherModules>") == 0) ||
		(strcmp(non_terminal, "<ret>") == 0) ||
		(strcmp(non_terminal, "<input_plist_ex>") == 0) ||
		(strcmp(non_terminal, "<output_plist_ex>") == 0) ||
		(strcmp(non_terminal, "<statements>") == 0) ||
		(strcmp(non_terminal, "<whichId>") == 0) ||
		(strcmp(non_terminal, "<optional>") == 0) ||
		(strcmp(non_terminal, "<idList_ex>") == 0) ||
		(strcmp(non_terminal, "<WithLogOp>") == 0) ||
		(strcmp(non_terminal, "<WithRelOp>") == 0) ||
		(strcmp(non_terminal, "<alpha>") == 0) ||
		(strcmp(non_terminal, "<N4>") == 0) ||
		(strcmp(non_terminal, "<N5>") == 0) ||
		(strcmp(non_terminal, "<MultiCase>") == 0) ||
		(strcmp(non_terminal, "<default>") == 0) ) return 1;
		else return 0;	

}

//Function to check the terminals to be removed.
int term_to_remove(char *terminal){	
	if( (strcmp(terminal, "SEMICOL") == 0) ||
	(strcmp(terminal, "BO") == 0) ||
	(strcmp(terminal, "BC") == 0) ||
	(strcmp(terminal, "START") == 0) ||
	(strcmp(terminal, "END") == 0) ||
	(strcmp(terminal, "CASE") == 0) ||
	(strcmp(terminal, "DECLARE") == 0) ||
	(strcmp(terminal, "COMMA") == 0) ||
	(strcmp(terminal, "ASSIGNOP") == 0) ||
	(strcmp(terminal, "COMMA") == 0) ||
	(strcmp(terminal, "COLON") == 0) ||
	(strcmp(terminal, "DEF") == 0) ||
	(strcmp(terminal, "ENDDEF") == 0) ||
	(strcmp(terminal, "TAKES") == 0) ||
	(strcmp(terminal, "MODULE") == 0) ||		
	(strcmp(terminal, "PROGRAM") == 0) ||
	(strcmp(terminal, "DRIVERDEF")==0) ||
    (strcmp(terminal, "DRIVERENDDEF") == 0) ||
    (strcmp(terminal, "PARAMETERS") == 0) ||
    (strcmp(terminal, "WITH") == 0) ||
    (strcmp(terminal, "e") == 0) ) return 1;
    else return 0;
}


void create2AST(TREE_NODE_PTR parent, TREE_NODE_PTR child){
	if(child==NULL) return;
	// printf("%s\n",parent->NodeSymbol );
	if((child->isLeafNode==0 && non_term_to_remove(child->NodeSymbol)==0 ) || (child->isLeafNode==1 && term_to_remove(child->NodeSymbol)==0) ){
	
	if(to_eps(child->NodeSymbol)==1 && (strcmp(child->child->NodeSymbol,"e")==0)){
		
	}else{

		TREE_NODE_PTR temp=parent->ASTchild;
		TREE_NODE_PTR prevtemp;

		if(temp==NULL){
			parent->ASTchild=child;
			child->ASTparent=parent;
		}
		else{
			while(temp!=NULL){
				prevtemp=temp;
				temp=temp->ASTsibling;
			}
			prevtemp->ASTsibling=child;
			child->ASTparent=parent;
		}
			
	
		create2AST(child,child->child);
	}

	}else{
		create2AST(parent,child->child);
	}
		create2AST(parent,child->sibling);
	
	return;
}

void construct2AST(TREE_NODE_PTR root){
	create2AST(root,root->child);
	return;
}



//Function to print the complete AST
void print2AST(TREE_NODE_PTR root){
	if(root==NULL){ return; }  
	 
    printf("%-20s",root->lexemeCurrentNode);
    
    if(root->isLeafNode==1){
        printf("%-20d",root->lineno);
        printf("%-20s",root->lexemeCurrentNode);
        }

    else{
        printf("%-20s"," - ");
        printf("%-20s"," - ");
         
    }
    if(strcmp(root->NodeSymbol,"NUM")==0 || strcmp(root->NodeSymbol,"RNUM")==0){
        printf("%-20s",root->lexemeCurrentNode);
        
    }else{
        printf("%-20s"," - ");
    }

	if(root->ASTparent!=NULL)
    printf("%-20s",root->ASTparent->NodeSymbol);
    else
   	printf("%-20s"," - ");
   	    
    if(root->isLeafNode==1){
        printf("%-20s","yes ");
        printf("%-20s\n"," - ");
        
    }else{
        printf("%-20s","no ");
        printf("%-20s\n",root->NodeSymbol);
        
    }
    print2AST(root->ASTchild);
    print2AST(root->ASTsibling);
    
    
    return;
}

int astcount,pstcount;
//Function to calculate the nodes in AST
void countAST(TREE_NODE_PTR root){
	if(root==NULL) return;
	astcount++;
	countAST(root->ASTchild);
	countAST(root->ASTsibling);
}

void countPST(TREE_NODE_PTR  t){
	if(t==NULL) return;
	pstcount++;
	countPST(t->child);
	countPST(t->sibling);
	
}