#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcPtr.h"
#include "linkedlist.h"
#include "updatedStruct.h"
#include "astOp.h"
#include "libasteroids.h"

/* Author: Lang Xu */

struct Asteroids *allocateAsteroid(struct Asteroids *single, struct Universe *common)
{
	struct Asteroids *astPtr;
	static int count = 0;
	if(astPtr = malloc(sizeof(struct Asteroids)))
	{
		*astPtr = *single;
		astPtr->ref_uni = common;
		common->lastID +=1;
		astPtr->ID = common->lastID;
		count += 1;
		fprintf(common->diagnostics,"Diagnostics: allocateAsteroid has allocated %d asteroids.\n",count); 
	}
	return astPtr;
}

void freeAsteroids(struct Asteroids **single,struct Universe *common)
{
	static int count = 0;
	if(*single == NULL) {fprintf(common->diagnostics,"Fail to free asteroid:NULL pointer received.\n");
	}else{count+=1;fprintf(common->diagnostics,"freeAsteroids has freed %d asteroids.\n",count);free(*single);}
}

void fission(struct Asteroids *single)
{
	struct Asteroids phobos;
	struct Asteroids deimos;
	struct Asteroids *deimosPtr;
	void *data;
	ComparisonFunction compareID = compareAstHold;
	
	if(single->steps == 0)
	{
		fprintf(single->ref_uni->diagnostics, "Diagnostic: Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf) fissions into 4 asteroids.\n", single->ID, (int)(single->size), single->X, single->Y, single->VX, single->VY);
		phobos = *single;
		phobos.size /= 2;
		phobos.steps = 3+(int)(phobos.X+phobos.Y)%8;
		
		deimos = phobos;
		if(!(deimosPtr = allocateAsteroid(&deimos,single->ref_uni)))
		{
			fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to allocate asteroid.\n");
		}else{
			data = deimosPtr;
			if(!insert(&(single->ref_uni->hold),data,compareAstHold,single->ref_uni->diagnostics)) {fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to insert node to hold.\n");freeAsteroids(&deimosPtr,single->ref_uni);}
		}	

		deimos.VX = -(phobos.VX);
		deimos.VY = -(phobos.VY);
		if(!(deimosPtr = allocateAsteroid(&deimos,single->ref_uni)))
		{
			fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to allocate asteroid.\n");
		}else{
			data = deimosPtr;
			if(!insert(&(single->ref_uni->hold),data,compareAstHold,single->ref_uni->diagnostics)) {fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to insert node to hold.\n");freeAsteroids(&deimosPtr,single->ref_uni);}
		}



		deimos.VX = -(phobos.VY);
		deimos.VY = phobos.VX;
		if(!(deimosPtr = allocateAsteroid(&deimos,single->ref_uni)))
		{
			fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to allocate asteroid.\n");
		}else{
			data = deimosPtr;
			if(!insert(&(single->ref_uni->hold),data,compareAstHold,single->ref_uni->diagnostics)) {fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to insert node to hold.\n");freeAsteroids(&deimosPtr,single->ref_uni);}
		}



		deimos.VX = (phobos.VY);
		deimos.VY = -(phobos.VX);
		if(!(deimosPtr = allocateAsteroid(&deimos,single->ref_uni)))
		{
			fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to allocate asteroid.\n");
		}else{
			data = deimosPtr;
			if(!insert(&(single->ref_uni->hold),data,compareAstHold,single->ref_uni->diagnostics)){fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to insert node to hold.\n");freeAsteroids(&deimosPtr,single->ref_uni);}
		}

	
 	}
}

void adjustPos(struct Asteroids *single)
{
	while((int)single->X > al_max_X()||(int)single->X < al_min_X()){
		if((int)single->X>al_max_X())single->X -=(al_max_X()-al_min_X()+1);
		if((int)single->X<al_min_X())single->X +=(al_max_X()-al_min_X()+1);
	}
	
	while((int)single->Y > al_max_Y()||(int)single->Y < al_min_Y()){
		if((int)single->Y>al_max_Y())single->Y -=(al_max_Y()-al_min_Y()+1);
		if((int)single->Y<al_min_Y())single->Y +=(al_max_Y()-al_min_Y()+1);
	}		
}

void split(struct Asteroids *single)
{
	struct Asteroids phobos;
	struct Asteroids deimos;
	struct Asteroids *deimosPtr;
	void *data;
	ComparisonFunction compareID = compareAstHold;
	
	if(single->steps == 0)
	{
		fprintf(single->ref_uni->diagnostics, "DIAGNOSTIC: Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf) splits into 2 asteroids.\n",single->ID, (int)(single->size), single->X, single->Y, single->VX, single->VY);
		phobos = *single;
		phobos.size-=1;
		phobos.steps = 3+(int)(phobos.X+phobos.Y)%8;

		deimos = phobos;
		deimos.VX = -(phobos.VY);
		deimos.VY = phobos.VX;
		deimos.X = phobos.X+(deimos.VX)*0.5;
		deimos.Y = phobos.Y+(deimos.VY)*0.5;
		adjustPos(&deimos);
		if(!(deimosPtr = allocateAsteroid(&deimos,single->ref_uni)))
		{
			fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to allocate asteroid.\n");
		}else{
			data = deimosPtr;
			if(!insert(&(single->ref_uni->hold),data,compareAstHold,single->ref_uni->diagnostics)){fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to insert node to hold.\n");freeAsteroids(&deimosPtr,single->ref_uni);}
		}


		deimos.VX = phobos.VY;
		deimos.VY = -(phobos.VX);
		deimos.X = phobos.X+(deimos.VX)*0.5;
		deimos.Y = phobos.Y+(deimos.VY)*0.5;
		adjustPos(&deimos);
		if(!(deimosPtr = allocateAsteroid(&deimos,single->ref_uni)))
		{
			fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to allocate asteroid.\n");
		}else{
			data = deimosPtr;
			if(!insert(&(single->ref_uni->hold),data,compareAstHold,single->ref_uni->diagnostics)){fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to insert node to hold.\n");freeAsteroids(&deimosPtr,single->ref_uni);}
		}

	}
}

void exhaust(struct Asteroids *single)
{
	struct Asteroids emit = *single;
	struct Asteroids *emitPtr;
	void *data;
	ComparisonFunction compareID = compareAstHold;

	if(single->steps> 0)
	{
		fprintf(single->ref_uni->diagnostics, "DIAGNOSTIC: Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf) emits an asteroid.\n", single->ID, (int)(single->size), single->X, single->Y, single->VX, single->VY);
		
		emit.VX = single->VX*0.25;
		emit.VY = single->VY*0.25;
		emit.steps = single->size*2;
        	emit.size = 0;
		if(!(emitPtr = allocateAsteroid(&emit,single->ref_uni)))
		{
			fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to allocate asteroid.\n");
		}else{
			data = emitPtr;
			if(!insert(&(single->ref_uni->hold),data,compareAstHold,single->ref_uni->diagnostics)){fprintf((single->ref_uni)->diagnostics,"Diagnostics: Fail to insert node to hold.\n");freeAsteroids(&emitPtr,single->ref_uni);}
		}
	}
	if(single->steps == 0)
	{
		fprintf(single->ref_uni->diagnostics, "DIAGNOSTIC: Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf) expires.\n",single->ID, (int)(single->size), single->X, single->Y, single->VX, single->VY);
	}
}

void timeout(struct Asteroids *single)
{
	if(single->steps == 0)
	{
		fprintf(single->ref_uni->diagnostics, "DIAGNOSTIC: Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf) expires.\n",single->ID, (int)(single->size), single->X, single->Y, single->VX, single->VY);
	}
}
