/* Author: Lang Xu */

/* header file for singly linked list */
/* be sure to include stdio.h before this file*/

typedef struct Node{
	struct Node *next;
	void *data;
	}Node;

typedef void (* ActionFunction)( void *data);
typedef int (* ComparisonFunction)(void *data1, void *data2);
typedef int (* CriteriaFunction)(void *data);

/* signatures that the list code provides to the outside world */

/* NOTE: insert returns a true value when it succeeds */
int insert(Node **p2head, void *data, ComparisonFunction goesInFrontOf,
	FILE *diagnostics);

void deleteSome(Node **p2head, CriteriaFunction mustGo, 
		ActionFunction disposal, FILE *diagnostics);

void traverse(Node *head, ActionFunction doThis, FILE *diagnostics);

