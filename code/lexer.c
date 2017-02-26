#include "lexer.h"
#include <stdio.h>	
#include "index_t.h"
#include "map.h"
#include <ctype.h>
// void returnToken(char* a)
// {
// 	printf("%s %d ",a,get_index_t(a));
// }
extern int line;
extern int column;
extern char last;
extern FILE* fp;
char* resolve(char* a)
{
	return find(a);
}


tokenInfo getNextToken()
{
	// printf("hello%c ", last);
	char ch;
	tokenInfo curr;
	while(!feof(fp))
	{
		
		char str[20];
		if(last==' ' || last=='\n' || last=='\t' || last=='\r'){
			if(last=='\n'){
				line++;
				column=1;
			}
			if(last==' ')
				column++;
			if(last=='\t')
				column+=4;
			last=fgetc(fp);
			continue;
		}
		int i=0;
		if(last=='<')
		{
			// printf("hey\n");
			ch=fgetc(fp);
			column++;
			if(ch=='='){
				sprintf(curr.token,"%s","LE");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
			}
			else if(ch=='<')
			{
				// printf("yo%c\n",ch );
				last=fgetc(fp);
				column++;
				if(last=='<')
				{
					sprintf(curr.token,"%s","DRIVERDEF");
					curr.line=line;
					curr.column=column;
					last=fgetc(fp);
					column++;
					return curr;
				}
				else {
					sprintf(curr.token,"%s","DEF");
					curr.line=line;
					curr.column=column;
					return curr;
				}
			}
			else {
				sprintf(curr.token,"%s","LT");
				curr.line=line;
				curr.column=column;

				last=ch;
				return curr;
			}
		}
		else if(last=='>')
		{
			ch=fgetc(fp);
			column++;
			if(ch=='='){
				sprintf(curr.token,"%s","GE");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
			}
			else if(ch=='>')
			{
				last=fgetc(fp);
				column++;
				if(last=='>')
				{
					sprintf(curr.token,"%s","DRIVERENDDEF");
					curr.line=line;
					curr.column=column;
					last=fgetc(fp);
					column++;
					return curr;
				}
				else 
					sprintf(curr.token,"%s","ENDDEF");
					curr.line=line;
					curr.column=column;
				return curr;
			}
			else {
				sprintf(curr.token,"%s","GT");
				curr.line=line;
				curr.column=column;
				last=ch;
				return curr;	
			}
		}
		else if(last=='=')
		{
			ch=fgetc(fp);
			column++;
			if(ch=='=')
			{
				sprintf(curr.token,"%s","EQ");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;	
				return curr;
			}
			// else errorfunc;
		}
		else if(last=='!')
		{
			ch=fgetc(fp);
			column++;
			if(ch=='=')
			{
				sprintf(curr.token,"%s","NE");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
			}
			// else errorfunc;
		}
		else if(last==':')
		{
			ch=fgetc(fp);
			column++;
			if(ch=='=')
			{
				sprintf(curr.token,"%s","ASSIGNOP");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
				
			}
			else {
				sprintf(curr.token,"%s","COLON");
				curr.line=line;
				curr.column=column;
				last=ch;
				return curr;
			}
		}
		else if(last==',')
		{
			sprintf(curr.token,"%s","COMMA");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
		}
		else if(last=='[')
		{
			sprintf(curr.token,"%s","SQBO");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
		}
		else if(last==']')
		{
				sprintf(curr.token,"%s","SQBC");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
		}
		else if(last=='(')
		{
			sprintf(curr.token,"%s","BO");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
		}
		else if(last==')')
		{
				sprintf(curr.token,"%s","BC");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
		}
		else if(last==';')
		{
				sprintf(curr.token,"%s","SEMICOL");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
		}
		else if(last=='+')
		{
				sprintf(curr.token,"%s","PLUS");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
		}
		else if(last=='-')
		{
			sprintf(curr.token,"%s","MINUS");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
		}
		else if(last=='*')
		{
				sprintf(curr.token,"%s","MUL");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
		}
		else if(last=='/')
		{
			sprintf(curr.token,"%s","DIV");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				column++;
				return curr;
		}
		else if(isalpha(last) && last>='a' && last<='z' || last>='A' && last<='Z' )
		{
			str[i++]=last;
			ch=fgetc(fp);
			column++;
			while((ch>='a' && ch<='z' || ch>='A' && ch<='Z' || ch<='9' && ch>='0' || ch=='_') && isalpha(last))
			{
				// printf("%c",ch );
				str[i++]=ch;
				ch=fgetc(fp);
				column++;
			}
			str[i]='\0';
			sprintf(curr.token,"%s",resolve(str));
				curr.line=line;
				curr.column=column;
			// indentifyToken();
			last=ch;
			return curr;
		}
		else if(last=='.')
		{
			ch=fgetc(fp);
			column++;
			if(ch=='.')
			{	
				sprintf(curr.token,"%s","RANGEOP");
				curr.line=line;
				curr.column=column;
				last=fgetc(fp);
				return curr;
			}
		}
		else if((last>='0' || last<='9') && isdigit(last))
		{
			str[i++]=last;
			ch=fgetc(fp);
			column++;
			while(ch<='9' && ch>='0')
			{
				str[i++]=ch;
				ch=fgetc(fp);
				column++;
			}
			if(ch=='.')
			{
				str[i++]=ch;
				ch=fgetc(fp);
				column++;
				if(ch=='.')
				{
					// printf("hi1\n");
					sprintf(curr.token,"%s","NUM");
					curr.line=line;
					curr.column=column;
					last=ch;
					fseek(fp,-1,SEEK_CUR);
					return curr;
				}
				else 
					if(ch<='9' && ch>='0')
					{
						ch=fgetc(fp);
						column++;
						while(ch<='9' && ch>='0')
						{
							str[i++]=ch;
							ch=fgetc(fp);
							column++;
						}
						str[i]='\0';
						sprintf(curr.token,"%s","RNUM");
						curr.line=line;
						curr.column=column;
						last=ch;
						return curr;
					}
				else {
					// errorfunc();
					return curr;
				}
			}
			else {
				while(ch<='9' && ch>='0')
				{
					str[i++]=ch;
					ch=fgetc(fp);
					column++;
				}
				// printf("hi\n");
				sprintf(curr.token,"%s","NUM");
				curr.line=line;
				curr.column=column;
				last=ch;
				return curr;
			}
		}
	}
}