#include <stdio.h>

/* Author: Lang Xu */

/* Calculate one step forward for x and y movement */
void move(double *PosX, double *PosY, double vX, double vY, double time);


main(){
	double posx = 2.0;
	double posy = 2.0;
	double vX = -1.0;
	double vY = -1.0;
	double time = 1.0;
	move(&posx,&posy,vX,vY,time);
	printf("%lf %lf\n",posx,posy);

}



void move(double *PosX, double *PosY, double vX, double vY, double time)
{
	*PosX += vX*time;
	*PosY += vY*time;
}
