#include <stdio.h>

/* Author: Lang Xu */

/* Calculate new adjuested position in x and y direction */
void newPos(double *oldPosX, double *oldPosY,int lowX, int upperX, int lowY, int upperY);

main(){

	int lowX = 3;
	int lowY = 3;
	int upperX = 78;
	int upperY = 19;
	double posx = 34.5;
	double posy = 23.6;
	newPos(&posx,&posy,lowX,upperX,lowY,upperY);
	printf("%lf  %lf\n",posx,posy);

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
