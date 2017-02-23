// Rishabh Garg
// 2014A7PS065P

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
extern stack push(stack st, element e);
extern stack pop(stack st);
extern boolean isEmptyStack(stack st);
extern void printStack(stack st);


