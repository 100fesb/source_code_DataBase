#include <stdlib.h>
#include <stdio.h>
#include "Studenti.h"


PozicijaAVL nadiPoID(int id, PozicijaAVL Root)
{
	if (!Root) return NULL;

	if (id > Root->ID) nadiPoID(id, Root->D);
	else if (id < Root->ID) nadiPoID(id, Root->L);
	else return Root;
}

int ispisStudenta(PozicijaAVL S)
{
	if (!S)
	{
		printf("Nismo nasli studenta!");
		return ERROR;
	}
	printf("Nadjeni student: %d %s", S->ID, S->PrezimeIme);
	return SUCCESS;
}

FILE* ispisZaglavljaStudenti()
{
	int brRedaka = 2;
	FILE* fp = NULL;
	char red[BUFFER_LENGTH];
	fp = OtvoriDatoteku();

	while (fgets(red, BUFFER_LENGTH, fp) != NULL && brRedaka != 0)
	{
		//fscanf(fp, "%[^\n]", red);
		printf("%s", red);
		brRedaka--;
	}
	return fp;
}

//int ispisSvihStudenata(PozicijaAVL Root)
//{
//	char red[BUFFER_LENGTH];
//	FILE* fp = NULL;
//	fp = ispisZaglavljaStudenti();
//
//	printf("Ispis nakon prve:\n");
//
//	while (fgets(red, BUFFER_LENGTH, fp) != NULL)
//	{
//		//fscanf(fp, "%[^\n]", red);
//		printf("%s", red);
//	}
//}

StabloAVL DodajAVL(int ID, char* PI, StabloAVL S)
{
	int n = 0;
	if (NULL == S)
	{
		S = (StabloAVL)malloc(sizeof(CvorAVL));
		S->ID = ID;
		S->visina = 0;
		strcpy(S->PrezimeIme, PI);
		S->L = S->D = NULL;
	}
	else
	{
		if (ID < S->ID){
			S->L = DodajAVL(ID, PI, S->L);
			n = Visina(S->L) - Visina(S->D);
			if (n == 2){
				if (ID < S->L->ID) S = JednostrukaRL(S);
				else S = DvostrukaRL(S);
			}
		}
		else if (ID > S->ID)
		{
			S->D = DodajAVL(ID, PI, S->D);
			n = Visina(S->D) - Visina(S->L);
			if (n == 2)
			{
				if (ID > S->D->ID) S = JednostrukaRD(S);
				else S = DvostrukaRD(S);
			}
		}
	}

	S->visina = Max(Visina(S->L), Visina(S->D)) + 1;
	return S;
}


// AVL stablo za studenta - vraca pokazivac na prvi element (root), prima root (do upsisa ce bit NULL)
// funkcije za AVL stabla moraju biti napisane posebno za svako AVLS jer moramo znati koji root vracamo (mogli smo sredit koji primamo preko druge funkcije)
StabloAVL generirajAVL_Student(StabloAVL P)
{
	FILE* fp = NULL;

	//temp variable
	int id = NULL;
	char str1[NAME_LENGTH / 2];
	char str2[NAME_LENGTH / 2];
	char prezimeIme[NAME_LENGTH];
	if (!str1 || !str2 || !prezimeIme) return ERROR;

	fp = OtvoriDatoteku();

	if (!fp) return NULL;

	while (!feof(fp))
	{

		fscanf(fp, " %d %s %s", &id, str1, str2);
		/*printf("ID: %d Name Acronim: %s\n", id, str);*/

		strcat(str1, " ");
		strcat(str1, str2);

		P = DodajAVL(id, str1, P);

	}


	fclose(fp);

	// treba vratiti root
	return P;
}

int Visina(StabloAVL S)
{

	if (NULL == S) return -1;

	if (NULL == S->L && NULL == S->D) return 0;

	if (NULL == S->L){
		return 1 + Visina(S->D);
	}
	else if (NULL == S->D){
		return 1 + Visina(S->L);
	}
	// slucaj kada imamo dijete i slijeva i zdesna
	else{
		return Max(Visina(S->L), Visina(S->D)) + 1;
	}
}


PozicijaAVL JednostrukaRL(PozicijaAVL K2)
{
	PozicijaAVL K1;

	K1 = K2->L;
	K2->L = K1->D;
	K1->D = K2;

	K2->visina = Max(Visina(K2->L), Visina(K2->D)) + 1;
	K1->visina = Max(Visina(K1->L), K2->visina) + 1;

	return K1;
}

PozicijaAVL JednostrukaRD(PozicijaAVL K2)
{
	PozicijaAVL K1;

	K1 = K2->D;
	K2->D = K1->L;
	K1->L = K2;

	K2->visina = Max(Visina(K2->D), Visina(K2->L)) + 1;
	K1->visina = Max(Visina(K1->D), K2->visina) + 1;

	return K1;
}

PozicijaAVL DvostrukaRL(PozicijaAVL K3)
{
	K3->L = JednostrukaRD(K3->L);

	return JednostrukaRL(K3);
}

PozicijaAVL DvostrukaRD(PozicijaAVL K3)
{
	K3->D = JednostrukaRL(K3->D);

	return JednostrukaRD(K3);
}

