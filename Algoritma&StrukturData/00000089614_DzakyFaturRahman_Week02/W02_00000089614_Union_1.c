#include <stdio.h>

union data{
	short number;
	char c[2];	
};

int main(){
	union data d;
	
	d.number = 17479;
	printf("Number\t\t: %d\n", d.number);
	printf("c[1]c[0]\t: %c%c", d.c[1], d.c[0]);
	
	return 0;
}
