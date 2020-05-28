#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

/* Author: Lang Xu */
void add(struct Asteroids *single, struct Universe *common);

void copyAst(struct Asteroids *copy, struct Asteroids single);


main(){
	struct Universe common ={0,0,100,0.0,NULL};
	struct Asteroids single;
	single.size = 0;
	single.steps = 2;
	single.X = 2.0;
	single.Y = 2.0;
	single.VX = 2.0;
	single.VY = 2.0;
	add(&single,&common);
}

void add(struct Asteroids *single, struct Universe *common)
{
	struct Asteroids *new_mem;
	(common->numAst)+=1;
	
	if((common->numAst)>=(common->length))
	{
		if(new_mem = realloc(common->ref_ast,(common->numAst+4)*sizeof(struct Asteroids)))
		{
			common->ref_ast = new_mem;
			common->length+=4;
			fprintf(stderr,"DIAGNOSTIC: Increasing size of the asteroid array by 4\n");
		}else{
			
		}

	}
	single->ref_uni = common;
	single->ID = ++(common->lastID);
	copyAst(common->ref_ast+(common->numAst-1),*single);
	fprintf(stderr,"DIAGNOSTIC: Spawning %d step asteroid #%d of size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf)\n", (int)(single->steps),single->ID,(int)(single->size),single->X,single->Y,single->VX,single->VY);
}

void copyAst(struct Asteroids *copy, struct Asteroids single)
{
	copy->ID = single.ID;
	copy->size = single.size;
	copy->steps = single.steps;
	copy->X = single.X;
	copy->Y = single.Y;
	copy->VX = single.VX;
	copy->VY = single.VY;
	copy->ref_uni = single.ref_uni;
}
