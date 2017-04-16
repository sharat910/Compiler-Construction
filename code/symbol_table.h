// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _symbol_table
#define _symbol_table


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbolTableDef.h"
#include "parseTree.h"

extern func_entry symbol_table[101];

extern VAR create_param_entry(char* name,int line,char* type);
extern list_params initialize_queue_params(void);
extern int isEmpty_queue_params(list_params st);
extern list_params distinct_queue_params(list_params st,VAR v);

extern void print_queue_params(list_params st);

extern void add_variable(int hash,int nesting,int offset,VAR v);
extern void create_func_entry(char* a);
extern void create_func_scope(int innum,int outnum,char* name);
extern int get_hash_value(char* a);
extern int get_func_hash_value(char* a);
extern int find_var(char* a,int hash,int nesting,int offset);
extern int find_param(list_params st,char* a);
extern int complete_find(char* a,int h,int n,int o);
extern void constructSymbolTable(TREE_NODE_PTR root,FILE* out_fp,int hash_value,int nesting,int offset);
extern VAR return_var(char* a,int hash,int nesting,int offset);
extern VAR get_symbol_table_var_entry(TREE_NODE_PTR ptr);
#endif