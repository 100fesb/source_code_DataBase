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

FILE* OtvoriDatoteku(char* fileName)
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

	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("\r\n\tError!\r\n\t%s Nije moguce citanje datoteke, molimo pokusajte ponovno.", fileName);
		return NULL;
	}

	return fp;
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

		printf("\n\n\t1 - Unos %sa\n\t2 - Ispis %sa\n\t3 - Brisanje %sa\n\t0 - Nazad\n\t\Unos: ", TEMP_NAME_HOLDER, TEMP_NAME_HOLDER, TEMP_NAME_HOLDER);
		scanf("%d", &izbor2);

		switch (izbor2)
		{
		case 1:
			// unos
			printf("\tunos");
			if (izbor == 1) unesiStudenta(rootS);

			break;
		case 2:
			printf("ispis");
			break;
		case 3:
			printf("brisanje");
			break;
		}

	} while (izbor2 != 0);

	return SUCCESS;
}