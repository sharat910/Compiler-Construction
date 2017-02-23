// Rishabh Garg
// 2014A7PS065P

#include"stackdef.h"
#include <stdlib.h>
#include <stdio.h>
// #include"element.h"
// #include"boolean.h"

// typedef struct
// {
// 	char str[50];
// }element;

NODE createNode(char * a)
{
	NODE temp;
	temp=(NODE) malloc(sizeof(struct node));
	if(temp!=NULL)
	{
		sprintf(temp->str,a);
		temp->link=NULL;
	}
	else
	{
		printf("ERROR: Insufficient Memory...\n");
		exit(0);
	}
return temp;

}

stack initializeStack(void)
{
	stack st;
	st.top=NULL;
	st.stack_size=0;
	return st;
}

stack push(stack st, char * a)
{
	if(st.top==NULL)
		st.top=createNode(a);
	else
	{
		NODE p=createNode(a);
		p->link=st.top;   
		st.top=p;
	}
	st.stack_size++;
	return st;
}


stack pop(stack st)
{
	NODE p=st.top;
	st.top=p->link;
	st.stack_size--;
	free(p);
	return st;
}



int isEmptyStack(stack st)
{
	if(st.top==NULL)
		return 1;
	else return 0;
}

void printStack(stack st)
{
	printf("TOP :");
	NODE p;
	p = st.top;
	while(p!=NULL)
	{
		printf(" %s -->", p->a);
		p = p->link;
	}
	printf("\n");
}
