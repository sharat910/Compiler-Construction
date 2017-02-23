#include "index_t.h"
#include <stdio.h>
#include <string.h>
entry_map_t map_t[57];
int get_index_t(char * a)
{
	for(int i=0;i<57;i++)
	{
		if(!strcmp(map_t[i].incoming,a)){

			return map_t[i].index;
		}
	}
	return -1;
}

void init_map_t()
{
	sprintf(map_t[0].incoming,"INTEGER");
	map_t[0].index=0;
	sprintf(map_t[1].incoming,"REAL");
	map_t[1].index=1;
	sprintf(map_t[2].incoming,"BOOLEAN");
	map_t[2].index=2;
	sprintf(map_t[3].incoming,"OF");
	map_t[3].index=3;
	sprintf(map_t[4].incoming,"ARRAY");
	map_t[4].index=4;
	sprintf(map_t[5].incoming,"START");
	map_t[5].index=5;
	sprintf(map_t[6].incoming,"END");
	map_t[6].index=6;
	sprintf(map_t[7].incoming,"DECLARE");
	map_t[7].index=7;
	sprintf(map_t[8].incoming,"MODULE");
	map_t[8].index=8;
	sprintf(map_t[9].incoming,"DRIVER");
	map_t[9].index=9;
	sprintf(map_t[10].incoming,"PROGRAM");
	map_t[10].index=10;
	sprintf(map_t[11].incoming,"GET_VALUE");
	map_t[11].index=11;
	sprintf(map_t[12].incoming,"PRINT");
	map_t[12].index=12;
	sprintf(map_t[13].incoming,"USE");
	map_t[13].index=13;
	sprintf(map_t[14].incoming,"WITH");
	map_t[14].index=14;
	sprintf(map_t[15].incoming,"PARAMETERS");
	map_t[15].index=15;
	sprintf(map_t[16].incoming,"TRUE");
	map_t[16].index=16;
	sprintf(map_t[17].incoming,"FALSE");
	map_t[17].index=17;
	sprintf(map_t[18].incoming,"TAKES");
	map_t[18].index=18;
	sprintf(map_t[19].incoming,"INPUT");
	map_t[19].index=19;
	sprintf(map_t[20].incoming,"RETURNS");
	map_t[20].index=20;
	sprintf(map_t[21].incoming,"AND");
	map_t[21].index=21;
	sprintf(map_t[22].incoming,"OR");
	map_t[22].index=22;
	sprintf(map_t[23].incoming,"FOR");
	map_t[23].index=23;
	sprintf(map_t[24].incoming,"IN");
	map_t[24].index=24;
	sprintf(map_t[25].incoming,"SWITCH");
	map_t[25].index=25;
	sprintf(map_t[26].incoming,"CASE");
	map_t[26].index=26;
	sprintf(map_t[27].incoming,"BREAK");
	map_t[27].index=27;
	sprintf(map_t[28].incoming,"DEFAULT");
	map_t[28].index=28;
	sprintf(map_t[29].incoming,"WHILE");
	map_t[29].index=29;
	sprintf(map_t[30].incoming,"PLUS");
	map_t[30].index=30;
	sprintf(map_t[31].incoming,"MINUS");
	map_t[31].index=31;
	sprintf(map_t[32].incoming,"MUL");
	map_t[32].index=32;
	sprintf(map_t[33].incoming,"DIV");
	map_t[33].index=33;
	sprintf(map_t[34].incoming,"LT");
	map_t[34].index=34;
	sprintf(map_t[35].incoming,"LE");
	map_t[35].index=35;
	sprintf(map_t[36].incoming,"GE");
	map_t[36].index=36;
	sprintf(map_t[37].incoming,"GT");
	map_t[37].index=37;
	sprintf(map_t[38].incoming,"EQ");
	map_t[38].index=38;
	sprintf(map_t[39].incoming,"NE");
	map_t[39].index=39;
	sprintf(map_t[40].incoming,"DEF");
	map_t[40].index=40;
	sprintf(map_t[41].incoming,"ENDDEF");
	map_t[41].index=41;
	sprintf(map_t[42].incoming,"COLON");
	map_t[42].index=42;
	sprintf(map_t[43].incoming,"RANGEOP");
	map_t[43].index=43;
	sprintf(map_t[44].incoming,"SEMICOL");
	map_t[44].index=44;
	sprintf(map_t[45].incoming,"COMMA");
	map_t[45].index=45;
	sprintf(map_t[46].incoming,"ASSIGNOP");
	map_t[46].index=46;
	sprintf(map_t[47].incoming,"SQBO");
	map_t[47].index=47;
	sprintf(map_t[48].incoming,"SQBC");
	map_t[48].index=48;
	sprintf(map_t[49].incoming,"BO");
	map_t[49].index=49;
	sprintf(map_t[50].incoming,"BC");
	map_t[50].index=50;
	sprintf(map_t[51].incoming,"COMMENTMARK");
	map_t[51].index=51;
	sprintf(map_t[52].incoming,"RNUM");
	map_t[52].index=52;
	sprintf(map_t[53].incoming,"NUM");
	map_t[53].index=53;
	sprintf(map_t[54].incoming,"ID");
	map_t[54].index=54;
	sprintf(map_t[55].incoming,"DRIVERDEF");
	map_t[55].index=55;
	sprintf(map_t[56].incoming,"DRIVERENDDEF");
	map_t[56].index=56;

}