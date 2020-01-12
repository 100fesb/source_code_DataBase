#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Constants.h"
#include "Profesori.h"


PozicijaAVLPro nadiPoIDPro(int tempID, PozicijaAVLPro Root)
{
	if (!Root) return NULL;

	if (tempID > Root->ID) nadiPoIDPro(tempID, Root->D);
	else if (tempID < Root->ID) nadiPoIDPro(tempID, Root->L);
	else return Root;
}


StabloAVLPro DodajAVLPro(int ID, char* PI, StabloAVLPro S)
{
	int n = 0;
	if (NULL == S)
	{
		S = (StabloAVLPro)malloc(sizeof(CvorAVLPro));
		S->ID = ID;
		S->visina = 0;
		strcpy(S->ImePro, PI);
		S->L = S->D = NULL;
	}
	else
	{
		if (ID < S->ID) {
			S->L = DodajAVLPro(ID, PI, S->L);
			n = Visina(S->L) - Visina(S->D);
			if (n == 2) {
				if (ID < S->L->ID) S = JednostrukaRL(S);
				else S = DvostrukaRL(S);
			}
		}
		else if (ID > S->ID)
		{
			S->D = DodajAVLPro(ID, PI, S->D);
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

StabloAVLPro generirajAVL_Profesori(StabloAVLPro P)
{
	FILE* fp = NULL;
	char red[BUFFER_LENGTH];
	int i = 0;

	int id = NULL;
	char imeProfesora[NAME_LENGTH];
	char* buff = NULL;
	buff = (char*)malloc(sizeof(char) * BUFFER_LEN);

	fp = OtvoriDatoteku("Predmeti.txt");

	if (!fp) return NULL;

	while (!feof(fp))
	{


		fgets(buff, BUFFER_LEN, fp);
		sscanf(buff, "%d %[^\n]", &id, imeProfesora);

		P = DodajAVLPro(id, imeProfesora, P);
	}


	fclose(fp);

	// treba vratiti root
	return P;
}

int VisinaPro(StabloAVLPro S)
{

	if (NULL == S) return -1;

	if (NULL == S->L && NULL == S->D) return 0;

	if (NULL == S->L) {
		return 1 + VisinaPro(S->D);
	}
	else if (NULL == S->D) {
		return 1 + VisinaPro(S->L);
	}
	// slucaj kada imamo dijete i slijeva i zdesna
	else {
		return Max(VisinaPro(S->L), VisinaPro(S->D)) + 1;
	}
}


PozicijaAVLPro JednostrukaRLPro(PozicijaAVLPro K2)
{
	PozicijaAVLPro K1;

	K1 = K2->L;
	K2->L = K1->D;
	K1->D = K2;

	K2->visina = Max(VisinaPro(K2->L), VisinaPro(K2->D)) + 1;
	K1->visina = Max(VisinaPro(K1->L), K2->visina) + 1;

	return K1;
}

PozicijaAVLPro JednostrukaRDPro(PozicijaAVLPro K2)
{
	PozicijaAVLPro K1;

	K1 = K2->D;
	K2->D = K1->L;
	K1->L = K2;

	K2->visina = Max(VisinaPro(K2->D), VisinaPro(K2->L)) + 1;
	K1->visina = Max(VisinaPro(K1->D), K2->visina) + 1;

	return K1;
}

PozicijaAVLPro DvostrukaRLPro(PozicijaAVLPro K3)
{
	K3->L = JednostrukaRDPro(K3->L);

	return JednostrukaRLPro(K3);
}

PozicijaAVLPro DvostrukaRDPro(PozicijaAVLPro K3)
{
	K3->D = JednostrukaRLPro(K3->D);

	return JednostrukaRDPro(K3);
}

