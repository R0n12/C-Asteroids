#include <stdio.h>
#include "libasteroids.h"

/* Author: Lang Xu */

/* Calculate new adjuested position in x and y direction */
void newPos(double *oldPosX, double *oldPosY,int lowX, int upperX, int lowY, int upperY);

/* Stimulate and conduct graphic output one step */
void stimulate(double posX,double posY,int size);

/* Calculate one step forward for x and y movement */
void move(double *PosX, double *PosY, double vX, double vY, double time);

/* Print header */
void printH(int *step, int *size);

int main(void){
	int lowX = al_min_X();
	int lowY = al_min_Y();
	int upperX = al_max_X();
	int upperY = al_max_Y();
	int counter;
	int step;
	int size;
	double PosX;
	double PosY;
	double vX;
	double vY;
	double time = 1.0;
	scanf("%d %d %lf %lf %lf %lf",&step,&size,&PosX,&PosY,&vX,&vY);
	printH(&step,&size);
	al_initialize();
	for(counter=0;counter<=step;counter++){	
		newPos(&PosX,&PosY,lowX,upperX,lowY,upperY);
		stimulate(PosX,PosY,size);
		fprintf(stderr,"  %6.3lf  %6.3lf  %+6.3lf  %+6.3lf   %6.3lf\n",PosX,PosY,vX,vY,(float)counter);
		move(&PosX,&PosY,vY,vX,time);				
        }
	al_teardown();
	return 0;
}
	

void newPos(double *oldPosX, double *oldPosY,int lowX, int upperX, int lowY, int upperY)
{
	while(*oldPosX > upperX){
		*oldPosX -= upperX;}
	if(*oldPosX<lowX){
		*oldPosX = upperX-*oldPosX;}
	while(*oldPosY > upperY){
		*oldPosY = *oldPosY-upperY;}
	if(*oldPosY<lowY){
		*oldPosY = upperY-*oldPosY;}
}


void stimulate(double posX,double posY,int size)
{
	
	al_clear();
	al_square(posX,posY,size);
	al_refresh();
	sleep(1);
	
}

void move(double *PosX, double *PosY, double vX, double vY, double time)
{
	*PosX += vX*time;
	*PosY += vY*time;
}

void printH(int *step, int *size)
{
	fprintf(stderr,"Start: %d steps with %d size\n",*step,*size);
	fprintf(stderr,"       X       Y     vX    vY      ET\n");
}











