CC = gcc
CFLAGS = -Wall -o

all: A B C argsxorstr xorstr

clean: 
	rm -f A B C argsxorstr xorstr

A: A.c
	$(CC) $(CFLAGS) A A.c strlib.c
	
B: B.c
	$(CC) $(CFLAGS) B B.c strlib.c
	
C: C.c
	$(CC) $(CFLAGS) C C.c strlib.c

argsxorstr: argsxorstr.c
	$(CC) $(CFLAGS) argsxorstr argsxorstr.c strlib.c
	
xorstr: xorstr.c
	$(CC) $(CFLAGS) xorstr xorstr.c strlib.c
