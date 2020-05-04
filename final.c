/*PROGRAM: To manage Patient's Record(add,search and delete)
AUTHOR:NEEMA KHATI*/

#include<stdio.h>
#include<string.h>


int showMenu(int*);//shows menu to the user

void addRecord(FILE*);//add new patient to the record of file

void checkRecords(FILE*);//shows all the records of a patient

void searchRecord(FILE*);   //search record of the patient

void deleteRecord(FILE*);//delete the record of a patien

typedef struct{
	int day;
	int month;
	int year;
}date;

 typedef struct{
	char patient_name[50];
	int room_no;
	date date_of_entry;
}patient_info;

int main(){
	
	patient_info patient;
	
	FILE *fptr;
	fptr=fopen("list.bin","a+");
	
	int choice=0;
	
	showMenu(&choice);

    switch(choice) {
        case 1:
            addRecord(fptr);
            break;
        case 2:
            checkRecords(fptr);
            break;
        case 3:
            searchRecord(fptr);
            break;
        case 4:
            deleteRecord(fptr);
            break;
    }

    fclose(fptr);
}
	int showMenu(int* choice){
	    printf("***WELCOME TO HOSPITAL MANAGEMENT SYSTEM***\n");
	    
		printf("1)To add new account press 1\n2)To check existing record press 2\n3)To search records press 3\n4)To delete existing record press 4\n");
		
		printf("Enter your choice: ");
		scanf("%d",choice);
	}
		
	void addRecord(FILE *fptr){
		patient_info patient;
		
		fptr=fopen("list.bin","a");
		
		printf("Enter patient's name: ");
		fflush(stdin);
		gets(patient.patient_name);
			
		printf("Enter room number: ");
		scanf("%d",&patient.room_no);
			
		printf("Enter the date of entry (DD MM YYYY) ");
		scanf("%d %d %d",&patient.date_of_entry.day,&patient.date_of_entry.month,&patient.date_of_entry.year);
			
		fwrite(&patient, sizeof(patient_info),1,fptr);
	}
	void checkRecords(FILE *fptr){
		
		patient_info patient;
		fptr=fopen("list.bin","r");
		fread(&patient,sizeof(patient_info),1,fptr);
		
		while(!feof(fptr)){
			printf("%s\n",patient.patient_name);
			printf("%d\n",patient.room_no);
			printf("%d/%d/%d\n",patient.date_of_entry.day,patient.date_of_entry.month,patient.date_of_entry.year);
				
				fread(&patient,sizeof(patient_info),1,fptr);
		}
	}
	void searchRecord(FILE *fptr){
		
		int count=0;
		char search_name[50];
		int end=0;
			
		printf("Enter the patient's name you want to search: ");
		scanf("%s",&search_name);
			
		patient_info patient;
			
		while(fread(&patient,sizeof(patient_info),1,fptr)){
				
			count=strcmp(patient.patient_name,search_name);
				
			if (count==0){
					
				printf("%s\n",patient.patient_name);
				printf("%d\n",patient.room_no);
				printf("%d/%d/%d\n",patient.date_of_entry.day,patient.date_of_entry.month,patient.date_of_entry.year);
					
					end=1;
					break;
				}
			else if (end=0)
				printf("NOT FOUND!!!");
			}
			
	}
	void deleteRecord(FILE *fptr){
		
		patient_info patient;	
			FILE *fptr1;
				int count=0;
				char delete_name[50];
				int end=0;
				
				printf("Enter the patient's name you want to delete: ");
				scanf("%s",&delete_name);
				
				fptr= fopen("list.bin","r");
				fptr1= fopen("re.bin","a");
				
				while(fread(&patient,sizeof (patient_info),1,fptr)){
					
					count=strcmp(patient.patient_name,delete_name);
					
					if (count==0){
						end=1;
					}
					else
						if(count!=0){
								
							fwrite(&patient,sizeof (patient_info),1,fptr1);
							end=1;
					}
					else if (end=0){
						printf("NOT FOUND!!!");
					}
				}
				fclose(fptr);
				fclose(fptr1);
				
				fptr= fopen("list.bin","w");
				fclose(fptr);
				
				//to read all the contents of fptr1
				
				fptr= fopen("list.bin","a");
				fptr1= fopen("re.bin","r");
				
				fread(&patient,sizeof (patient_info),1,fptr1);
				while(!feof(fptr1)){
					printf("%s\n",patient.patient_name);
					printf("%d\n",patient.room_no);
					printf("%d/%d/%d\n",patient.date_of_entry.day,patient.date_of_entry.month,patient.date_of_entry.year);	
					fread(&patient,sizeof (patient_info),1,fptr1);
				}
				fclose(fptr);
				fclose(fptr1);
					
				//to copy the contents of fptr1 to fptr
				
				fptr= fopen("list.bin","w");
				fptr1= fopen("re.bin","r");
				int ch;
				
				while((ch=fgetc(fptr1))!=EOF){
					fputc(ch,fptr);
				}
				fclose(fptr);
				fclose(fptr1);
				
				
				fptr1= fopen("re.bin","w");
				fclose(fptr);
}
