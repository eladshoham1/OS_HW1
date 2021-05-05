CC = gcc
CFLAGS = -Wall -o

all: versionA versionB versionC argsxorstr xorstr

clean: 
	rm -f versionA versionB versionC argsxorstr xorstr

versionA: versionA.c
	$(CC) $(CFLAGS) versionA versionA.c strlib.c
	
versionB: versionB.c
	$(CC) $(CFLAGS) versionB versionB.c strlib.c
	
versionC: versionC.c
	$(CC) $(CFLAGS) versionC versionC.c strlib.c

argsxorstr: argsxorstr.c
	$(CC) $(CFLAGS) argsxorstr argsxorstr.c strlib.c
	
xorstr: xorstr.c
	$(CC) $(CFLAGS) xorstr xorstr.c strlib.c
