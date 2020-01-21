#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Constants.h"
#include "Profesori.h"
#include "Assets.h"

int IspisiSveProfesore() {

	FILE* fp = NULL;
	char* buffer = NULL;
	char Ime[NAME_LENGTH] = " ";
	char Prezime[NAME_LENGTH] = " ";
	int ID = 0;

	buffer = (char*)malloc(sizeof(char)* NAME_LENGTH);
	if (!buffer) return ERROR;

	fp = fopen("Profesori.txt", "r");
	if (!fp)  return ERROR;

	while (!feof(fp)) {
		fgets(buffer, NAME_LENGTH, fp);
		if (buffer[0] != '\n' && buffer[0] != '\0')
		{
			fscanf(fp, " %d %s %s", &ID, Ime, Prezime);
			printf("\n\tID profesora je %d a ime profesora je %s %s", ID, Ime, Prezime);
		}
	}
	fclose(fp);

	free(buffer);

	return 0;
};

int unesiProfesora(StabloAVLPro P)
{
	FILE* fa = NULL;
	FILE* fr = NULL;
	FILE* fw = NULL;
	int tempIDprofesora = 0;
	char predmeti[NAME_LENGTH][NAME_LENGTH];
	char imePredmeta[NAME_LENGTH] = "";
	char imePrezimeProfesora[NAME_LENGTH] = "";
	char tempLine[BUFFER_LENGTH] = "";
	char* tempStr = NULL;
	int i = 0;
	int brPredmeta = 0;

	tempStr = (char*)malloc(sizeof(char)*NAME_LENGTH);
	if (!tempStr) return ERROR;


	tempIDprofesora = generirajID(3000, 3999);

	fa = OtvoriDatoteku('a', "Profesori.txt");

	printf("\t\t-- Ime i prezime profesora: ");
	tempStr = readLine();
	strcat(imePrezimeProfesora, tempStr);
	if (!strcmp(imePrezimeProfesora, "kraj")) return END;
	fprintf(fa, "\n%d\t%s", tempIDprofesora, imePrezimeProfesora);
	fclose(fa);


	printf("\t\t~~Unesite predmete koje predaje ('kraj' za izlazak)~~~\n");

	do{
		printf("\t\t\t-- Predmet: ");
		tempStr = readLine();
		strcpy(imePredmeta, tempStr);
		if (!strcmp(imePredmeta, "kraj")) break;
		strcpy(predmeti[i], imePredmeta);

		i++;
	} while (imePredmeta != "kraj");
	brPredmeta = i;

	P = DodajAVLPro(tempIDprofesora, imePrezimeProfesora, predmeti, P, brPredmeta);


	fa = OtvoriDatoteku('a', "ProfesoriPredmeti.txt");

	fprintf(fa, "\n%d %s : ", tempIDprofesora, imePrezimeProfesora);
	for (i = 0; i < brPredmeta; i++)
	{
		if (brPredmeta != (i + 1)) fprintf(fa, "%s, ", predmeti[i]);
		else fprintf(fa, "%s", predmeti[i]);
	}

	fclose(fa);

	free(tempStr);

	return SUCCESS;
}

PozicijaAVLPro nadiPoIDPro(int tempID, PozicijaAVLPro Root)
{
	if (!Root) return NULL;

	if (tempID > Root->ID) nadiPoIDPro(tempID, Root->D);
	else if (tempID < Root->ID) nadiPoIDPro(tempID, Root->L);
	else return Root;
}


StabloAVLPro DodajAVLPro(int ID, char* ImeProf, char predmeti[][NAME_LENGTH], StabloAVLPro S, int brojPredmeta)
{
	int n = 0;
	int i = 0;

	if (NULL == S)
	{
		S = (StabloAVLPro)malloc(sizeof(CvorAVLPro));
		S->ID = ID;
		S->visina = 0;
		strcpy(S->ImePro, ImeProf);
		S->L = S->D = NULL;

		for (i = 0; i < brojPredmeta; i++){
			strcpy(S->predmeti[i], predmeti[i]);
		}
	}
	else
	{
		if (ID < S->ID) {
			S->L = DodajAVLPro(ID, ImeProf, predmeti, S->L, brojPredmeta);
			n = VisinaPro(S->L) - VisinaPro(S->D);
			if (n == 2) {
				if (ID < S->L->ID) S = JednostrukaRLPro(S);
				else S = DvostrukaRLPro(S);
			}
		}
		else if (ID > S->ID)
		{
			S->D = DodajAVLPro(ID, ImeProf, predmeti, S->D, brojPredmeta);
			n = VisinaPro(S->D) - VisinaPro(S->L);
			if (n == 2)
			{
				if (ID > S->D->ID) S = JednostrukaRDPro(S);
				else S = DvostrukaRDPro(S);
			}
		}
	}

	S->visina = Max(VisinaPro(S->L), VisinaPro(S->D)) + 1;
	return S;
}

StabloAVLPro generirajAVL_Profesori(StabloAVLPro P)
{
	FILE* fp = NULL;
	int i = 0;
	int bytesRead = 0;
	int len = 0;

	int id = NULL;
	int brojPredmeta = 0;
	char imeProfesora[NAME_LENGTH];
	char predmeti[NAME_LENGTH][NAME_LENGTH];
	char* buff = NULL;
	char* temp = NULL;

	buff = (char*)malloc(sizeof(char)* BUFFER_LEN);

	fp = OtvoriDatoteku('r', "ProfesoriPredmeti.txt");

	if (!fp) return NULL;

	while (!feof(fp))
	{

		fgets(buff, BUFFER_LEN, fp);
		sscanf(buff, "%d %[^:] %n", &id, imeProfesora, &bytesRead);
		buff += bytesRead;
		memmove(buff, buff + 2, strlen(buff));

		temp = buff;
		for (i = 0; temp[i]; temp[i] == ',' ? i++ : *temp++);
		brojPredmeta = i + 1;

		for (i = 0; i < brojPredmeta; i++){
			sscanf(buff, "%[^,] %n", predmeti[i], &bytesRead);
			buff += bytesRead + 2;
		}

		len = strlen(predmeti[i - 1]) - 1;
		if (predmeti[i - 1][len] == '\n') predmeti[i - 1][len] = NULL;

		P = DodajAVLPro(id, imeProfesora, predmeti, P, brojPredmeta);
	}


	fclose(fp);

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

int _printAVLprof(StabloAVLPro tree, int is_left, int offset, int depth, char s[20][255])
{
	char b[20];
	int width = 5;

	if (!tree) return 0;

	sprintf(b, "(%03d)", tree->ID);

	int left = _printAVLprof(tree->L, 1, offset, depth + 1, s);
	int right = _printAVLprof(tree->D, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
	for (int i = 0; i < width; i++)
		s[depth][offset + left + i] = b[i];

	if (depth && is_left) {

		for (int i = 0; i < width + right; i++)
			s[depth - 1][offset + left + width / 2 + i] = '-';

		s[depth - 1][offset + left + width / 2] = '.';

	}
	else if (depth && !is_left) {

		for (int i = 0; i < left + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';

		s[depth - 1][offset + left + width / 2] = '.';
	}
#else
	for (int i = 0; i < width; i++)
		s[2 * depth][offset + left + i] = b[i];

	if (depth && is_left) {

		for (int i = 0; i < width + right; i++)
			s[2 * depth - 1][offset + left + width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

	}
	else if (depth && !is_left) {

		for (int i = 0; i < left + width; i++)
			s[2 * depth - 1][offset - width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset - width / 2 - 1] = '+';
	}
#endif

	return left + width + right;
}

void printAVLprof(StabloAVLPro tree)
{
	char s[20][255];
	for (int i = 0; i < 20; i++)
		sprintf(s[i], "%80s", " ");

	_printAVLprof(tree, 0, 0, 0, s);

	for (int i = 0; i < 20; i++)
		printf("%s\n", s[i]);
}