#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "Constants.h"
#include "Predmeti.h"
#include "Studenti.h"
#include "Profesori.h"



int main()
{
	StabloAVL rootS = NULL, nadjeni = NULL;
	StabloAVLPre rootP = NULL;		//predmet
	StabloAVLPro rootPr = NULL;		//profesor 
	int tempID = 0;
	StabloAVL NadjeniS = NULL;
	PozicijaAVLPre NadjeniPre = NULL;
	PozicijaAVLPro NadjeniPro = NULL;

	int id;


	rootS = generirajAVL_Student(rootS);
	rootP = generirajAVL_Predmeti(rootP);
	rootPr = generirajAVL_Profesori(rootPr);

	print_t(rootS);

	
	/*
	printf("Unesite ID trazenog studenta:");
	scanf(" %d", &tempID);
	NadjeniS = nadiPoID(tempID, rootS);
	printf("Nasli smo ga! To je %d %s", NadjeniS->ID, NadjeniS->PrezimeIme);
	*/

	/*
	printf("Unesite ID trazenog predmeta:");
	scanf(" %d", &tempID);
	NadjeniPre = nadiPoIDPre(tempID, rootP);
	printf("Nasli smo ga! To je %d %s", NadjeniPre->ID, NadjeniPre->ImePre);
	*/

	/*
	printf("Unesite ID trazenog profesora:");
	scanf(" %d", &tempID);
	NadjeniPro = nadiPoIDPro(tempID, rootPr);
	printf("Nasli smo ga! To je %d %s", NadjeniPro->ID, NadjeniPro->ImePro);
	*/

	ispisSvihOcjenaStudenta(rootS, rootP);


	system("pause");
	return 0;
}

