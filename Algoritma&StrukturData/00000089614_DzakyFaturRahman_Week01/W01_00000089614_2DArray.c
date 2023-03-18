#include <stdio.h>

void printArray(int arr[][3]){
	int row, col;
	
	printf("Isi dari array:\n");
	for(row = 0; row < 3; row++){
		for(col = 0; col < 3; col++){
			printf("%d", arr[row][col]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(){
	int randomNumbers[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	
	printArray(randomNumbers);
	
	return 0;
}
