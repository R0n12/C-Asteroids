#include "libasteroids.h"

main(){
	al_initialize();
	al_clear();
	al_square(1,19,2);
	al_refresh();
	getchar();
	al_teardown();
}

