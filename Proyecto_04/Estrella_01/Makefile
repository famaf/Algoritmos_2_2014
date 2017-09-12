CC = gcc
EJECUTABLE = kruskal
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
VALGRINDFLAGS = --leak-check=full --show-reachable=yes
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

kruskal : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EJECUTABLE) $(OBJECTS)

union_find.o : union_find.c union_find.h
	$(CC) $(CFLAGS) -c $< -o $@

stack.o : stack.c stack.h graph.h helpers.h
	$(CC) $(CFLAGS) -c $< -o $@

helpers.o : helpers.c helpers.h
	$(CC) $(CFLAGS) -c $< -o $@    

graph.o : graph.c graph.h helpers.h
	$(CC) $(CFLAGS) -c $< -o $@        

heap.o : heap.c heap.h graph.h
	$(CC) $(CFLAGS) -c $< -o $@        

priority_queue.o : priority_queue.c priority_queue.h heap.h
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY : clean estilo comprimir

estilo :
	python2.7 -m unittest discover -v style_tests/

clean :
	rm -f kruskal $(OBJECTS) *.diff.html grupo25.tar.gz

checkmemory : kruskal
	valgrind $(VALGRINDFLAGS) ./$(EJECUTABLE) < input/test.dot

comprimir :
	tar czvf grupo25.tar.gz main.c union_find.c union_find.h heap.c heap.h stack.c stack.h priority_queue.c priority_queue.h Makefile

