// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#include "astDef.h"
#include "symbolTable.h"

func_entry symbol_table[101];

extern int offset_arr[100];
VAR create_param_entry(char* name,int line,char* type)
{
	VAR temp;
	temp=(VAR) malloc(sizeof(var));
	if(temp!=NULL){
		sprintf(temp->var_name,"%s",name);
		sprintf(temp->type,"%s",type);
		temp->line_no=line;
		temp->next=NULL;
	}
	else
	{
		printf("ERROR: Insufficient Memory...\n");
		exit(0);
	}
return temp;

}

list_params initialize_queue_params(void)
{
	list_params st;
	st.front=NULL;
	st.no_of_params=0;
	return st;
}

int isEmpty_queue_params(list_params st)
{
	if(st.front==NULL)
		return 1;
	else return 0;
}

list_params distinct_queue_params(list_params st,VAR v)
{
	v->next=NULL;
	VAR p;
	p = st.front;
	if(st.no_of_params==0)
	{
		st.front=v;
		st.no_of_params=1;
		return st;
	}
	
	while(p!=NULL)
	{	

		if(strcmp(p->var_name,v->var_name)==0)
		{
			printf("Duplicate\n");
			return st;
		}

		printf("error free\n");
		if(p->next==NULL){
			p->next=v;
			st.no_of_params++;
			return st;
		}
		p = p->next;
	}
	printf("error free\n");

	
	return st;
}

void print_queue_params(list_params st)
{
	VAR p;
	p = st.front;
	while(p!=NULL)
	{
		printf(" %s -->", p->var_name);
		p = p->next;
	}
	printf("\n");
}

int find_param(list_params st,char* a)
{
	if(st.no_of_params==0)
		return 0;
	VAR v=st.front;
	while(v!=NULL)
	{
		if(strcmp(v->var_name,a)==0)
			return 1;
		v=v->next;
	}
	return 0;
}

int find_param2(list_params st,char* a)
{
	if(st.no_of_params==0)
		return -1;
	VAR v=st.front;
	int i=0;
	while(v!=NULL)
	{
		if(strcmp(v->var_name,a)==0)
			return i;
		v=v->next;
		i++;
	}
	return -1;
}

char* find_param2_with_index(list_params st,int index)
{
	if(st.no_of_params==0)
		return NULL;
	VAR v=st.front;
	while(index != 0)
	{		
		v=v->next;
		index--;
	}
	return v->var_name;
}

int get_hash_value(char* a)
{
	long long num=1;
	long long hash=0;
	for(int i=0;i<strlen(a);i++)
	{
		hash+=num*a[i];
		num*=41;
	}
	return hash%1009;
}
int get_func_hash_value(char* a)
{
	long long num=1;
	long long hash=0;
	for(int i=0;i<strlen(a);i++)
	{
		hash+=num*a[i];
		num*=41;
	}
	return hash%101;
}
void add_variable(int h,int nesting,int offset,VAR v)
{
	symbol_table[h].scope.func_table[nesting][offset].exist=1;
	int num=get_hash_value(v->var_name);
	int n=num;
	int i=1;
	while(1)
	{
		// printf("%d\n", i);
		if(symbol_table[h].scope.func_table[nesting][offset].variables[n]==NULL)
		{
			// printf("yo\n");
			symbol_table[h].scope.func_table[nesting][offset].variables[n]=(VAR)malloc(sizeof(var));
			sprintf(symbol_table[h].scope.func_table[nesting][offset].variables[n]->var_name,"%s",v->var_name);
			sprintf(symbol_table[h].scope.func_table[nesting][offset].variables[n]->type,"%s",v->type);
			symbol_table[h].scope.func_table[nesting][offset].variables[n]->line_no=v->line_no;
			symbol_table[h].scope.func_table[nesting][offset].variables[n]->h=h;
			symbol_table[h].scope.func_table[nesting][offset].variables[n]->n=nesting;
			symbol_table[h].scope.func_table[nesting][offset].variables[n]->o=offset;
			symbol_table[h].scope.func_table[nesting][offset].variables[n]->dec=1;
			symbol_table[h].scope.func_table[nesting][offset].variables[n]->is_array=v->is_array;
			symbol_table[h].scope.func_table[nesting][offset].variables[n]->s_range=v->s_range;
			symbol_table[h].scope.func_table[nesting][offset].variables[n]->e_range=v->e_range;
			symbol_table[h].scope.func_table[nesting][offset].variables[n]->m=v->m;
			symbol_table[h].scope.func_table[nesting][offset].variables[n]->size=v->size;
			break;
		}
		n=(n+i)%1009;
		i++;
	}
}
// {
// 	printf("%s\n",a );
// 	fflush(stdout);
// 	int num=get_hash_value(a);
// 	symbol_table[h].scope.func_table[n][o].variables[num]=(VAR)malloc(sizeof(var));
// 	symbol_table[h].scope.func_table[n][o].variables[num]->dec=0;
// }
void symbol_table_init()
{
	for(int i=0;i<101;i++)
		symbol_table[i].exist=0;
}
void create_func_scope(int in_num,int out_num,char* name)
{
	func_entry* f=&symbol_table[get_func_hash_value(name)];
	f->exist=1;

	f->scope.in_num=in_num;
	f->scope.out_num=out_num;
	f->scope.in_list=initialize_queue_params();
	f->scope.out_list=initialize_queue_params();
}

int find_var(char* a,int hash,int nesting,int offset)
{
	int n=nesting;
	int o=offset;
	
	while(n>0)
	{
		printf("Nesting:%d Offset:%d\n",n,o );
		for(int i=0;i<1009;i++)
		{
			if(symbol_table[hash].scope.func_table[n][o].variables[i]!=NULL)
			{
				if(strcmp(a,symbol_table[hash].scope.func_table[n][o].variables[i]->var_name)==0)
					{
						// printf("nesting:%d offset:%d\n",n,o );
						return 1;
					}
			}
		}
		n--;
		o=symbol_table[hash].scope.func_table[n][o].parent;
	}
	return 0;
}

int complete_find(char* a,int h,int n,int o)
{
	if(find_var(a,h,n,o))
		return 1;
	else return 0;
}


VAR return_var(char* a,int hash,int nesting,int offset)
{
	int n=nesting;
	int o=offset;
	
	while(n>0)
	{
		// printf("Nesting:%d Offset:%d\n",n,o );
		for(int i=0;i<1009;i++)
		{
			if(symbol_table[hash].scope.func_table[n][o].variables[i]!=NULL)
			{
				if(strcmp(a,symbol_table[hash].scope.func_table[n][o].variables[i]->var_name)==0)
					{
						// printf("nesting:%d offset:%d\n",n,o );
						return symbol_table[hash].scope.func_table[n][o].variables[i];
					}
			}
		}
		n--;
		o=symbol_table[hash].scope.func_table[n][o].parent;
	}
	return NULL;
}

VAR get_symbol_table_var_entry(TREE_NODE_PTR ptr)
{
	return return_var(ptr->lexemeCurrentNode,ptr->hash_value,ptr->nesting,ptr->offset);
}

int main_seen=0;
int m=0;;
void constructSymbolTable(TREE_NODE_PTR root,FILE* out_fp,int hash_value,int nesting,int offset)
{
	// printf("Function %d %d\n",hash_value,nesting);
	int n=nesting;
	int h=hash_value;
	int o=offset;
	int d=1;
	if(root!=NULL)
	{
		// if(strcmp(root->token,"NUM")!=0 && strcmp(root->token,"RNUM")!=0)
		// 	fprintf(out_fp,"%s\t%d\t%s\t%s\t%s\t%d\t%s\n",root->lexemeCurrentNode,root->lineno,root->token," N/A ",root->parentNodeSymbol,root->isLeafNode,root->NodeSymbol);
		// else
		// 	fprintf(out_fp,"%s\t%d\t%s\t%lf\t%s\t%d\t%s\n",root->lexemeCurrentNode,root->lineno,root->token,root->valueLfNumber,root->parentNodeSymbol,root->isLeafNode,root->NodeSymbol);
		if(strcmp(root->token,"DRIVER")==0)
		{
			h=get_func_hash_value("DRIVER");
			create_func_scope(0,0,"DRIVER");
			main_seen=1;
			for(int i=1;i<100;i++)
				offset_arr[i]=0;
			n=0;
			printf("Driver Function seen.\n");
			m=0;
		}

		if(strcmp(root->token,"START")==0){
			
			symbol_table[h].scope.func_table[n][o].parent=o;
			printf("Line %d parent offset %d\n", root->lineno,o);
			o=offset_arr[++n];
			symbol_table[h].scope.func_table[n][o].start=root->lineno;
		}

		if(strcmp(root->token,"END")==0){
			symbol_table[h].scope.func_table[n][o].end=root->lineno;
			o=symbol_table[h].scope.func_table[n][o].parent;
			offset_arr[n]++;
			n--;
			if(n==-1)
				h=-1;

		}
		
		fflush(stdout);
		if(strcmp(root->token,"ID")==0)
		{

			printf("Line %d ID encountered->%s ",root->lineno,root->lexemeCurrentNode );
			if(strcmp(root->parentNodeSymbol,"<moduleDeclaration>")==0)
				{
					printf("1 ");
					printf("Module Declared.");
					printf("Declaring%s\n",root->lexemeCurrentNode);
					h=get_func_hash_value(root->lexemeCurrentNode);
					create_func_scope(0,0,root->lexemeCurrentNode);
					m=0;
				}
			else if(strcmp(root->parentNodeSymbol,"<module>")==0)
				{// check existence and feed parameters;
					printf("2 ");
					printf("ModuleDefinition.\n");
					int h_curr=get_func_hash_value(root->lexemeCurrentNode);
					if(symbol_table[h_curr].exist || !main_seen){
						h=h_curr;
						for(int i=1;i<100;i++)
							offset_arr[i]=0;
						n=0;
						m=0;
					}
					else{
						printf("Function %s not declared.\n",root->lexemeCurrentNode );
						h=get_func_hash_value(root->lexemeCurrentNode);
						create_func_scope(0,0,root->lexemeCurrentNode);
						for(int i=1;i<100;i++)
							offset_arr[i]=0;
						n=0;
						m=0;
					}
				}
			else if(strcmp(root->parentNodeSymbol,"<moduleReuseStmt>")==0)
				{// check params;


				}
			else if(strcmp(root->parentNodeSymbol,"<assignmentStmt>")==0 || 
				strcmp(root->parentNodeSymbol,"<iterativeStmt>")==0 ||
				strcmp(root->parentNodeSymbol,"<condionalStmt>")==0 ||
				strcmp(root->parentNodeSymbol,"<whichId>")==0 ||
				strcmp(root->parentNodeSymbol,"<var>")==0 ||
				strcmp(root->parentNodeSymbol,"<index>")==0 ||
				strcmp(root->parentNodeSymbol,"<ioStmt>")==0)
				{// check var entry in hash_table

					printf("3 ");
					if(complete_find(root->lexemeCurrentNode,h,n,o)==0)
						printf("Not declared.\n");
					else {
						printf("Declared.\n");
						root->hash_value=h;
						root->nesting=n;
						root->offset=o;
					}
				}
			else if(strcmp(root->parentNodeSymbol,"<idList>")==0)
			{
				if(strcmp(root->parent->parentNodeSymbol,"<declareStmt>")==0)
				{
					printf("4 ");
					VAR v=(VAR)malloc(sizeof(var));
					d=0;
					char type[20];
					int st,en;
					
					// printf("Here");
					sprintf(type,"%s",root->parent->sibling->sibling->child->NodeSymbol);
					// printf(" %s ",root->parent->sibling->sibling->NodeSymbol);
					TREE_NODE_PTR a;
					
					int this_array=0;
					if(strcmp(type,"ARRAY")==0)
					{
						// printf("%sHI\n",type);
						fflush(stdout);
						a=root->parent->sibling->sibling->child;
						st=a->sibling->sibling->child->valueLfNumber;
						en=a->sibling->sibling->child->sibling->sibling->valueLfNumber;
						a=a->sibling->sibling->sibling->sibling->sibling->child;
						printf("type of array %s\n", a->NodeSymbol);
						sprintf(type,"%s",a->NodeSymbol);
						this_array=1;
						if(strcmp(type,"BOOLEAN")==0)
							v->size=en-st+1;
						else if(strcmp(type,"INTEGER")==0)
							v->size=(en-st+1)*2;
						else v->size=(en-st+1)*4;
						v->is_array=1;
						v->s_range=st;
						v->e_range=en;
					}
					else{
						if(strcmp(type,"BOOLEAN")==0)
							v->size=1;
						else if(strcmp(type,"INTEGER")==0)
							v->size=2;
						else v->size=4;
						
						v->is_array=0;
						v->s_range=-1;
						v->e_range=-1;
					}
					sprintf(v->var_name,"%s",root->lexemeCurrentNode);
					sprintf(v->type,"%s",type);
					v->line_no=root->lineno;
					
					if(complete_find(root->lexemeCurrentNode,h,n,o)){
						printf("Redeclaration.\n");
					}
					else{
						root->hash_value=h;
						root->nesting=n;
						root->offset=o;
						v->m=m;
						m+=v->size;
						printf("%s Declared of type",root->lexemeCurrentNode );
						printf("%s in nesting %d and offset %d.\n",type,n,o);
						add_variable(h,n,o,v);
						VAR v=get_symbol_table_var_entry(root);
						if(v!=NULL)
							printf("Yeahhhhh %s\n",v->var_name);
						else printf("NOOO\n");
					}

					a=root->sibling;
					while(strcmp(a->child->NodeSymbol,"e")!=0)
					{
						a=a->child->sibling;
						// printf("Bakchodi\n");
						printf("Line %d ID encountered->%s ",a->lineno,a->lexemeCurrentNode );
						
						// fflush(stdout);
						VAR v=(VAR)malloc(sizeof(var));
						sprintf(v->var_name,"%s",a->lexemeCurrentNode);
						v->line_no=a->lineno;
						sprintf(v->type,"%s",type);
						
						if(this_array)
						{
							v->is_array=1;
							v->s_range=st;
							v->e_range=en;
						if(strcmp(type,"BOOLEAN")==0)
							v->size=en-st+1;
						else if(strcmp(type,"INTEGER")==0)
							v->size=(en-st+1)*2;
						else v->size=(en-st+1)*4;
						}
						else{
							if(strcmp(type,"BOOLEAN")==0)
								v->size=1;
							else if(strcmp(type,"INTEGER")==0)
								v->size=2;
							else v->size=4;
						
							v->is_array=0;
							v->s_range=-1;
							v->e_range=-1;
						}
						
						if(complete_find(v->var_name,h,n,o)){
							printf("Redeclaration.\n");
						}
						else{
							v->m=m;
							m+=v->size;
							a->hash_value=h;
							a->nesting=n;
							a->offset=o;
							
							printf("Declared of type%s in nesting %d and offset %d.\n",type,n,o );
							add_variable(h,n,o,v);
							VAR v1=return_var(v->var_name,h,n,o);
							if(v1!=NULL)
								printf("declared and found %s\n",v1->var_name);
							else printf("sad\n");
						}
						a=a->sibling;
					}
					// printf("here2\n");
				}
				else if(strcmp(root->parent->parentNodeSymbol,"<optional>")==0 ||
					(strcmp(root->parent->parentNodeSymbol,"<moduleReuseStmt>")==0))
				{
					printf("5 ");
					d=0;
					if(complete_find(root->lexemeCurrentNode,h,n,o)==0)
						printf("Undeclared.\n");
					else {
						printf("Declared.\n");
						root->hash_value=h;
						root->nesting=n;
						root->offset=o;
					}
					TREE_NODE_PTR a=root->sibling;
					while(strcmp(a->child->NodeSymbol,"e")!=0)
					{
						a=a->child->sibling;
						printf("ID->%s ",a->lexemeCurrentNode );
						if(complete_find(a->lexemeCurrentNode,h,n,o)==0)
							printf("Undeclared.\n");
						else {
							printf("Declared.\n");
							a->hash_value=h;
							a->nesting=n;
							a->offset=o;
						}
						a=a->sibling;
					}
				}
			}
			else if(strcmp(root->parentNodeSymbol,"<input_plist>")==0 ||
			strcmp(root->parentNodeSymbol,"<input_plist_ex>")==0)
			{
				printf("6 ");
				fflush(stdout);
				// printf("%d %d %d\n",h,nesting,o);
				VAR v=(VAR)malloc(sizeof(var));
				sprintf(v->var_name,"%s",root->lexemeCurrentNode);
				printf("Declared of type %s. \n", root->sibling->sibling->child->token);
				sprintf(v->type,"%s",root->sibling->sibling->child->token);
				TREE_NODE_PTR a=root->sibling->sibling->child;
				int st,en;
				if(strcmp(v->type,"ARRAY")==0)
				{
					// printf("%sHI\n",type);
					fflush(stdout);
					// a=a->sibling->sibling->child;
					st=a->sibling->sibling->child->valueLfNumber;
					en=a->sibling->sibling->child->sibling->sibling->valueLfNumber;
					a=a->sibling->sibling->sibling->sibling->sibling->child;
					printf("%s.\n", a->NodeSymbol);
					sprintf(v->type,"%s",a->NodeSymbol);
					v->is_array=1;
					v->s_range=st;
					v->e_range=en;
					if(strcmp(v->type,"BOOLEAN")==0)
						v->size=en-st+1;
					else if(strcmp(v->type,"INTEGER")==0)
						v->size=(en-st+1)*2;
					else v->size=(en-st+1)*4;
				}
				else{
					v->is_array=0;
					v->s_range=-1;
					v->e_range=-1;
					if(strcmp(v->type,"BOOLEAN")==0)
						v->size=1;
					else if(strcmp(v->type,"INTEGER")==0)
						v->size=2;
					else v->size=4;
				}
				symbol_table[h].scope.in_num++;
				v->m=m;
				m+=v->size;
				add_variable(h,n+1,o,v);
				root->hash_value=h;
				root->nesting=n+1;
				root->offset=o;
				
				symbol_table[h].scope.in_list=distinct_queue_params(symbol_table[h].scope.in_list,v);
				fflush(stdout);
			}
			else if(strcmp(root->parentNodeSymbol,"<output_plist>")==0 ||
			strcmp(root->parentNodeSymbol,"<output_plist_ex>")==0)
			{
				printf("7 ");
				fflush(stdout);
				printf("%d %d %d\n",h,nesting,o);
				VAR v=(VAR)malloc(sizeof(var));
				v->is_array=0;
				v->s_range=-1;
				v->e_range=-1;
				sprintf(v->var_name,"%s",root->lexemeCurrentNode);
				printf("Declared of type %s.\n", root->sibling->sibling->child->token);
				sprintf(v->type,"%s",root->sibling->sibling->child->token);
				if(strcmp(v->type,"BOOLEAN")==0)
					v->size=1;
				else if(strcmp(v->type,"INTEGER")==0)
					v->size=2;
				else v->size=4;	
				v->m=m;
				symbol_table[h].scope.out_num++;
				add_variable(h,n+1,o,v);
				root->hash_value=h;
				root->nesting=n+1;
				root->offset=o;
				m+=v->size;
				symbol_table[h].scope.out_list=distinct_queue_params(symbol_table[h].scope.out_list,v);
				fflush(stdout);
			}
		}
		if(d)
		{
			constructSymbolTable(root->child,out_fp,h,n,o);
			constructSymbolTable(root->sibling,out_fp,h,n,o);
		}
		fflush(out_fp);
	}
}