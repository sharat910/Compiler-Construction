#include "stack_ptr.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include"element.h"
// #include"boolean.h"

// typedef struct
// {
// 	char str[50];
// }element;

ptr_map createNodeTree(TREE_NODE_PTR current)
{
	ptr_map temp;
	temp=(ptr_map) malloc(sizeof(ptr_map));
	if(temp!=NULL)
	{
		temp->node_info=current;
		temp->link=NULL;
		temp->node_info->child=NULL;
		temp->node_info->sibling=NULL;
		temp->node_info->parent=NULL;
	}
	else
	{
		printf("ERROR: Insufficient Memory...\n");
		exit(0);
	}
return temp;

}

ptr_stack initialize_ptr_stack(void)
{
	ptr_stack st;
	st.top=NULL;
	st.stack_size=0;
	return st;
}

ptr_stack push_ptr_stack(ptr_stack st, TREE_NODE_PTR curr)
{
	if(st.top==NULL)
		st.top=createNodeTree(curr);
	else
	{
		ptr_map p=createNodeTree(curr);
		p->link=st.top;   
		st.top=p;
	}
	st.stack_size++;
	return st;
}


void pop_ptr_stack(ptr_stack* st)
{
	if(!isEmpty_ptr_stack(*st))
	{
		// printStack(*st);
		ptr_map p=st->top;
		if(st->stack_size==1)
			st->top=NULL;
		else	
		st->top=p->link;
		st->stack_size--;
		free(p);
		// printf("here\n");
		// printStack(*st);
	}
}



int isEmpty_ptr_stack(ptr_stack st)
{
	if(st.top==NULL)
		return 1;
	else return 0;
}

void print_ptr_stack(ptr_stack st)
 {
	// printf("TOP :");
 	ptr_map p;
 	p = st.top;
 	while(p!=NULL)
 	{
		printf("%s --> ", p->node_info->NodeSymbol);
 		p = p->link;
 	}
	printf("\n");
 }