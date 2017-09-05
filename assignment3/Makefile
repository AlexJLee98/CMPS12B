CC = gcc
LEX = lex
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = aes.o banhammer.o bf.o bv.o hash.o ll.o lex.yy.o

.PHONY: all
all: banhammer

banhammer: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o banhammer

aes.o: aes.c
	$(CC) $(CFLAGS) -c aes.c

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

hash.o: hash.c
	$(CC) $(CFLAGS) -c hash.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c
    
lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c
    
lex.yy.c: scanner.l
	$(LEX) scanner.l


.PHONY: clean
clean:
	rm -f $(OBJECTS) aes banhammer newspeak bf bv hash ll lex.yy


