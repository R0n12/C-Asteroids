#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

/* Author: Lang Xu */
void removeAst(struct Asteroids *single, struct Universe *common);

void add(struct Asteroids *single, struct Universe *common);

main()
{
	struct Universe common ={0,0,100,0.0,NULL};
	struct Asteroids single1;
	struct Asteroids single2;
	struct Asteroids single3;
	int c;
	single1.size = 1;
	single1.steps = 1;
	single1.X = 1.0;
	single1.Y = 1.0;
	single1.VX = 1.0;
	single1.VY = 1.0;
	single2.size = 2;
	single2.steps = 2;
	single2.X = 2.0;
	single2.Y = 2.0;
	single2.VX = 2.0;
	single2.VY = 2.0;
	single3.size = 3;
	single3.steps = 3;
	single3.X = 3.0;
	single3.Y = 3.0;
	single3.VX = 3.0;
	single3.VY = 3.0;
	add(&single1,&common);
	add(&single2,&common);
	add(&single3,&common);
	removeAst(&single1,&common);
	
	for(c = 0; c<common.numAst;c++)
	{
		printf("ID:%d,size:%d,steps:%d,X:%lf,Y:%lf,VX:%lf,VY:%lf \n",(common.ref_ast+c)->ID,(common.ref_ast+c)->size,(common.ref_ast+c)->steps,(common.ref_ast+c)->X,(common.ref_ast+c)->Y,(common.ref_ast+c)->VX,(common.ref_ast+c)->VY);
		
	}
	printf("Number of Asteroids: %d \n Length of array: %d\n,common.numAst,common.length);
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
	*(common->ref_ast+(common->numAst-1)) = *single;
	fprintf(stderr,"DIAGNOSTIC: Spawning %d step asteroid #%d of size %d at (%6.3lf, %6.3lf) moving (%+4.3lf, %+4.3lf)\n", (int)(single->steps),single->ID,(int)(single->size),single->X,single->Y,single->VX,single->VY);
}


void removeAst(struct Asteroids *single, struct Universe *common)
{
	int c;
	for(c = 0;c<(common->numAst);c++)
	{
		if((common->ref_ast+c)->ID==single->ID)
		{
			printf("Found\n");
			*(common->ref_ast+c)=*(common->ref_ast+(common->numAst-1));
		}
	}
	common->numAst-=1;				
}	
