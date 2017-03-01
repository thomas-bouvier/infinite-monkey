CC=gcc
CFLAGS=-Wall
LDFLAGS=-lm

main: main.o simulation.o dna.o
	$(CC) $^ $(LDFLAGS) -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $<

simulation.o: simulation.c simulation.h
	$(CC) $(CFLAGS) -c $<

dna.o: dna.c dna.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f main
