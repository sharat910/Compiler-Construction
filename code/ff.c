#include "ff.h"
#include <stdio.h>
#include "index_nt.h"

rule firsts[57];
rule follows[57];
int isTerminal(stack s)
{
	if(s.top->str[0]=='<')
		return 0;
	else return 1;	
}

void fill_lhs()
{
	sprintf(firsts[0].lhs,"<AOBE>");
	sprintf(firsts[1].lhs,"<output_plist>");
	sprintf(firsts[2].lhs,"<idList>");
	sprintf(firsts[3].lhs,"<statement>");
	sprintf(firsts[4].lhs,"<whichStmt>");
	sprintf(firsts[5].lhs,"<WithLogOp>");
	sprintf(firsts[6].lhs,"<moduleReuseStmt>");
	sprintf(firsts[7].lhs,"<idList_ex>");
	sprintf(firsts[8].lhs,"<declareStmt>");
	sprintf(firsts[9].lhs,"<MultiCase>");
	sprintf(firsts[10].lhs,"<simpleStmt>");
	sprintf(firsts[11].lhs,"<expression>");
	sprintf(firsts[12].lhs,"<term>");
	sprintf(firsts[13].lhs,"<index>");
	sprintf(firsts[14].lhs,"<module>");
	sprintf(firsts[15].lhs,"<lvalueARRStmt>");
	sprintf(firsts[16].lhs,"<negOrPosAE>");
	sprintf(firsts[17].lhs,"<dataType>");
	sprintf(firsts[18].lhs,"<input_plist>");
	sprintf(firsts[19].lhs,"<var>");
	sprintf(firsts[20].lhs,"<op2>");
	sprintf(firsts[21].lhs,"<N4>");
	sprintf(firsts[22].lhs,"<output_plist_ex>");
	sprintf(firsts[23].lhs,"<driverModule>");
	sprintf(firsts[24].lhs,"<program>");
	sprintf(firsts[25].lhs,"<iterativeStmt>");
	sprintf(firsts[26].lhs,"<caseStmts>");
	sprintf(firsts[27].lhs,"<logicalOp>");
	sprintf(firsts[28].lhs,"<whichId>");
	sprintf(firsts[29].lhs,"<ioStmt>");
	sprintf(firsts[30].lhs,"<input_plist_ex>");
	sprintf(firsts[31].lhs,"<ret>");
	sprintf(firsts[32].lhs,"<WithRelOp>");
	sprintf(firsts[33].lhs,"<condionalStmt>");
	sprintf(firsts[34].lhs,"<optional>");
	sprintf(firsts[35].lhs,"<op1>");
	sprintf(firsts[36].lhs,"<range>");
	sprintf(firsts[37].lhs,"<relationalOp>");
	sprintf(firsts[38].lhs,"<BorNBAE>");
	sprintf(firsts[39].lhs,"<factor>");
	sprintf(firsts[40].lhs,"<value>");
	sprintf(firsts[41].lhs,"<moduleDeclarations>");
	sprintf(firsts[42].lhs,"<otherModules>");
	sprintf(firsts[43].lhs,"<type>");
	sprintf(firsts[44].lhs,"<moduleDeclaration>");
	sprintf(firsts[45].lhs,"<moduleDef>");
	sprintf(firsts[46].lhs,"<default>");
	sprintf(firsts[47].lhs,"<N5>");
	sprintf(firsts[48].lhs,"<assignmentStmt>");
	sprintf(firsts[49].lhs,"<lvalueIDStmt>");
	sprintf(firsts[50].lhs,"<statements>");
	sprintf(firsts[51].lhs,"<arithmeticExpr>");
	sprintf(firsts[52].lhs,"<AnyTerm>");
}
void fill_firsts(rule rules[100])
{
	fill_lhs();
	for(int i=0;i<97;i++)
	{
		// if(isTerminal((*(r+i*sizeof(rule))).rhs))
		// {
		// 	stack curr=firsts[get_index_nt((*(r+i*sizeof(rule))).lhs)].rhs;
		// 	curr=distinct_push(curr,((*(r+i*sizeof(rule))).rhs.top)->str);
		// }
		if(isTerminal(rules[i].rhs))
		{
			stack a=firsts[get_index_nt(rules[i].lhs)].rhs;
			a=distinct_push(a,rules[i].rhs.top->str);
		}
	}
}