#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/* Author: Lang Xu */

/* Included additional allocateNode and freeNode function */

Node *allocateNode(FILE *diagnostics);

void freeNode(Node **node, FILE *diagnostics);

Node *allocateNode(FILE *diagnostics)
{
	static int allocateNode_count = 0;
	Node *allocate = NULL;
	if(allocate = malloc(sizeof(struct Node)))
	{
		allocateNode_count++;
		fprintf(diagnostics, "Diagnostics: AllocateNode: Succeeded allocating node.\n");
		fprintf(diagnostics, "Diagnostics: AllocateNode: allocateNode has created %d nodes.\n",allocateNode_count);
	}else{
		fprintf(diagnostics, "Diagnostics: AllocateNode: Fail to allocate node.\n");
	}
	return allocate;
}

void freeNode(Node **node, FILE *diagnostics)
{
	static int freeNode_count = 0;
	if(node == NULL)
	{
		fprintf(diagnostics, "Diagnostics: FreeNode: NULL pointer received.\n");
	}else{
		free(*node);
		freeNode_count++;
		fprintf(diagnostics, "Diagnostics: FreeNode: freeNode has freed %d nodes.\n",freeNode_count);
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
		if(*p2head == NULL || goesInFrontOf(toInsertNode->data,(*p2head)->data))
		{
			toInsertNode->next = *p2head;
			*p2head = toInsertNode;
		}else{
			priorNode = *p2head;
			while(priorNode->next!=NULL && goesInFrontOf(priorNode->next->data,toInsertNode->data))
			{
				priorNode = priorNode->next;
			}
			toInsertNode->next = priorNode->next;
			priorNode->next = toInsertNode;
		}
	}else{
		fprintf(diagnostics,"Diagnostics: Fail to insert node.\n");
	}
	return result;							
}

void deleteSome(Node **p2head, CriteriaFunction mustGo, ActionFunction disposal, FILE *diagnostics)
{
	Node *traversePtr = *p2head,*previousNodePtr;
	while(traversePtr != NULL && mustGo(traversePtr->data))
	{
		*p2head = traversePtr->next;
		disposal(traversePtr->data);
		freeNode(&traversePtr,diagnostics);
		traversePtr = *p2head;
	}
	while(traversePtr!=NULL)
	{
		while(traversePtr != NULL && !mustGo(traversePtr->data))
		{
			previousNodePtr = traversePtr;
			traversePtr = traversePtr->next;
		}
		if(traversePtr == NULL) return;
		previousNodePtr->next = traversePtr->next;
		disposal(traversePtr->data);
		freeNode(&traversePtr,diagnostics);
		traversePtr = previousNodePtr->next;
	}			
}

void traverse(Node *head, ActionFunction doThis, FILE *diagnostics)
{
	Node *traversePtr = head;
	while(traversePtr != NULL)
	{
		doThis(traversePtr->data);
		traversePtr = traversePtr->next;
	}
}
