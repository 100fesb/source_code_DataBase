#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Constants.h"
#include "Predmeti.h"

int unesiPredmet(StabloAVLPre rootPre)
{
	FILE* fa = NULL;
	FILE* fr = NULL;
	int tempIDpredmeta = 0;
	char imePredmeta[NAME_LENGTH] = "";
	char imeProfesora[NAME_LENGTH] = "";
	char* tempStr = NULL;

	tempStr = (char*)malloc(sizeof(char)*NAME_LENGTH);


	tempIDpredmeta = generirajID(3000, 3999);
	// dodati u 'Predmeti.txt', upit koji profesor predaje, dodati u studPotpTab taj novi stupac

	fa = OtvoriDatoteku('a', "Predmeti.txt");

	printf("\n\t\t-- Ime predmeta: ");
	tempStr = readLine();
	strcat(imePredmeta, tempStr);
	fprintf(fa, "\n%d\t%s", tempIDpredmeta, imePredmeta);


	printf("\n\t\t-- Predavac (profesor): ");
	tempStr = readLine();
	strcat(imeProfesora, tempStr);
	rootPre

	return SUCCESS;
}


PozicijaAVLPre nadiPoIDPre(int tempID, PozicijaAVLPre Root)
{
	if (!Root) return NULL;

	if (tempID > Root->ID) nadiPoIDPre(tempID, Root->D);
	else if (tempID < Root->ID) nadiPoIDPre(tempID, Root->L);
	else return Root;
}

StabloAVLPre DodajAVLPre(int ID, char* PI, StabloAVLPre S)
{
	int n = 0;
	if (NULL == S)
	{
		S = (StabloAVLPre)malloc(sizeof(CvorAVLPre));
		S->ID = ID;
		S->visina = 0;
		strcpy(S->ImePre, PI);
		S->L = S->D = NULL;
	}
	else
	{
		if (ID < S->ID){
			S->L = DodajAVLPre(ID, PI, S->L);
			n = VisinaPre(S->L) - VisinaPre(S->D);
			if (n == 2){
				if (ID < S->L->ID) S = JednostrukaRLPre(S);
				else S = DvostrukaRLPre(S);
			}
		}
		else if (ID > S->ID)
		{
			S->D = DodajAVLPre(ID, PI, S->D);
			n = VisinaPre(S->D) - VisinaPre(S->L);
			if (n == 2)
			{
				if (ID > S->D->ID) S = JednostrukaRDPre(S);
				else S = DvostrukaRDPre(S);
			}
		}
	}

	S->visina = Max(VisinaPre(S->L), VisinaPre(S->D)) + 1;
	return S;
}

StabloAVLPre generirajAVL_Predmeti(StabloAVLPre P)
{
	FILE* fp = NULL;
	char red[BUFFER_LENGTH];
	int i = 0;

	int id = NULL;
	char imePredmeta[NAME_LENGTH];
	char* buff = NULL;
	buff = (char*)malloc(sizeof(char)* BUFFER_LEN);

	fp = OtvoriDatoteku('r', "Predmeti.txt");

	if (!fp) return NULL;

	while (!feof(fp))
	{


		fgets(buff, BUFFER_LEN, fp);
		sscanf(buff, "%d %[^\n]", &id, imePredmeta);

		P = DodajAVLPre(id, imePredmeta, P);
	}


	fclose(fp);

	// treba vratiti root
	return P;
}

int VisinaPre(StabloAVLPre S)
{

	if (NULL == S) return -1;

	if (NULL == S->L && NULL == S->D) return 0;

	if (NULL == S->L){
		return 1 + VisinaPre(S->D);
	}
	else if (NULL == S->D){
		return 1 + VisinaPre(S->L);
	}
	// slucaj kada imamo dijete i slijeva i zdesna
	else{
		return Max(VisinaPre(S->L), VisinaPre(S->D)) + 1;
	}
}


PozicijaAVLPre JednostrukaRLPre(PozicijaAVLPre K2)
{
	PozicijaAVLPre K1;

	K1 = K2->L;
	K2->L = K1->D;
	K1->D = K2;

	K2->visina = Max(VisinaPre(K2->L), VisinaPre(K2->D)) + 1;
	K1->visina = Max(VisinaPre(K1->L), K2->visina) + 1;

	return K1;
}

PozicijaAVLPre JednostrukaRDPre(PozicijaAVLPre K2)
{
	PozicijaAVLPre K1;

	K1 = K2->D;
	K2->D = K1->L;
	K1->L = K2;

	K2->visina = Max(VisinaPre(K2->D), VisinaPre(K2->L)) + 1;
	K1->visina = Max(VisinaPre(K1->D), K2->visina) + 1;

	return K1;
}

PozicijaAVLPre DvostrukaRLPre(PozicijaAVLPre K3)
{
	K3->L = JednostrukaRDPre(K3->L);

	return JednostrukaRLPre(K3);
}

PozicijaAVLPre DvostrukaRDPre(PozicijaAVLPre K3)
{
	K3->D = JednostrukaRLPre(K3->D);

	return JednostrukaRDPre(K3);
}

