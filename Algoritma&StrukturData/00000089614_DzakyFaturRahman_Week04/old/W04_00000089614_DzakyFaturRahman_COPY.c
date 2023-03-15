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
void deleteAllData(Mahasiswa *head);
Mahasiswa *deleteFirstData(Mahasiswa *head);

Mahasiswa *deleteByNIM(Mahasiswa *head, Mahasiswa *tail){
	Mahasiswa *temp, *trash;
	int nim;
	
	printf("\nEnter NIM: "); scanf("%d", &nim);
	
	temp = head;
	trash = head;
	printf("\nhead=>%d, temp=>%d, trash=>%d", head->nim, temp->nim, trash->nim);
	do{	
		// After first loop iteration, move temp.
		if(trash != head){
			temp = temp->next;
		// If head is target, skip loop.
		}else if(head->nim == nim){
			continue;
		}
		trash = trash->next;
		printf("\nhead=>%d, temp=>%d, trash=>%d", head->nim, temp->nim, trash->nim);
	}while(trash->nim != nim);
	
	// If head is target and there exists next node, move head to next node.
	if(trash == head && head->next != NULL){
		head = head->next;
	// If head is target, BUT there is no next node, then head returns to NULL.
	}else if(trash == head){
		head = NULL;
	// If there exists a node after trash, then connect node before trash and node after trash.	
	}else if(trash->next != NULL){
		temp->next = trash->next;
	// If target is tail, node before trash has no link and move tail.
	// Note to self: tail = temp; doesn't affects data, but something like tail = temp->next; affects data.
	// Because one is a struct equals another struct, while the other a struct equals a pointer in a struct.
	}else if(trash->next == NULL){
		tail = temp;
		temp->next = NULL;
	}
	trash->next = NULL;
	free(trash);
	
	return tail;
}

int main(){
	Mahasiswa *head, *tail, *node;
	
	head = NULL;
	
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
			if(head == NULL){
				head = node;
				tail = node;
			}else{
				tail->next = node;
				tail = node;
			}
			node->next = NULL;
			pressAny();
			goto mainmenu;
		case '2':
			printLinkedList(head);
			printf("tail=>%d", tail->nim);
			pressAny();
			goto mainmenu;
		case '3':
			deleteAllData(head);
			head = NULL;
			node = NULL;
			tail = NULL;
			pressAny();
			goto mainmenu;
		case '4':
			head = deleteFirstData(head);
			pressAny();
			goto mainmenu;
		case '5':
			tail = deleteByNIM(head, tail);
			pressAny();
			goto mainmenu;
		case '6':
			break;
		default:
			goto mainmenu;
	}
}

void pressAny(){
	printf("\nPress any key to continue..");
	getch();
}

Mahasiswa *createNewNode(){
	char nama[100], jurusan[30];
	int nim;
	
	Mahasiswa *newNode = (Mahasiswa*)malloc(sizeof(Mahasiswa));
	printf("\nInsert new node data:\n");
	printf("NIM \t: "); scanf("%d", &nim);
	printf("Nama \t: "); fflush(stdin); scanf("%[^\n]", nama);
	printf("Jurusan : "); fflush(stdin); scanf("%[^\n]", jurusan);
	
	newNode->nim = nim;
	strcpy(newNode->nama, nama);
	strcpy(newNode->jurusan, jurusan);
	newNode->next = NULL;
	
	return newNode;
}

void printLinkedList(Mahasiswa *head){
	Mahasiswa *temp;
	int i = 1;
	if(head == NULL){
		printf("\nLinked list doesn't exist."); return;
	}
	
	temp = head;
	while(temp != NULL){
		printf("Data ke #%d\n", i);
		printf("NIM \t: %d\n", temp->nim);
		printf("Nama \t: %s\n", temp->nama);
		printf("Jurusan : %s\n\n", temp->jurusan);
		temp = temp->next;
		i++;
	}
}

void deleteAllData(Mahasiswa *head){
	Mahasiswa *temp;
	if(head == NULL){
		printf("\nLinked list doesn't exist."); return;
	}
	
	while(head != NULL){
		temp = head;
		head = head->next;
		temp->next = NULL;
		free(temp);	
	}
}

Mahasiswa *deleteFirstData(Mahasiswa *head){
	Mahasiswa *temp;
	temp = head;
	head = temp->next;
	
	printf("\nNIM: %d, Nama: %s, Jurusan: %s has been deleted.\n", temp->nim, temp->nama, temp->jurusan);
	temp->next = NULL;
	free(temp);
	
	return head;
}

