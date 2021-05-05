#include <stdio.h>
#include <string.h>

#include "strlib.h"

char *mygets(char *buf, int len) {
	char *retval = fgets(buf, len, stdin);
	buf[len] = EPSILON;
	
	if (buf[strlen(buf) - 1] == 10)
		buf[strlen(buf) - 1] = EPSILON;
	else if (retval)
		while (getchar() != '\n');
		
	return retval;
}

int strxor(char *str1, char *str2) {
	char retval = EPSILON;
	int len, i;
	
	len = (int)strlen(str1);
	for (i = 0; i < len; i++)
		retval ^= str1[i];
		
	len = (int)strlen(str1);
	for (i = 0; i < len; i++)
		retval ^= str2[i];

	return (int)retval;
}
