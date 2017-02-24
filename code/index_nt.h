#ifndef _index_nt
#define _index_nt
typedef struct {
	char incoming[30];
	int index;
}entry_map_nt;

int get_index_nt(char * a);
void init_map_nt();
#endif