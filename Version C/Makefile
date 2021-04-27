all: progFather progChild

clean: 
	rm -f progFather progChild

progFather: father.c
	gcc -o progFather father.c -Wall

progChild: child.c
	gcc -o progChild child.c ../functions.c -Wall
	
