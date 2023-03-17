#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Nodes{
	char data[2];
	struct Nodes *next;
}Nodes;

int isEmpty(Nodes *top);
void push(Nodes **top, char data);
void pop(Nodes **top);
int isMatchingPair(Nodes *top, char c);
int checkExpression(char input[]);

int main(){
	char input[100];
	printf("Welcome to stack challenge program. Let's check for valid parentheses expressions. Don't use letters or other symbols in brackets.\n");
	printf("Enter \"-1\" to exit.\n");
	do{
		printf("\n\nEnter expression: "); fflush(stdin); scanf("%[^\n]", input);
		if(checkExpression(input)) printf("Valid parenthesis expression.");
		else if(input == "") printf("Invalid parenthesis expression.");
		else printf("Invalid parenthesis expression.");
	}while(strcmp(input, "-1"));
	return 0;
}

int isEmpty(Nodes *top){
	if(top == NULL) return 1;
	return 0;
}

void push(Nodes **top, char data){
	Nodes *newNode = (Nodes*)malloc(sizeof(Nodes));
	newNode->data[0] = data;
	newNode->next = NULL;
	if(!isEmpty(*top)){		
		newNode->next = *top;
	}
	*top = newNode;
}

void pop(Nodes **top){
	if(isEmpty(*top)){
		printf("Stack is empty."); return;
	}
	Nodes *temp = *top;
	*top = (*top)->next;
	temp->next = NULL;
	free(temp);
}

int isMatchingPair(Nodes *top, char c){
	if(top->data[0] == '(' && c == ')')
		return 1;
	else if(top->data[0] == '{' && c == '}')
		return 1;
	else if(top->data[0] == '[' && c == ']')
		return 1;
	return 0;
}

int checkExpression(char input[]){
	Nodes *top = NULL;
	int i = 0;
	char c;
	while(input[i] != '\0'){
		c = input[i];
		// push when empty or when opening bracket
		if(top == NULL || c == '(' || c == '{' || c == '['){
			push(&top, c);
		}
		// check when closing bracket
		if(c == ')' || c == '}' || c == ']'){
			if(isMatchingPair(top, c)){
				pop(&top);
			}else{
				return 0;
			}
		}
		// if there's anything other than brackets, expression is invalid
		if(!(c == '(' || c == '{' || c == '[' || c == ')' || c == '}' || c == ']'))
			return 0;
		i++;
	}
	return 1;
}

//void printNodes(Nodes *top){
//	Nodes *temp = top;
//	while(temp != NULL){
//		printf("%c -> ", temp->data[0]);
//		temp = temp->next;
//	}
//}
