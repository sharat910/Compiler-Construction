#include "map.h"
#include <stdio.h>
#include <string.h>
entry lookup_table[40];
char * find(char * a)
{
	for(int i=0;i<40;i++)
	{
		if(!strcmp(lookup_table[i].incoming,a)){

			return lookup_table[i].token;
		}
	}

	return "ID";
}
void init()
{
	sprintf(lookup_table[0].incoming,"integer");
	sprintf(lookup_table[0].token,"INTEGER");
	sprintf(lookup_table[1].incoming,"real");
	sprintf(lookup_table[1].token,"REAL");
	sprintf(lookup_table[2].incoming,"boolean");
	sprintf(lookup_table[2].token,"BOOLEAN");
	sprintf(lookup_table[3].incoming,"of");
	sprintf(lookup_table[3].token,"OF");
	sprintf(lookup_table[4].incoming,"array");
	sprintf(lookup_table[4].token,"ARRAY");
	sprintf(lookup_table[5].incoming,"start");
	sprintf(lookup_table[5].token,"START");
	sprintf(lookup_table[6].incoming,"end");
	sprintf(lookup_table[6].token,"END");
	sprintf(lookup_table[7].incoming,"declare");
	sprintf(lookup_table[7].token,"DECLARE");
	sprintf(lookup_table[8].incoming,"module");
	sprintf(lookup_table[8].token,"MODULE");
	sprintf(lookup_table[9].incoming,"driver");
	sprintf(lookup_table[9].token,"DRIVER");
	sprintf(lookup_table[10].incoming,"program");
	sprintf(lookup_table[10].token,"PROGRAM");
	sprintf(lookup_table[11].incoming,"get_value");
	sprintf(lookup_table[11].token,"GET_VALUE");
	sprintf(lookup_table[12].incoming,"print");
	sprintf(lookup_table[12].token,"PRINT");
	sprintf(lookup_table[13].incoming,"use");
	sprintf(lookup_table[13].token,"USE");
	sprintf(lookup_table[14].incoming,"with");
	sprintf(lookup_table[14].token,"WITH");
	sprintf(lookup_table[15].incoming,"parameters");
	sprintf(lookup_table[15].token,"PARAMETERS");
	sprintf(lookup_table[16].incoming,"true");
	sprintf(lookup_table[16].token,"TRUE");
	sprintf(lookup_table[17].incoming,"false");
	sprintf(lookup_table[17].token,"FALSE");
	sprintf(lookup_table[18].incoming,"takes");
	sprintf(lookup_table[18].token,"TAKES");
	sprintf(lookup_table[19].incoming,"input");
	sprintf(lookup_table[19].token,"INPUT");
	sprintf(lookup_table[20].incoming,"returns");
	sprintf(lookup_table[20].token,"RETURNS");
	sprintf(lookup_table[21].incoming,"AND");
	sprintf(lookup_table[21].token,"AND");
	sprintf(lookup_table[22].incoming,"OR");
	sprintf(lookup_table[22].token,"OR");
	sprintf(lookup_table[23].incoming,"for");
	sprintf(lookup_table[23].token,"FOR");
	sprintf(lookup_table[24].incoming,"in");
	sprintf(lookup_table[24].token,"IN");
	sprintf(lookup_table[25].incoming,"switch");
	sprintf(lookup_table[25].token,"SWITCH");
	sprintf(lookup_table[26].incoming,"case");
	sprintf(lookup_table[26].token,"CASE");
	sprintf(lookup_table[27].incoming,"break");
	sprintf(lookup_table[27].token,"BREAK");
	sprintf(lookup_table[28].incoming,"default");
	sprintf(lookup_table[28].token,"DEFAULT");
	sprintf(lookup_table[29].incoming,"while");
	sprintf(lookup_table[29].token,"WHILE");
}
// int main()
// {
	
// 	init();
// 	char s[30];
// 	printf("Enter\n");
// 	scanf("%s",s);
// 	printf("%s",find(s));
// }