#include <stdio.h>

struct Student{
	char name[50];
	char major[35];
	float gpa;
};

int main(){
	struct Student st[20];
	char selection;
	int i, studentCount = 0;
	
	system("color A");
	
	menu:
	system("cls");
	printf("Welcome to simple student database (%d/20)\n", studentCount);
	printf("1. Show all students\n2. Input new students\n3. Exit\n");
	printf("Choose : ");
	fflush(stdin);
	scanf("%c", &selection);
	
	switch(selection){
		case '1':
			printf("\n                                        List of Student Information\n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			printf("|No.|                       Name                       |                 Major             |       GPA      |\n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			if(studentCount == 0){
				printf("|   |                                          Database is empty!                                           |\n");
			}
			for(i = 0; i < studentCount; i++){
				printf("|%-3d|%-50s|%-35s|%-16.2f|\n", i+1, st[i].name, st[i].major, st[i].gpa);
			}
			printf("-------------------------------------------------------------------------------------------------------------\n");
			printf("\nPress any key to continue..");
			getch();
			goto menu;
		case '2':
			if(studentCount >= 20){
				printf("Database is full\n");
				printf("Press any key to continue..");
				getch();
				goto menu;
			}else{
				printf("\n  Insert Student Information  \n");
				printf("------------------------------\n");
				printf("Name\t: "); fflush(stdin); scanf("%[^\n]", &st[studentCount].name);
				printf("Major\t: "); fflush(stdin); scanf("%[^\n]", &st[studentCount].major);
				printf("GPA\t: "); scanf("%f", &st[studentCount].gpa);
				studentCount++;
				printf("Inserting data\nNew students added\nPress any key to continue..");
				getch();
				goto menu;
			}
			
		case '3':
			break;
		default:
			printf("\n");
			goto menu;
	}
	
	return 0;
}

