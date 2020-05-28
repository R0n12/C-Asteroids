#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "updatedStruct.h"
#include "astOp.h"
#include "funcPtr.h"

void printString(void *data);

int main()
{
	struct Universe common = {0,0,100,0.0,NULL,NULL,NULL,NULL,NULL};
	struct Asteroids ast1 = {101,5,5,5,5,5,5,NULL};
	struct Asteroids *astPtr = allocateAsteroid(&ast1,&common);
	void *data = astPtr;
	ComparisonFunction holdcompare = compareAstHold;
	ActionFunction print = printString;
	printf("\n");
	
	if(insert(&(common.hold),data,holdcompare,common.diagnostics))
	{
		traverse(common.hold,print,common.diagnostics);
	}else{
		printf("Fail to insert\n");
	}
	
}

struct Asteroids *allocateAsteroid(struct Asteroids *single, struct Universe *common)
{
	struct Asteroids *astPtr;
	static int count1 = 0;
	if(astPtr = malloc(sizeof(struct Asteroids)))
	{
		*astPtr = *single;
		astPtr->ref_uni = common;
		common->lastID +=1;
		astPtr->ID = common->lastID;
		count1 += 1;
		printf("Diagnostics: allocateAsteroid has allocated %d asteroids.\n",&count1); 
	}
	return astPtr;
}

Node *allocateNode(FILE *diagnostics)
{
	static int allocateNode_count = 0;
	Node *allocate = NULL;
	if(allocate = malloc(sizeof(struct Node)))
	{
		allocateNode_count++;
		printf("Diagnostics: AllocateNode: Succeeded allocating node.\n");
		printf("Diagnostics: AllocateNode: allocateNode has created %d nodes.\n",allocateNode_count);
	}else{
		printf("Diagnostics: AllocateNode: Fail to allocate node.\n");
	}
	return allocate;
}

void freeNode(Node *node, FILE *diagnostics)
{
	static int freeNode_count = 0;
	if(node == NULL)
	{
		printf( "Diagnostics: FreeNode: NULL pointer received.\n");
	}else{
		free(node);
		freeNode_count++;
		printf("Diagnostics: FreeNode: freeNode has freed %d nodes.\n",freeNode_count);
	}
}

int insert(Node **p2head, void *data, ComparisonFunction goesInFrontOf, FILE *diagnostics)
{
	int result = 0;
	Node *toInsertNode;
	Node *priorNode;
	if(toInsertNode = allocateNode(diagnostics))
	{
		result = 1;
		toInsertNode->data = data;
		if(*p2head == NULL || goesInFrontOf((*p2head)->data,toInsertNode->data))
		{
			toInsertNode->next = *p2head;
			*p2head = toInsertNode;
		}else{
			priorNode = *p2head;
			while(priorNode->next!=NULL && goesInFrontOf(toInsertNode->data,priorNode->next->data))
			{
				priorNode = priorNode->next;
			}
			toInsertNode->next = priorNode->next;
			priorNode->next = toInsertNode;
		}
	}else{
		printf("Diagnostics: Fail to insert node.\n");
	}
	return result;							
}

void deleteSome(Node **p2head, CriteriaFunction mustGo, ActionFunction disposal, FILE *diagnostics)
{
	Node *traversePtr = *p2head,*previousNode;
	while(traversePtr != NULL && mustGo(traversePtr->data))
	{
		*p2head = traversePtr->next;
		disposal(traversePtr->data);
		freeNode(traversePtr,diagnostics);
		traversePtr = *p2head;
	}
	while(traversePtr!=NULL)
	{
		while(traversePtr != NULL && !mustGo(traversePtr->data))
		{
			previousNode = traversePtr;
			traversePtr = traversePtr->next;
		}
		if(traversePtr == NULL) return;
		previousNode->next = traversePtr->next;
		disposal(traversePtr->data);
		freeNode(traversePtr,diagnostics);
		traversePtr = previousNode->next;
	}			
}

void traverse(Node *head, ActionFunction doThis, FILE *diagnostics)
{
	while(head != NULL)
	{
		doThis(head->data);
		head = head->next;
	}
}

int compareAstHold(void *data1,void *data2)
{
	struct Asteroids *toInsertAst = data1;
	struct Asteroids *currentAst = data2;
	return (toInsertAst->ID<=currentAst->ID);
}

void printString(void *data)
{
	struct Asteroids *toInsertAst = data;
	printf("ID: %d\n",toInsertAst->ID);
}

