#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<ctype.h>
#pragma warning(disable : 4996)
//Define constant for size of the structure array
#define VALUE 100

//Structure declaration for medical check
typedef struct {
	char status[20];
	int systolicBloodPressure, diastolicBloodPressure, bloodSugarTest, cholesterol;
}Medical;

//structure declaration for array
typedef struct {
	int days, month, years, hours, minutes;
	char patientID[9], patientName[50], gender;
	int age;
	char staffID[5], diagnosis[30];
	double charges;
	Medical medical;
}PatientVisit;

//Functions declaration for different function
int readPatientVisit(PatientVisit data[VALUE]);
int addPatientVisit(PatientVisit data[VALUE], int count);
void displayPatientVisit(PatientVisit data[VALUE], int count);
void searchPatientVisit(PatientVisit data[VALUE], int count);
void modifyPatientVisit(PatientVisit data[VALUE], int count);
void medicalCheck(PatientVisit data[VALUE], int count);
int deletePatientVisit(PatientVisit data[VALUE], int count);
void exitProgram(PatientVisit data[VALUE], int count);
char getGender();

//Main program
void patientVisit()
{
	//Structure array declaration
	PatientVisit patientData[VALUE];
		
	//Variable declaration
	int counter, selection;

	//Read the binary file "PatientVist.bin" and write the content in this file to structure array and return one integer value which is how many element that array use to records the data in "PatientVisit.bin"
	counter = readPatientVisit(patientData);

	//Display Logo
	printf("                        **       **\n");
	printf("                       *  *     *  *\n");
	printf("                            ***\n");
	printf("              Welcome to Patient Visit System  ^-^  \n\n");

	//Print the menu that consists of all the function that this system have and loop until the user choice to exit this system
	do {
		printf("\n");
		printf("                          Menu \n");
		printf("                          ==== \n");
		printf("                 1. Add Patient Data\n");
		printf("                 2. Display Patient Data\n");
		printf("                 3. Search Patient Data \n");
		printf("                 4. Modify Patient Data \n");
		printf("                 5. Medical Check \n");
		printf("                 6. Delete Patient Data\n");
		printf("                 7. Exit Patient Visit System\n");
		printf("\n");

		//Let user to enter the function that the user need to perform
		printf("         Please enter your choice > ");
		scanf("%d", &selection);
		rewind(stdin);
		printf("\n");

		//Call the function depend on which functions that user choice and also print the error message if the user input the invalid selection
		switch (selection)
		{
		case 1:
			counter = addPatientVisit(patientData, counter);
			break;
		case 2:
			displayPatientVisit(patientData, counter);
			break;
		case 3:
			searchPatientVisit(patientData, counter);
			break;
		case 4:
			modifyPatientVisit(patientData, counter);
			break;
		case 5:
			medicalCheck(patientData, counter);
			break;
		case 6:
			counter = deletePatientVisit(patientData, counter);
			break;
		case 7:
			exitProgram(patientData, counter);
			break;
		default:
			printf("Invalid Selection !!! Please enter again !!! \n");
		}
	} while (selection != 7);

	system("pause");
}

//On beginning of this system run, this function will read and write all the content in "PatientVisit.bin" into strucutre array and return a value which represent how many element of the array uses to record the data in the "PatientVisit.bin"
int readPatientVisit(PatientVisit data[VALUE])
{
	//Variable declaration that store how many element that array use to record the data in "PatientVisit.bin"
	int count = 0;

	//File pointer declaration
	FILE *patient;

	//Open the file "PatientVisit.bin" for reading and store address of this file into patient
	patient = fopen("PatientVisit.bin", "rb");

	//Check whether the file is successful open if fail to open the file error message will printed and exit the program
	if (patient == NULL)
	{
		printf("Unable to open the file <PatientVisit.bin> !!! \n");
		exit(-1);
	}

	//Read all the element in "PatientVisit.bin" until end-of-file and write the content into structure array data
	while (fread(&data[count], sizeof(PatientVisit), 1, patient) != 0)
	{
		count++;
	}

	//Close the file "PatientVisit.bin"
	fclose(patient);

	//Return a value which represent how many element that struture array use to store the element of the array
	return count;
}

//Allow user to add new record of Patient Visit
int addPatientVisit(PatientVisit data[VALUE], int count) {

	//Variable declaration
	char codition;
	int temp;

	//Get system time from computer
	SYSTEMTIME t;
	GetLocalTime(&t);

	//Display the title of this fun ction
	printf("\tAdd Patient Data\n");
	printf("\t================\n\n");
	
	//Prompt user to input the Patient information and loop until no more data to record
	do {
		data[count].days = t.wDay;
		data[count].month = t.wMonth;
		data[count].years = t.wYear;
		data[count].hours = t.wHour;
		data[count].minutes = t.wMinute;
		rewind(stdin);
		printf("STAFF INFORMATION : \n");
		printf("  Staff ID > ");
		gets(data[count].staffID);
		rewind(stdin);
		printf("\n");
		printf("PATIENT INFORMATION : \n");
		//The system will generated the new Patient ID to makesure the Patient ID is not repeated
		char id[9] = "P00", append[3];
		temp = count;
		temp++;
		sprintf(append, "%02d", temp);
		strcat(id, append);
		strcpy(data[count].patientID, id);
		printf("  Patient ID > %s\n", data[count].patientID);
		rewind(stdin);
		printf("  Patient Name > ");
		gets(data[count].patientName);
		rewind(stdin);
		data[count].gender = getGender();
		printf("  Age > ");
		//Check whether the age is integer if not prompt the user to enter again
		while (scanf("%d", &data[count].age) != 1)
		{
			printf("Invalid age entered!!! Age must be in integer form!!!\n");
			printf("  Age > ");
			scanf("%d", &data[count].age);
			rewind(stdin);
		}
		rewind(stdin);
		printf("  Diagnosis > ");
		gets(data[count].diagnosis);
		rewind(stdin);
		printf("  Fee charges(RM) > ");
		scanf("%lf", &data[count].charges);
		rewind(stdin);
		strcpy(data[count].medical.status, "None");
		printf("\nAny new record? (Y = yes/N = no) > ");
		scanf("%c", &codition);
		rewind(stdin);
		printf("\n\n");
		count++;
	} while (codition != 'n' && codition != 'N');

	//Return new value which represent how many element that struture array use to store the element of the array
	return count;
}

//Display all the Patient Visit information that store in the structure array
void displayPatientVisit(PatientVisit data[VALUE], int count)
{
	//Variable declaration
	int a, codition = 0;
	char selection, id[9];

	//Display the title of this function
	printf("\tDislay Patient Data\n");
	printf("\t===================\n\n");

	//Display the patient visit information
	printf(" Staff ID   Patient ID  Patient Name      Gender  Age  Diagnosis                 Time        Charges   Status\n");
	printf("===============================================================================================================\n");

	for (a = 0; a < count; a++)
	{
		printf("   %-5s      %-7s   %-20s%c     %2d   %-20s%02d/%02d/%d %02d:%02d   %.2lf    %-8s\n", data[a].staffID, data[a].patientID, data[a].patientName, toupper(data[a].gender), data[a].age, data[a].diagnosis, data[a].days, data[a].month, data[a].years, data[a].hours, data[a].minutes, data[a].charges, data[a].medical.status);
	}
	printf("===============================================================================================================\n");
	printf("        < %d records listed > \n\n", a);
	
	//Ask user whether the user want to view the patient's medical check record
	printf("Want to view status details (Y = yes/N = no) > ");
	scanf("%c", &selection);
	rewind(stdin);
	//If user answer is yes medical check record will displayed
	if (selection == 'y' || selection == 'Y')
	{
		do {
			codition = 0;
			printf("\nPlease enter Patient ID > ");
			gets(id);
			rewind(stdin);
			for (a = 0; a < count; a++)
			{
				if (strcmp(id, data[a].patientID) == 0)
				{
					codition++;
					if (strcmp(data[a].medical.status, "None") == 0)
						printf("No any medical check record found !\n");
					else {
						printf("\nPatient Name > %s\n", data[a].patientName);
						printf("\nMedical Check Details : \n\n");
						printf("Blood Presure\n");
						printf("Systolic pressure(mm Hg)  : %d\n", data[a].medical.systolicBloodPressure);
						printf("Diastolic pressure(mm Hg) : %d\n", data[a].medical.diastolicBloodPressure);
						if (data[a].medical.systolicBloodPressure >= 120 && data[a].medical.systolicBloodPressure <= 140 || data[a].medical.diastolicBloodPressure >= 80 && data[a].medical.diastolicBloodPressure <= 90)
							printf("Remarks : Blood pressure is normal.\n");
						else if (data[a].medical.systolicBloodPressure < 120 || data[a].medical.diastolicBloodPressure < 80)
							printf("Remarks : Blood pressure is low!!!\n");
						else if (data[a].medical.systolicBloodPressure > 140 || data[a].medical.diastolicBloodPressure > 90)
							printf("Remarks : Blood pressure is high!!! \n");

						printf("\nBlood Sugar\n");
						printf("Blood Sugar Levels(mmol/L) : %d\n", data[a].medical.bloodSugarTest);
						if (data[a].medical.bloodSugarTest >= 4 && data[a].medical.bloodSugarTest <= 5.4)
							printf("Remarks : Blood suger level is normal.\n");
						else if (data[a].medical.bloodSugarTest < 4)
							printf("Remarks : Blood suger level is low!!!\n");
						else if (data[a].medical.bloodSugarTest > 5.4)
							printf("Remarks : Blood sugar level is high!!!\n");

						printf("\nCholesterol Level\n");
						printf("Cholesterol level(mg/dL) : %d\n", data[a].medical.cholesterol);
						if (data[a].medical.cholesterol < 200)
							printf("Remarks : Cholesterol level is normal.\n");
						else if (data[a].medical.cholesterol >= 200 && data[a].medical.cholesterol <= 239)
							printf("Remarks : Cholesterol level is Borderline high.\n");
						else if (data[a].medical.cholesterol >= 240)
							printf("Remarks : Cholesterol level is high!!!\n");

						printf("\nOverall Results : %s\n", data[a].medical.status);
					}
					printf("\nWant to view another status details? (Y = yes/N = no) > ");
					scanf("%c", &selection);
					rewind(stdin);
				}
			}
			if(codition == 0)
				printf("Invalid Patient ID entered!!! Please enter again!!!\n");
		} while (selection != 'n' && selection != 'N');

	}

}

//Allow user to search the Patient Visit information
void searchPatientVisit(PatientVisit data[VALUE], int count)
{
	//Variable declaration
	int a, counter = 0;
	char pID[9], selection;

	//Display the title of this function
	printf("\tSearch Patient Data\n");
	printf("\t===================\n\n");

	//Allow user to input the patient ID to view the record of the patient visit
	do {
		printf("Please enter Patient ID > ");
		gets(pID);
		rewind(stdin);
		counter = 0;

		for (a = 0; a < count; a++)
		{
			if (strcmp(pID, data[a].patientID) == 0)
			{
				printf(" Staff ID   Patient ID  Patient Name      Gender  Age  Diagnosis                 Time        Charges   Status\n");
				printf("===============================================================================================================\n");
				printf("   %-5s      %-7s   %-20s%c     %d   %-20s%02d/%02d/%d %02d:%02d   %.2lf    %-8s\n", data[a].staffID, data[a].patientID, data[a].patientName, toupper(data[a].gender), data[a].age, data[a].diagnosis, data[a].days, data[a].month, data[a].years, data[a].hours, data[a].minutes, data[a].charges, data[a].medical.status);
				printf("===============================================================================================================\n");
				counter++;
				printf("        < %d records found > \n\n", counter);

				printf("Want to view status details (Y = yes/N = no) > ");
				scanf("%c", &selection);
				rewind(stdin);

				if (selection == 'y' || selection == 'Y')
				{
					if (strcmp(data[a].medical.status, "None") == 0)
						printf("No medical check record found !!!\n");
					else {
						printf("\nMedical Check Details : \n\n");
						printf("Blood Presure\n");
						printf("Systolic pressure(mm Hg)  : %d\n", data[a].medical.systolicBloodPressure);
						printf("Diastolic pressure(mm Hg) : %d\n", data[a].medical.diastolicBloodPressure);
						if (data[a].medical.systolicBloodPressure >= 120 && data[a].medical.systolicBloodPressure <= 140 || data[a].medical.diastolicBloodPressure >= 80 && data[a].medical.diastolicBloodPressure <= 90)
							printf("Remarks : Blood pressure is normal.\n");
						else if (data[a].medical.systolicBloodPressure < 120 || data[a].medical.diastolicBloodPressure < 80)
							printf("Remarks : Blood pressure is low!!!\n");
						else if (data[a].medical.systolicBloodPressure > 140 || data[a].medical.diastolicBloodPressure > 90)
							printf("Remarks : Blood pressure is high!!! \n");

						printf("\nBlood Sugar\n");
						printf("Blood Sugar Levels(mmol/L) : %d\n", data[a].medical.bloodSugarTest);
						if (data[a].medical.bloodSugarTest >= 4 && data[a].medical.bloodSugarTest <= 5.4)
							printf("Remarks : Blood suger level is normal.\n");
						else if (data[a].medical.bloodSugarTest < 4)
							printf("Remarks : Blood suger level is low!!!\n");
						else if (data[a].medical.bloodSugarTest > 5.4) {
							printf("Remarks : Blood sugar level is high!!!\n");
						}
							
						printf("\nCholesterol Level\n");
						printf("Cholesterol level(mg/dL) : %d\n", data[a].medical.cholesterol);
						if (data[a].medical.cholesterol < 200)
							printf("Remarks : Cholesterol level is normal.\n");
						else if (data[a].medical.cholesterol >= 200 && data[a].medical.cholesterol <= 239)
							printf("Remarks : Cholesterol level is Borderline high.\n");
						else if (data[a].medical.cholesterol >= 240)
							printf("Remarks : Cholesterol level is high!!!\n");

						printf("\nOverall Results : %s\n", data[a].medical.status);
					}
				}
			}
		}//If no result found error message will printed
		if (counter == 0)
			printf("No result found !!!\n");

		//Ask user wheather want to add another record if no exit this function
		printf("\nWant to search another record? (Y = yes/N = no) > ");
		scanf("%c", &selection);
		rewind(stdin);
	} while (selection != 'n' && selection != 'N');
}

//Allow user to modify the Patient Visit information
void modifyPatientVisit(PatientVisit data[VALUE], int count)
{
	//Variable declaration
	int a, choice, counter = 0;
	char pID[9], selection;

	//Display the title of this function
	printf("\tModify Patient Data\n");
	printf("\t===================\n");

	//Prompt user to enter the patient ID to be modify and loop until no more data to modify
	do{
		printf("\nPatient ID > ");
		gets(pID);
		rewind(stdin);
	
		//Search the Patient data according to patient ID
		for (a = 0; a < count; a++)
		{
			//If the patient ID that user input match which the patient ID that store inside structure array patient visit information to particular patient will displayed
			if (strcmp(pID, data[a].patientID) == 0)
			{
				printf(" Staff ID   Patient ID  Patient Name      Gender  Age  Diagnosis                 Time        Charges   Status\n");
				printf("===============================================================================================================\n");
				printf("   %-5s      %-7s   %-20s%c     %d   %-20s%02d/%02d/%d %02d:%02d   %.2lf    %-8s\n", data[a].staffID, data[a].patientID, data[a].patientName, toupper(data[a].gender), data[a].age, data[a].diagnosis, data[a].days, data[a].month, data[a].years, data[a].hours, data[a].minutes, data[a].charges, data[a].medical.status);
				printf("===============================================================================================================\n");
				counter++;
				//Prompt user to choose which data that user want to modify
				do {
					printf("Please select which data that you want to modify : \n");
					printf("\t1. Staff ID\n");
					printf("\t2. Patient Name\n");
					printf("\t3. Gender\n");
					printf("\t4. Age\n");
					printf("\t5. Diagnosis\n");
					printf("\t6. Time\n");
					printf("\t7. Charges\n");
					printf("\t8. Exit\n\n");
					printf("Please enter you selction > ");
					scanf("%d", &choice);
					rewind(stdin);
					//Modify Staff ID
					if (choice == 1)
					{
						printf("Staff ID > ");
						gets(data[a].staffID);
						rewind(stdin);
					}//Modify Patient Name
					else if (choice == 2)
					{
						printf("Patient Name > ");
						gets(data[a].patientName);
						rewind(stdin);
					}//Modify Patient's gender
					else if (choice == 3)
					{
						data[a].gender = getGender();
					}//Modify Patient's ages
					else if (choice == 4)
					{
						printf("Age > ");
						//Check whether the age is integer if not prompt the user to enter again
						while (scanf("%d", &data[a].age) != 1)
						{
							printf("Invalid age entered!!! Age must be in integer form!!!\n");
							printf("Age > ");
							scanf("%d", &data[a].age);
							rewind(stdin);
						}
						rewind(stdin);
					}//Modify Patient's diagnosis
					else if (choice == 5)
					{
						printf("Diagnosis > ");
						gets(data[a].diagnosis);
						rewind(stdin);
					}//Modify time
					else if (choice == 6)
					{
						printf("Date (day/month/year) > ");
						scanf("%d/%d/%d", &data[a].days, &data[a].month, &data[a].years);
						rewind(stdin);
						printf("Time (hours:minutes) > ");
						scanf("%d:%d", &data[a].hours, &data[a].minutes);
						rewind(stdin);
					}//Modify payment that patient paid
					else if (choice == 7)
					{
						printf("Charges > ");
						scanf("%lf", &data[a].charges);
						rewind(stdin);
					}//The user no want to edit this patient's data and the system will ask whether the user want to modify another patient's data
					else if (choice == 8)
						break;
					//Error message printed if the user enter the selction which is no between 0 to 8
					else
						printf("Invalid Input!!! Please enter again!!!\n");
					printf("\n");
					//Display updated record
					printf(" Staff ID   Patient ID  Patient Name      Gender  Age  Diagnosis                 Time        Charges   Status\n");
					printf("===============================================================================================================\n");
					printf("   %-5s      %-7s   %-20s%c     %d   %-20s%d/%d/%d %02d:%02d   %.2lf    %-8s\n", data[a].staffID, data[a].patientID, data[a].patientName, toupper(data[a].gender), data[a].age, data[a].diagnosis, data[a].days, data[a].month, data[a].years, data[a].hours, data[a].minutes, data[a].charges, data[a].medical.status);
					printf("===============================================================================================================\n");
					//Ask user whether need to modify another data
					printf("\nWhat to modify another record? (Y = yes/N = no) > ");
					scanf("%c", &selection);
					rewind(stdin);
					printf("\n");
				} while (selection != 'n' && selection != 'N');
			}
		}//Display error message if cannot find the patient's record
		if (counter == 0)
			printf("No record found!!!\n");
		//Ask user whether want to modify another Patient Visit record if no exit this function
		printf("What to modify another patient data? (Y = yes/N = no) > ");
		scanf("%c", &selection);
		rewind(stdin);
	} while (selection != 'n' && selection != 'N');

}

//Record the medical check result for the particular patient
void medicalCheck(PatientVisit data[VALUE], int count)
{
	//Variable declaration
	int a, bloodPresureStatus, bloodSugarStatus, cholesterolStatus;
	char patientIDNumber[9], codition;

	//Display the title of this function
	printf("\tMedical Check\n");
	printf("\t=============\n\n");

	//Prompt user to input the Patient ID and loop until no more medical check record that user need to record
	do {
		printf("Please enter Patient ID > ");
		gets(patientIDNumber);
		rewind(stdin);
		//Search the patient data in structure array
		for (a = 0; a < count; a++)
		{
			//If the record found prompt user to input the medical check result 
			if (strcmp(patientIDNumber, data[a].patientID) == 0)
			{
				printf("\nPatient Name : %s \n\n", data[a].patientName);
				printf("Please enter systolic pressure(mm Hg) > ");
				scanf("%d", &data[a].medical.systolicBloodPressure);
				rewind(stdin);
				printf("Please enter diastolic pressure(mm Hg) > ");
				scanf("%d", &data[a].medical.diastolicBloodPressure);
				rewind(stdin);
				if (data[a].medical.systolicBloodPressure >= 120 && data[a].medical.systolicBloodPressure <= 140 || data[a].medical.diastolicBloodPressure >= 80 && data[a].medical.diastolicBloodPressure <= 90)
				{
					printf("Blood pressure is normal.\n");
					bloodPresureStatus = 1;
				}
				else if (data[a].medical.systolicBloodPressure < 120 || data[a].medical.diastolicBloodPressure < 80)
				{
					printf("Blood pressure is low!!!\n");
					bloodPresureStatus = 0;
				}
				else if (data[a].medical.systolicBloodPressure > 140 || data[a].medical.diastolicBloodPressure > 90)
				{
					printf("Blood pressure is high!!! \n");
					bloodPresureStatus = 0;
				}
				else
					printf("Invalid Input !!! \n");

				printf("\nPlease enter Blood Sugar Levels(mmol/L) > ");
				scanf("%d", &data[a].medical.bloodSugarTest);
				rewind(stdin);
				if (data[a].medical.bloodSugarTest >= 4 && data[a].medical.bloodSugarTest <= 5.4)
				{
					printf("Blood suger level is normal.\n");
					bloodSugarStatus = 1;
				}
				else if (data[a].medical.bloodSugarTest < 4)
				{
					printf("Blood suger level is low!!!\n");
					bloodSugarStatus = 0;
				}
				else if (data[a].medical.bloodSugarTest > 5.4)
				{
					printf("Blood sugar level is high!!!\n");
					bloodSugarStatus = 0;
				}
				else
					printf("Invalid Input !!! \n");

				printf("\nPlease enter Cholesterol level(mg/dL) > ");
				scanf("%d", &data[a].medical.cholesterol);
				rewind(stdin);
				if (data[a].medical.cholesterol < 200)
				{
					printf("Cholesterol level is normal.\n");
					cholesterolStatus = 1;
				}
				else if (data[a].medical.cholesterol >= 200 && data[a].medical.cholesterol <= 239)
				{
					printf("Cholesterol level is Borderline high.\n");
					cholesterolStatus = 1;
				}
				else if (data[a].medical.cholesterol >= 240)
				{
					printf("Cholesterol level is high!!!\n");
					cholesterolStatus = 0;
				}
				else
					printf("Invalid Input !!! \n");

				if (bloodPresureStatus == 1 && bloodSugarStatus == 1 && cholesterolStatus == 1)
				{
					strcpy(data[a].medical.status, "Normal");
				}
				else if (bloodPresureStatus == 0 || bloodSugarStatus == 0 || cholesterolStatus == 0)
				{
					strcpy(data[a].medical.status, "Abnormal");
				}
			}
		}//Ask user whether have another patient's medical check result need to add if no exit the function
		printf("\nAdd more record? (Y = yes/N = no) > ");
		scanf("%c", &codition);
		rewind(stdin);
	} while (codition != 'n' && codition != 'N');
}

//Delete the patient visit information
int deletePatientVisit(PatientVisit data[VALUE], int count)
{
	//Variable declaration
	int a = 0, counter = 0, temp, counter1;
	char pID[9], action;

	//Assign the value in parameter count into counter1
	counter1 = count;

	//Display the title of this function
	printf("\tDelete Patient Visit\n");
	printf("\t====================\n");

	//Prompt user to enter the Patient ID to be delete
	printf("\nPatient ID > ");
	gets(pID);
	rewind(stdin);

	//Search the patient record in struture array
	for (a = 0; a < count; a++)
	{
		//If the patient record found display the patient record and aks the user whether confirm to delete or not
		if (strcmp(pID, data[a].patientID) == 0)
		{
			printf(" Staff ID   Patient ID  Patient Name      Gender  Age  Diagnosis                 Time        Charges   Status\n");
			printf("===============================================================================================================\n");
			printf("   %-5s      %-7s   %-20s%c     %d   %-20s%02d/%02d/%d %02d:%02d   %.2lf    %-8s\n", data[a].staffID, data[a].patientID, data[a].patientName, toupper(data[a].gender), data[a].age, data[a].diagnosis, data[a].days, data[a].month, data[a].years, data[a].hours, data[a].minutes, data[a].charges, data[a].medical.status);
			printf("===============================================================================================================\n\n");
			printf("Are you sure want to delete it?(Y = yes/N = no) > ");
			scanf("%c", &action);
			//If the user input y the information that displayed will deleted
			if (action == 'y' || action == 'Y')
			{
				for (temp = a; temp < count; temp++)
					data[temp] = data[temp + 1];
				printf("1 records delete succesful\n");
				counter1 = counter1 - 1;
			}//If the user input n the deleting process will cancelled
			else
				printf("Delete Cancelled!!!\n");
			counter++;
		}
	}//If no record found the system will display the error message and exit the function
	if (counter == 0)
		printf("No record found!!!\n");
	
	
	return counter1;
}

//Check whether the user input the correct data for gender
char getGender()
{
	//Variable declaration
	char gender;

	//Prompt user input the gender
	printf("  Gender(M = Male/F = Female) > ");
	scanf("%c", &gender);
	rewind(stdin);
	//Valid the gender whether the input is either 'F' or 'M' if not this funtion will tell the user to input again
	while((gender != 'm' && gender != 'M' && gender != 'f' && gender != 'F' || isalpha(gender) == 0 ))
	{
		printf("Invalid gender entered!!! (M = male/F = female)\n");
		printf("  Gender(M = Male/F = Female) > ");
		scanf("%c", &gender);
		rewind(stdin);
	}

	//Return the gender to main program
	return gender;
}

//Exit the program and write all the data in structure array to file "PatientVisit.bin"
void exitProgram(PatientVisit data[VALUE], int count)
{
	//Variable declaration
	int a = 0;
	//Declare a file pointer called patient
	FILE *patient;

	//Open the file "PatientVisit.bin" for writing and store address of this file into patient
	patient = fopen("PatientVisit.bin", "wb");

	//Check whether the file is successful open if fail to open the file error message will printed and exit the program
	if (patient == NULL)
	{
		printf("Unable to open the file <PatientVisit.bin> !!! \n");
		exit(-1);
	}

	//Write all the content in structure array data into file "PatientVisit.bin"
	for (a = 0; a < count; a++) {
		fwrite(&data[a], sizeof(PatientVisit), 1, patient);
	}

	//Display the message to tell user all the data has been successful write to PatientVisit.bin
	printf("All the data has been successful write to PatientVisit.bin ^-^\n\n");

	//Close the file "PatientVisit.bin"
	fclose(patient);
}