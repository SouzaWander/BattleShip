CFLAGS = -g -Og -Wall


QUAD: mainQ
MAT: mainM

mainQ:  mainQ.o barcos.o QuadTree.o ioQ.o
	gcc -Wall $^ -o $@

mainM: mainM.o barcos.o tabuleiro.o ioM.o
	gcc -Wall $^ -o $@

mainQ.o: main.c
	gcc -DQUAD -c  $(CFLAGS) $< -o mainQ.o

barcos.o: barcos.c
	gcc -DQUAD -c $(CFLAGS) $< 

ioQ.o: io.c
	gcc -DQUAD -c $(CFLAGS) $< -o ioQ.o

mainM.o: main.c
	gcc -DMAT -c  $(CFLAGS) $< -o mainM.o

ioM.o: io.c
	gcc -DMAT -c $(CFLAGS) $< -o ioM.o

tabuleiro.o: tabuleiro.c
	gcc -DMAT -c $(CFLAGS) $<

QuadTree.o: QuadTree.c
	gcc -DQUAD -c $(CFLAGS) $<

cleanQ:
	rm *.o mainQ

cleanM:
	rm *.o mainM

