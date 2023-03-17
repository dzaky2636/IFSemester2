#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Numbers{
	int num;
	struct Numbers *next;
}Numbers;

void pressAny();
int isEmpty(Numbers *front);
void enqueue(Numbers **front, Numbers **rear, int num);
void dequeue(Numbers **front);
void viewQueue(Numbers *front);
void inputNumbers(Numbers **front, Numbers **rear);
void clearQueue(Numbers **front);

int main(){
	int selection;
	Numbers *front, *rear;
	front = rear = NULL;

	mainmenu:
	system("cls");
	printf("Welcome to queue challenge program. You'll input a number (n). Here are the rules:\n");
	printf("1.) When queue == empty, queue the number n, n times.\n");
	printf("2.) When queue != empty: If n < front, dequeue n times. If n >= front, do number 1.\n");
	printf("3.) Number must be n > 0\n\n");
	
	if(front != NULL){
		viewQueue(front);
		printf("\n\tFRONT => %d\n\n", front->num);
	}
	printf("Menu:\n1. Enter number\n2. Clear queue\n3. Exit\nSelect: ");
	scanf("%d", &selection);
	
	switch(selection){
		case 1: inputNumbers(&front, &rear); pressAny(); goto mainmenu;
		case 2: clearQueue(&front); goto mainmenu;
		case 3: clearQueue(&front); break;
		default: goto mainmenu;
	}
	return 0;
}


void pressAny(){
	printf("\n\nPress any key to continue..");
	getch();
}

int isEmpty(Numbers *front){
	if(front == NULL) return 1;
	return 0;
}

void inputNumbers(Numbers **front, Numbers **rear){
	int num, i;
	printf("Input number: "); scanf("%d", &num);
	if(num <= 0){
		printf("Enter a valid number."); return;
	}
	
	// if queue is empty
	if((*front) == NULL){
		for(i = 0; i < num; i++){	
			enqueue(front, rear, num);
		}
		printf("Enqueuing number %d, %dx times...", num, num);
	}else{
		if(num < (*front)->num){
			for(i = 0; i < num; i++){
				if(isEmpty(*front)){
					printf("\nStopped dequeue because queue is empty.\n");
					break;
				}
				dequeue(front);
			}
			printf("Dequeued %dx times...", i);
		}else{
			for(i = 0; i < num; i++){
				enqueue(front, rear, num);
			}
			printf("Enqueuing number %d, %dx times...", num, num);
		}
	}	
}

void enqueue(Numbers **front, Numbers **rear, int num){
	Numbers *newNode = (Numbers*)malloc(sizeof(Numbers));
	newNode->num = num;
	newNode->next = NULL;
	if(*front == NULL){
		*front = newNode;
	}else{
		(*rear)->next = newNode;
	}
	*rear = newNode;
}

void dequeue(Numbers **front){
	if(isEmpty(*front)) return;
	Numbers *temp = *front;
	*front = (*front)->next;
	temp->next = NULL;
	free(temp);
}

void viewQueue(Numbers *front){
	if(isEmpty(front)) return;
	Numbers *temp = front;
	printf("\t");
	while(temp != NULL){
		printf("%d ", temp->num);
		if(temp->next != NULL) printf("<- ");
		temp = temp->next;
	}
}

void clearQueue(Numbers **front){
	Numbers *temp = *front;
	while((*front) != NULL){
		temp = *front;
		*front = (*front)->next;
		temp->next = NULL;
		free(temp);
	}
}
