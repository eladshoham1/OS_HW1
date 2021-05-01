CC = gcc
CFLAGS = -Wall -o

all: versionA versionB versionC child

clean: 
	rm -f versionA versionB versionC child

versionA: versionA.c
	$(CC) $(CFLAGS) versionA versionA.c functions.c
	
versionB: versionB.c
	$(CC) $(CFLAGS) versionB versionB.c functions.c
	
versionC: versionC.c
	$(CC) $(CFLAGS) versionC versionC.c functions.c

child: child.c
	$(CC) $(CFLAGS) child child.c functions.c
