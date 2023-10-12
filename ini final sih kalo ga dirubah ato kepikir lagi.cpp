/* Library yang digunakan dalam program ini */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

int n = 0; // Variabel  yang akan digunakan untuk patokan nantinya ( N untuk diarynya sendiri , M untuk program loginnya)
int m = 0;
struct AkashicRecord{ // Mendefinisikan struct yang digunakan sebagai kerangka dalam diary nanti
	char Title[26];
	char Date[11];
	char DiaryLog[991];
};	

struct login{ //Mendefinisikan struct untuk login nanti                      
char username[30];
char password[20];
};
AkashicRecord record[800]; //Mmatok besar structnya secara langsung , dimana 800 menurut saya cukup karena apabila kita kita memasukkan 1 Entry perhari, bisa bertahan hingga kurang lebih 2 tahun/
login logg[50];

// Mendefiniskan fungsi untuk login 
void registration(); 
void enter();

void import(){
	FILE *fp;
	fp = fopen("PersonalDiary.txt","r"); // Membuka file .txt dimana semua data diary disimpan
		while(fscanf(fp,"%[^|]|%[^|]|%s\n", &record[n].Title , &record[n].DiaryLog , &record[n].Date) != EOF){ //membaca hingga baris terakhir
			n++; //n bertambah sebagai acuan ada berapa baris dalam notepad
		}	
	fclose(fp);
}

// Fungsi untuk Menambahkan Diary
void AddDiary(){

char newtitle[100];
char newlog[991];
char newdate[30];

	FILE *fp;
	fp = fopen("PersonalDiary.txt","a");// Membuka file tempat data disimpan , lalu menambahkan isinya di baris paling bawah
	getchar(); // Menggunakan getchar agar kita bisa mengisi Diary Entry dari atas
		printf("\n\tInput Diary Title: ");					    scanf("%[^\n]",&newtitle);			getchar();//menggunakan regex agar kita bisa memakai spasi dan berbagai "emoji" lainnya
		printf("\n\tInput Diary Log (Max 990 Characters): ");   scanf("%[^\n]",&newlog);			getchar();
		printf("\n\tInput Diary Date [DD-MM-YYYY]: ");	        scanf("%[^\n]",&newdate);			getchar();
		fprintf(fp,"%s|%s|%s\n",newtitle,newlog,newdate); // Menulis Diary Entry kedalam File.txt
		printf("\n\t*** Diary Succesfully Added!***\t");
		puts("");
    	printf("\n\tPress Any Key to Continue!");
    	getch();
	fclose(fp);
}

// Fungsi untuk Menghapus Diary
void DeleteDiary(){

import();
	FILE *fp;
	fp = fopen("PersonalDiary.txt","w");// Membuka File.txt dan kemudian membaca isi diary lalu menulisnya dari awal (seperti di reset).
	int tanda = 0; // Digunakan untuk penanda yang akan dihapus
	char line[100];	
	getchar();
	printf("\n\tEnter the Title of the Diary You Want to Delete: \t");
	scanf("%[^\n]",&line); getchar();

		for(int i = 0; i < n; i++){
			if(strcmp(line,record[i].Title) == 0){ // Untuk mencari diary berdasarkan judul dengan menggunakan strcmp
				tanda = i;			
			}				
		}
		for(int i = 0; i < n; i++){ // Menulis ulang semua isi diary , namun yang sudah ditandai tadi di skip dengan continue / langsung dilanjut.
			if(tanda == i)continue;	
			else if(tanda != i)fprintf(fp,"%s|%s|%s\n", record[i].Title, record[i].DiaryLog, record[i].Date);
		}
		fclose(fp);
		n=0;
		printf("\n\t*** Diary Succesfully Deleted!***\t");
}

// Fungsi untuk Melihat Diary
void ViewDiary(){

import(); // Memanggil function import untuk mengetahui panjang diarynya
	char line[100]; // Variabel untuk mencari
	getchar();
	printf("\n\tEnter the Title of your Diary: ");
	scanf("%[^\n]",&line); getchar();

	int target = -1; //untuk penanda yang akan dicari
	for(int i = 0; i < n; i++){ //mencari yang sama dengan linear search lalu ditandai jika ketemu.
		if(strcmp(line,record[i].Title) == 0)target = i;	  
	}
	if(target == -1) printf("\tDiary Not Found!\n");// Jika Diary Entry tidak ditemukan
	else{ // Format Print Apabila Diary Entry ditemukan
		printf("\n\t-----------------------------------------------");
		printf("\n\tTitle: %s\n",record[target].Title);
        printf("\n\tDate: %s\n",record[target].Date);
        printf("\n\tDiary Log: %s\n",record[target].DiaryLog);
		printf("\n\t-----------------------------------------------");
		n=0;
		puts("");
    	printf("\n\tPress Any Key to Continue!");
    	getch(); 
	}
}

// Fungsi untuk Mengedit Diary
void EditDiary(){

import();
	FILE *fp;
	fp = fopen("PersonalDiary.txt","w"); // Membuka File.txt kemudian menulis ulang lagi secara menyeluruh 
	int tanda =- 1; // Penanda yang akan diganti
	char line[100];	
	getchar();
	printf("\n\tEnter the Title of your Diary That You Want to Edit: ");
	scanf("%[^\n]",&line); getchar();

		for(int i = 0; i < n; i++){ // Mencari yang sama dengan linear search lalu ditandai jika ketemu.
			if(strcmp(line,record[i].Title) == 0){
				tanda = i;		
			}				
		}
 		// Apabila Diary Entry Ditemukan maka User akan diminta untuk menulis Diary Entrynya lagi
		for(int i=0;i<n;i++){
			if(tanda == i){
				printf("\n\tEnter New Title For Your Diary: ");
				scanf("%[^\n]",&record[tanda].Title);	 getchar();
				printf("\n\tEnter New Diary Log For Your Diary: ");
				scanf("%[^\n]",&record[tanda].DiaryLog); getchar();
				printf("\n\tEnter New Date For Your Diary: ");
				scanf("%s",&record[tanda].Date);		 getchar();					
			}
		}
		for(int i = 0; i < n; i++){//menulis ulang lagi ke dalam notepad
			fprintf(fp,"%s|%s|%s\n",record[i].Title,record[i].DiaryLog,record[i].Date);
		}
		
		printf("\n\tYour Change Was Made Successfully!\n\n");
		n=0;
			fclose(fp);		
	}

// Fungsi untuk Menampilkan Seluruh Diary Entry
void ViewAllDiary(){
	import();
	for(int i = 0; i < n; i++){//print semua isi diary yang ada saat itu
		printf("\t-----------------------------------------------\n");
		printf("\tDate     : ");printf("%s\n",record[i].Date);
		printf("\tTitle    : ");printf("%s\n",record[i].Title);
		printf("\tDiary Log: ");printf("%s\n",record[i].DiaryLog);
		printf("\t-----------------------------------------------\n");
	}
	n=0;
}
// Fungsi Untuk Menampilkan Menu Utama
void MainMenu(){
printf("\n\n\t--------------\n");
printf("\t*Personal Diary*\n");
printf("\t--------------");
int select;

   while(1){
        printf("\n\t**************\n\n");
		printf("\n\t      --------");
        printf("\n\t\tMenu:");
        printf("\n\t      --------\n\n");
        printf("\n\tAdd Diary Log        \t[1]");
        printf("\n\tDelete Diary Log     \t[2]");
        printf("\n\tView Diary Log       \t[3]");
        printf("\n\tEdit Diary Log       \t[4]");
		printf("\n\tView All Diary Log   \t[5]");
        printf("\n\tExit                 \t[6]");
        printf("\n\n\tHello, What Would You Like to Do?:");
        scanf("%d",&select);

        switch(select){
            case 1:
                AddDiary();
                break;
            case 2:
                DeleteDiary();
                break;
            case 3:
                ViewDiary();
                break;
            case 4:
                EditDiary();
                break;
			case 5:
                ViewAllDiary();
                break;
            case 6:
                printf("\n\tSee You Later!");
                exit(1);
            default:
                printf("\n\tInvalid Option. Please Try Again.\n");
                break;                
        }    
    } 
}

// Fungsi Untuk Menampilkan Menu Login
void LoginMenu(){
	FILE *ptr;   
	ptr = fopen("Password.txt","r");
    printf("\n\n\t--------------------------------\n");    
	printf("\tCreate A Username & Password [1]\n");
	printf("\t                       Login [2]\n");
	printf("\t                       Exit  [3]\n");	
    printf("\t--------------------------------\n");
	int Select;
	scanf("%d",&Select);

	switch(Select){
		case 1:
        	registration();
        	break;
        case 2:
            enter();
            break;
		case 3:
			exit(1);     
		default:
            printf("Invalid Option. Please Try Again.\n");
            break; 
	}		
}

// Fungsi Untuk Registrasi
void registration(){

	FILE *ptr;// Menulis data baru untuk dijadikan username & password di notepad terpisah dengan diary di baris paling bawahnya
	ptr = fopen("Password.txt", "a"); 
    if(ptr == NULL){ // Membuat file Password.txt apabila tidak ditemukan
         ptr = fopen("Password.txt", "a");
            if(ptr == NULL){
                puts("Error, File Does Not Exist!");
                exit(1);
            }
        }
	char username[100]; // Temporary Variabel untuk menampung Username & Passwordnya
	char password[100];
	getchar();

    printf("\tUsername:\t"); 
	scanf("%[^\n]", &username);getchar(); // Menginput datanya
	printf("\t*** Don't Use Space As Part Of Your Password! ***\n");
	printf("\tPassword:\t"); 
	scanf("%s", &password);getchar(); // Menginput datanya

	fprintf(ptr,"%s|%s\n",username,password); //menulis datanya ke dalam notepad agar tersimpan
	fclose(ptr);
	printf("\n\t*** Account Credentials Successfully Added! Please Restart The program To Save Your Changes! :) ***\n");      
    LoginMenu();
	
}

// Fungsi Untuk Login
void enter(){

	FILE *ptr = fopen("Password.txt", "r");//membaca data yang ada dalam notepad
	char namalogin[30];//variabel penampung sementara untuk dibandingkan
	char passlogin[20];

	while(fscanf(ptr,"%[^|]|%s\n", &logg[m].username, &logg[m].password) != EOF){ 
	m++; //membaca sampai akhir file / end of file
	}
	getchar();
	printf("\nUsername: ");scanf("%[^\n]",&namalogin);getchar();//menginput datanya
	printf("\nPassword: ");scanf("%[^\n]",&passlogin);getchar();//menginput datanya
	int tanda = -1;

		for(int i = 0; i < m; i++){
			if(strcmp(namalogin,logg[i].username) == 0 && strcmp(passlogin,logg[i].password) == 0){ //membandingkan seluruh isi data pada notepad dengan data yang diinput apakah sesuai
				tanda = i; //menandainya jika ada
			}
		}
		if(tanda != -1 ){// Jika data sudah bukan -1 lagi maka akan dilanjut ke Menu Utama, apabila salah akan dikembalikan ke menu login
			printf("\nLogging In...");
			MainMenu();	
		}else{
			printf("\t*** Wrong Login Credentials. Please Try Again. ***\n");
			LoginMenu();
		}
		fclose(ptr);
	}


int main(){
	LoginMenu();
	return 0;
}