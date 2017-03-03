// Group 56
// Rishabh Garg (2014A7PS065P)
// M Sharat Chandra (2014A7PS108P)

#ifndef _stack_ptr
#define _stack_ptr

#include "parseTree.h"

struct ptr 
{
	TREE_NODE_PTR node_info;
	struct ptr *link;
};

typedef struct ptr* ptr_map;
typedef struct ptr ptr;
typedef struct 
{
	ptr_map top;
	int stack_size;
} ptr_stack;

extern ptr_stack initialize_ptr_stack(void);
extern ptr_stack push_ptr_stack(ptr_stack st, TREE_NODE_PTR curr);
extern void pop_ptr_stack(ptr_stack* st);
extern int isEmpty_ptr_stack(ptr_stack st);
extern void print_ptr_stack(ptr_stack st);

#endif