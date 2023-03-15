#include <stdio.h>
#include <string.h>

typedef struct{
	char nim[16];
	char nama[50];
	char jurusan[40];
}MahasiswaDB;

typedef struct{
	char nim[16];
	float tugas;
	float uts;
	float uas;
	float nilai_akhir;
	char grade[3];
}NilaiDB;

int readDataMahasiswa(MahasiswaDB *mahasiswa);
int readDataNilai(NilaiDB *nilai);
void insertMahasiswa(MahasiswaDB *mahasiswa, NilaiDB *nilai, int mahasiswaCount, int nilaiCount);
void printAllMahasiswa(MahasiswaDB *mahasiswa, int mahasiswaCount);
void printAllNilai(NilaiDB *nilai, int nilaiCount);
void pressAny();
char* grade(float nilai_akhir);

int main(){
	char selection;
	int i = 0, mahasiswaCount = 0, nilaiCount = 0;
	MahasiswaDB mahasiswa[100] = {};
	NilaiDB nilai[100] = {};
		
	mainmenu:
	system("cls");
	printf("Selamat datang pada database! Pilih command!\n");
	printf("1. Data Mahasiswa\n2. Data Nilai\n3. Insert New Mahasiswa dan Nilainya\n4. Keluar\n");
	printf("Pilih: ");
	fflush(stdin);
	scanf("%c", &selection);
	
	switch(selection){
		i = 0;
		case '1':
			mahasiswamenu:
			{
				mahasiswaCount = readDataMahasiswa(mahasiswa);
			}
			system("cls");
			printf("Selamat datang pada database mahasiswa! (%d/100)\n", mahasiswaCount);
			printf("1. Print Semua Mahasiswa\n2. Kembali\n");
			printf("Pilih: ");
			fflush(stdin);
			scanf("%c", &selection);
			switch(selection){
				case '1':{
					printAllMahasiswa(mahasiswa, mahasiswaCount);
					pressAny();
					goto mahasiswamenu;
				}
				case '2':
					goto mainmenu;
				default:
					goto mahasiswamenu;
			}
		case '2':
			nilaimenu:
			{
				nilaiCount = readDataNilai(nilai);
			}
			system("cls");
			printf("Selamat datang pada database nilai! (%d/100)\n", nilaiCount);
			printf("1. List Nilai\n2. Kembali\n");
			printf("Pilih: ");
			fflush(stdin);
			scanf("%c", &selection);
			
			switch(selection){
				case '1':{
					printAllNilai(nilai, nilaiCount);
					pressAny();
					goto nilaimenu;
				}
				case '2':
					goto mainmenu;
				default:
					goto nilaimenu;
			}
		case '3':
		{
			mahasiswaCount = readDataMahasiswa(mahasiswa);
			nilaiCount = readDataNilai(nilai);	
		}
			if(mahasiswaCount >= 100 || nilaiCount >= 100){
				printf("\nDatabase sudah penuh!\n");
			}else{
				insertMahasiswa(mahasiswa, nilai, mahasiswaCount, nilaiCount);
			}
			pressAny();
			goto mainmenu;
		case '4':
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

int readDataMahasiswa(MahasiswaDB *mahasiswa){
	int i = 0;
	// create file if it doesn't exist.
	if(fopen("dataMahasiswa.txt", "r") == NULL){
		FILE *fout = fopen("dataMahasiswa.txt", "w");
		fprintf(fout, "");
		fclose(fout);
		
		system("cls");
		printf("dataMahasiswa.txt doesn't exist.. Creating anew..\n\n");
		sleep(1);
	}
	
	FILE *fp = fopen("dataMahasiswa.txt", "r");
	// check if file is empty, if true, then data = 0;
	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	if(fileSize == 0){
		i = 0;
	}else{
		fclose(fp);
		FILE *fp = fopen("dataMahasiswa.txt", "r");
		while(!feof(fp)){
		MahasiswaDB newMahasiswa;
		fscanf(fp, "%[^#]#%[^#]#%[^#]#\n", newMahasiswa.nim, newMahasiswa.nama,
			newMahasiswa.jurusan);
		mahasiswa[i] = newMahasiswa;
		i++;
		}
	}

	fclose(fp);
	return i;
}

int readDataNilai(NilaiDB *nilai){
	int i = 0;
	// same deal, refer to before.
	if(fopen("nilaiMahasiswa.txt", "r") == NULL){
		FILE *fout = fopen("nilaiMahasiswa.txt", "w");
		fprintf(fout, "");
		fclose(fout);
		
		system("cls");
		printf("nilaiMahasiswa.txt doesn't exist.. Creating anew..\n\n");
		sleep(1);
	}
	
	FILE *fp = fopen("nilaiMahasiswa.txt", "r");
	// same deal, refer to before.
	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	if(fileSize == 0){
		i = 0;
	}else{
		fclose(fp);
		FILE *fp = fopen("nilaiMahasiswa.txt", "r");
		while(!feof(fp)){
		NilaiDB newNilai;
		fscanf(fp, "%[^#]#%f#%f#%f#%f#%[^#]#\n", &newNilai.nim, &newNilai.tugas,
			&newNilai.uts, &newNilai.uas, &newNilai.nilai_akhir, &newNilai.grade);
		nilai[i] = newNilai;
		i++;
		}		
	}
	
	fclose(fp);
	return i;
	
}

void printAllMahasiswa(MahasiswaDB *mahasiswa, int mahasiswaCount){
	int i = 0;
	printf("\n                                        List of Student Information\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("|No.|      NIM       |                      Nama                        |          Jurusan          |\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	if(mahasiswaCount == 0){
	printf("|   |                                          Database is empty!                                   |\n");
	}
	for(i = 0; i < mahasiswaCount; i++){
		printf("|%-3d|%-16s|%-50s|%-27s|\n", i+1, mahasiswa[i].nim, mahasiswa[i].nama, mahasiswa[i].jurusan);
	}
	printf("-----------------------------------------------------------------------------------------------------\n");
}

void printAllNilai(NilaiDB *nilai, int nilaiCount){
	int i = 0;
	printf("\n                                        List of Student Grades\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("|No.|      NIM       |     Tugas    |      UTS     |      UAS     |    NilaiAkhir   |      Grade    |\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	if(nilaiCount == 0){
	printf("|   |                                          Database is empty!                                   |\n");
	}
	for(i = 0; i < nilaiCount; i++){
		printf("|%-3d|%-16s|%-14.2f|%-14.2f|%-14.2f|%-17.2f|%-15s|\n", i+1, nilai[i].nim, nilai[i].tugas, nilai[i].uts, nilai[i].uas, nilai[i].nilai_akhir, nilai[i].grade);
	}
	printf("-----------------------------------------------------------------------------------------------------\n");
}

char* grade(float nilai_akhir){
	// switch case doesn't work with floats, so i'm using if else.
	if(nilai_akhir <= 0){
		return "E";
	}else if(nilai_akhir <= 55){
		return "D";
	}else if(nilai_akhir <= 60){
		return "C-";
	}else if(nilai_akhir <= 65){
		return "C";
	}else if(nilai_akhir <= 70){
		return "B";
	}else if(nilai_akhir <= 75){
		return "B+";
	}else if(nilai_akhir <= 80){
		return "A-";
	}else if(nilai_akhir <= 85){
		return "A";
	}else{
		return "A+";
	}
}

void insertMahasiswa(MahasiswaDB *mahasiswa, NilaiDB *nilai, int mahasiswaCount, int nilaiCount){
	int i = 0;
	printf("\n  Insert Student Information  \n");
	printf("------------------------------\n");
	printf("NIM\t: "); fflush(stdin); scanf("%[^\n]", &mahasiswa[mahasiswaCount].nim);
	printf("Nama\t: "); fflush(stdin); scanf("%[^\n]", &mahasiswa[mahasiswaCount].nama);
	printf("Jurusan\t: "); fflush(stdin); scanf("%[^\n]", &mahasiswa[mahasiswaCount].jurusan);
	
	printf("\n  Insert Student Grades  \n");
	printf("------------------------------\n");
	strcpy(nilai[nilaiCount].nim, mahasiswa[mahasiswaCount].nim);
	printf("Tugas\t\t: "); fflush(stdin); scanf("%f", &nilai[nilaiCount].tugas);
	printf("UTS\t\t: "); fflush(stdin); scanf("%f", &nilai[nilaiCount].uts);
	printf("UAS\t\t: "); fflush(stdin); scanf("%f", &nilai[nilaiCount].uas);
	nilai[nilaiCount].nilai_akhir = (nilai[nilaiCount].tugas * 0.3) + (nilai[nilaiCount].uts * 0.3) + (nilai[nilaiCount].uas * 0.4);
	printf("Nilai Akhir\t: %.2f\n", nilai[nilaiCount].nilai_akhir);
	strcpy(nilai[nilaiCount].grade, grade(nilai[nilaiCount].nilai_akhir));
	printf("Grade\t\t: %s\n", nilai[nilaiCount].grade);
	
	// if one of the input has zero value (excluding float inputs), restart input.
	if(strlen(mahasiswa[nilaiCount].nim) * strlen(mahasiswa[nilaiCount].nama) * strlen(mahasiswa[nilaiCount].jurusan) == 0){
		printf("\nOne of the input is empty. Data not saved. Please try again.\n");
		return;
	}else{
		FILE *fout = fopen("dataMahasiswa.txt", "w");
		for(i = 0; i <= mahasiswaCount; i++){
			fprintf(fout, "%s#%s#%s#\n", mahasiswa[i].nim, mahasiswa[i].nama, mahasiswa[i].jurusan);
		}
		fclose(fout);
		
		FILE *fout2 = fopen("nilaiMahasiswa.txt", "w");
		for(i = 0; i <= nilaiCount; i++){
			fprintf(fout2, "%s#%.2f#%.2f#%.2f#%.2f#%s#\n", nilai[i].nim, nilai[i].tugas,
				nilai[i].uts, nilai[i].uas, nilai[i].nilai_akhir, nilai[i].grade);
			}
		fclose(fout2);
	}	
}
