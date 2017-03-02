#ifndef _lexerDef
#define _lexerDef
typedef struct {
	char incoming[30];
	int index;
}entry_map_nt;

int get_index_nt(char * a);

typedef struct {
	char incoming[20];
	int index;
}entry_map_t;

int get_index_t(char * a);

typedef struct {
	char incoming[20];
	char token[20];
}entry;

char * find(char * a);

#endif
