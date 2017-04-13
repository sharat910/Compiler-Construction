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
}var;

typedef var* VAR;
typedef struct
{
	VAR variables[1009];
}hash_table;

typedef struct
{
	VAR front;
	int no_of_params;
}list_params;


typedef struct
{
	int para_num;
	list_params	 para_list;
	char type[10];
	hash_table func_table[100][100];
}func_scope;

typedef struct
{
	char func_name[50];
	func_scope scope;
}func_entry;


#endif