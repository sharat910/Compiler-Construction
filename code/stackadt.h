// Rishabh Garg
// 2014A7PS065P
#ifndef _stackadt
#define _stackadt


struct node 
{
	char str[50];
	struct node *link;
};

typedef struct node *NODE;
typedef struct 
{
	NODE top;
	int stack_size;
} stack;
extern stack initializeStack(void);
extern stack push(stack st, char * a);
extern stack pop(stack st);
extern int isEmptyStack(stack st);
extern void printStack(stack st);

#endif

