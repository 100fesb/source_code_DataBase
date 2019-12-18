//int Izbornik();
//int StvoriListuStudenata();
//int BrisiStudenta();
//int BrisiSveStudente();
//int BrisiPredmetStudentu();
//int PromjeniImeStudenta();
//int PromjeniPrezimeStudenta();
//int PromjeniOcjenuStudenta();
//int DodajStudenta();
//int DodajPredmetStudentu();
//int IspisiTrazenogStudenta();
//int IspisiSveStudente();



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

//#include "Studenti.h"
#include "Constants.h"

//deklarirali pokazivace
typedef struct Studenti* PozicijaS;					//pokazivac na sljedeceg studenta
typedef struct PredmetiOcjene_PO* PozicijaPO;		//pokazivac na predmete profesora



struct Studenti{	//1

	//ovdje ide ID za ime studenta
	int ID;
	char ImePrezime[NAME_LENGTH];
	//pokazivac na sljedeceg studenta
	PozicijaS NextS;
	//pokazivac na predmete i ocjene studenta
	PozicijaPO NextPO;

};


// AVL stablo za studenta - vraca pokazivac na prvi element (root), prima root (do upsisa ce bit NULL) 
PozicijaS generirajAVL_Student(PozicijaS P)
{
	char *fileName = NULL;
	FILE *fp = NULL;
	PozicijaAVL root = NULL;

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
		/*printf("ID: %d Name Acronim: %s\n", id, str);*/

		root = DodajAVL(id, root);

	}

	fclose(fp);
	return root;
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