#include <stdio.h>
#include <stdlib.h>
#include "libasteroids.h"
#include "struct.h"
#include "fancy.h"
#define GRAPHICS 1
#define TIME 1.05

/* Author: Lang Xu */

/* Calculate new adjuested position in x and y direction */
void adjustPos(struct Asteroids *single);

/* Calculate one step forward for x and y movement */
void move(struct Universe *common);

/* simulation */
void simulation(struct Universe *common);

/* readin all the asteroids */
void readin(struct Universe *common);

/* add asteroids in */
void add(struct Asteroids *single, struct Universe *common);

/* run asteroids */
void run(struct Universe *common);

/* move the asteroids */
void updatePos(struct Asteroids *single);

/* a collection of special functions */
void fancy(struct Universe *common);

/* remove an asteroid */
void removeAst(struct Asteroids *single, struct Universe *common);

/* graphics integration */
void printFinal(struct Universe *common);

/* free memory */
void freeMem(struct Universe *common);

/* print all the current asteroids */
void printAll(struct Universe *common);

int main(void){
	struct Universe common = {0,0,100,0.0,NULL};
	if(GRAPHICS ? al_initialize():1)
	{
		
		simulation(&common);
		al_teardown();
	}
	return 0;
}

void simulation(struct Universe *common)
{
	readin(common);
	fprintf(stderr, "\n");
	fprintf(stderr, "At time ET = %6.3lf\n",common->ET);
	run(common);
	freeMem(common);
}

void readin(struct Universe *common)
{
	struct Asteroids single;
	while(scanf("%d %d %lf %lf %lf %lf",&single.size,&single.steps,&single.X,&single.Y,&single.VX,&single.VY)==6)
	{
		if(single.steps>=1) add(&single,common);
		
	}
}
void add(struct Asteroids *single, struct Universe *common)
{
	struct Asteroids *new_mem;	
	if((common->numAst)>=(common->length))
	{
		if(new_mem = realloc(common->ref_ast,(common->numAst+4)*sizeof(struct Asteroids)))
		{
			common->ref_ast = new_mem;
			common->length+=4;
			fprintf(stderr,"DIAGNOSTIC: Increasing size of the asteroid array by 4\n");
		}else{
			fprintf(stderr,"DIAGNOSTIC: Fail to allocate memory.\n");
			return;
		}

	}
	single->ref_uni = common;
	common->lastID +=1;
	single->ID = common->lastID;
	*(common->ref_ast+(common->numAst++)) = *single;
	fprintf(stderr,"DIAGNOSTIC: Spawning %d step asteroid #%d of size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf)\n", (int)(single->steps),single->ID,(int)(single->size),single->X,single->Y,single->VX,single->VY);
}


void run(struct Universe *common)
{	
	printAll(common);
	while((common->numAst)>0)
	{	
		(common->ET) += TIME;
		move(common);
		fancy(common);
		printFinal(common);
	}
}

void move(struct Universe *common)
{
	int c;
	for(c = 0; c<common->numAst;c++)
	{
		updatePos(common->ref_ast+c);
		adjustPos(common->ref_ast+c);
	}
}


void updatePos(struct Asteroids *single)
{
	single->X += single->VX*TIME;
	single->Y += single->VY*TIME;
	single->steps-=1;
}

void adjustPos(struct Asteroids *single)
{
	while(single->X > al_max_X()||single->X < al_min_X()){
		if(single->X>al_max_X())single->X -=al_max_X();
		if(single->X<al_min_X())single->X = al_max_X()-single->X;
	}
	
	while(single->Y > al_max_Y()||single->Y < al_min_Y()){
		if(single->Y>al_max_Y())single->Y -=al_max_Y();
		if(single->Y<al_min_Y())single->Y = al_max_Y()-single->Y;
	}		
}

void fancy(struct Universe *common)
{
	
	int (*fp[])(struct Asteroids *) = {timeout,split,exhaust,fission,fission,split};
        const int SIZE = sizeof(fp)/sizeof(fp[0]);
	int c;
	int result;
	for(c = common->numAst-1;c>=0;c--)
	{
		if((common->ref_ast+c)->size>SIZE-1)
		{
			result = fp[SIZE-1](common->ref_ast+c);
		}
		if((common->ref_ast+c)->size<0)
		{
			result = fp[0](common->ref_ast+c);
		}
		if(((common->ref_ast+c)->size<SIZE) && ((common->ref_ast+c)->size>=0))
		{
			result = fp[(common->ref_ast+c)->size](common->ref_ast+c);
		}
		
		if(result == 0)
		{
			removeAst(common->ref_ast+c,common);
		}
	}
	
}

int fission(struct Asteroids *single)
{
	struct Asteroids phobos;
	struct Asteroids deimos;
	
	if(single->steps == 0)
	{
		fprintf(stderr, "DIAGNOSTIC: Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf) fissions into 4 asteroids.\n", single->ID, (int)(single->size), single->X, single->Y, single->VX, single->VY);
		phobos = *single;
		phobos.size /= 2;
		phobos.steps = 3+(int)(phobos.X+phobos.Y)%8;
		
		deimos = phobos;
		add(&deimos,deimos.ref_uni);

		deimos.VX = -(phobos.VX);
		deimos.VY = -(phobos.VY);
		add(&deimos,deimos.ref_uni);

		deimos.VX = phobos.VY;
		deimos.VY = phobos.VX;
		add(&deimos,deimos.ref_uni);

		deimos.VX = -(phobos.VY);
		deimos.VY = -(phobos.VX);
		add(&deimos,deimos.ref_uni);
		return 0;
		
 	}
	return single->steps;
}

int split(struct Asteroids *single)
{
	struct Asteroids phobos;
	struct Asteroids deimos;
	
	if(single->steps == 0)
	{
		fprintf(stderr, "DIAGNOSTIC: Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf) splits into 2 asteroids.\n",single->ID, (int)(single->size), single->X, single->Y, single->VX, single->VY);
		phobos = *single;
		phobos.size-=1;
		phobos.steps = 3+(int)(phobos.X+phobos.Y)%8;

		deimos = phobos;
		deimos.VX = -(phobos.VY);
		deimos.VY = phobos.VX;
		deimos.X = phobos.X+(deimos.VX)*0.5;
		deimos.Y = phobos.Y+(deimos.VY)*0.5;
		adjustPos(&deimos);
		add(&deimos,deimos.ref_uni);

		deimos.VX = phobos.VY;
		deimos.VY = -(phobos.VX);
		deimos.X = phobos.X+(deimos.VX)*0.5;
		deimos.Y = phobos.Y+(deimos.VY)*0.5;
		adjustPos(&deimos);
		add(&deimos,deimos.ref_uni);

		return 0;
		
	}
	return single->steps;
}


int exhaust(struct Asteroids *single)
{
	struct Asteroids emit = *single;
	int parent_steps= single->steps;
	if(single->steps> 0)
	{
		fprintf(stderr, "DIAGNOSTIC: Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf) emits an asteroid.\n", single->ID, (int)(single->size), single->X, single->Y, single->VX, single->VY);
		
		emit.VX = single->VX*0.25;
		emit.VY = single->VY*0.25;
		emit.steps = single->size*2;
        	emit.size = 0;
		add(&emit, emit.ref_uni);

	}
	if(single->steps == 0)
	{
		fprintf(stderr, "DIAGNOSTIC: Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf) expires.\n",single->ID, (int)(single->size), single->X, single->Y, single->VX, single->VY);
	}
	
	return parent_steps;
}
	

int timeout(struct Asteroids *single)
{
	if(single->steps == 0)
	{
		fprintf(stderr, "DIAGNOSTIC: Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf) expires.\n",single->ID, (int)(single->size), single->X, single->Y, single->VX, single->VY);
	}
	return single->steps;
}

void removeAst(struct Asteroids *single, struct Universe *common)
{
	int inner;
	int c;
	fprintf(stderr,"DIAGNOSTIC: Removing asteroid #%d\n",single->ID);				
	
	for(c = 0;c<(common->numAst);c++)
	{
		if((common->ref_ast+c)->ID==single->ID)
		{
			*(common->ref_ast+c)=*(common->ref_ast+(common->numAst-1));
		}
	}
	common->numAst-=1;
}	

void printFinal(struct Universe *common)
{
	int c;
	fprintf(stderr, " \n");
	fprintf(stderr, "At time ET = %6.3lf \n",common->ET);
	if(GRAPHICS)al_clear();
	for(c = 0; c<(common->numAst);c++)
	{
		fprintf(stderr, "Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf) has %d steps.\n",(common->ref_ast+c)->ID, (common->ref_ast+c)->size, (common->ref_ast+c)->X, (common->ref_ast+c)->Y, (common->ref_ast+c)->VX, (common->ref_ast+c)->VY, (int)(common->ref_ast+c)->steps);
		if(GRAPHICS)al_square((common->ref_ast+c)->X,(common->ref_ast+c)->Y,(int)((common->ref_ast+c)->size));
	}
	if(GRAPHICS){al_refresh();
	sleep(1);}	
}

void freeMem(struct Universe *common)
{
	if(common->ref_ast!=NULL) free(common->ref_ast);
}

void printAll(struct Universe *common)
{
	int c;
	for(c = 0; c<(common->numAst);c++)
	{
		fprintf(stderr, "Asteroid #%d size %d at (%6.3lf, %6.3lf) moving (%+6.3lf, %+6.3lf) has %d steps\n", (common->ref_ast+c)->ID,(int)((common->ref_ast+c)->size),(common->ref_ast+c)->X,(common->ref_ast+c)->Y,(common->ref_ast+c)->VX,(common->ref_ast+c)->VY,(int)((common->ref_ast+c)->steps));
	}
}



		
