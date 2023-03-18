#include <stdio.h>

union val{
	int a, b;
};

int main(){
	union val value;
	value.a = 5;
	value.b = 10;
	printf("%d", value.a);
}
