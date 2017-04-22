// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)


#include "semantic_checker.h"
int semantic_error_cnt;

void semantic_check(AST_NODE* root){
	if(root == NULL)
		return;
	if (root->is_leaf)
		return;

	if (strcmp(root->ptNode->NodeSymbol,"<module>")==0)
	{
		AST_NODE* func_id = root->array[0];
		char* funct_name = func_id->name;
		int h1 = get_func_hash_value(funct_name);
		int n  = symbol_table[h1].scope.out_num;
		int arr[n];
		for (int i = 0; i < n; i++)
			arr[i]=0;

		list_params ret_params = symbol_table[h1].scope.out_list;

		
		
		AST_NODE* stmts = root->array[3];
		while(stmts != NULL)
		{
			AST_NODE* stmt = stmts->array[0];

			// Check for recursions
			// printf("%s\n",stmt->ptNode->NodeSymbol);
			// fflush(stdout);
			if (strcmp(stmt->ptNode->NodeSymbol,"<moduleReuseStmt>")==0)
			{
				AST_NODE* use_func_id = stmt->array[1];
				printf("%s\n",use_func_id->name );
				int h2 = get_func_hash_value(use_func_id->name);
				if (h1 == h2)
					printf("Line No. %d | Sematic Error: Recursive Function\n",use_func_id->ptNode->lineno);
			}

			//Check for assignments to the returned variables
			if (strcmp(stmt->ptNode->NodeSymbol,"<assignmentStmt>")==0)
			{
				AST_NODE* id = stmt->array[0];
				int a = find_param2(ret_params,id->name);
				if (a != -1)
					arr[a] = 1;
			}
			stmts = stmts->array[1];
		}

		for (int i = 0; i < n;i++)
			if (arr[i] == 0)
				printf("Line No. %d | Semantic Error: Return value %s not assigned\n",func_id->ptNode->lineno, find_param2_with_index(ret_params,i));

	}

	if (strcmp(root->ptNode->NodeSymbol,"<conditionalStmt>")==0)
	{
		AST_NODE* id = root->array[0];

		if (strcmp(id->ptNode->type,"INTEGER")==0){
			if(root->array[2] == NULL)
				printf("Line No. %d | Semantic Error: Switch on integer needs to have a default statement\n",id->ptNode->lineno);
		}
				
		else if (strcmp(id->ptNode->type,"BOOLEAN")==0){
			if (root->array[2] != NULL)
				printf("Line No. %d | Semantic Error: Switch on boolean cannot have a default statement\n",id->ptNode->lineno);
		}

		else
			printf("Line No. %d | Semantic Error: Switch can't be applied on real type variable\n",id->ptNode->lineno);
	}

	if (strcmp(root->ptNode->NodeSymbol,"<iterativeStmt>")==0)
	{
		//FOR Statement
		if(root->count == 3){
			AST_NODE* for_id = root->array[0];
			AST_NODE* stmts = root->array[2];
			while(stmts != NULL)
			{
				AST_NODE* stmt = stmts->array[0];			
				if (strcmp(stmt->ptNode->NodeSymbol,"<assignmentStmt>")==0)
				{
					AST_NODE* id = stmt->array[0];
					if (strcmp(id->name,for_id->name)==0)
						printf("Line No. %d | Semantic Error: For iterative variable %s can't be assigned value\n",
							id->ptNode->lineno,id->name);
				}
				stmts = stmts->array[1];

			}
		}
	}
	int loop_count = root->count;
	for (int i = 0; i < loop_count; i++)
	{
		if (root->array[i] != NULL)
		{
			semantic_check(root->array[i]);
		}
		
	}
		
}