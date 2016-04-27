#include "tool.h"
int match(char *a,char *b)
{
	for(; *a!='\0'||*b!='\0'; a++,b++)
		{
			if(*a!=*b) return 0;
		}
	return 1;
}
void clear(u16 a[])
{
	for(; *a!='\0'; a++)
		{
			*a=NULL;
		}
}
