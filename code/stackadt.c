// Rishabh Garg
// 2014A7PS065P

#include "stackadt.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
		sprintf(temp->str,"%s",a);
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

stack distinct_push(stack st,char * a)
{
	NODE p;
	p = st.top;
	while(p!=NULL)
	{
		if(strcmp(p->str,a)==0)
			return st;
		p = p->link;
	}
	st=push(st,a);
	return st;
}
stack merge(stack one, stack two)
{
	NODE p;
	p = one.top;
	while(p!=NULL)
	{
		two=distinct_push(two,p->str);
		p = p->link;
	}
	return two;
}

stack merge_without_e(stack one, stack two)
{
	NODE p;
	p = two.top;
	while(p!=NULL)
	{
		if (strcmp(p->str,"e")==0){
			p=p->link;
			continue;
		}
		one=distinct_push(one,p->str);
		p = p->link;
	}
	return one;
}

void printStack(stack st)
 {
	// printf("TOP :");
 	NODE p;
 	p = st.top;
 	while(p!=NULL)
 	{
		printf(" %s -->", p->str);
 		p = p->link;
 	}
	printf("\n");
 }
int find_stack(stack* a, char * str)
{
	NODE p;
	p = (*a).top;
	while(p!=NULL)
	{
		if(strcmp(p->str,str)==0)
			return 1;
		p = p->link;
	}
	return 0;
}

NODE get_element(stack*a ,char *str)
{
	NODE p;
	p = (*a).top;
	while(p!=NULL)
	{
		if(strcmp(p->str,str)==0)
			return p;
		p = p->link;
	}
	return NULL;
}
