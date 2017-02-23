#include <stdio.h>
#include <ctype.h>
#include "map.h"
#include "index_nt.h"
#include "index_t.h"
#include "rule_table.h"
int line;
int column;
void returnToken(char* a)
{
	printf("%s %d ",a,get_index_nt(a));
}
void resolve(char* a)
{
	printf("%s %d ",find(a),get_index_nt(find(a)));
}
extern entry lookup_table[40];
extern entry_map_nt map_nt[57];
extern entry_map_t map_t[57];
extern rule rules[100];
int main()
{
	init();
	init_map_t();
	init_map_nt();
	rule_table_init();
	for(int i=1;i<98;i++)
	{
		printf(rules[i].lhs);
		printStack(rules[i].rhs);
	}

	// for(int i=0;i<57;i++)
	// {
	// 	printf("%s ,%d\n",map_nt[i].incoming,map_nt[i].index);
	// }
	char last,ch;
	FILE * fp=fopen( "code.txt", "r" );
	last=fgetc(fp);
	// while(!feof(fp))
	// {
	// 	last=fgetc(fp);
	// 	printf("%c", last);
	// }
	line=1;
	column=1;
	while(!feof(fp))
	{
		column++;
		// printf("%c ", last);
		char str[20];
		if(last==' ' || last=='\n' || last=='\t' || last=='\r'){
			if(last=='\n'){
				line++;
				column=0;
			}
			last=fgetc(fp);
			continue;
		}
		int i=0;
		if(last=='<')
		{
			// printf("hey\n");
			ch=fgetc(fp);
			if(ch=='='){
				returnToken("LE");
				last=fgetc(fp);
				continue;
			}
			else if(ch=='<')
			{
				// printf("yo%c\n",ch );
				last=fgetc(fp);
				if(last=='<')
				{
					returnToken("DRIVERDEF");
					last=fgetc(fp);
					continue;
				}
				else {
					returnToken("DEF");
					continue;
				}
			}
			else {
				returnToken("LT");
				last=ch;
				continue;
			}
		}
		else if(last=='>')
		{
			ch=fgetc(fp);
			if(ch=='='){
				returnToken("GE");
				last=fgetc(fp);
				continue;
			}
			else if(ch=='>')
			{
				last=fgetc(fp);
				if(last=='>')
				{
					returnToken("DRIVERENDDEF");
					last=fgetc(fp);
					continue;
				}
				else 
					returnToken("ENDDEF");
				continue;
			}
			else {
				returnToken("GT");
				last=ch;
				continue;	
			}
		}
		else if(last=='=')
		{
			ch=fgetc(fp);
			if(ch=='=')
			{
				returnToken("EQ");
				last=fgetc(fp);	
				continue;
			}
			// else errorfunc;
		}
		else if(last=='!')
		{
			ch=fgetc(fp);
			if(ch=='=')
			{
				returnToken("NE");
				last=fgetc(fp);
				continue;
			}
			// else errorfunc;
		}
		else if(last==':')
		{
			ch=fgetc(fp);
			if(ch=='=')
			{
				returnToken("ASSIGNOP");
				last=fgetc(fp);
				continue;
				
			}
			else {
				returnToken("COLON");
				last=ch;
				continue;
			}
		}
		else if(last==',')
		{
				returnToken("COMMA");
				last=fgetc(fp);
				continue;
		}
		else if(last=='[')
		{
				returnToken("SQBO");
				last=fgetc(fp);
				continue;
		}
		else if(last==']')
		{
				returnToken("SQBC");
				last=fgetc(fp);
				continue;
		}
		else if(last=='(')
		{
				returnToken("BO");
				last=fgetc(fp);
				continue;
		}
		else if(last==')')
		{
				returnToken("BC");
				last=fgetc(fp);
				continue;
		}
		else if(last==';')
		{
				returnToken("SEMICOL");
				last=fgetc(fp);
				continue;
		}
		else if(last=='+')
		{
				returnToken("PLUS");
				last=fgetc(fp);
				continue;
		}
		else if(last=='-')
		{
				returnToken("MINUS");
				last=fgetc(fp);
				continue;
		}
		else if(last=='*')
		{
				returnToken("MUL");
				last=fgetc(fp);
				continue;
		}
		else if(last=='/')
		{
				returnToken("DIV");
				last=fgetc(fp);
				continue;
		}
		else if(isalpha(last) && last>='a' && last<='z' || last>='A' && last<='Z' )
		{
			str[i++]=last;
			ch=fgetc(fp);
			while((ch>='a' && ch<='z' || ch>='A' && ch<='Z' || ch<='9' && ch>='0' || ch=='_') && isalpha(last))
			{
				// printf("%c",ch );
				str[i++]=ch;
				ch=fgetc(fp);
			}
			str[i]='\0';
			resolve(str);
			// indentifyToken();
			last=ch;
			continue;
		}
		else if(last=='.')
		{
			ch=fgetc(fp);
			if(ch=='.')
			{
				returnToken("RANGEOP");
				last=fgetc(fp);
				continue;
			}
		}
		else if((last>='0' || last<='9') && isdigit(last))
		{
			str[i++]=last;
			ch=fgetc(fp);
			while(ch<='9' && ch>='0')
			{
				str[i++]=ch;
				ch=fgetc(fp);
			}
			if(ch=='.')
			{
				str[i++]=ch;
				ch=fgetc(fp);
				if(ch=='.')
				{
					returnToken("NUM");
					returnToken("RANGEOP");
					continue;
				}
				else 
					if(ch<='9' && ch>='0')
					{
						ch=fgetc(fp);
						while(ch<='9' && ch>='0')
						{
							str[i++]=ch;
							ch=fgetc(fp);
						}
						str[i]='\0';
						returnToken("RNUM");
						last=ch;
						continue;
					}
				else {
					// errorfunc();
					continue;
				}
			}
			else {
				while(ch<='9' && ch>='0')
				{
					str[i++]=ch;
					ch=fgetc(fp);
				}
				returnToken("NUM");
				last=ch;
						continue;
			}
		}
	}
	fclose(fp);
}