#include <stdio.h>

int main(){
	int randNum[] = {10, 24, 234, 345, 234};
	
	printf("randomNumber = %p\n", randNum);
	printf("&randomNumber = %p\n", &randNum);
	printf("&randomNumber[0] = %p\n\n", &randNum[0]);
	
	printf("randomNumber = %d\n", randNum[0]);
	printf("*randomNumber = %d\n\n", *randNum);
	
	printf("randomNumber[2] = %d\n", randNum[2]);
	printf("*(randomNumber + 2) = %d\n\n", *(randNum + 2));
	
	printf("&randomNumber[2] = %p\n", &randNum[2]);
	
	return 0;
}
