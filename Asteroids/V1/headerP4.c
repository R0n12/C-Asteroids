#include <stdio.h>

/* Author: Lang Xu */

/* Print header */
void printH(int *step, int *size);

main(){
	int step = 5;
	int size = 4;
	printH(step,size);
}

void printH(int *step, int *size)
{
	fprintf(stderr,"Start: %d steps with %d size\n",*step,*size);
	fprintf(stderr,"       X       Y     vX    vY      ET\n");
}
