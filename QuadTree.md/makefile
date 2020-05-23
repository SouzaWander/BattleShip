CFLAGS = -g -Og -Wall

all: main

main: main.o barcos.o tabuleiro.o io.o
	gcc -Wall $^ -o $@

main.o: main.c
	gcc -c $(CFLAGS) $<

barcos.o: barcos.c
	gcc -c $(CFLAGS) $<

tabuleiro.o: tabuleiro.c
	gcc -c $(CFLAGS) $<

io.o: io.c
	gcc -c $(CFLAGS) $<

clean:
	rm *.o main

