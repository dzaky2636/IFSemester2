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

int main(){
	Mahasiswa *head, *tail, *node;
	
	// Below is used in case 5.
	Mahasiswa *temp, *trash;
	int nim;
	
	head = NULL;
	
	int selection;
	
	mainmenu:
	system("cls");
	printf("Selamat datang dalam menu Linked List.\n");
	printf("1. Insert New Node\n2. Print Linked List\n3. Delete all data\n");
	printf("4. Delete first data\n5. Delete data by NIM\n6. Keluar\nPilih: ");
	scanf("%d", &selection);
	
	switch(selection){
		case 1:
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
		case 2:
			printLinkedList(head);
			pressAny();
			goto mainmenu;
		case 3:
			deleteAllData(head);
			head = NULL;
			node = NULL;
			tail = NULL;
			pressAny();
			goto mainmenu;
		case 4:
			head = deleteFirstData(head);
			pressAny();
			goto mainmenu;
		case 5:
			// Wanted to put this into a function, but we would have to return two variables (and that's currently impossible with my current knowledge.)
			// Elaboration? So, for this to work we need to return both what head and tail points to. And right now, I don't know if there's a way to
			// change what either head or node points to without needing to return it. 
			
			if(head == NULL){
				printf("Linked list doesn't exist."); 
				pressAny();
				goto mainmenu;
			}
			
			printf("\nEnter NIM: "); scanf("%d", &nim);
			
			temp = head;
			trash = head;	
			
			do{	
				// If head is target, skip loop.
				if(head->nim == nim){
					continue;
				}else if(trash->next == NULL || (head->next == NULL && nim != head->nim)){
					printf("NIM not found."); 
					pressAny();
					goto mainmenu;
				}

				// After first loop iteration, move temp.
				if(trash != head){
					temp = temp->next;
				}
				
				trash = trash->next;	
			}while(trash->nim != nim && trash != NULL);
		
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
			// Note to self: tail = temp; is only local to function, but something like tail = temp->next; affects main().
			// Because one is a struct equals another struct, while the other a struct equals a data in a struct.
			}else if(trash->next == NULL){
				tail = temp;
				temp->next = NULL;
			}
			trash->next = NULL;
			free(trash);
			
			pressAny();
			goto mainmenu;
		case 6:
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

