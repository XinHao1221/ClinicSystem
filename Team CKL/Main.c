#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<ctype.h>
#pragma warning(disable : 4996)

void patientInfo();
void patientVisit();
void staffInfo();

void printLogo() {
	for (int i = 0; i < 15; i++) {
		if (i > 5 && i < 10) {
			printf(" 				      =============================\n");
		}
		else
			printf("              					=========\n");
	}
	printf("\n						WELCOME~\n"
		"					THIS IS A CLINIC SYSTEM\n\n");
	
}

void main() {

	int mainMenuChoice;

	do {
		system("cls");

		printLogo();

		//print Main Menu
		printf("						MAIN MENU\n"
			"				1. Patient Infomation\n"
			"				2. Patient Visit\n"
			"				3. Staff Information\n"
			"				4. Exit\n"
			"				Please enter your choice > ");

		//Request for module selection
		scanf("%d", &mainMenuChoice);
		rewind(stdin);

		//Clear screen, set window size and print menu of module depends on user choice
		switch (mainMenuChoice) {
		case 1: 
			system("cls"); 
			patientInfo(); 
			break;
		case 2: 
			system("cls"); 
			patientVisit(); 
			break;
		case 3: 
			system("cls"); 
			staffInfo(); 
			break;
		case 4: 
			printf("Exited the program.\n"); 
			break;
		default: 
			printf("Invalid choice!\n");
		}


	} while (mainMenuChoice != 4);

	system("pause");
}