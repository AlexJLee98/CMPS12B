CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = bv.o sieve.o parfait.o

.PHONY: all
all: parfait

parfait: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o parfait

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

sieve.o: sieve.c
	$(CC) $(CFLAGS) -c sieve.c

parfait.o: parfait.c
	$(CC) $(CFLAGS) -c parfait.c


.PHONY: clean
clean:
	rm -f $(OBJECTS) bv sieve parfait


