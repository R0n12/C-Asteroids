reallocP1: reallocP1.c struct.h
	gcc -ansi -pedantic -g -o reallocP1 reallocP1.c

removeP2: removeP2.c struct.h
	gcc -ansi -pedantic -g -o removeP2 removeP2.c

readinP3: readinP3.c struct.h
	gcc -ansi -pedantic -g -o readinP3 readinP3.c

addP4: addP4.c struct.h
	gcc -ansi -pedantic -g -o addP4 addP4.c

lab3 : lab3.o libasteroids.h struct.h fancy.h
	gcc -g -o lab3 lab3.o -L. -lasteroids -lncurses

lab3.o: lab3.c libasteroids.h struct.h fancy.h
	gcc -g -ansi -pedantic -c lab3.c

lab3.zip: makefile *.c *.h README_LAB3
	zip lab3 *.c *.h README_LAB3 makefile
	rm -rf install
	mkdir install
	unzip lab3.zip -d install
	make -C install lab3
