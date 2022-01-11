#include <stdio.h>
#include <ctype.h>
#include <string.h>
#pragma warning (disable:4996)

#define MAX_RECORD_PER_FILE 100	//define the size of Patient[] & the max record stored in the file 

//Structure for identity card
struct IdentityCard {
	char icNo[20], nationality[20];
};

//Structure for patient info
typedef struct {
	char id[10], name[20], gender;
	int age;
	char contactNo[15], allergies[10];
	struct IdentityCard ic;
}Patient;

//Functions
int addPatientInfo(Patient[MAX_RECORD_PER_FILE],int pCount);
void searchPatientInfo(Patient[MAX_RECORD_PER_FILE],int pCount);
void modifyPatientInfo(Patient[MAX_RECORD_PER_FILE],int pCount);
void displayPatientInfo(Patient[MAX_RECORD_PER_FILE],int pCount);
int deletePatientInfo(Patient[MAX_RECORD_PER_FILE], int pCount);
void backupPatientInfo(Patient[MAX_RECORD_PER_FILE],int pCount);

void patientInfo() {

	//Declaration of variables and pointers
	FILE *readPtr, *writePtr;
	int menuChoice, pCount = 0;  //pCount = patient count in the structure
	Patient patient[MAX_RECORD_PER_FILE], p;

	//Read the binary file and stores the data into patient[]
	readPtr = fopen("PatientInfo.bin", "rb");
	if (readPtr == NULL) {
		printf("Cannot read from PatientInfo.bin\n");
		exit(-1);
	}
	while (fread(&p,sizeof(Patient),1,readPtr)!=0)
	{
		patient[pCount] = p;
		pCount++;
	}

	//print Patient Info Menu and respond to user input
	do {
		printf("\tPatient Info Menu\n"
			"\t=================\n"
			"   1.\tAdd record\n"
			"   2.\tSearch record\n"
			"   3.\tModify record\n"
			"   4.\tDisplay record\n"
			"   5.\tDelete record\n"
			"   6.\tBackup record\n"
			"   7.\tBack\n"
			"Please enter your choice > ");
		scanf("%d", &menuChoice);
		rewind(stdin);			//To prevent user enter a char and enter infinite loop
		switch (menuChoice) {
		case 1: pCount = addPatientInfo(patient,pCount); break;
		case 2: searchPatientInfo(patient,pCount); break;
		case 3: modifyPatientInfo(patient,pCount); break;
		case 4: displayPatientInfo(patient,pCount); break;
		case 5: pCount = deletePatientInfo(patient, pCount); break;
		case 6: backupPatientInfo(patient,pCount); break;
		case 7: printf("Back to the main menu...\n"); break;
		default: 
			printf("Invalid choice!\n");
		} 
	} while(menuChoice != 7);

	//Write the patient[] into the binary file
	writePtr = fopen("PatientInfo.bin", "wb");
	if (writePtr == NULL) {
		printf("Cannot write to PatientInfo.bin\n");
		exit(-1);
	}
	fwrite(patient, sizeof(Patient), pCount, writePtr);

	//Close the file
	fclose(readPtr);
	fclose(writePtr);

	system("pause");

}


int addPatientInfo(Patient p[MAX_RECORD_PER_FILE], int pCount) {

	char next = 'Y';
	do {
		//Check whether the stucture size whether sufficient to add more record
		if (pCount == MAX_RECORD_PER_FILE) {
			printf("Unable to add more records.\n"
				"Please increase the record limit per file.\n");
			return pCount;			//The function returned if no more space for more records
		}

		//Request for details of patient
		printf("Please enter the details of patient : \n");

		rewind(stdin);
		printf("Patient ID     > ");
		scanf("%s", p[pCount].id);

		rewind(stdin);
		printf("Name           > ");
		gets(p[pCount].name);

		printf("Gender         > ");
		p[pCount].gender = toupper(getchar());
		while (p[pCount].gender != 'M'&&p[pCount].gender != 'F') {
			printf("Invalid Gender!> ");
			rewind(stdin);
			p[pCount].gender = toupper(getchar());
		}

		printf("Age            > ");
		while (scanf("%d", &p[pCount].age) != 1) {
			printf("Invalid age!\nEnter digit(s)!> ");
			rewind(stdin);
		}
		while (p[pCount].age <= 0 || p[pCount].age >= 150) {
			printf("Irrational age!\nYou entered %d!> ",p[pCount].age);
			scanf("%d", &p[pCount].age);
			rewind(stdin);
		}

		rewind(stdin);
		printf("Contact Number > ");
		gets(p[pCount].contactNo);

		printf("Allergies      > ");
		gets(p[pCount].allergies);

		printf("Patient IC details : \n"
			   "IC Number      > ");
		gets(p[pCount].ic.icNo);

		printf("Nationality    > ");
		gets(p[pCount].ic.nationality);

		pCount++;

		//Ask whether to continue
		rewind(stdin);
		printf("Continue ? (Y=Yes,others=No) > ");
		next = toupper(getchar());

		printf("\n");

	} while (next == 'Y');

	//print successful message
	printf("Done adding the records.\n");
	return pCount;
}

void searchPatientInfo(Patient p[MAX_RECORD_PER_FILE], int pCount) {

	Patient pSearch[MAX_RECORD_PER_FILE];	//To store found elements
	int choice, qtyFound = 0;
	char input[20];

	//Choose search criteria
	do {
		printf("Search by :\n"
			" 1. Patient ID\n"
			" 2. Name\n"
			" 3. IC\n"
			"PLease enter your search criteria > ");
		scanf("%d", &choice);
		rewind(stdin);			//To prevent user enter a char and enter infinite loop
	} while (choice < 1 || choice > 3);

	//Input search criteria and the elements that fulfill the criteria is stored in pSearch[]
	switch (choice) {
	case 1:
		printf("Patient ID > ");
		scanf("%[^\n]", input);
		for (int i = 0; i < pCount; i++) {
			if (strcmp(p[i].id, input) == 0) {
				pSearch[qtyFound] = p[i];
				qtyFound++;
			}
		}
		break;
	case 2:
		printf("Patient Name > ");
		scanf("%[^\n]", input);
		for (int i = 0; i < pCount; i++) {
			if (strcmp(input, p[i].name) == 0) {
				pSearch[qtyFound] = p[i];
				qtyFound++;
			}
		}
		break;
	case 3:
		printf("Patient IC > ");
		scanf("%[^\n]", input);
		for (int i = 0; i < pCount; i++) {
			if (strcmp(input, p[i].ic.icNo) == 0) {
				pSearch[qtyFound] = p[i];
				qtyFound++;
			}
		}
		break;
	default:
		printf("Invalid choice!!\n");
	}

	//Display pSearch[] using displayPatientInfo declared
	printf("%d record(s) found : \n", qtyFound);
	displayPatientInfo(pSearch, qtyFound);
}

void modifyPatientInfo(Patient p[MAX_RECORD_PER_FILE], int pCount) {

	int choice, index[MAX_RECORD_PER_FILE], qtyFound = 0;	//index[] used to store index number of patient[] that is found
	char input[20];


	//Choose search criteria
	printf("Please enter the details to search for records to be modified : \n");
	do {
		printf("Search by :\n"
			" 1. Patient ID\n"
			" 2. Name\n"
			" 3. IC\n"
			"PLease enter your search criteria > ");
		scanf("%d", &choice);
		rewind(stdin);			//To prevent user enter a char and enter infinite loop
	} while (choice < 1 || choice > 3);

	//Input search criteria and get the index number of elements that fulfill criteria
	switch (choice) {
	case 1:
		printf("Patient ID > ");
		scanf("%[^\n]", input);
		for (int i = 0; i < pCount; i++) {
			if (strcmp(p[i].id, input) == 0) {
				index[qtyFound] = i;
				qtyFound++;
			}
		}
		break;
	case 2:
		printf("Patient Name > ");
		scanf("%[^\n]", input);
		for (int i = 0; i < pCount; i++) {
			if (strcmp(input, p[i].name) == 0) {
				index[qtyFound] = i;
				qtyFound++;
			}
		}
		break;
	case 3:
		printf("Patient IC > ");
		scanf("%[^\n]", input);
		for (int i = 0; i < pCount; i++) {
			if (strcmp(input, p[i].ic.icNo) == 0) {
				index[qtyFound] = i;
				qtyFound++;
			}
		}
		break;
	default:
		printf("Invalid choice!!\n");
	}
	rewind(stdin);

	if (qtyFound == 0) {
		printf("No record found.\n");
	}
	else {
		for (int i = 0; i < qtyFound; i++) {

			//print the record associated
			printf("\nElement %d found :\n", i + 1);
			printf("==============================================================================================================\n"
				"Patient ID          Name          Gender  Age  Contact Number  Allergies           IC             Nationality\n"
				"==========  ====================  ======  ===  ==============  =========  ====================  ==============\n");
			printf("%-10s  %-20s     %c    %-2d   %-15s %-10s %-20s  %-20s\n", p[index[i]].id, p[index[i]].name, p[index[i]].gender, p[index[i]].age, p[index[i]].contactNo, p[index[i]].allergies, p[index[i]].ic.icNo, p[index[i]].ic.nationality);
			printf("==============================================================================================================\n");

			//Choose what to modify
			do {
				printf("What to modify? \n"
					" 1. Patient ID\n"
					" 2. Patient Name\n"
					" 3. Gender\n"
					" 4. Age\n"
					" 5. Contacts\n"
					" 6. Allergies\n"
					" 7. IC\n"
					" 8. Nationality\n"
					" 9. Nothing to be modified\n"
					"Please enter your choice > ");
				scanf("%d", &choice);
				rewind(stdin);			//To prevent user enter a char and enter infinite loop
			} while (choice < 1 || choice>9);

			if (choice != 9) {
				printf("Modify to > ");
				gets(input);
			}

			//Assign the value to p[] which is same as the patient[] in the main program
			switch (choice) {
			case 1: strcpy(p[index[i]].id, input); break;
			case 2: strcpy(p[index[i]].name, input); break;
			case 3:
				p[index[i]].gender = toupper(input[0]); //Assign the first character of input as gender
				while (p[index[i]].gender != 'M' && p[index[i]].gender != 'F') {
					printf("Please enter M for male or F for female !\n");
					gets(input);
					p[index[i]].gender = toupper(input[0]);
				}
				break;
			case 4:
				p[index[i]].age = atoi(input); //Convert the input to int using atoi() and assign to age
				while (p[index[i]].age == 0) {		//atoi() return 0 when unable to covert string to integer
					printf("Error! Please input patient age again !\n");
					gets(input);
					p[index[i]].age = atoi(input);
				}
				break;
			case 5: strcpy(p[index[i]].contactNo, input); break;
			case 6: strcpy(p[index[i]].allergies, input); break;
			case 7: strcpy(p[index[i]].ic.icNo, input); break;
			case 8: strcpy(p[index[i]].ic.nationality, input); break;
			case 9: printf("Skipped this record.\n"); break;
			default: printf("Invalid choice!!\n");
			}
		}
	}
	//print success message records after modified
	printf("Done modified.\n");
	displayPatientInfo(p, pCount);
}

void displayPatientInfo(Patient p[MAX_RECORD_PER_FILE], int pCount) {

	//Nothing much but print records
	printf("==============================================================================================================\n"
		"Patient ID          Name          Gender  Age  Contact Number  Allergies           IC             Nationality\n"
		"==========  ====================  ======  ===  ==============  =========  ====================  ==============\n");
	for (int i = 0; i < pCount; i++) {
		printf("%-10s  %-20s     %c    %-2d   %-15s %-10s %-20s  %-20s\n", p[i].id, p[i].name, p[i].gender, p[i].age, p[i].contactNo, p[i].allergies, p[i].ic.icNo, p[i].ic.nationality);
	}
	printf("==============================================================================================================\n");


}

int deletePatientInfo(Patient p[MAX_RECORD_PER_FILE], int pCount) {

	char input[10];
	int found = 0, recordNo[MAX_RECORD_PER_FILE] = { 0 }, menuChoice, deleteChoice;

	//Request for patient ID to be deleted
	printf("Please enter the patient ID > ");
	scanf("%[^\n]", input);

	//Check whether any record is found
	for (int i = 0; i < pCount; i++) {
		if (strcmp(p[i].id, input) == 0)
			found++;
	}

	if (found > 0) {

		//Intitialize found
		found = 0;

		//print records found and obtain the record's index into recordNo[]
		printf("==============================================================================================================\n"
			"Patient ID          Name          Gender  Age  Contact Number  Allergies           IC             Nationality\n"
			"==========  ====================  ======  ===  ==============  =========  ====================  ==============\n");
		for (int i = 0; i < pCount; i++) {
			if (strcmp(p[i].id, input) == 0) {
				printf("Record No.%d : \n", found + 1);
				printf("%-10s  %-20s     %c    %-2d   %-15s    %-10s %-20s  %-20s\n", p[i].id, p[i].name, p[i].gender, p[i].age, p[i].contactNo, p[i].allergies, p[i].ic.icNo, p[i].ic.nationality);
				recordNo[found] = i;
				found++;
			}
		}
		printf("==============================================================================================================\n");


		//Ask wheter to delete all records or selected records only
		printf("Delete record(s) for %s : \n"
			" 1. All records\n"
			" 2. Selected record\n"
			" 3. Cancel\n", input);
		scanf("%d", &menuChoice);

		switch (menuChoice) {
		case 1:
			//for every records found
			for (int i = 0; i < found; i++){
				//move the record after to current
				for (int j = recordNo[i]; j < pCount; j++) {
					p[j] = p[j + 1];
				}
			}
			printf("Current number of patient records : %d\n", --pCount);
			break;
		case 2:
			//Request for record number to be deleted
			printf("Please enter Record No. to be deleted > ");
			scanf("%d", &deleteChoice);

			//move the record after selected record to current
			for (int j = recordNo[deleteChoice-1]; j < pCount; j++) {
				p[j] = p[j + 1];
			}
			printf("Current number of patient records : %d\n", --pCount);
			break;
		case 3:
			printf("Canceled.\n");
			break;
		default:
			printf("Invalid input!\n");
		}
	}
	else
		printf("No record found.\n");

	displayPatientInfo(p,pCount);

	return pCount;
}

void backupPatientInfo(Patient p[MAX_RECORD_PER_FILE], int pCount) {

	FILE *writePtr;
	char filename[30];

	//Request for backup filename
	rewind(stdin);
	printf("Enter the backup filename (extension name not required£© > ");
	scanf("%[^\n]", filename);

	//Append the extension name
	strcat(filename, ".bin");

	//Open and write to file
	writePtr = fopen(filename, "wb");

	if (writePtr == NULL) {
		printf("Cannot write to %s\n",filename);
		exit(-1);
	}

	fwrite(p, sizeof(Patient), pCount, writePtr);
	fclose(writePtr);

	printf("Attempting to backup info(s)...\n");
	printf("File successfully backup.\n");
}
