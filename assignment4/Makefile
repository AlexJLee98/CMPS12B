CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = queue.o stack.o huffman.o encode.o bv.o
DECODEROBJECTS = queue.o stack.o huffman.o decode.o bv.o

.PHONY: all
all: encode decode

encode: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o encode

decode: $(DECODEROBJECTS)
	$(CC) $(CFLAGS) $(DECODEROBJECTS) $(CLAGS) -o decode

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c    

huffman.o: stack.c
	$(CC) $(CFLAGS) -c huffman.c

.PHONY: clean
clean:
	rm -f $(OBJECTS) queue stack encoder bv huffman
	rm -f $(DECODEROBJECTS) queue stack decoder bv huffman


