#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timespec.h"
#include "linkedlist.h"
#include "updatedStruct.h"
#include "astOp.h"
#include "libasteroids.h"
#define GRAPHICS 1
#define TIME 0.050000001

/* Author: Lang Xu */

int compareAstHold(void *data1,void *data2)
{
	struct Asteroids *toInsertAst = data1;
	struct Asteroids *currentAst = data2;
	return (toInsertAst->ID<=currentAst->ID);
}

int compareAstBelt(void *data1, void *data2)
{
	struct Asteroids *toInsertAst = data1;
	struct Asteroids *currentAst = data2;
	if(toInsertAst->size == currentAst->size)
	{
		return toInsertAst->steps<=currentAst->steps;	
	}else{
		return toInsertAst->size<=currentAst->size;
	}
}

int clearHold(void *data)
{
	return 1;
}

int stepZero(void *data)
{
	return ((*(struct Asteroids *)data).steps == 0);	
}

void printOutput(void *data)
{
	struct Asteroids *astPtr = data;
	fprintf(astPtr->ref_uni->output,"Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+6.3lf, %+6.3lf) has %d steps\n",astPtr->ID,astPtr->size,astPtr->X,astPtr->Y,astPtr->VX,astPtr->VY,astPtr->steps);
}

void noActionHold(void *data)
{
	return;
}

void disposalBelt(void *data)
{
	struct Asteroids *astPtr = data;
	fprintf(astPtr->ref_uni->diagnostics,"DIAGNOSTIC: Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf) expires.\n",astPtr->ID, astPtr->size,astPtr->X,astPtr->Y,astPtr->VX,astPtr->VY);
	freeAsteroids(&astPtr,astPtr->ref_uni);
}

void forwardAst(void *data)
{
	struct Asteroids *astPtr = data;
	astPtr->X += astPtr->VX*TIME;
	astPtr->Y += astPtr->VY*TIME;
	while((int)(astPtr->X) > al_max_X()||(int)(astPtr->X) < al_min_X()){
		if((int)(astPtr->X)>al_max_X())astPtr->X-=al_max_X()-al_min_X()+1;
		if((int)(astPtr->X)<al_min_X())astPtr->X+=al_max_X()-al_min_X()+1;
	}
	
	while((int)(astPtr->Y) > al_max_Y()||(int)(astPtr->Y) < al_min_Y()){
		if((int)(astPtr->Y)>al_max_Y())astPtr->Y-=al_max_Y()-al_min_Y()+1;
		if((int)(astPtr->Y)<al_min_Y())astPtr->Y+=al_max_Y()-al_min_Y()+1;
	}	
}

void decrementSteps(void *data)
{
	((struct Asteroids *)data)->steps -= 1;
}

void specials(void *data)
{
	void (*fp[])(struct Asteroids *) = {timeout,split,exhaust,fission,fission,split};
        const int SIZE = sizeof(fp)/sizeof(fp[0]);
	struct Asteroids *astPtr = data;
	if(astPtr->size>SIZE-1){fp[SIZE-1](astPtr);}
	if(astPtr->size<0){fp[0](astPtr);}
	if((astPtr->size<SIZE) && (astPtr->size>=0)){fp[astPtr->size](astPtr);}	
}

void drawCurrent(void *data)
{
	struct Asteroids *astPtr = data;
	if(GRAPHICS)al_square(astPtr->X,astPtr->Y,astPtr->size);
}

void insertNodeBelt(void *data)
{
	struct Asteroids *astPtr = data;
	ComparisonFunction compareSizeAndSteps = compareAstBelt;
	if(insert(&(astPtr->ref_uni->belt),data,compareSizeAndSteps,astPtr->ref_uni->diagnostics))
	{
		fprintf(astPtr->ref_uni->diagnostics,"Diagnostics: Spawning %d step asteroid #%d of size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf)\n", astPtr->steps,astPtr->ID,astPtr->size,astPtr->X,astPtr->Y,astPtr->VX,astPtr->VY);
	}
}

