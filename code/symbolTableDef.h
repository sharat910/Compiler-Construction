// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _symbol_table_def
#define _symbol_table_def

typedef struct v
{
	char var_name[20];
	int line_no;
	char type[10];
	struct v* next;
	int is_array;
	int s_range;
	int e_range;
	int dec;
	int start;
	int end;
	char func_name[100];
}var;

typedef var* VAR;
typedef struct
{	int parent;
	int exist;
	VAR variables[1009];
}hash_table;

typedef struct
{
	VAR front;
	int no_of_params;
}list_params;


typedef struct
{
	int in_num;
	list_params	in_list;
	list_params	out_list;

	int out_num;
	char type[10];
	hash_table func_table[100][100];
}func_scope;

typedef struct
{
	int exist;
	
	char func_name[50];
	func_scope scope;
}func_entry;


#endif