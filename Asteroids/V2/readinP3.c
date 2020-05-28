#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

/* Author: Lang Xu */
void add(struct Asteroids *single, struct Universe *common);

void readin(struct Universe *common);

main()
{
	struct Universe common ={0,0,100,0.0,NULL};
	int c;
	readin(&common);
	for(c = 0; c<common.numAst;c++)
	{
		printf("ID:%d,size:%d,steps:%d,X:%lf,Y:%lf,VX:%lf,VY:%lf \n",(common.ref_ast+c)->ID,(common.ref_ast+c)->size,(common.ref_ast+c)->steps,(common.ref_ast+c)->X,(common.ref_ast+c)->Y,(common.ref_ast+c)->VX,(common.ref_ast+c)->VY);
		
	}
	
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

void readin(struct Universe *common)
{
	struct Asteroids single;
	while(scanf("%d %d %lf %lf %lf %lf",&single.size,&single.steps,&single.X,&single.Y,&single.VX,&single.VY)==6)
	{
		add(&single,common);
	}
}
