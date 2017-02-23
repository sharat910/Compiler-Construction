#ifndef _index_t
#define _index_t
typedef struct {
	char incoming[20];
	int index;
}entry_map_t;

int get_index_t(char * a);
void init_map_t();
#endif