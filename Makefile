CC = gcc
CFLAGS = -Wall -o

all: verA verB verC argsxorstr xorstr

clean: 
	rm -f verA verB verC argsxorstr xorstr

verA: verA.c
	$(CC) $(CFLAGS) verA verA.c strlib.c
	
verB: verB.c
	$(CC) $(CFLAGS) verB verB.c strlib.c
	
verC: verC.c
	$(CC) $(CFLAGS) verC verC.c strlib.c

argsxorstr: argsxorstr.c
	$(CC) $(CFLAGS) argsxorstr argsxorstr.c strlib.c
	
xorstr: xorstr.c
	$(CC) $(CFLAGS) xorstr xorstr.c strlib.c
