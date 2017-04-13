// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _symbol_table
#define _symbol_table
#include "symbolTableDef.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern func_entry symbol_table[101];

extern VAR create_param_entry(char* name,int line,char* type);
extern list_params initialize_queue_params(void);
extern int isEmpty_queue_params(list_params st);
extern list_params distinct_queue_params(list_params st,VAR v);

extern void print_queue_params(list_params st);

extern void add_variable(hash_table** h,int nesting,int offset,VAR v);
extern void create_func_entry(char* a);
extern void create_func_scope(int pnum,char* ret_type,list_params l,char* name);
extern int get_hash_value(char* a);
extern int get_func_hash_value(char* a);

#endif