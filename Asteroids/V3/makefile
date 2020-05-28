functionPtr: functionPtr.c linkedlist.h
	gcc -ansi -pedantic -g -o functionPtr functionPtr.c

listTraverse: listTraverse.c linkedlist.h
	gcc -ansi -pedantic -g -o listTraverse listTraverse.c

listInsert: listInsert.c linkedlist.h
	gcc -ansi -pedantic -g -o listInsert listInsert.c

listDelete: listDelete.c linkedlist.h
	gcc -ansi -pedantic -g -o listDelete listDelete.c

funcPtr.o: funcPtr.c funcPtr.h timespec.h linkedlist.h updatedStruct.h astOp.h libasteroids.h
	gcc -ansi -pedantic -g -c funcPtr.c

astOp.o: astOp.c astOp.h linkedlist.h updatedStruct.h libasteroids.h
	gcc -g -ansi -pedantic -c astOp.c

linkedlist.o: linkedlist.c linkedlist.h updatedStruct.h
	gcc -g -ansi -pedantic -c linkedlist.c

lab4.o: lab4.c astOp.h funcPtr.h linkedlist.h timespec.h updatedStruct.h libasteroids.h 
	gcc -g -ansi -pedantic -c lab4.c

lab4:lab4.o linkedlist.o funcPtr.o astOp.o 
	gcc -g -o lab4 lab4.o linkedlist.o funcPtr.o astOp.o -L. -lasteroids -lncurses

lab4.zip: makefile *.c *.h README_LAB4
	zip lab4 *.c *.h README_LAB4 makefile
	rm -rf install
	mkdir install
	unzip lab4.zip -d install
	make -C install lab4

