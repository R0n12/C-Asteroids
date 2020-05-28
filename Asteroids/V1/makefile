graphicsP1 : graphicsP1.o libasteroids.h
	gcc -o graphicsP1 graphicsP1.o -L. -lasteroids -lncurses

graphicsP1.o: graphicsP1.c libasteroids.h
	gcc -ansi -pedantic -c graphicsP1.c

moveP2 : moveP2.c
	gcc -ansi -pedantic -g -o moveP2 moveP2.c

newPosP3 : newPosP3.c
	gcc -ansi -pedantic -g -o newPosP3 newPosP3.c

headerP4 : headerP4.c
	gcc -ansi -pedantic -g -o headerP4 headerP4.c

Asteroids-1.0 : Asteroids-1.0.o libasteroids.h
	gcc -o Asteroids-1.0 Asteroids-1.0.o -L. -lasteroids -lncurses

Asteroids-1.0.o: Asteroids-1.0.c libasteroids.h
	gcc -ansi -pedantic -c Asteroids-1.0.c

Asteroids-1.0.zip: makefile *.c README_1.0.md
	zip Asteroids-1.0 *.c README_1.0.md makefile
	rm -rf install
	mkdir install
	unzip Asteroids-1.0.zip -d install
	make -C install Asteroids-1.0




