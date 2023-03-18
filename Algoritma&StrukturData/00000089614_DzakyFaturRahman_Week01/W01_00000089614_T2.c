#include <stdio.h>

void printMx(int Mx[3][3]){
	int i, j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			printf("%d ", Mx[i][j]);
		}
		printf("\n");
	}
}

void transMx(int (*MxA)[3], int (*MxB)[3]){
	int i, j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			MxA[i][j] = MxB[j][i];
		}
	}
}

void plusMx(int (*MxHasil)[3], int (*MxA)[3], int (*MxB)[3]){
	int i, j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			MxHasil[i][j] = MxA[i][j] + MxB[i][j];
		}
	}
}

void timesMx(int (*MxHasil)[3], int (*MxA)[3], int (*MxB)[3]){
	int i, j, k;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			MxHasil[i][j] = 0;
			for(k = 0; k < 3; k++){
				MxHasil[i][j] += MxA[i][k] * MxB[k][j];
			}
		}
	}
}

int main(){
	int Mx1[3][3], Mx2[3][3], MxHasil[3][3];
	int i, j, k;
	char selection;
	
	printf("Masukkan Matrix Pertama(3 x 3)\n");
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			scanf("%d", &Mx1[i][j]);
		}
	}
	printf("\n");
	printf("Masukkan Matrix Kedua(3 x 3)\n");
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			scanf("%d", &Mx2[i][j]);
		}
	}
	printf("\n");
	
	ulang:
	printf("\n1. Perkalian Dua Buah Matrix\n2. Penjumlahan Dua Buah Matrix\n3. Transpose Dua Buah Matrix\n4. Keluar\n");
	printf("Pilihan: ");
	fflush(stdin);
	scanf("%c", &selection);
	
	switch(selection){
		case '1':
			timesMx(MxHasil, Mx1, Mx2);
			printMx(MxHasil);
			break;
		case '2':
			plusMx(MxHasil, Mx1, Mx2);
			printMx(MxHasil);
			break;
		case '3':
			transMx(MxHasil, Mx1);
			transMx(Mx1, Mx2);
			printf("Hasil transpose Matrix Pertama:\n");
			printMx(MxHasil);
			printf("\n");
			printf("Hasil transpose Matrix Kedua:\n");
			printMx(Mx1);
			break;
		case '4':
			break;
		default:
			printf("\n");
			goto ulang;
	}
}
