#include "type_checker.h"
//Typecheck function

int type_error_cnt;
void type_check(TREE_NODE_PTR node){
	int rule_no = node->rule_no;
	
	//<arithmeticExpr> → <term> <N4> 
	//<term> → <factor> <N5>
	if (rule_no == 76 || rule_no == 79 || rule_no==65)
	{
		TREE_NODE_PTR factor1 = node->child;
		TREE_NODE_PTR n5 = factor1->sibling;
		if (n5->nptr != NULL)
			if (strcmp(factor1->type,"BOOLEAN") == 0){
				printf("Line %d | Type Error: BOOLEAN type variable invalid with operator %s\n",node->lineno,n5->child->NodeSymbol);
				type_error_cnt++;
			}
	}
	//<var> →  ID <whichId>
	else if (rule_no == 34)
	{
		VAR a = node->child->nptr->st_ptr;
		if ( a != NULL)
		{
			if (a->is_array && node->nptr->array[1] == NULL){
				printf("Type Error in line %d: Array %s not indexed\n",node->lineno,a->var_name);
				type_error_cnt++;
			}
			if (!(a->is_array) && node->nptr->array[1] != NULL){
				type_error_cnt++;
				printf("Type Error in line %d: Cannot index %s. It's not an array\n",node->lineno,a->var_name);
			}
		}
	}

	//<assignmentStmt> →  ID <whichStmt>
	else if (rule_no == 43){
		TREE_NODE_PTR id = node->child;
		TREE_NODE_PTR whichStmt = id->sibling;
		if (strcmp(id->type,whichStmt->type) != 0){
			type_error_cnt++;
			printf("Line %d | Type Error: Mismatch between %s and %s\n",node->lineno,id->type,whichStmt->type);
		}
	}

	//<moduleReuseStmt> → <optional> USE MODULE ID WITH PARAMETERS <idList> SEMICOL
	else if (rule_no == 50){

		TREE_NODE_PTR opt = node->child;
		AST_NODE* id = find_id_ka_nptr(node);
		char *identifier = id->name;
		int h = get_func_hash_value(identifier);
		VAR function_exit = symbol_table[h].scope.out_list.front;
		int no_of_out_params = symbol_table[h].scope.out_num;
		if (opt->nptr == NULL){
			if (function_exit != NULL){
				type_error_cnt++;
				printf("Error in line %d: The function is returning %d no. of arguments\n",
					opt->lineno,no_of_out_params);
			}
		}
		else{
			TREE_NODE_PTR idd = opt->child->sibling->child;
			while(idd->nptr != NULL && function_exit != NULL)
			{
				VAR id_st_entry = get_symbol_table_var_entry(idd);
				if (id_st_entry != NULL){				
					if (strcmp(id_st_entry->type,function_exit->type) != 0){
						type_error_cnt++;
							printf("Type Mismatch in line %d: Expected %s but got %s\n",
								idd->lineno,function_exit->type,id_st_entry->type);
					}
					if (id_st_entry->is_array){
						type_error_cnt++;
						printf("ERROR! in line %d: Return argument can not be array\n",idd->lineno);
					}
				}
				idd = idd->sibling->child;
				function_exit = function_exit->next;
				
				if(strcmp(idd->NodeSymbol,"e")==0)
					{
						if (function_exit != NULL){
							type_error_cnt++;
							printf("Error in line %d: More parameters returned by function\n",idd->lineno);
						}
					}
				else
					 idd=idd->sibling;

				if (function_exit == NULL){
					if(strcmp(idd->NodeSymbol,"e")!=0){
						type_error_cnt++;
						printf("Error in line %d: Less parameters returned by function\n",idd->lineno);
					}
				}

			}
		}
		// Checking input params
		VAR function_entry = symbol_table[h].scope.in_list.front;
		TREE_NODE_PTR first_id=opt->sibling->sibling->sibling->sibling->sibling->sibling->child;
		while(first_id->nptr != NULL && function_entry != NULL)
		{
			VAR id_st_entry = get_symbol_table_var_entry(first_id);
			if (id_st_entry != NULL){				
				if (strcmp(id_st_entry->type,function_entry->type) != 0){
					type_error_cnt++;
						printf("Line %d | Type Error: Type mismatch expected %s but got %s\n",
							first_id->lineno,function_entry->type,id_st_entry->type);
					}
				// printf("%d %d\n",id_st_entry->is_array, function_entry->is_array);
				if (id_st_entry->is_array && function_entry->is_array){
					if ((id_st_entry->e_range - id_st_entry->s_range) != (function_entry->e_range - function_entry->s_range)){
						type_error_cnt++;
						printf("Line %d | Type Error: Array type variable's range length mismatch\n",first_id->lineno);
					}
				}
				else if(id_st_entry->is_array || function_entry->is_array){
					type_error_cnt++;
					printf("Line %d | Type Error: Array type mismatch\n",first_id->lineno);
				}
			}
			first_id = first_id->sibling->child;
			function_entry = function_entry->next;
			
			if (strcmp(first_id->NodeSymbol,"e")==0)
			{
				if (function_entry != NULL){
					type_error_cnt++;
					printf("Line %d | Error: More parameters required by function\n",first_id->lineno);
				}
			}
			else{ 
				first_id=first_id->sibling;
			}
			if (function_entry == NULL)
				if(strcmp(first_id->NodeSymbol,"e")!=0){
					type_error_cnt++;
					printf("Line %d | Error: More parameters passed into the function\n",first_id->lineno);
				}

		}
	}

	// <expression> → MINUS <BorNBAE>
	// <negOrPosAE> → MINUS <BorNBAE>
	else if (rule_no == 57 || rule_no == 58)
	{
		TREE_NODE_PTR child = find_first_nt(node);
		if (strcmp(child->type,"BOOLEAN") == 0){
				printf("Line %d | Type Error: BOOLEAN type expression cannot be negated\n",node->lineno);
			type_error_cnt++;
		}
	}

	else if(rule_no == 62)
	{
		TREE_NODE_PTR anyterm = node->child;
		TREE_NODE_PTR withlogop = anyterm->sibling;
		if (withlogop->nptr != NULL)
			if (strcmp(anyterm->type,"BOOLEAN") != 0){
				type_error_cnt++;
				printf("Line %d | Type Error: BOOLEAN type expression expected.\n",node->lineno);
			}
	}

	//<WithLogOp> → <logicalOp> <AnyTerm2> <WithLogOp>
	else if (rule_no == 63)
	{
		TREE_NODE_PTR AnyTerm2 = node->child->sibling;
		if (strcmp(AnyTerm2->type,"BOOLEAN") != 0){
				printf("Line %d | Type Error: BOOLEAN type expression expected.\n",node->lineno);
			type_error_cnt++;
		}
	}

	//<WithRelOp> → <relationalOp> <negOrPosAE> <WithRelOp>
	else if (rule_no == 68)
	{
		TREE_NODE_PTR negOrPosAE = node->child->sibling;
		TREE_NODE_PTR WithRelOp = negOrPosAE->sibling;
		// printf("Hererrerere\n");
		// fflush(stdout);
		if (WithRelOp->nptr != NULL){
			type_error_cnt++;
			printf("Error in line %d: Multiple relationalOps in same expression\n",node->lineno);
		}
	
		if (strcmp(negOrPosAE->type,"BOOLEAN") == 0){
			type_error_cnt++;
			printf("Line %d | Type Error: BOOLEAN type expression invalid with relational operator\n",node->lineno);
		}
		// printf("Hererrererexit\n");
		// fflush(stdout);
	}

	else if (rule_no == 70){
		TREE_NODE_PTR all_ops = node->child;
		TREE_NODE_PTR aobe = all_ops->sibling;
		if (strcmp(all_ops->child->NodeSymbol,"<logicalOp>")==0){
			if (strcmp(aobe->type,"BOOLEAN") != 0){
				type_error_cnt++;
				printf("Line %d | Type Error: expression after logicalOp is not BOOLEAN type\n",node->lineno);
			}
		}
		else{
			if (strcmp(aobe->type,"BOOLEAN") == 0){
				type_error_cnt++;
				printf("Line %d | Type Error: expression after cannot be BOOLEAN type\n",node->lineno);
			}
		}
			
	}

	//<N4>1 → <op1> <term> 
	//<N5>1 → <op2> <factor> <N5>2
	else if (rule_no == 77 || rule_no == 80)
	{
		TREE_NODE_PTR factor1 = node->child->sibling;
		// printf("here %s\n",factor1->type);
		// fflush(stdout);
		if (strcmp(factor1->type,"BOOLEAN") == 0){
			type_error_cnt++;
			printf("Line %d | Type Error: BOOLEAN type var invalid here\n",node->lineno);
		}
	}

	//<conditionalStmt> → SWITCH BO ID BC START <caseStmts> <default> END
	else if (rule_no == 96)
	{
		TREE_NODE_PTR id = node->child->sibling->sibling;
		TREE_NODE_PTR casestmts = id->sibling->sibling->sibling;
		if (strcmp(id->type,casestmts->type) != 0)
		{	
			type_error_cnt++;
			printf("Line %d | Type Error: type of switch Identifier (%s) differs from case statements type (%s)\n",
				node->lineno,id->type,casestmts->child->sibling->type);
		}
	}

	//<caseStmts> → CASE <value> COLON <statements> BREAK SEMICOL <MultiCase>
	//<MultiCase>1 → CASE <value> COLON <statements> BREAK SEMICOL <MultiCase>2
	else if (rule_no == 97 || rule_no == 98)
	{

		TREE_NODE_PTR value = find_first_nt(node);
		TREE_NODE_PTR multicase = value->sibling->sibling->sibling;
		if (multicase->nptr != NULL)
			if (strcmp(value->type,multicase->type) != 0){
				type_error_cnt++;
				printf("Line %d | Type Error: Type mismatch between case values\n",node->lineno);
			}
		node->type = value->type;
	}

	//<iterativeStmt> → WHILE BO <AOBE> BC START <statements> END	
	else if (rule_no == 106)
	{
		if(strcmp(node->child->sibling->sibling->type,"BOOLEAN")!=0){
			type_error_cnt++;
			printf("Line %d | Type Error: While condition not of BOOLEAN type\n",node->lineno);
		}
	}

}