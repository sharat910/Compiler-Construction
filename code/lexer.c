#include "lexer.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
extern int line;
extern int column;
extern char last;
extern FILE* fp;
char buffer[200];
int buffer_pointer=0;
int buffer_size=0;
entry lookup_table[40];
entry_map_nt map_nt[57];
entry_map_t map_t[59];
int get_index_t(char * a)
{
	for(int i=0;i<59;i++)
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
	sprintf(map_t[57].incoming,"e");
	map_t[57].index=57;
	sprintf(map_t[58].incoming,"$");
	map_t[58].index=58;

}
int get_index_nt(char * a)
{
	// printf("in map%s\n",a );
	for(int i=0;i<56;i++)
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
	sprintf(map_nt[53].incoming,"<all_ops>");
	map_nt[53].index=53;	
	sprintf(map_nt[54].incoming,"<alpha>");
	map_nt[54].index=54;
	sprintf(map_nt[55].incoming,"<AnyTerm2>");
	map_nt[55].index=55;	
	sprintf(map_nt[56].incoming,"$");
	map_nt[56].index=56;	
}
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
char* resolve(char* a)
{
	return find(a);
}

char custom_fgetc(){
	if (buffer_pointer<buffer_size)
	{
		return buffer[buffer_pointer++];
	}
	else
	{
		//printf("Reached EOF in custom_fgetc\n");
		return '\0';
	}
	
}


FILE* getStream(FILE* fp)
{
	if (fgets(buffer, 200,fp) != NULL)
	{
		buffer_pointer = 0;
		buffer_size = strlen(buffer)+1;
		return fp;
	}
	else
		return NULL;
}

void removeComments(char *testcaseFile, char *cleanFile)
{
	FILE* fp1 = fopen(testcaseFile,"r");
	FILE* fp2 = fopen(cleanFile,"w");
	while(!feof(fp1))
	{

		char ch = fgetc(fp1);
		// printf("%c",ch );
		if (ch == '*')
		{
			char lookahead = fgetc(fp1);
			if (lookahead == '*')
			{
				while(1)
				{
					while(fgetc(fp1) != '*' && !feof(fp1));
					if (feof(fp1))
						break;
					char lookahead2 = fgetc(fp1);
					if (lookahead2 == '*')
						break;
				}
			}
			else
			{
				fputc(ch,fp2);
				fputc(lookahead,fp2);				
			}
		}
		else{
			fflush(fp2);
			if(!feof(fp1))
				fputc(ch,fp2);
		}
	}
	fflush(fp2);
}


tokenInfo getNextToken()
{
	char ch;
	tokenInfo curr;

	if (buffer_pointer == buffer_size || last=='\n' || last=='\r')
	{
		// if(last=='$')
		// {			
		// 	sprintf(curr.token,"%s","$");
		// 	return curr;
		// }
		fp = getStream(fp);
		// printf("\n%s\n",buffer);		
		if (fp == NULL)
		{			
			sprintf(curr.token,"%s","$");
			curr.line=line;
			sprintf(curr.lexeme,"%s","----");
			return curr;
		}
		line++;
		column=1;
		last = custom_fgetc();
	}

	while(buffer_pointer < buffer_size)
	{
		// printf("Input:_%c_%d %d\n",last,buffer_pointer,buffer_size);
		char str[20];
		if(last==' ' || last=='\n' || last=='\t' || last=='\r'){
			
			if(last==' ')
				column++;
			if(last=='\t')
				column+=1;
			last=custom_fgetc();
			if (buffer_pointer == buffer_size)
			{
				fp = getStream(fp);
				// printf("\n%s\n",buffer);
				if (fp == NULL)
				{			
					sprintf(curr.token,"%s","$");
					curr.line=line;
					sprintf(curr.lexeme,"%s","----");
					return curr;
				}
				line++;
				column=1;
				last = custom_fgetc();
			}
			continue;
		}
		int i=0;
		if(last=='<')
		{
			// printf("hey\n");
			ch=custom_fgetc();
			column++;
			if(ch=='='){
				sprintf(curr.token,"%s","LE");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s","<=");
				last=custom_fgetc();
				column++;
				return curr;
			}
			else if(ch=='<')
			{
				// printf("yo%c\n",ch );
				last=custom_fgetc();
				column++;
				if(last=='<')
				{
					sprintf(curr.token,"%s","DRIVERDEF");
					curr.line=line;
					curr.column=column;
					sprintf(curr.lexeme,"%s","<<<");
					last=custom_fgetc();
					column++;
					return curr;
				}
				else {
					sprintf(curr.token,"%s","DEF");
					curr.line=line;
					curr.column=column;
					sprintf(curr.lexeme,"%s","<<");
					return curr;
				}
			}
			else {
				sprintf(curr.token,"%s","LT");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s","<");
				last=ch;
				return curr;
			}
		}
		else if(last=='>')
		{
			ch=custom_fgetc();
			column++;
			if(ch=='='){
				sprintf(curr.token,"%s","GE");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s",">=");
				last=custom_fgetc();
				column++;
				return curr;
			}
			else if(ch=='>')
			{
				last=custom_fgetc();
				column++;
				if(last=='>')
				{
					sprintf(curr.token,"%s","DRIVERENDDEF");
					curr.line=line;
					curr.column=column;
					sprintf(curr.lexeme,"%s",">>>");
					last=custom_fgetc();
					column++;
					return curr;
				}
				else {
					sprintf(curr.token,"%s","ENDDEF");
					curr.line=line;
					curr.column=column;
					sprintf(curr.lexeme,"%s",">>");
					return curr;
				}
			}
			else {
				sprintf(curr.token,"%s","GT");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s",">");
				last=ch;
				return curr;	
			}
		}
		else if(last=='=')
		{
			ch=custom_fgetc();
			column++;
			if(ch=='=')
			{
				sprintf(curr.token,"%s","EQ");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s","==");
				last=custom_fgetc();
				column++;	
				return curr;
			}
			else
			{
				printf("Unknown pattern %c%c in line no. %d\n",last,ch,line );
				last=custom_fgetc();
				continue;
			}
		}
		else if(last=='!')
		{
			ch=custom_fgetc();
			column++;
			if(ch=='=')
			{
				sprintf(curr.token,"%s","NE");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s","!=");
				last=custom_fgetc();
				column++;
				return curr;
			}
			else
			{
				printf("Unknown pattern %c%c in line no. %d\n",last,ch,line );
				last=custom_fgetc();
				continue;
			}
			// else errorfunc;
		}
		else if(last==':')
		{
			ch=custom_fgetc();
			column++;
			if(ch=='=')
			{
				sprintf(curr.token,"%s","ASSIGNOP");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s",":=");
				last=custom_fgetc();
				column++;
				return curr;
				
			}
			else {
				sprintf(curr.token,"%s","COLON");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s",":");
				last=ch;
				return curr;
			}
		}
		else if(last==',')
		{
			sprintf(curr.token,"%s","COMMA");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s",",");
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last=='[')
		{
			sprintf(curr.token,"%s","SQBO");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s","[");
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last==']')
		{
				sprintf(curr.token,"%s","SQBC");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s","]");
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last=='(')
		{
			sprintf(curr.token,"%s","BO");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s","(");
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last==')')
		{
				sprintf(curr.token,"%s","BC");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s",")");
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last==';')
		{
				sprintf(curr.token,"%s","SEMICOL");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s",";");
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last=='+')
		{
				sprintf(curr.token,"%s","PLUS");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s","+");
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last=='-')
		{
			sprintf(curr.token,"%s","MINUS");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s","-");
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last=='*')
		{
				sprintf(curr.token,"%s","MUL");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s","*");
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last=='/')
		{
			sprintf(curr.token,"%s","DIV");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s","/");
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if((isalpha(last) && last>='a' && last<='z') || (last>='A' && last<='Z') )
		{
			str[i++]=last;
			ch=custom_fgetc();
			column++;
			while(((ch>='a' && ch<='z') || (ch>='A' && ch<='Z') || (ch<='9' && ch>='0') || ch=='_') && isalpha(last))
			{
				// printf("%c",ch );
				str[i++]=ch;
				ch=custom_fgetc();
				column++;
			}
			str[i]='\0';
			sprintf(curr.lexeme,"%s",str);
			sprintf(curr.token,"%s",resolve(str));
			if(strlen(str)>8 && strcmp(curr.token,"ID")==0)
			{
				printf("%s: This Identifier is too long\n",str );
				last=ch;
				continue;
			}
			curr.line=line;
			curr.column=column;
			// indentifyToken();
			last=ch;
			// printf("Input: %c %d %d\n",last,buffer_pointer,buffer_size);
			return curr;
		}
		else if(last=='.')
		{
			ch=custom_fgetc();
			column++;
			if(ch=='.')
			{	
				sprintf(curr.token,"%s","RANGEOP");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s","..");
				last=custom_fgetc();
				return curr;
			}
			else
			{
				printf("Unidentified pattern %c%c in line no. %d\n",last,ch,line );
				last=custom_fgetc();
				continue;
			}
		}
		else if((last>='0' || last<='9') && isdigit(last))
		{
			str[i++]=last;
			ch=custom_fgetc();
			column++;
			while(ch<='9' && ch>='0')
			{
				str[i++]=ch;
				ch=custom_fgetc();
				column++;
			}
			if(ch=='.')
			{
				str[i++]=ch;
				ch=custom_fgetc();
				column++;
				if(ch=='.')
				{
					// printf("hi1\n");
					sprintf(curr.token,"%s","NUM");
					curr.line=line;
					curr.column=column;
					str[i-1]='\0';
					sprintf(curr.lexeme,"%s",str);
					last=ch;
					buffer_pointer--;
					return curr;
				}
				else 
					if(ch<='9' && ch>='0')
					{
						str[i++]=ch;
						ch=custom_fgetc();
						column++;
						while(ch<='9' && ch>='0')
						{
							str[i++]=ch;
							ch=custom_fgetc();
							column++;
						}
						if (ch == 'e' || ch == 'E')
						{
							str[i++]=ch;
							ch=custom_fgetc();
							column++;
							if (ch=='+' || ch=='-' || (ch<='9' && ch>='0'))
							{	
								str[i++]=ch;
								ch=custom_fgetc();
								column++;
								while(ch<='9' && ch>='0')
								{
									str[i++]=ch;
									ch=custom_fgetc();
									column++;
								}
							}
							else {
								printf("1Unidentified Symbol %c in line no. %d\n",ch,line );
								last=custom_fgetc();
								continue;
							}
						}
						str[i]='\0';
						sprintf(curr.token,"%s","RNUM");
						curr.line=line;
						curr.column=column;
						sprintf(curr.lexeme,"%s",str);
						last=ch;
						return curr;
					}
				else {
					printf("2Unidentified Symbol %c in line no. %d\n",ch,line );
					last=custom_fgetc();
					printf("%c\n", last);
					continue;
				}
			}
			else if (ch == 'e' || ch == 'E')
			{
				str[i++]=ch;
				ch=custom_fgetc();
				column++;
				if (ch=='+' || ch=='-' || (ch<='9' && ch>='0'))
				{	
					str[i++]=ch;
					ch=custom_fgetc();
					column++;
					while(ch<='9' && ch>='0')
					{
						str[i++]=ch;
						ch=custom_fgetc();
						column++;
					}
				}
				else {
					printf("1Unidentified Symbol %c in line no. %d\n",ch,line );
					last=custom_fgetc();
					continue;
				}
				str[i]='\0';
				sprintf(curr.token,"%s","RNUM");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s","-");
				last=ch;
				return curr;
			}
			else {
				// while(ch<='9' && ch>='0')
				// {
				// 	str[i++]=ch;
				// 	ch=custom_fgetc();
				// 	column++;
				// }
				// printf("hi\n");
				str[i]='\0';
				sprintf(curr.token,"%s","NUM");
				curr.line=line;
				curr.column=column;
				sprintf(curr.lexeme,"%s",str);
				last=ch;
				return curr;
			}
		}
		else
		{
			printf("Foreign symbol %c in line no. %d\n",last,line );
			last=custom_fgetc();
		}
	}
	return curr;
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