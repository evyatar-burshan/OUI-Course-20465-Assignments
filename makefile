mat: mainmat.o mymat.o
	gcc -ansi -pedantic -Wall mainmat.o mymat.o -o mainmat
mainmat.o: mainmat.c mymat.h
	gcc -ansi -pedantic -Wall -c mainmat.c
mymat.o: mymat.c mymat.h
	gcc -ansi -pedantic -Wall -c mymat.c
	
