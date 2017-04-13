// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)


#include "symbol_table.h"

func_entry symbol_table[101];

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
	VAR p;
	p = st.front;
	VAR* prev=NULL;
	while(p!=NULL)
	{	
		prev=&p;
		if(strcmp(p->var_name,v->var_name)==0)
		{
			printf("Redeclaration in the same scope\n");
		}
		p = p->next;
	}
	VAR end=*prev;
	if(prev==NULL){
		st.front=v;
		st.no_of_params++;
	}
	else
	{
		end->next=v;
		st.no_of_params++;
	}
	
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
void add_variable(hash_table** h,int nesting,int offset,VAR v)
{
	int num=get_hash_value(v->var_name);
	int n=num;
	int i=1;
	while(1)
	{
		if(h[nesting][offset].variables[n]==NULL)
		{
			h[nesting][offset].variables[n]=v;
			break;
		}
		n=(n+i)%1009;
		i++;
	}
}

void create_func_entry(char* a)
{
	printf("HI%d\n",get_func_hash_value(a) );
	func_entry* f=&symbol_table[get_func_hash_value(a)];
	sprintf(f->func_name,"%s",a);
}


void create_func_scope(int pnum,char* ret_type,list_params l,char* name)
{
	func_entry* f=&symbol_table[get_func_hash_value(name)];
	f->scope.para_num=pnum;
	sprintf(f->scope.type,"%s",ret_type);
	f->scope.para_list=l;
	for(int i=0;i<100;i++)
		for(int j=0;j<100;j++)
			for(int k=0;k<1009;k++)
				f->scope.func_table[i][j].variables[k]=(VAR)malloc(sizeof(var));
}


