#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#include "Constants.h"
#include "Assets.h"
#include "Studenti.h"
#include "Predmeti.h"
#include "Profesori.h"

int getNthItemFromString(int INDEX, char* STR)
{
	int i = 0;
	int tempItem = -1;
	int readBytes = 0;

	while (i <= INDEX){
		sscanf(STR, " %d %n", &tempItem, &readBytes);
		STR += readBytes;
		i++;
	}

	return tempItem;
}


FILE* OtvoriDatoteku(char mode, char* fileName)
{
	FILE *fp = NULL;

	/*
	fileName = (char*)malloc(sizeof(char)* BUFFER_LENGTH);
	if (fileName == NULL) return NULL;
	memset(fileName, '\0', BUFFER_LENGTH);
	*/

	if (NULL == fileName){
		printf("\r\n\tUnesite ime datoteke : ");
		scanf(" %s", fileName);
	}
	
	
	

	//strcpy(fileName, "StudentiPotpunaTablica"); // ZA TEST SAMO, ODKOMENTIRAT IZNAT U PRODUKCIJI

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	if (mode == 'r') fp = fopen(fileName, "r");
	else if (mode == 'w') fp = fopen(fileName, "w");
	else if (mode == 'a') fp = fopen(fileName, "a");

	if (fp == NULL)
	{
		printf("\r\n\tError!\r\n\tNije moguce ucitavanje datoteke '%s', molimo pokusajte ponovno.", fileName);
		return NULL;
	}

	return fp;
}

char* readLine()
{
	char placeholder[NAME_LENGTH] = "";
	fflush(stdin);
	fgets(placeholder, sizeof(placeholder), stdin);
	if (placeholder[strlen(placeholder) - 1] == '\n') placeholder[strlen(placeholder) - 1] = NULL;

	return placeholder;
}


int Max(int a, int b)
{
	return a > b ? a : b;
}

int generirajID(int MIN, int MAX)
{
	int DIVIDER = MAX - MIN;
	return rand() % DIVIDER + MIN;
}

int nadjiIdPoImenu(FILE* fp, char* ime)
{
	int ID = 0;
	char tempStr[BUFFER_LENGTH] = "";

	while (!feof(fp))
	{
		fscanf(fp, "%d %[^\n]", &ID, tempStr);
		if (!strcmp(tempStr, ime)) return ID;
	}


	return ERROR;
}

int ispisIzbornika(StabloAVL rootS, StabloAVLPre rootPre, StabloAVLPro rootPro)
{
	int izbor = 0;
	int izbor2 = 0;
	char* TEMP_NAME_HOLDER = NULL;

	TEMP_NAME_HOLDER = (char*)malloc(sizeof(char)*NAME_LENGTH);


	do{
		printf("\n\n\t1 - Studenti\n\t2 - Predmeti\n\t3 - Profesori\n\t0 - Kraj Aplikacije\n\t\Unos: ");
		scanf("%d", &izbor);

		switch (izbor)
		{
			case 1:
				TEMP_NAME_HOLDER = "student";
				break;
			case 2:
				TEMP_NAME_HOLDER = "predmet";
				break;
			case 3:
				TEMP_NAME_HOLDER = "profesor";
				break;
		}
		if (izbor == 0) break;

		ispisPodIzbornika(rootS, rootPre, rootPro, izbor, TEMP_NAME_HOLDER);
		
	} while (izbor != 0);

	return SUCCESS;
}

int ispisPodIzbornika(StabloAVL rootS, StabloAVLPre rootPre, StabloAVLPro rootPro, int izbor, char* TEMP_NAME_HOLDER)
{
	int izbor2 = 0;

	do{

		printf("\n\n\t1 - Unos jednog %sa\n\t2 - Unos liste %sa\n\t3 - Ispis %sa\n\t4 - Brisanje %sa\n\t0 - Nazad\n\t\Unos: ", TEMP_NAME_HOLDER, TEMP_NAME_HOLDER, TEMP_NAME_HOLDER, TEMP_NAME_HOLDER);
		scanf("%d", &izbor2);

		switch (izbor2)
		{
		case 1:
			// unos jednog
			if (izbor == 1) unesiStudenta(rootS);
			if (izbor == 2) unesiPredmet(rootPre);
			if (izbor == 3) unesiProfesora(rootPro);

			break;
		case 2:
			// unos liste
			printf("\n\t~~Unesite kraj za prekid~~\n");
			if (izbor == 1){
				while (unesiStudenta(rootS) != END){ /*system("cls || clear");*/ }
			}
			else if (izbor == 2){
				while (unesiPredmet(rootPre) != END){ /*system("cls || clear");*/ }
			}
			else if (izbor == 3){
				while (unesiProfesora(rootPro) != END){ /*system("cls || clear");*/ }
			}


			break;
		case 3:
			printf("ispis");
			break;
		case 4:
			printf("brisanje");
			break;
		}

	} while (izbor2 != 0);

	return SUCCESS;
}