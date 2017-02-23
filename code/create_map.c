#include <stdio.h>
#include <ctype.h>
#include <string.h>
char * str_to_upper(char * a)
{
	char ans[100];
	int i;
	for(i=0;i<strlen(a);i++)
	{
		a[i]=toupper(a[i]);
	}
	a[i]='\0';
	return a;
}
int main()
{
	FILE * fp=fopen("map_population.txt","w");
	int i=0;
		char str[100];
		while(scanf("%s",str)!=EOF)
		{
			// printf("%s\n", str);
			fprintf(fp,"sprintf(map_t[%d].incoming,\"%s\");\n",i,str );
			fprintf(fp,"map_t[%d].token=%d;\n",i,i);
			i++;
		}
		fflush(fp);
		printf("yo\n");
	return 0;
}