CC = gcc
EJECUTABLE = parcialito
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
VALGRINDFLAGS = --leak-check=full --show-reachable=yes
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

parcialito : $(OBJECTS)

bst.o : bst.c bst.h list.h pair.h

list.o : list.c list.h index.h pair.h

pair.o : pair.c pair.h index.h data.h

index.o : index.c index.h

data.o : data.c data.h

.PHONY : clean comprimir checkmemory

clean :
	rm -f parcialito $(OBJECTS) *.tar.gz

checkmemory : parcialito
	valgrind $(VALGRINDFLAGS) ./$(EJECUTABLE)

comprimir :
	tar czvf mario.tar.gz bst.c bst.h parcialito.c Makefile

