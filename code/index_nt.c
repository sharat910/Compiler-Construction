#include "index_nt.h"
#include <stdio.h>
#include <string.h>
entry_map_nt map_nt[53];
int get_index_nt(char * a)
{
	// printf("in map%s\n",a );
	for(int i=0;i<53;i++)
	{
		if(!strcmp(map_nt[i].incoming,a)){

			return map_nt[i].index;
		}
	}
	return -1;
}
void init_map_nt()
{
	sprintf(map_nt[0].incoming,"<AOBE>");
	map_nt[0].index=0;
	sprintf(map_nt[1].incoming,"<output_plist>");
	map_nt[1].index=1;
	sprintf(map_nt[2].incoming,"<idList>");
	map_nt[2].index=2;
	sprintf(map_nt[3].incoming,"<statement>");
	map_nt[3].index=3;
	sprintf(map_nt[4].incoming,"<whichStmt>");
	map_nt[4].index=4;
	sprintf(map_nt[5].incoming,"<WithLogOp>");
	map_nt[5].index=5;
	sprintf(map_nt[6].incoming,"<moduleReuseStmt>");
	map_nt[6].index=6;
	sprintf(map_nt[7].incoming,"<idList_ex>");
	map_nt[7].index=7;
	sprintf(map_nt[8].incoming,"<declareStmt>");
	map_nt[8].index=8;
	sprintf(map_nt[9].incoming,"<MultiCase>");
	map_nt[9].index=9;
	sprintf(map_nt[10].incoming,"<simpleStmt>");
	map_nt[10].index=10;
	sprintf(map_nt[11].incoming,"<expression>");
	map_nt[11].index=11;
	sprintf(map_nt[12].incoming,"<term>");
	map_nt[12].index=12;
	sprintf(map_nt[13].incoming,"<index>");
	map_nt[13].index=13;
	sprintf(map_nt[14].incoming,"<module>");
	map_nt[14].index=14;
	sprintf(map_nt[15].incoming,"<lvalueARRStmt>");
	map_nt[15].index=15;
	sprintf(map_nt[16].incoming,"<negOrPosAE>");
	map_nt[16].index=16;
	sprintf(map_nt[17].incoming,"<dataType>");
	map_nt[17].index=17;
	sprintf(map_nt[18].incoming,"<input_plist>");
	map_nt[18].index=18;
	sprintf(map_nt[19].incoming,"<var>");
	map_nt[19].index=19;
	sprintf(map_nt[20].incoming,"<op2>");
	map_nt[20].index=20;
	sprintf(map_nt[21].incoming,"<N4>");
	map_nt[21].index=21;
	sprintf(map_nt[22].incoming,"<output_plist_ex>");
	map_nt[22].index=22;
	sprintf(map_nt[23].incoming,"<driverModule>");
	map_nt[23].index=23;
	sprintf(map_nt[24].incoming,"<program>");
	map_nt[24].index=24;
	sprintf(map_nt[25].incoming,"<iterativeStmt>");
	map_nt[25].index=25;
	sprintf(map_nt[26].incoming,"<caseStmts>");
	map_nt[26].index=26;
	sprintf(map_nt[27].incoming,"<logicalOp>");
	map_nt[27].index=27;
	sprintf(map_nt[28].incoming,"<whichId>");
	map_nt[28].index=28;
	sprintf(map_nt[29].incoming,"<ioStmt>");
	map_nt[29].index=29;
	sprintf(map_nt[30].incoming,"<input_plist_ex>");
	map_nt[30].index=30;
	sprintf(map_nt[31].incoming,"<ret>");
	map_nt[31].index=31;
	sprintf(map_nt[32].incoming,"<WithRelOp>");
	map_nt[32].index=32;
	sprintf(map_nt[33].incoming,"<condionalStmt>");
	map_nt[33].index=33;
	sprintf(map_nt[34].incoming,"<optional>");
	map_nt[34].index=34;
	sprintf(map_nt[35].incoming,"<op1>");
	map_nt[35].index=35;
	sprintf(map_nt[36].incoming,"<range>");
	map_nt[36].index=36;
	sprintf(map_nt[37].incoming,"<relationalOp>");
	map_nt[37].index=37;
	sprintf(map_nt[38].incoming,"<BorNBAE>");
	map_nt[38].index=38;
	sprintf(map_nt[39].incoming,"<factor>");
	map_nt[39].index=39;
	sprintf(map_nt[40].incoming,"<value>");
	map_nt[40].index=40;
	sprintf(map_nt[41].incoming,"<moduleDeclarations>");
	map_nt[41].index=41;
	sprintf(map_nt[42].incoming,"<otherModules>");
	map_nt[42].index=42;
	sprintf(map_nt[43].incoming,"<type>");
	map_nt[43].index=43;
	sprintf(map_nt[44].incoming,"<moduleDeclaration>");
	map_nt[44].index=44;
	sprintf(map_nt[45].incoming,"<moduleDef>");
	map_nt[45].index=45;
	sprintf(map_nt[46].incoming,"<default>");
	map_nt[46].index=46;
	sprintf(map_nt[47].incoming,"<N5>");
	map_nt[47].index=47;
	sprintf(map_nt[48].incoming,"<assignmentStmt>");
	map_nt[48].index=48;
	sprintf(map_nt[49].incoming,"<lvalueIDStmt>");
	map_nt[49].index=49;
	sprintf(map_nt[50].incoming,"<statements>");
	map_nt[50].index=50;
	sprintf(map_nt[51].incoming,"<arithmeticExpr>");
	map_nt[51].index=51;
	sprintf(map_nt[52].incoming,"<AnyTerm>");
	map_nt[52].index=52;
	
}
