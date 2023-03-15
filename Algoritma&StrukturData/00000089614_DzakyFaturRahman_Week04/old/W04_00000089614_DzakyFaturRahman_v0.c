#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Mahasiswa{
	char nama[100];
	char jurusan[30];
	int nim;
	struct Mahasiswa *next;
}Mahasiswa;

void pressAny();
Mahasiswa *createNewNode();
void printLinkedList(Mahasiswa *head);
void deleteAllData(Mahasiswa *head, Mahasiswa *node);
Mahasiswa *deleteFirstData(Mahasiswa *head);
Mahasiswa *deleteByNIM(Mahasiswa *head, Mahasiswa *tail);

int main(){
	Mahasiswa *head, *node, *tail;
	
	restart:
	head = NULL;
	node = (Mahasiswa*) malloc(sizeof(Mahasiswa));
	tail = node;
	
	char selection;
	
	mainmenu:
	system("cls");
	printf("Selamat datang dalam menu Linked List.\n");
	printf("1. Insert New Node\n2. Print Linked List\n3. Delete all data\n");
	printf("4. Delete first data\n5. Delete data by NIM\n6. Keluar\nPilih: ");
	scanf("%c", &selection);
	
	switch(selection){
		case '1':
			node = createNewNode();
			tail->next = node;
			tail = node;
			if(head == NULL){
				head = node;
			}
			pressAny();
			goto mainmenu;
		case '2':
			print:
			printLinkedList(head);
			printf("head: %d tail: %d", head->nim, tail->nim);
			pressAny();
			goto mainmenu;
		case '3':
			deleteAllData(head, node);
			pressAny();
			goto restart;
		case '4':
			head = deleteFirstData(head);
			pressAny();
			goto mainmenu;
		case '5':
			head = deleteByNIM(head, tail);
			printf("tail = %d", tail->nim);
			
			pressAny();
			if(head == NULL){
				goto restart;
			}
			goto mainmenu;
		case '6':
			break;
		default:
			goto mainmenu;
	}
	return 0;
}

void pressAny(){
	printf("\nPress any key to continue..");
	getch();
}

Mahasiswa *createNewNode(){	
	int nim;
	char nama[100], jurusan[30];

	Mahasiswa *newNode = (Mahasiswa*) malloc(sizeof(Mahasiswa));
	printf("Insert new node data:\n");
	printf("NIM\t: "); scanf("%d", &nim);
	printf("Nama\t: "); fflush(stdin); scanf("%[^\n]", &nama);
	printf("Jurusan\t: "); fflush(stdin); scanf("%[^\n]", &jurusan);
	newNode->nim = nim;
	strcpy(newNode->nama, nama);
	strcpy(newNode->jurusan, jurusan);
	newNode->next = NULL;
	return newNode;
}

void printLinkedList(Mahasiswa *head){
	if(head == NULL){
		printf("Linked list doesn't exist.");
		return;
	}
	
	Mahasiswa *temp;
	temp = head; 
	int i = 1;
	while(temp != NULL){
		printf("Data ke %d\n", i);
		printf("NIM\t: %d\n", temp->nim);
		printf("Nama\t: %s\n", temp->nama);
		printf("Jurusan : %s\n\n", temp->jurusan);
		temp = temp->next;
		i++;
	}
}

void deleteAllData(Mahasiswa *head, Mahasiswa *node){
	if(head == NULL){
		printf("Linked list doesn't exist.");
		return;
	}
	
	while(head != NULL){
		node = head;
		head = head->next;
		free(node);
	}
}

Mahasiswa *deleteFirstData(Mahasiswa *head){
	if(head == NULL){
		printf("Linked list doesn't exist.");
		return head;
	}
	
	Mahasiswa *trash;
	trash = head;
	head = head->next;
	free(trash);
	
	return head;
}

Mahasiswa *deleteByNIM(Mahasiswa *head, Mahasiswa *tail){
	if(head == NULL){
		printf("Linked list doesn't exist.");
		return head;
	}
	
	int nim;
	printf("Insert NIM: "); fflush(stdin); scanf("%d", &nim);
	
	Mahasiswa *trash, *temp;
	trash = head;
	
	if(head->nim == nim){
		trash = head;
		head = head->next;
		free(trash);
		return head;
	}else{
		if(head->next == NULL){
			printf("NIM not found.");
			return head;
		}
		while(trash->next->nim != nim){
			trash = trash->next;
			
			if(trash->next == NULL){
				printf("NIM not found.");
				return head;
			}
		}
	}
	temp = trash;
	trash = trash->next;
	if(trash->next != NULL){
		temp->next = trash->next;
	}else{
		temp->next = NULL;
	}
	
	trash->next = NULL;
	free(trash);
	
	return head;
}


