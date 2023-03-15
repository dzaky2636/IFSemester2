#include <stdio.h>
#include <string.h>

void inputkata(int *input, int *len){
	printf("Masukkan kata: ");
	fflush(stdin);
	scanf("%[^\n]", input);
	*len = strlen(input);
}

void upChar(char *input, int len){
	int i;
	for(i = 0; i < len; i++){
		if(input[i] >= 'a' && input[i] <= 'z'){
			printf("%c", input[i] - 32);
		}else{
			printf("%c", input[i]);
		}
	}	
}

void downChar(char *input, int len){
	int i;
	for(i = 0; i < len; i++){
		if(input[i] >= 'A' && input[i] <= 'Z'){
			printf("%c", input[i] + 32);
		}else{
			printf("%c", input[i]);
		}
	}
}

void switchChar(char *input, int len){
	int i;
	for(i = 0; i < strlen(input); i++){
		if(input[i] >= 'a' && input[i] <= 'z'){
			printf("%c", input[i] - 32);
		}else if(input[i] >= 'A' && input[i] <= 'Z'){
			printf("%c", input[i] + 32);
		}else{
			printf("%c", input[i]);
		}
	}
}

int main(){
	char input[1000], selection;
	int i, len;
	
	ulang:
	printf("1. Uppercase\n2. Lowercase\n3. Switching\n4. Keluar\nPilihan: ");
	fflush(stdin);
	scanf("%c", &selection);
	
	switch(selection){
		case '1':
			inputkata(input, &len);
			upChar(input, len);
			break;
		case '2':
			inputkata(input, &len);
			downChar(input, len);
			break;
		case '3':
			inputkata(input, &len);
			switchChar(input, len);
			break;
		case '4':
			break;
		default:
			printf("\n");
			goto ulang;
			
	}
	
}
