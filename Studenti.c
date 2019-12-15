#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<time.h>

//deklarirali pokazivace
typedef struct Studenti* PozicijaStudent;					//pokazivac na sljedeceg studenta
typedef struct PredmetiOcjene_PO* PozicijaPredmet_PO;		//pokazivac na predmete profesora

struct Studenti{	//1

	//ovdje ide ID za ime studenta
	int ID_Ime;
	//pokazivac na sljedeceg studenta
	PozicijaStudent Next;
	//pokazivac na predmete studenta
	PozicijaPredmet_PO Next;

};

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