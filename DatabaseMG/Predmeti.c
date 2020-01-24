#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Constants.h"
#include "Predmeti.h"
#include "Assets.h"

StabloAVLPre traziNajmanjiIDPre(StabloAVLPre P)
{
	if (P != NULL)
	{
		while (P->L != NULL)
			P = P->L;
	}
	return P;
}

StabloAVLPre brisiAVLElementPre(StabloAVLPre S, int ID)
{
	StabloAVLPre tempPredmet = NULL;

	if (S == NULL){
		printf("\t\tNe postoji taj predmet u bazi podataka.\n");
		return NULL;
	}
	else if (S->ID > ID)
		S->L = brisiAVLElementPre(S->L, ID);
	else if (S->ID < ID)
		S->D = brisiAVLElementPre(S->D, ID);
	else
	{
		if (S->L != NULL && S->D != NULL)
		{
			tempPredmet = traziNajmanjiIDPre(S->D);
			S->ID = tempPredmet->ID;
			strcpy(S->ImePre, tempPredmet->ImePre);
			strcpy(S->ImePrezimeProfesora, tempPredmet->ImePrezimeProfesora);
			S->D = brisiAVLElementPre(S->D, S->ID);
		}
		else {
			tempPredmet = S;
			if (S->L == NULL)
				S = S->D;
			else if (S->D == NULL)
				S = S->L;
			free(tempPredmet);
		}

	}

	return S;
}

int brisiPoIDuPredmet(StabloAVLPre rootPre)
{
	StabloAVLPre nadjeniPredmet = NULL;
	FILE* fr = NULL;
	FILE* fw = NULL;
	int trazeniID = 0;
	int ucitaniID = 0;
	int tempBroj = 0;
	int readBytes = 0;
	int i = 0;
	int tempOC = 0;
	int tempID = 0;
	int indentSpacing = 30;
	int brPredmetaPrijeBrisanog = 0;
	int tempBrPredmetaProfesora = 0;
	char nadjeniPredIme[NAME_LENGTH] = "";
	char tempImePredmeta[NAME_LENGTH] = "";
	char tempImeProfesora[NAME_LENGTH] = "";
	char tempImeStudenta[NAME_LENGTH] = "";
	char tempStr[NAME_LENGTH] = "";
	char tempFileLine[BUFFER_LENGTH] = "";
	char* buff = NULL;
	char* temp = NULL;

	buff = (char*)malloc(sizeof(char)*BUFFER_LENGTH);

	do{
		printf("\t\t-- ID predmeta za brisanje (0 za kraj): ");
		scanf(" %d", &trazeniID);
		if (trazeniID == 0) break;

		izbrisiLinijuPoID("Predmeti.txt", trazeniID);
		izbrisiLinijuPoID("PredmetiProfesori.txt", trazeniID);


		// brisanje stupca u datoteci 'StudentiPotpunaTablica.txt'
		fr = OtvoriDatoteku('r', "StudentiPotpunaTablica.txt");
		fw = OtvoriDatoteku('w', "temp.txt");

		fgets(buff, BUFFER_LENGTH, fr); // zaglavlje
		fprintf(fw, "%s", buff);
		fgets(buff, BUFFER_LENGTH, fr); // sadrzi sva imena i ID-eve predmeta (2. redak)
		fprintf(fw, "%*s", indentSpacing, "");

		while (sscanf(buff, " %d %s %d %n", &ucitaniID, tempImePredmeta, &tempBroj, &readBytes) > 0)
		{

			if (tempBroj > 0 && tempBroj < 9){ // nastavak predmeta npr. 'Fizika 2<---'
				sprintf(tempStr, "%d", tempBroj);
				strcat(tempImePredmeta, " ");
				strcat(tempImePredmeta, tempStr);
				memmove(buff, buff + readBytes, BUFFER_LENGTH);
			}

			else{
				memmove(buff, buff + readBytes - BUFFER_DECREMENTER, BUFFER_LENGTH);
			}
			if (ucitaniID != trazeniID){
				fprintf(fw, " \t%d %s", ucitaniID, tempImePredmeta);
				brPredmetaPrijeBrisanog++;
			}
			else break;
		}
		fputs("\t\t", fw);
		fputs(buff, fw);

		while (!feof(fr))
		{
			fgets(buff, BUFFER_LENGTH, fr);
			sscanf(buff, " %d %s %s %n", &ucitaniID, tempImeStudenta, tempStr, &readBytes);
			fprintf(fw, "%5d %10s %10s ", ucitaniID, tempImeStudenta, tempStr);
			memmove(buff, buff + readBytes, BUFFER_LENGTH);

			for (i = 0; i <= brPredmetaPrijeBrisanog; i++)
			{
				sscanf(buff, " %d %n", &tempOC, &readBytes);
				memmove(buff, buff + readBytes, BUFFER_LENGTH);
				if (i == brPredmetaPrijeBrisanog) break;
				fprintf(fw, "\t\t\t%d", tempOC);
			}
			fputs("\t\t", fw);
			fputs(buff, fw);
		}

		fclose(fr);
		fclose(fw);

		remove("StudentiPotpunaTablica.txt");
		rename("temp.txt", "StudentiPotpunaTablica.txt");

		nadjeniPredmet = nadiPoIDPre(trazeniID, rootPre);
		strcpy(nadjeniPredIme, nadjeniPredmet->ImePre);
		
		

		fr = OtvoriDatoteku('r', "ProfesoriPredmeti.txt");
		fw = OtvoriDatoteku('w', "temp.txt");



		while (!feof(fr)){
			fgets(buff, BUFFER_LENGTH, fr);
			temp = buff;


			sscanf(buff, "%d %[^:] %n", &tempID, tempImeProfesora, &readBytes);
			tempImeProfesora[strlen(tempImeProfesora) - 1] = NULL;
			if (strcmp(tempImeProfesora, nadjeniPredmet->ImePrezimeProfesora)){
				fprintf(fw, "%s", buff);
				continue;
			}
			for (i = 0; temp[i]; temp[i] == ',' ? i++ : *temp++);
			tempBrPredmetaProfesora = i + 1;

			memmove(buff, buff + readBytes+2, BUFFER_LENGTH);
			strcpy(tempFileLine, tempImeProfesora);
			strcat(tempFileLine, " : ");
			for (i = 0; i < tempBrPredmetaProfesora; i++)
			{
				sscanf(buff, "%[^,] %n", tempImePredmeta, &readBytes);
				memmove(buff, buff + readBytes + 2, BUFFER_LENGTH);
				if (tempImePredmeta[strlen(tempImePredmeta) - 1] == '\n') tempImePredmeta[strlen(tempImePredmeta) - 1] = NULL;
				if (tempBrPredmetaProfesora == 1 && !strcmp(tempImePredmeta, nadjeniPredIme)){
					printf("\t\tBrisete predmet %s, zadnji predmet profesora. \n\t\tZelite li dodati novi? ('ne' za prekid)\n", nadjeniPredIme);
					strcpy(tempStr, unesiPredmet(rootPre));
					if (!strcmp(tempStr, "ne") || !strcmp(tempStr, "kraj")) break;
					strcat(tempFileLine, tempStr); 
					strcat(tempFileLine, ", ");

					break;
				}
				if (!strcmp(tempImePredmeta, nadjeniPredIme)) continue;
				strcat(tempFileLine, tempImePredmeta);
				strcat(tempFileLine, ", ");
			}
			tempFileLine[strlen(tempFileLine) - 1] = NULL;
			tempFileLine[strlen(tempFileLine) - 1] = NULL;
			strcat(tempFileLine, "\n");
			if (strcmp(tempStr, "ne")){
				fprintf(fw, "%d ", tempID);
				fprintf(fw, "%s", tempFileLine);
			}
		}

		rootPre = brisiAVLElementPre(rootPre, trazeniID);
		if (nadjeniPredmet) printf("\t\tIzbrisan predmet %s.\n", nadjeniPredIme);
		fclose(fr);
		fclose(fw);

		remove("ProfesoriPredmeti.txt");
		rename("temp.txt", "ProfesoriPredmeti.txt");

	} while (trazeniID != 0);




	free(buff);

	return SUCCESS;
}

int ispisiPredmet() {

}

int IspisiSvePredmete() {

	FILE* fp = NULL;
	char* buffer = NULL;
	char imePredmeta[NAME_LENGTH] = "";
	char imeProfesora[NAME_LENGTH] = "";
	int ID = 0;

	buffer = (char*)malloc(sizeof(char)* NAME_LENGTH);

	fp = fopen("PredmetiProfesori.txt", "r");
	if (!fp)  return ERROR;

	while (!feof(fp)) {
		fgets(buffer, NAME_LENGTH, fp);
		if (buffer[0] != '\n' && buffer[0] != '\0')
		{
			sscanf(buffer, "%d %[^:] %[^\n]", &ID, imePredmeta, imeProfesora);
			imePredmeta[strlen(imePredmeta) - 1] = NULL;
			memmove(imeProfesora, imeProfesora + 2, NAME_LENGTH);
			if (imeProfesora[strlen(imeProfesora) - 1] == '\n') imeProfesora[strlen(imeProfesora) - 1] = NULL;;
			printf("\n\tID: %d %s predaje %s", ID, imePredmeta, imeProfesora);
		}
	}
	fclose(fp);
	free(buffer);

	return 0;
};

char* unesiPredmet(StabloAVLPre rootPre)
{
	FILE* fa = NULL;
	FILE* fr = NULL;
	FILE* fw = NULL;
	int tempIDpredmeta = 0;
	char imePredmeta[NAME_LENGTH] = "";
	char imeProfesora[NAME_LENGTH] = "";
	char tempLine[BUFFER_LENGTH] = "";
	char* tempStr = NULL;
	char* buff = NULL;

	tempStr = (char*)malloc(sizeof(char)*NAME_LENGTH);
	buff = (char*)malloc(sizeof(char)*BUFFER_LENGTH);


	tempIDpredmeta = generirajID(2000, 2999);

	fa = OtvoriDatoteku('a', "Predmeti.txt");

	printf("\t\t-- Ime predmeta: ");
	tempStr = readLine();
	strcat(imePredmeta, tempStr);
	if (!strcmp(imePredmeta, "kraj") || !strcmp(imePredmeta, "ne")) return "kraj";
	fprintf(fa, "\n%d\t%s", tempIDpredmeta, imePredmeta);
	fclose(fa);

	fa = OtvoriDatoteku('a', "PredmetiProfesori.txt");

	printf("\t\t-- Predavac (profesor): ");
	tempStr = readLine();
	strcat(imeProfesora, tempStr);
	fprintf(fa, "\n%d\t%s : %s", tempIDpredmeta, imePredmeta, imeProfesora);
	fclose(fa);


	DodajAVLPre(tempIDpredmeta, imePredmeta, imeProfesora, rootPre);

	fr = OtvoriDatoteku('r', "StudentiPotpunaTablica.txt");
	fw = OtvoriDatoteku('w', "temp.txt");

	// ispis zaglavlja

	fgets(buff, BUFFER_LENGTH, fr);
	sscanf(buff, "%[^\n]", tempLine);
	fprintf(fw, "%s\n", tempLine);

	fgets(buff, BUFFER_LENGTH, fr);
	sscanf(buff, "%[^\n]", tempLine);
	strcat(tempLine, "\t\t");
	sprintf(tempStr, "%d", tempIDpredmeta);
	strcat(tempLine, tempStr);
	strcat(tempLine, " ");
	strcat(tempLine, imePredmeta);
	fprintf(fw, "%s\n", tempLine);

	while (!feof(fr))
	{
		fgets(buff, BUFFER_LENGTH, fr);
		sscanf(buff, "%[^\n]", tempLine);
		strcat(tempLine, "\t\t-1");
		fprintf(fw, "%s\n", tempLine);
	}

	fclose(fr);
	fclose(fw);

	remove("StudentiPotpunaTablica.txt");
	rename("temp.txt", "StudentiPotpunaTablica.txt");

	free(tempStr);
	free(buff);

	return imePredmeta;
}


PozicijaAVLPre nadiPoIDPre(int tempID, PozicijaAVLPre Root)
{
	if (!Root) return NULL;

	if (tempID > Root->ID) nadiPoIDPre(tempID, Root->D);
	else if (tempID < Root->ID) nadiPoIDPre(tempID, Root->L);
	else return Root;
}

StabloAVLPre DodajAVLPre(int ID, char* imePre, char* imeProf, StabloAVLPre S)
{
	int n = 0;

	if (NULL == S)
	{
		S = (StabloAVLPre)malloc(sizeof(CvorAVLPre));
		S->ID = ID;
		S->visina = 0;
		strcpy(S->ImePre, imePre);
		S->L = S->D = NULL;
		strcpy(S->ImePrezimeProfesora, imeProf);
	}
	else
	{
		if (ID < S->ID){
			S->L = DodajAVLPre(ID, imePre, imeProf, S->L);
			n = VisinaPre(S->L) - VisinaPre(S->D);
			if (n == 2){
				if (ID < S->L->ID) S = JednostrukaRLPre(S);
				else S = DvostrukaRLPre(S);
			}
		}
		else if (ID > S->ID)
		{
			S->D = DodajAVLPre(ID, imePre, imeProf, S->D);
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
	char tempStr[BUFFER_LENGTH] = "";
	char tempChar = NULL;

	int id = NULL;
	char imePredmeta[NAME_LENGTH] = "";
	char imeProfesora[NAME_LENGTH] = "";
	char* buff = NULL;

	buff = (char*)malloc(sizeof(char)* BUFFER_LEN);
	if (!buff) return ERROR;

	fp = OtvoriDatoteku('r', "PredmetiProfesori.txt");

	if (!fp) return NULL;

	while (!feof(fp))
	{


		fgets(buff, BUFFER_LEN, fp);
		sscanf(buff, "%d %[^\n]", &id, tempStr);

		strcat(tempStr, "\n");
		sscanf(tempStr, "%[^:] %[^\n]", imePredmeta, imeProfesora);
		imePredmeta[strlen(imePredmeta) - 1] = NULL;
		memmove(imeProfesora, imeProfesora + 2, strlen(imeProfesora));

		P = DodajAVLPre(id, imePredmeta, imeProfesora, P);
	}


	fclose(fp);

	free(buff);

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


int _printAVLpred(StabloAVLPre tree, int is_left, int offset, int depth, char s[20][255])
{
	char b[20];
	int width = 5;

	if (!tree) return 0;

	sprintf(b, "(%03d)", tree->ID);

	int left = _printAVLpred(tree->L, 1, offset, depth + 1, s);
	int right = _printAVLpred(tree->D, 0, offset + left + width, depth + 1, s);

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

void printAVLpred(StabloAVLPre tree)
{
	char s[20][255];
	for (int i = 0; i < 20; i++)
		sprintf(s[i], "%80s", " ");

	_printAVLpred(tree, 0, 0, 0, s);

	for (int i = 0; i < 20; i++)
		printf("%s\n", s[i]);
}