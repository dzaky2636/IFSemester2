#include <stdio.h>

typedef struct{
	char name[50];
	char position[20];
	int dateJoined;
	int workDuration;
	int salary;
}Employee;

int main(){
	int i = 0;
	Employee employees[3];
	
	FILE *fp = fopen("data.txt", "r");
	while(!feof(fp)){
		Employee newEmp;
		fscanf(fp, "%[^#]#%[^#]#%d#%d#%d\n", newEmp.name, newEmp.position,
			&newEmp.dateJoined, &newEmp.salary, &newEmp.workDuration);
		employees[i] = newEmp;
		i++;
	}
	fclose(fp);
	
	for(i = 0; i < 3; i++){
		printf("Employee #%d\n", i + 1);
		printf("Name\t\t: %s\n", employees[i].name);
		printf("Position\t: %s\n", employees[i].position);
		printf("Date Joined\t: %d\n", employees[i].dateJoined);
		printf("Work Duration\t: %d\n", employees[i].workDuration);
		printf("Salary\t\t: Rp.%d\n", employees[i].salary);
		printf("\n");
	}
	
	// Comment or something.
	FILE *fout = fopen("output.txt", "w");
	for(i = 0; i < 3; i++){
		fprintf(fout, "%s#%s$%d#%d#%d\n", employees[i].name, employees[i].position, 
			employees[i].dateJoined, employees[i].workDuration, employees[i].salary);
	}
	fclose(fout);
	
	return 0;
}
