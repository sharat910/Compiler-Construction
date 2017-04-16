#include "ast.h"
#include "symbol_table.h"
#include <stdio.h>

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
	leaf->line_no=node->lineno;
	leaf->is_leaf = 1;
	sprintf(leaf->name,"%s", identifier);
	leaf->st_ptr = NULL;
	leaf->value = -99999;
	leaf->type=type;
	switch (type){
		case ID_TYPE:
			printf("Function hash:%d Nest:%d Offset:%d\n",node->hash_value,node->nesting,node->offset );
			leaf->st_ptr = get_symbol_table_var_entry(node);
			break;
		
		case NUM_RNUM_TYPE:
			leaf->value = value;
			break;
		
		// Nothing to be done for BOOL NUM RNUM

		// default:
		// 	printf("Unidentified type \"%d\" in make_ast_leaf\n",type);
	}
	printf("Creating leaf for %s whose type is %d\n",identifier,type);
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
	printf("Creating ast node for %s\n with count %d\n",node->NodeSymbol,ast_node->count);
	if(ast_node==NULL)
		printf("Sorry\n");
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
	while(temp!=NULL && is_terminal(temp))
		temp=temp->sibling;
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
	return new_ast_node;
}

//Typecheck function
void type_check(TREE_NODE_PTR node){
	int rule_no = node->rule_no;
	printf("type_check called on node %s with rule no %d\n",node->NodeSymbol,rule_no);
	fflush(stdout);
	//<arithmeticExpr> → <term> <N4> 
	//<term> → <factor> <N5>
	if (rule_no == 77 || rule_no == 80)
	{
		TREE_NODE_PTR factor1 = node->child;
		TREE_NODE_PTR n5 = factor1->sibling;
		printf("Fine till here\n");
		fflush(stdout);
		if (n5->nptr != NULL)
			if (strcmp(factor1->type,"BOOLEAN") == 0)
				printf("Type Error in line %d: BOOLEAN type var invalid here\n",node->lineno);
		printf("Fine till here2\n");
		fflush(stdout);
	}

	//<moduleReuseStmt> → <optional> USE MODULE ID WITH PARAMETERS <idList> SEMICOL
	else if (rule_no == 50){

		TREE_NODE_PTR opt = node->child;
		AST_NODE* id = find_id_ka_nptr(node);
		char *identifier = id->name;
		int h = get_func_hash_value(identifier);
		printf("%s\n",identifier);
		fflush(stdout);
		VAR function_exit = symbol_table[h].scope.out_list.front;
		printf("Fine till here0.1\n");
		fflush(stdout);
		int no_of_out_params = symbol_table[h].scope.out_num;
		printf("Fine till here1\n");
		fflush(stdout);
		if (opt->nptr == NULL && function_exit != NULL){
			printf("Error in line %d: The function is returning %d no. of arguments\n",
				opt->lineno,no_of_out_params);
		}
		else{
			printf("Fine till here2\n");
			fflush(stdout);
			TREE_NODE_PTR idd = opt->child->sibling->child;
			printf("Fine till here3\n");
			fflush(stdout);
			while(idd->nptr != NULL && function_exit != NULL)
			{
				VAR id_st_entry = get_symbol_table_var_entry(idd);
				if (id_st_entry != NULL){				
					if (strcmp(id_st_entry->type,function_exit->type) != 0)
							printf("Type Mismatch in line %d: Expected %s but got %s\n",
								idd->lineno,function_exit->type,id_st_entry->type);
					
					if (id_st_entry->is_array){
						printf("ERROR! in line %d: Return argument can not be array\n",idd->lineno);
					}
				}
				idd = idd->sibling->child;
				function_exit = function_exit->next;
				
				if (idd->nptr == NULL)
					if (function_exit != NULL)
						printf("Error in line %d: More parameters returned by function\n",idd->lineno);

				if (function_exit == NULL)
					if (idd->nptr != NULL)
						printf("Error in line %d: Less parameters returned by function\n",idd->lineno);

			}
		}

		printf("Fine till here4\n");
		fflush(stdout);
		// Checking input params
		VAR function_entry = symbol_table[h].scope.in_list.front;
		TREE_NODE_PTR first_id=opt->sibling->sibling->sibling->sibling->sibling->sibling->child;
		while(first_id->nptr != NULL && function_entry != NULL)
		{
			VAR id_st_entry = get_symbol_table_var_entry(first_id);
			if (id_st_entry != NULL){				
				if (strcmp(id_st_entry->type,function_entry->type) != 0)
						printf("Type Mismatch in line %d: Expected %s but got %s\n",
							first_id->lineno,function_entry->type,id_st_entry->type);
				printf("%d %d\n",id_st_entry->is_array, function_entry->is_array);
				if (id_st_entry->is_array && function_entry->is_array){
					if (id_st_entry->e_range - id_st_entry->s_range != id_st_entry->e_range - id_st_entry->s_range)
						printf("Range length Mismatch in line %d\n",first_id->lineno);
				}
				else
					printf("Type Mismatch in line %d: Array type mismatch\n",first_id->lineno);
			}
			first_id = first_id->sibling->child;
			function_entry = function_entry->next;
			
			if (first_id->nptr == NULL)
				if (function_entry != NULL)
					printf("Error in line %d: More parameters required by function\n",first_id->lineno);

			if (function_entry == NULL)
				if (first_id->nptr != NULL)
					printf("Error in line %d: More parameters passed into the function\n",first_id->lineno);

		}
	}

	// <expression> → MINUS <BorNBAE>
	// <negOrPosAE> → MINUS <BorNBAE>
	else if (rule_no == 57 || rule_no == 58)
	{
		TREE_NODE_PTR child = find_first_nt(node);
		if (strcmp(child->type,"BOOLEAN") == 0)
				printf("Type Error in line %d: BOOLEAN type var invalid here\n",node->lineno);
	}

	//<WithLogOp> → <logicalOp> <AnyTerm2> <WithLogOp>
	else if (rule_no == 63)
	{
		TREE_NODE_PTR AnyTerm2 = node->child->sibling;
		if (strcmp(AnyTerm2->type,"BOOLEAN") != 0)
				printf("Type Error in line %d: Expecting BOOLEAN type expression here\n",node->lineno);
	}

	//<WithRelOp> → <relationalOp> <negOrPosAE> <WithRelOp>
	else if (rule_no == 68)
	{
		TREE_NODE_PTR negOrPosAE = node->child->sibling;
		TREE_NODE_PTR WithRelOp = negOrPosAE->sibling;
		printf("Hererrerere\n");
		fflush(stdout);
		if (WithRelOp->nptr != NULL)
			printf("Error in line %d: Multiple relationalOps in same expression\n",node->lineno);
	
		if (strcmp(negOrPosAE->type,"BOOLEAN") == 0)
			printf("Type Error in line %d: BOOLEAN type expression invalid here\n",node->lineno);
		printf("Hererrererexit\n");
		fflush(stdout);
	}

	//<AOBE>​1​ → BO <AOBE>​2​ BC <alpha>
	else if (rule_no == 70){
		TREE_NODE_PTR aobe = find_first_nt(node);
		TREE_NODE_PTR alpha = aobe->sibling->sibling;
		if (alpha->nptr != NULL)
		{
			TREE_NODE_PTR all_ops = aobe->sibling->sibling->child;
			printf("Debug\n");
			fflush(stdout);
			if (strcmp(all_ops->child->NodeSymbol,"<logicalOp>")==0){
				printf("IF Debug2\n");
				fflush(stdout);
				if (strcmp(aobe->type,"BOOLEAN") != 0)
					printf("Type Error in line %d: Expecting BOOLEAN type expression here\n",node->lineno);
			}
			else{
				printf("ELSE Debug2\n");
				fflush(stdout);			
				if (strcmp(aobe->type,"BOOLEAN") == 0)
					printf("Type Error in line %d:  BOOLEAN type expression invalid here\n",node->lineno);
			}
			printf("Debug2\n");
			fflush(stdout);
		}
	}

	//<alpha> → <all_ops> <AOBE> 
	else if (rule_no == 71){
		TREE_NODE_PTR all_ops = node->child;
		TREE_NODE_PTR aobe = all_ops->sibling;
		if (strcmp(all_ops->child->NodeSymbol,"<logicalOp>")==0){
			if (strcmp(aobe->type,"BOOLEAN") != 0)
				printf("Type Error in line %d: expression after logicalOp not BOOLEAN type\n",node->lineno);
		}
		else{
			if (strcmp(aobe->type,"BOOLEAN") == 0)
				printf("Type Error in line %d: expression after cannot be BOOLEAN type\n",node->lineno);
		}
			
	}

	//<N4>1 → <op1> <term> <N4>2
	//<N5>1 → <op2> <factor> <N5>2
	else if (rule_no == 78 || rule_no == 81)
	{
		TREE_NODE_PTR factor1 = node->child->sibling;
		printf("here %s\n",factor1->type);
		fflush(stdout);
		if (strcmp(factor1->type,"BOOLEAN") == 0)
			printf("Type Error in line %d: BOOLEAN type var invalid here\n",node->lineno);
	}

	//<condionalStmt> → SWITCH BO ID BC START <caseStmts> <default> END
	else if (rule_no == 97)
	{
		TREE_NODE_PTR id = node->child->sibling->sibling;
		TREE_NODE_PTR casestmts = id->sibling->sibling->sibling;
		if (strcmp(id->type,casestmts->type) != 0)
		{
			printf("Type Error in line %d: type of ID (%s) differs from case statements type (%s)\n",
				node->lineno,id->type,casestmts->child->sibling->type);
		}
	}

	//<caseStmts> → CASE <value> COLON <statements> BREAK SEMICOL <MultiCase>
	//<MultiCase>1 → CASE <value> COLON <statements> BREAK SEMICOL <MultiCase>2
	else if (rule_no == 98 || rule_no == 99)
	{

		TREE_NODE_PTR value = find_first_nt(node);
		TREE_NODE_PTR multicase = value->sibling->sibling->sibling->sibling->sibling;
		if (multicase->nptr != NULL)
			if (strcmp(value->type,multicase->type) != 0)
				printf("Type Error in line %d: Case value type mismatch\n",node->lineno);
		node->type = value->type;
	}

	//<iterativeStmt> → WHILE BO <AOBE> BC START <statements> END	
	else if (rule_no == 107)
	{
		if(strcmp(node->child->sibling->sibling->type,"BOOLEAN")!=0)
			printf("Type Error in line %d: while condition not of BOOLEAN type\n",node->lineno);
	}

}

void magic_function(TREE_NODE_PTR node)
{
	int rule_no = node->rule_no;
	printf("%d\n",rule_no);
	// printf("Line no. %d ",node->lineno );
	if (is_non_terminal(node))
		switch(rule_no){
			// Just make a new node
			case 1:
			case 2:
			case 5:
			case 7:
			case 8:
			case 9:
			case 11:
			case 12:
			case 14:
			case 15:
			case 25:
			case 43:

			case 53:
			case 54:
			case 106:
			node->nptr = make_ast_node(node);
			break;


			case 77:
			case 80:			
			//Typecheck
			// type_check(node);			
			node->nptr = make_ast_node(node);
			node->type = node->child->type;
			printf("Setting type of %s to be %s\n",node->NodeSymbol,node->type);
			fflush(stdout);
			break;

			case 50:
			case 63:
			case 68:
			case 71:
			case 78:
			case 81:
			case 97:
			case 98:
			case 99:
			case 107:
			type_check(node);
			printf("After type check\n");
			fflush(stdout);
			node->nptr = make_ast_node(node);
			break;

			// Datatype statements
			case 17:
			case 18:
			case 19:
			case 21:
			case 22:
			case 23:
			node->type=node->child->lexemeCurrentNode;
			break;

			// <var> → ID <whichId>
			case 34:
			node->nptr = make_ast_node(node);
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
			case 83:
			case 101:
			case 102:
			case 103:
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
			case 58:
			type_check(node);
			node->nptr = find_first_nt(node)->nptr;
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
			case 33:
			case 51:


			// Only one child which is non_terminal
			case 27:
			case 28:
			case 29:
			case 30:
			case 31:
			case 41:
			case 42:
			case 73:
			case 74:
			case 75:
			case 76:
			case 104:
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

			
			case 70:
			//Typecheck
			type_check(node);
			node->nptr = make_ast_node(node);
			TREE_NODE_PTR alpha = node->child->sibling->sibling->sibling;
			if (alpha->nptr != NULL)
				if (strcmp(alpha->child->child->NodeSymbol,"<relationalOp>")==0)
					node->type = "BOOLEAN";
				else
					node->type = node->child->sibling->type;
			else					
				node->type = node->child->sibling->type;
			break;

			// <declareStmt> → DECLARE <idList> COLON <dataType> SEMICOL
			case 96:
			node->nptr = make_ast_node(node);
			TREE_NODE_PTR idList = node->child->sibling;
			TREE_NODE_PTR dataType = idList->sibling->sibling;
			idList->type = dataType->type;
			break;

			//<range> → NUM​1​ RANGEOP NUM​2
			case 108:
			node->nptr = get_nptr_range(node);
            break;

			//All Op cases
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
			case 95:
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
			case 72:
			case 79:
			case 82:
			case 100:
			case 105:
			node->nptr = NULL;
			break;

			case 4:
			case 32:
			case 39:
			node->nptr = find_id_ka_nptr(node);
			break;

		}

	else if (strcmp(node->NodeSymbol,"ID") == 0)
	{
		node->nptr = make_ast_leaf(node,ID_TYPE,0);
		VAR st_entry = get_symbol_table_var_entry(node);
		if (st_entry != NULL)
			node->type = st_entry->type;
		else{
			node->type = (char*) malloc(sizeof(char)*10);
			sprintf(node->type,"%s","DUMMY");
		}
	}
	else if (strcmp(node->NodeSymbol,"NUM") == 0){
		node->nptr = make_ast_leaf(node,NUM_RNUM_TYPE,node->valueLfNumber);
		node->type = (char*) malloc(sizeof(char)*10);
		sprintf(node->type,"%s","INTEGER");
	}
		
	else if	(strcmp(node->NodeSymbol,"RNUM") == 0)
	{
		node->nptr = make_ast_leaf(node,NUM_RNUM_TYPE,node->valueLfNumber);
		node->type = (char*) malloc(sizeof(char)*10);
		sprintf(node->type,"%s","REAL");
	}
	else if ((strcmp(node->NodeSymbol,"TRUE") == 0) || 
		(strcmp(node->NodeSymbol,"FALSE") == 0))
	{
		node->nptr = make_ast_leaf(node,BOOL_TYPE,0);
		node->type = (char*) malloc(sizeof(char)*10);
		sprintf(node->type,"%s","BOOLEAN");
	}
	else{
	}
}


void recursive_function(TREE_NODE_PTR node)
{
	if (node->child != NULL)
		recursive_function(node->child);
	printf("Line no. %d ",node->lineno);
	printf("Calling magic_function on %s\n",node->NodeSymbol);
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
	else 
		if (root->is_leaf)
		{
			printf("Line No. %d ", root->line_no);
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