#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<time.h>

//#include "Studenti.h"
#include "Constants.h"

//deklarirali pokazivace
typedef struct Studenti* PozicijaS;					//pokazivac na sljedeceg studenta
typedef struct PredmetiOcjene_PO* PozicijaPO;		//pokazivac na predmete profesora

struct Studenti{	//1

	//ovdje ide ID za ime studenta
	int ID;
	//pokazivac na sljedeceg studenta
	PozicijaS Next;
	//pokazivac na predmete i ocjene studenta
	PozicijaPO Next;

};

PozicijaS generateAVL_S(PozicijaS P)
{
	char *fileName = NULL;
	FILE *fp = NULL;

	//temp variable
	int id = NULL;
	char* str = NULL;
	str = (char*)malloc(sizeof(char*)*BUFFER_LENGTH);
	if (!str) return ERROR;

	fileName = (char*)malloc(sizeof(char)* BUFFER_LENGTH);
	if (fileName == NULL) return ERROR;
	memset(fileName, '\0', BUFFER_LENGTH);

	printf("\r\n\tEnter file name : ");
	scanf(" %s", fileName);

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("\r\n\tError!\r\n\t%s The file couldn't be opened.", fileName);
		return ERROR;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %d %s", &id, str);
		printf("ID: %d Name Acronim: %s\n", id, str);



	}

	fclose(fp);
}

PozicijaS findById(int id)
{
	
}

//int Izbornik()
//{
//	//ovjde cemo unijeti listu potrebnik izbora za nase potrebe
//	printf("\n\n\t\t\t");
//	printf("1-");
//	printf("");
//	printf("");
//	printf("");
//	printf("");
//	printf("");
//	printf("");
//	printf("");
//
//	return 0;
//
//}