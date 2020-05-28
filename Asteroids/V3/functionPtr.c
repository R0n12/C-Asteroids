#include <stdio.h>
#include "linkedlist.h"

void printString(void *data);

int compareFirst(void *data1, void *data2);

int isUpperCase(void *data);

int main()
{
	ActionFunction action = printString;
	ComparisonFunction compare = compareFirst;
	CriteriaFunction criteria = isUpperCase;
	char *string1 = "string";
	char *string2 = "String";
	void *data1 = string1;
	void *data2 = string2;
	action(data1);
	if(compare(data1,data2))
	{
		printf("true\n");
	}else{
		printf("false\n");
	}
	if(criteria(data2))
	{
		printf("true\n");
	}else{
		printf("false\n");
	}
	return 0;
}

void printString(void *data)
{
	printf("%s\n",data);
}

int compareFirst(void *data1, void *data2)
{
	int result = 0;
	if(*(char *)data1>*(char *)data2)
	{
		result = 1;
	}
	return result;
}

int isUpperCase(void *data)
{
	int ascii = (int)(*(char *)data);
	
	int result = 0;
	printf("%d\n",ascii);
	if(ascii<=90&&ascii>=65)
	{
		result = 1;
	}
	return result;
}
