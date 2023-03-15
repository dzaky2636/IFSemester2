#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Mahasiswa{
	char nama[100];
	char jurusan[30];
	int nim;
	struct Mahasiswa *next, *prev;
}Mahasiswa;

void *createNewNode(int nim, char *nama, char *jurusan, Mahasiswa **tail);
void headDeletion(Mahasiswa **head);
void tailDeletion(Mahasiswa **tail);
void middleDeletion(Mahasiswa **head, int target);
void printLinkedList(Mahasiswa *head);

int main(){
	Mahasiswa *head, *node, *tail;
	head = tail = NULL;
	
	node = (Mahasiswa*)malloc(sizeof(Mahasiswa));
	node->nim = 14026;
	strcpy(node->nama, "James Christian Wira");
	strcpy(node->jurusan, "Informatika");
	
	node->next = node->prev = NULL;
	head = node;
	tail = node;
	
	node = (Mahasiswa*)malloc(sizeof(Mahasiswa));
	node->nim = 17492;
	strcpy(node->nama, "Matthew Evans");
	strcpy(node->jurusan, "Informatika");
	node->next = NULL;
	
	node->prev = tail;
	tail->next = node;
	tail = node;
	
	createNewNode(13633, "Justin Susanto", "Informatika", &tail);
	createNewNode(12335, "Vionie Leorensa", "Informatika", &tail);
	createNewNode(14045, "Mario Alexander", "Informatika", &tail);
	createNewNode(11440, "Leonaro Pratama", "Informatika", &tail);
	createNewNode(15840, "Handriki Kasa", "Informatika", &tail);
	createNewNode(15773, "CIndy Michelle", "Informatika", &tail);
	createNewNode(19587, "Aldric Leonardo", "Informatika", &tail);
	
	printf("All data inside linked list\n");
	printLinkedList(head);
	
	printf("\nAll data after 2x head deletion\n");
	headDeletion(&head);
	headDeletion(&head);
	printLinkedList(head);
	
	printf("\nAll data after 1x tail deletion\n");
	tailDeletion(&tail);
	printLinkedList(head);
	
	printf("\nAll data after middle deletion (Mario Alexander - 14045)\n");
	middleDeletion(&head, 14045);
	printLinkedList(head);
	
	return 0;
}

void *createNewNode(int nim, char *nama, char *jurusan, Mahasiswa **tail){
	Mahasiswa *newNode = (Mahasiswa*)malloc(sizeof(Mahasiswa));
	newNode->nim = nim;
	strcpy(newNode->nama, nama);
	strcpy(newNode->jurusan, jurusan);
	newNode->next = NULL;
	
	newNode->prev = *tail;
	(*tail)->next = newNode;
	*tail = newNode;
}

void headDeletion(Mahasiswa **head){
	Mahasiswa *trash = *head;
	*head = trash->next;
	(*head)->prev = NULL;
	trash->next = NULL;
	free(trash);
}

void tailDeletion(Mahasiswa **tail){
	Mahasiswa *trash = *tail;
	*tail = trash->prev;
	(*tail)->next = NULL;
	trash->prev = NULL;
	free(trash);
}

void middleDeletion(Mahasiswa **head, int target){
	Mahasiswa *trash = *head, *tempBefore, *tempAfter;
	while(trash->nim != target){
		trash = trash->next;
	}
	tempBefore = trash->prev;
	tempAfter = trash->next;
	
	tempBefore->next = tempAfter;
	tempAfter->prev = tempBefore;
	
	trash->prev = NULL;
	trash->next = NULL;
	free(trash);
}

void printLinkedList(Mahasiswa *head){
	Mahasiswa *temp;
	temp = head;
	int i = 1;
	while(temp != NULL){
		printf("Data ke %d\n", i);
		printf("NIM \t: %d\n", temp->nim);
		printf("Nama \t: %s\n", temp->nama);
		printf("Jurusan : %d\n", temp->jurusan);
		temp = temp->next;
		i++;
	}
}
