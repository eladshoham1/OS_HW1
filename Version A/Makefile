all: progParent progChild

clean: 
	rm -f progParent progChild

progParent: parent.c
	gcc -o progParent parent.c ../functions.c

progChild: child.c
	gcc -o progChild child.c ../functions.c
	
