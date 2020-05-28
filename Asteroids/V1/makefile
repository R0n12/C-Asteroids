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

lab2 : lab2.o libasteroids.h
	gcc -o lab2 lab2.o -L. -lasteroids -lncurses

lab2.o: lab2.c libasteroids.h
	gcc -ansi -pedantic -c lab2.c

lab2.zip: makefile *.c README_LAB2
	zip lab2 *.c README_LAB2 makefile
	rm -rf install
	mkdir install
	unzip lab2.zip -d install
	make -C install lab2




