#include <stdio.h>
#include <string.h>

typedef struct{
	char nim[16];
	char nama[50];
	char jurusan[50];
}Mahasiswa;

typedef struct{
	char nim[16];
	float tugas;
	float uts;
	float uas;
	float nilai_akhir;
	char grade[3];
}Nilai;

char* grade(float nilai_akhir){
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

int main(){
	char selection;
	int i = 0, mahasiswaCount = 0, nilaiCount = 0;
	float nilai_akhir;
	Mahasiswa mahasiswa[100] = {};
	Nilai nilai[100] = {};
		
	mainmenu:
	system("cls");
	printf("Selamat datang pada database! Pilih database yang akan diedit!\n");
	printf("1. Data mahasiswa\n2. Data nilai\n3. Keluar\n");
	printf("Pilih: ");
	fflush(stdin);
	scanf("%c", &selection);
	
	switch(selection){
		//dataMahasiswa
		i = 0;
		case '1':
			mahasiswamenu:
			{
				FILE *fp = fopen("dataMahasiswa.txt", "r");
				while(!feof(fp)){
					Mahasiswa newMahasiswa;
					fscanf(fp, "%[^#]#%[^#]#%[^#]#\n", newMahasiswa.nim, newMahasiswa.nama,
						newMahasiswa.jurusan);
					mahasiswa[i] = newMahasiswa;
					i++;
				}
				
				if(strlen(mahasiswa[0].nim) + strlen(mahasiswa[0].nama) + strlen(mahasiswa[0].jurusan) == 0){
						mahasiswaCount = 0;
					}else{
						mahasiswaCount = i;
					}
				fclose(fp);
				
				system("cls");
				printf("Selamat datang pada edit data mahasiswa!\n");
				printf("1. List mahasiswa\n2. Insert mahasiswa\n3. Kembali\n");
				printf("Pilih: ");
				fflush(stdin);
				scanf("%c", &selection);
				switch(selection){
					case '1':
						for(i = 0; i < mahasiswaCount; i++){
							// skip print if empty
							if(strlen(mahasiswa[i].nim) + strlen(mahasiswa[i].nama) + strlen(mahasiswa[i].jurusan) == 0){
								continue;
							}
							printf("Mahasiswa #%d\n", i + 1);
							printf("NIM\t: %s\n", mahasiswa[i].nim);
							printf("Nama\t: %s\n", mahasiswa[i].nama);
							printf("Jurusan\t: %s\n", mahasiswa[i].jurusan);
							printf("\n");
						}
						printf("Press any key to continue..");
						getch();
						goto mahasiswamenu;
					case '2':
						if(mahasiswaCount >= 100){
							printf("Data mahasiswa sudah penuh! Press any key to continue..\n");
							getch();
							goto mahasiswamenu;
						}else{
							printf("NIM\t: "); fflush(stdin); scanf("%[^\n]", &mahasiswa[mahasiswaCount].nim);
							printf("Nama\t: "); fflush(stdin); scanf("%[^\n]", &mahasiswa[mahasiswaCount].nama);
							printf("Jurusan\t: "); fflush(stdin); scanf("%[^\n]", &mahasiswa[mahasiswaCount].jurusan);
							mahasiswaCount++;
							
							FILE *fout = fopen("dataMahasiswa.txt", "w");
							for(i = 0; i < mahasiswaCount; i++){
								// dont save if input is empty
								if(strlen(mahasiswa[i].nim) + strlen(mahasiswa[i].nama) + strlen(mahasiswa[i].jurusan) == 0){
									continue;
								}
								fprintf(fp, "%s#%s#%s#\n", mahasiswa[i].nim, mahasiswa[i].nama,
									mahasiswa[i].jurusan);
							}
							fclose(fout);
							
							printf("\nBerhasil disimpan! Press any key to continue..");
							getch();
							goto mahasiswamenu;
						}	
					case '3':
						goto mainmenu;
					default:
						goto mahasiswamenu;
					}
			}	
		//nilaiMahasiswa
		case '2':
			nilaimenu:
			{
			FILE *fp2 = fopen("nilaiMahasiswa.txt", "r");
			while(!feof(fp2)){
				Nilai newNilai;
				fscanf(fp2, "%[^#]#%f#%f#%f#%f#%[^#]#\n", &newNilai.nim, &newNilai.tugas,
					&newNilai.uts, &newNilai.uas, &newNilai.nilai_akhir, &newNilai.grade);
				nilai[i] = newNilai;
				i++;
			}
		
			if(strlen(nilai[0].nim) == 0){
					nilaiCount = 0;
				}else{
					nilaiCount = i;
				}
			fclose(fp2);
			
			system("cls");
			printf("Selamat datang pada edit data nilai!\n");
			printf("1. List nilai\n2. Insert nilai\n3. Kembali\n");
			printf("Pilih: ");
			fflush(stdin);
			scanf("%c", &selection);
			
			switch(selection){
				case '1':
					for(i = 0; i < nilaiCount; i++){
						// skip print if empty
						if(strlen(nilai[i].nim) == 0){
							continue;
						}
						printf("Nilai #%d\n", i + 1);
						printf("NIM\t\t: %s\n", nilai[i].nim);
						printf("Tugas\t\t: %.2f\n", nilai[i].tugas);
						printf("UTS\t\t: %.2f\n", nilai[i].uts);
						printf("UAS\t\t: %.2f\n", nilai[i].uas);
						printf("Nilai Akhir\t: %.2f\n", nilai[i].nilai_akhir);
						printf("Grade\t\t: %s\n", nilai[i].grade);
						printf("\n");
					}
					printf("Press any key to continue..");
					getch();
					goto nilaimenu;
				case '2':
					if(nilaiCount >= 100){
						printf("Data nilai sudah penuh! Press any key to continue..\n");
						getch();
						goto nilaimenu;
					}else{
						printf("NIM\t\t: "); fflush(stdin); scanf("%[^\n]", &nilai[nilaiCount].nim);
						printf("Tugas\t\t: "); fflush(stdin); scanf("%f", &nilai[nilaiCount].tugas);
						printf("UTS\t\t: "); fflush(stdin); scanf("%f", &nilai[nilaiCount].uts);
						printf("UAS\t\t: "); fflush(stdin); scanf("%f", &nilai[nilaiCount].uas);
						nilai[nilaiCount].nilai_akhir = (nilai[nilaiCount].tugas * 0.3) + (nilai[nilaiCount].uts * 0.3) (nilai[nilaiCount].uas * 0.4) / 3;
						printf("Nilai Akhir\t: %.2f\n", nilai[nilaiCount].nilai_akhir);
						strcpy(nilai[nilaiCount].grade, grade(nilai[nilaiCount].nilai_akhir));
						printf("Grade\t\t: %s\n", nilai[nilaiCount].grade);
						nilaiCount++;
						
						FILE *fout2 = fopen("nilaiMahasiswa.txt", "w");
						for(i = 0; i < nilaiCount; i++){
							// dont save if input is empty
							if(strlen(nilai[i].nim) == 0){
								continue;
							}
							fprintf(fp2, "%s#%f#%f#%f#%f#%s#\n", nilai[i].nim, nilai[i].tugas,
								nilai[i].uts, nilai[i].uas, nilai[i].nilai_akhir, nilai[i].grade);
							}
				
						fclose(fout2);
						printf("\nBerhasil disimpan! Press any key to continue..");
						getch();
						goto nilaimenu;
					}	
				case '3':
					goto mainmenu;
				default:
					goto nilaimenu;
				}
			}
		case '3':
			break;
		default:
			goto mainmenu;	
	}
	return 0;
}
