#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Playlist{
	char singer[30];
	char album[30];
	char title[30];
	int year;
	struct Playlist *next, *prev;
}Playlist;

void pressAny();
void *createNewNode(char *singer, char *album, char *title, int year, Playlist **head, Playlist **tail);
void addNewSong(Playlist **head, Playlist **tail);
void readPlaylistFile(Playlist **head, Playlist **tail);
void printAllSongs(Playlist *head);
void deleteLastSong(Playlist **head, Playlist **tail);
void clearLinkedList(Playlist **head, Playlist **tail);

int main(){
	Playlist *head, *tail, *node;
	head = tail = NULL;
	
	int selection;
	
	mainmenu:
	system("cls");
	printf("Selamat datang pada menu playlist! Pilih:\n");
	printf("1. Tampilkan semua lagu\n2. Tambah lagu\n");
	printf("3. Hapus lagu terakhir\n4. Keluar\nPilih: ");
	scanf("%d", &selection);
	
	switch(selection){
		case 1:
			readPlaylistFile(&head, &tail);
			printAllSongs(head);
			pressAny(); goto mainmenu;
		case 2:
			addNewSong(&head, &tail);
			pressAny(); goto mainmenu;
		case 3:
			deleteLastSong(&head, &tail);
			pressAny(); goto mainmenu;
		case 4: 
			// if list exists, free memory
			if(head != NULL){
				clearLinkedList(&head, &tail);
			}
			break;
		default: goto mainmenu;
	}
	return 0;
}

void pressAny(){
	printf("\nPress any key to continue..");
	getch();
}

void *createNewNode(char *singer, char *album, char *title, int year, Playlist **head, Playlist **tail){
	Playlist *newNode = (Playlist*)malloc(sizeof(Playlist));
	strcpy(newNode->singer, singer);
	strcpy(newNode->album, album);
	strcpy(newNode->title, title);
	newNode->year = year;
	newNode->next = NULL;
	if((*head) == NULL){
		*head = *tail = newNode;
	}else{
		newNode->prev = *tail;
		(*tail)->next = newNode;
		*tail = newNode;
	}
}

void addNewSong(Playlist **head, Playlist **tail){
	char singer[30], album[30], title[30];
	int year;
	
	printf("\nTambah lagu baru:\n");
	printf("----------------------\n");
	printf("Input Singer   : "); fflush(stdin); scanf("%[^\n]", singer);
	printf("Album          : "); fflush(stdin); scanf("%[^\n]", album);
	printf("Title          : "); fflush(stdin); scanf("%[^\n]", title);
	printf("Released Year  : "); scanf("%d", &year);
	
	createNewNode(singer, album, title, year, head, tail);
	
	FILE *fout = fopen("playlist.txt", "a");
	fprintf(fout, "%s*%s*%s*%d\n", singer, album, title, year);
	fclose(fout);
	
	printf("Data berhasil ditambahkan!");
}

void readPlaylistFile(Playlist **head, Playlist **tail){
	// if playlist.txt not found
	if(fopen("playlist.txt", "r") == NULL){
		FILE *fout = fopen("playlist.txt", "w");
		fprintf(fout, "");
		fclose(fout);
		
		printf("\nplaylist.txt doesn't exist.. Creating anew..\n");
		sleep(1);
	}
	
	// If list exists, clear linked list
	clearLinkedList(head, tail);
	
	FILE *fin = fopen("playlist.txt", "r");
	long int savePos = ftell(fin); 				// save position for start of file
	fseek(fin, 0, SEEK_END);					// tell file pointer to go to end
	int fileSize = ftell(fin);					// from pointer location, we can tell file size
	if(fileSize != 0){							// if file is empty, skip scanning
		fseek(fin, savePos, SEEK_SET);			// set file pointer to go back to start of file using save position
		while(!feof(fin)){
			Playlist newSong;
			fscanf(fin, "%[^*]*%[^*]*%[^*]*%d\n", newSong.singer, newSong.album, newSong.title, &newSong.year);
			createNewNode(newSong.singer, newSong.album, newSong.title, newSong.year, head, tail);
		}
	}
	fclose(fin);
}

void printAllSongs(Playlist *head){
	Playlist *temp;
	if(head == NULL){
		printf("Playlist empty."); return;
	}else{
		temp = head;
		printf("\nSinger                         Album                          Song Title                     Year\n");
		while(temp != NULL){
			printf("%-30s %-30s %-30s %-5d\n", temp->singer, temp->album, temp->title, temp->year);
			temp = temp->next;
		}
	}
}

void deleteLastSong(Playlist **head, Playlist **tail){
	readPlaylistFile(head, tail);
	
	if((*head) == NULL){
		printf("Playlist empty."); return;
	}else{
		char selection;
		printf("\nDELETE THIS SONG DATA? ARE YOU SURE? Y/N");
		printf("\nSinger                         Album                          Song Title                     Year\n");
		printf("%-30s %-30s %-30s %-5d\n", (*tail)->singer, (*tail)->album, (*tail)->title, (*tail)->year);
		
		do{
			fflush(stdin); scanf("%c", &selection);
		}while(selection != 'Y' && selection != 'N' && selection != 'y' && selection != 'n');
		
		if(selection == 'N' || selection == 'n'){
			printf("\nCancelled deletion.\n"); return;
		}else{
			printf("\n\nLagu %s oleh %s berhasil di hapus", (*tail)->title, (*tail)->singer);
			
			// delete in list
			Playlist *trash = *tail;
			*tail = trash->prev;
			(*tail)->next = NULL;
			trash->prev = NULL;
			free(trash);
			
			// update file
			FILE *fout = fopen("playlist.txt", "w");
			Playlist *temp;
			temp = *head;
			while(temp != NULL){
				fprintf(fout, "%s*%s*%s*%d\n", temp->singer, temp->album, temp->title, temp->year);
				temp = temp->next;
			}
			fclose(fout);
		}
	}
}

void clearLinkedList(Playlist **head, Playlist **tail){
	if((*head) != NULL){
		Playlist *temp;
		while((*head) != NULL){
			temp = *head;
			*head = (*head)->next;
			temp->prev = temp->next = NULL;
			free(temp);
		}
		*head = NULL;
		*tail = NULL;
	}
}
