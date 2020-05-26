CFLAGS = -g -Og -Wall

all: main

main: main.o barcos.o tabuleiro.o QuadTree.o io.o
	gcc -Wall $^ -o $@

main.o: main.c
	gcc -DQUAD -c  $(CFLAGS) $<

barcos.o: barcos.c
	gcc -DQUAD -c $(CFLAGS) $<

tabuleiro.o: tabuleiro.c
	gcc -DQUAD -c $(CFLAGS) $<

QuadTree.o: QuadTree.c
	gcc -DQUAD -c $(CFLAGS) $<

io.o: io.c
	gcc -DQUAD -c $(CFLAGS) $<

clean:
	rm *.o main

