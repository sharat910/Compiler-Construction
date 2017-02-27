#include "lexer.h"
#include <stdio.h>	
#include "index_t.h"
#include "map.h"
#include <ctype.h>
#include <string.h>
// void returnToken(char* a)
// {
// 	printf("%s %d ",a,get_index_t(a));
// }
extern int line;
extern int column;
extern char last;
extern FILE* fp;
char buffer[200];
int buffer_pointer=0;
int buffer_size=0;
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
		buffer_size = strlen(buffer);
		return fp;
	}
	else
		return NULL;
}

void removeComments(char *testcaseFile, char *cleanFile)
{
	FILE* fp1 = fopen(testcaseFile,"r");
	FILE* fp2 = fopen(cleanFile,"w");
	while(!feof(fp1)){
		char ch = fgetc(fp1);
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

}


tokenInfo getNextToken()
{
	char ch;
	tokenInfo curr;
	if (buffer_pointer == buffer_size || last=='\n')
	{
		fp = getStream(fp);
		// printf("\n%s\n",buffer);		
		if (fp == NULL)
		{			
			sprintf(curr.token,"%s","#");
			return curr;
		}
		line++;
		column=1;
		last = custom_fgetc();
	}

	while(buffer_pointer < buffer_size)
	{
		
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
					sprintf(curr.token,"%s","#");
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
					last=custom_fgetc();
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
			ch=custom_fgetc();
			column++;
			if(ch=='='){
				sprintf(curr.token,"%s","GE");
				curr.line=line;
				curr.column=column;
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
					last=custom_fgetc();
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
			ch=custom_fgetc();
			column++;
			if(ch=='=')
			{
				sprintf(curr.token,"%s","EQ");
				curr.line=line;
				curr.column=column;
				last=custom_fgetc();
				column++;	
				return curr;
			}
			// else errorfunc;
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
				last=custom_fgetc();
				column++;
				return curr;
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
				last=custom_fgetc();
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
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last=='[')
		{
			sprintf(curr.token,"%s","SQBO");
				curr.line=line;
				curr.column=column;
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last==']')
		{
				sprintf(curr.token,"%s","SQBC");
				curr.line=line;
				curr.column=column;
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last=='(')
		{
			sprintf(curr.token,"%s","BO");
				curr.line=line;
				curr.column=column;
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last==')')
		{
				sprintf(curr.token,"%s","BC");
				curr.line=line;
				curr.column=column;
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last==';')
		{
				sprintf(curr.token,"%s","SEMICOL");
				curr.line=line;
				curr.column=column;
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last=='+')
		{
				sprintf(curr.token,"%s","PLUS");
				curr.line=line;
				curr.column=column;
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last=='-')
		{
			sprintf(curr.token,"%s","MINUS");
				curr.line=line;
				curr.column=column;
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last=='*')
		{
				sprintf(curr.token,"%s","MUL");
				curr.line=line;
				curr.column=column;
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(last=='/')
		{
			sprintf(curr.token,"%s","DIV");
				curr.line=line;
				curr.column=column;
				last=custom_fgetc();
				column++;
				return curr;
		}
		else if(isalpha(last) && last>='a' && last<='z' || last>='A' && last<='Z' )
		{
			str[i++]=last;
			ch=custom_fgetc();
			column++;
			while((ch>='a' && ch<='z' || ch>='A' && ch<='Z' || ch<='9' && ch>='0' || ch=='_') && isalpha(last))
			{
				// printf("%c",ch );
				str[i++]=ch;
				ch=custom_fgetc();
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
			ch=custom_fgetc();
			column++;
			if(ch=='.')
			{	
				sprintf(curr.token,"%s","RANGEOP");
				curr.line=line;
				curr.column=column;
				last=custom_fgetc();
				return curr;
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
					last=ch;
					fseek(fp,-1,SEEK_CUR);
					return curr;
				}
				else 
					if(ch<='9' && ch>='0')
					{
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
							ch=custom_fgetc();
							column++;
							if (ch=='+' || ch=='-')
							{
								ch=custom_fgetc();
								column++;
								while(ch<='9' && ch>='0')
								{
									str[i++]=ch;
									ch=custom_fgetc();
									column++;
								}
							}
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
			else if (ch == 'e' || ch == 'E')
			{
				ch=custom_fgetc();
				column++;
				if (ch=='+' || ch=='-')
				{
					ch=custom_fgetc();
					column++;
					while(ch<='9' && ch>='0')
					{
						str[i++]=ch;
						ch=custom_fgetc();
						column++;
					}
					str[i]='\0';
						sprintf(curr.token,"%s","RNUM");
						curr.line=line;
						curr.column=column;
						last=ch;
						return curr;
				}
			}
			else {
				while(ch<='9' && ch>='0')
				{
					str[i++]=ch;
					ch=custom_fgetc();
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