#ifndef _map
#define _map
typedef struct {
	char incoming[20];
	char token[20];
}entry;

char * find(char * a);
void init();
#endif