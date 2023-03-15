#include <stdio.h>

typedef struct{
	char name[50];
	char major[35];
	float gpa;
}Student;

int main(){
	// Penulisan struct di depan dapat dihilangkan.
	Student waldo = {"Waldo", "Informatika", 3.98};
	
	printf("Name\t: %s\n", waldo.name);
	printf("Major\t: %s\n", waldo.major);
	printf("GPA\t: %.2f\n", waldo.gpa);
	
	return 0;
}
