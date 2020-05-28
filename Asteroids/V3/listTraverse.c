#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void printString(void *data);

int compareFirst(void *data1, void *data2);

int isUpperCase(void *data);

int main()
{
	char *data1 = "apple";
	char *data2 = "bad";
	char *data3 = "catch";
	ActionFunction doThis = printString;
	FILE *diagnostics = NULL;
	Node *list_head ;
	Node *second;
	Node *third;
	list_head = (struct Node *)malloc(sizeof(struct Node));
	second = (struct Node *)malloc(sizeof(struct Node));
	third = (struct Node *)malloc(sizeof(struct Node));
	
	
	list_head->data = data1;
	list_head->next = second;
	
	second->data = data2;
	second->next = third;
	
	third->data = data3;
	third->next = NULL;
	traverse(list_head,printString,diagnostics);
		
}

void traverse(Node *head, ActionFunction doThis, FILE *diagnostics)
{
	while(head != NULL)
	{
		doThis(head->data);
		head = head->next;
	}
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

