#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timespec.h"
#include "linkedlist.h"
#include "updatedStruct.h"
#include "funcPtr.h"
#include "astOp.h"
#include "libasteroids.h"
#define GRAPHICS 1
#define TIME 0.050000001

/* Author: Lang Xu */

int openFiles(char **argv,struct Universe *common);

int readInAndOpen(int argc, char **argv, struct Universe *common);

void initializeAsteroids(struct Universe *common);

void transferToBelt(struct Universe *common);

void printInitials(struct Universe *common);

void drawInitials(struct Universe *common);

void initializeOutput(struct Universe *common);

void outputET(struct Universe *common);

void move(struct Universe *common);

void deleteBelt(struct Universe *common);

void linkedlistOp(struct Universe *common);

void simulation(struct Universe *common);

void closeFiles(struct Universe *common);

void drawAndPrintSim(struct Universe *common);

int main(int argc, char **argv)
{
	struct Universe common = {0,0,100,0.000000000,NULL,NULL,NULL,NULL,NULL};
	if(readInAndOpen(argc,argv,&common))
	{
		if(GRAPHICS)al_initialize();
		initializeAsteroids(&common);
		transferToBelt(&common);
		initializeOutput(&common);
		simulation(&common);
		closeFiles(&common);
		
	}else{
		closeFiles(&common);
		fprintf(stderr,"EXITING: Fail to open all files.\n");
	}	
	return 0;
}

int openFiles(char **argv,struct Universe *common)
{
	int result = 1;
	if(!(common->input = fopen(argv[1],"r"))){fprintf(stderr,"Fail to open input file.\n");result = 0;}else{fprintf(stderr,"Opening input file.\n");}
   
	if(!(common->output = fopen(argv[2],"w"))){fprintf(stderr,"Fail to open output file.\n");result = 0;}else{fprintf(stderr,"Opening output file.\n");}

	if(!(common->diagnostics = fopen(argv[3],"w"))){fprintf(stderr,"Fail to open diagnostics file.\n");result = 0;}else{fprintf(stderr,"Opening diagnostics file.\n");}
	
	return result;
}

int readInAndOpen(int argc, char **argv, struct Universe *common)
{
	int result = 1;
	if(argc!=4)
	{
		fprintf(stderr,"Command Line Arguments: invalid arguments.\n");
		result = 0;
	}else{
		if(!openFiles(argv,common))result = 0;
	}
	return result;	
}

void initializeAsteroids(struct Universe *common)
{
	struct Asteroids single;
	ComparisonFunction compareID = compareAstHold;
	struct Asteroids *astData;
	while(fscanf(common->input,"%d %d %lf %lf %lf %lf",&single.size,&single.steps,&single.X,&single.Y,&single.VX,&single.VY)==6)
	{
		if(astData = allocateAsteroid(&single,common))
		{
			fprintf(common->diagnostics,"Diagnostics: Succeeded allocating Asteroid #%d.\n",single.ID);
			if(!insert(&common->hold,astData,compareID,common->diagnostics)){fprintf(common->diagnostics,"Diagnostics: Fail to initialize node to hold.\n");freeAsteroids(&astData,common);}
		}else{
			fprintf(common->diagnostics,"Diagnostics: Fail to allocate Asteroid.\n");
		}
	}
}

void transferToBelt(struct Universe *common)
{
	ActionFunction insertBelt = insertNodeBelt;
	ActionFunction doNothing = noActionHold;
	CriteriaFunction clearTrue = clearHold;
	traverse(common->hold, insertBelt,common->diagnostics);
	deleteSome(&common->hold,clearTrue,doNothing,common->diagnostics);
}

void printInitials(struct Universe *common)
{
	ActionFunction printNumerical = printOutput;
	traverse(common->belt,printNumerical,common->output);
}

void drawInitials(struct Universe *common)
{
	struct timespec request = {0,50000001},remain = {0,0};
	ActionFunction drawAsteroids = drawCurrent;
	if(GRAPHICS)al_clear();
	traverse(common->belt,drawAsteroids,common->output);
	if(GRAPHICS){al_refresh();nanosleep(&request,&remain);}
}

void initializeOutput(struct Universe *common)
{
	outputET(common);
	printInitials(common);
	drawInitials(common);
}

void drawAndPrint(struct Universe *common)
{
	printInitials(common);
	drawInitials(common);
}

void outputET(struct Universe *common)
{
	fprintf(common->output,"\n");
	fprintf(common->diagnostics,"\n");
	fprintf(common->output,"At time ET = %6.3lf \n",common->ET);
	fprintf(common->diagnostics,"At time ET = %6.3lf \n",common->ET);
}

void move(struct Universe *common)
{
	ActionFunction moveAst = forwardAst;
	traverse(common->belt,moveAst,common->diagnostics);
}

void deleteBelt(struct Universe *common)
{
	CriteriaFunction isStepZero = stepZero;
	ActionFunction freeAst = disposalBelt;
	deleteSome(&common->belt,isStepZero,freeAst,common->diagnostics);	
}

void linkedlistOp(struct Universe *common)
{
	ActionFunction insertBelt = insertNodeBelt;
	ActionFunction doNothing = noActionHold;
	CriteriaFunction clearTrue = clearHold;
	transferToBelt(common);
	deleteSome(&common->hold,clearTrue,doNothing,common->diagnostics);
	deleteBelt(common);
}

void simulation(struct Universe *common)
{
	double currentET = common->ET;
	ActionFunction decrement = decrementSteps;
	ActionFunction specialAst = specials;
	while(common->belt)
	{
		common->ET+=TIME;
		outputET(common);
		move(common);
		if((int)currentET!=(int)common->ET)
		{
			fprintf(common->diagnostics,"Decrementing step counts.\n");
			traverse(common->belt,decrement,common->diagnostics);
			traverse(common->belt,specialAst,common->diagnostics);
			linkedlistOp(common);
		}
		drawAndPrint(common);
	}
	if(GRAPHICS)al_teardown();
}

void closeFiles(struct Universe *common)
{
	if(common->input != NULL) {fclose(common->input); fprintf(stderr,"Closing input file.\n");}
	if(common->output != NULL){fclose(common->output); fprintf(stderr,"Closing output file.\n");}
	if(common->diagnostics != NULL) {fclose(common->diagnostics); fprintf(stderr,"Closing diagnostics file.\n");}
	
}
