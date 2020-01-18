#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "Constants.h"
#include "Studenti.h"
#include "Predmeti.h"
#include "Assets.h"

StabloAVL traziNajmanjiID(StabloAVL P)
{
	if (P != NULL)
	{
		while (P->L != NULL)
			P = P->L;
	}
	return P;
}

StabloAVL brisiAVLElement(StabloAVL S, int ID)
{
	StabloAVL tempStudent = NULL;

	if (S == NULL){
		printf("\t\tNe postoji taj student u bazi podataka.\n");
		return NULL;
	}
	else if (S->ID > ID)
		S->L = brisiAVLElement(S->L, ID);
	else if (S->ID < ID)
		S->D = brisiAVLElement(S->D, ID);
	else
	{
		if (S->L != NULL && S->D != NULL)
		{
			tempStudent = traziNajmanjiID(S->D);
			S->ID = tempStudent->ID;
			S->D = brisiAVLElement(S->D, S->ID);
		}
		else {
			tempStudent = S;
			if (S->L == NULL)
				S = S->D;
			else if (S->D == NULL)
				S = S->L;
			free(tempStudent);
		}

	}

	return S;
}

int brisiPoIDuStudent(StabloAVL rootStudent)
{
	StabloAVL nadjeniStudent = NULL;
	int trazeniID = 0;
	char nadjeniStudIme[NAME_LENGTH] = "";

	do{
		printf("\t\t-- ID studenta za brisanje (0 za kraj): ");
		scanf(" %d", &trazeniID);
		if (trazeniID == 0) break;


		izbrisiLinijuPoID("Studenti.txt", trazeniID);
		izbrisiLinijuPoID("StudentiPotpunaTablica.txt", trazeniID);

		nadjeniStudent = nadiPoID(trazeniID, rootStudent);
		strcpy(nadjeniStudIme, nadjeniStudent->PrezimeIme);
		rootStudent = brisiAVLElement(rootStudent, trazeniID);
		if (nadjeniStudent) printf("\t\tIzbrisan student %s.\n", nadjeniStudIme);


	} while (trazeniID != 0);

	return SUCCESS;
}


int unesiStudenta(StabloAVL rootS)
{
	FILE* fa = NULL;
	FILE* fr = NULL;
	int tempIDstud = 0;
	char imePrezime[BUFFER_LENGTH] = "";
	char tempStr[BUFFER_LENGTH] = "";
	char tempImePredmeta[BUFFER_LENGTH] = "";
	char ocjene[BUFFER_LENGTH] = "";
	char izborImePredmeta[BUFFER_LENGTH] = "";
	int IDeviPredmeta[BUFFER_LENGTH];
	int brPredmetaStudenta = 0;
	int brPredmetaDatoteke = 0;
	int tempOcjena = 0;
	int tempIDpredmeta = 0;
	int i = 0;
	int j = 0;

	tempIDstud = generirajID(1000, 1999);

	printf("\tUnos podataka studenta:\n\t\t--  Ime:");
	scanf("%s", imePrezime);
	if (!strcmp(imePrezime, "kraj")) return END;
	strcat(imePrezime, " ");
	printf("\t\t-- Prezime:");
	scanf("%s", tempStr);
	strcat(imePrezime, tempStr);

	printf("\t~~~Unos ocjena studenta (0 ako nije upisana ocjena, 'kraj' za kraj unosa)~~~\n");


	fr = OtvoriDatoteku('r', "Predmeti.txt");

	while (!feof(fr)){
		fgets(tempStr, sizeof(tempStr), fr);
		brPredmetaDatoteke++;
	}

	rewind(fr);

	do{
		printf("\t\t\t-- Ime predmeta: ");
		fflush(stdin);
		fgets(izborImePredmeta, sizeof(izborImePredmeta), stdin);
		if (izborImePredmeta[strlen(izborImePredmeta) - 1] == '\n') izborImePredmeta[strlen(izborImePredmeta) - 1] = NULL;
		if (!strcmp(izborImePredmeta, "kraj")) break;

		tempIDpredmeta = nadjiIdPoImenu(fr, izborImePredmeta);
		if (tempIDpredmeta == -1){
			printf("\t\tNe postoji taj predmet. \n\t\tPrvo unesite taj predmet u bazu podataka, pa pokusajte ponovno.\n");
			rewind(fr);
			continue;
		}

		IDeviPredmeta[brPredmetaStudenta] = tempIDpredmeta;
		brPredmetaStudenta++;

		do{
			printf("\t\t\t>>Ocjena: ");
			scanf(" %d", &tempOcjena);
		} while (tempOcjena > 5 || tempOcjena < 0);

		sprintf(tempStr, "%d", tempOcjena);
		strcat(ocjene, tempStr);
		strcat(ocjene, " ");


		rewind(fr);
	} while (strcmp(izborImePredmeta, "kraj"));

	fclose(fr);

	DodajAVL(tempIDstud, imePrezime, rootS, IDeviPredmeta, ocjene, brPredmetaStudenta);

	fa = OtvoriDatoteku('a', "Studenti.txt");
	fprintf(fa, "%d %s\n", tempIDstud, imePrezime);

	fclose(fa);

	// pretpostavka je da su predmeti po redu u obe dateoteke - 'StudentiPotpTab' i 'Predmeti'
	// jer uvijek predmete dodajemo na kraj
	// ali u varijablama ove funkcije ne moraju biti po redu - ovisi o unosu korisnika
	fa = OtvoriDatoteku('a', "StudentiPotpunaTablica.txt");

	fprintf(fa, "\n%d\t\t\t%s", tempIDstud, imePrezime);

	fr = OtvoriDatoteku('r', "Predmeti.txt");

	while (!feof(fr))
	{
		fscanf(fr, "%d %[^\n]", &tempIDpredmeta, tempImePredmeta);
		for (i = 0; i < brPredmetaStudenta; i++){
			if (IDeviPredmeta[i] == tempIDpredmeta){
				tempOcjena = getNthItemFromString(i, ocjene);
				break;
			}
			else{
				tempOcjena = -1; // nije upisana
			}
		}
		fprintf(fa, "\t\t%d", tempOcjena);
	}

	fclose(fa);
	fclose(fr);

	return SUCCESS;
}

int IspisiSve() {

	FILE* fp;
	char str[SIZE_FOR_FULL_PRINT];

	fp = fopen("StudentiPotpunaTablica.txt", "r");
	if (fp == NULL) return ERROR;
	while (!feof(fp)) {
		if (fgets(str, SIZE_FOR_FULL_PRINT, fp) != NULL) {
			puts(str);
		}
	}
	fclose(fp);

	return(0);
};

int IspisiSveStudente() {

	FILE* fp = NULL;
	char* buffer = NULL;
	char Ime[NAME_LENGTH] = " ";
	char Prezime[NAME_LENGTH] = " ";
	int ID = 0;

	buffer = (char*)malloc(sizeof(char)* NAME_LENGTH);

	fp = fopen("Studenti.txt", "r");
	if (!fp)  return ERROR;

	while (!feof(fp)) {
		fgets(buffer, NAME_LENGTH, fp);
		if (buffer[0] != '\n' && buffer[0] != '\0')
		{
			fscanf(fp, " %d %s %s", &ID, Ime, Prezime);
			printf("\n\tID studenta je %d a ime studenta je %s %s", ID, Ime, Prezime);
		}
	}
	fclose(fp);
	free(buffer);

	return 0;
};

PozicijaAVL nadiPoID(int tempID, PozicijaAVL Root)
{
	if (!Root) return NULL;

	if (tempID > Root->ID) nadiPoID(tempID, Root->D);
	else if (tempID < Root->ID) nadiPoID(tempID, Root->L);
	else return Root;
}


int ispisSvihOcjenaStudenta(PozicijaAVL RootS, PozicijaAVLPre RootPre)
{
	StabloAVL NadjeniS = NULL;
	PozicijaP Predmet = NULL;
	PozicijaAVLPre NadjeniPre = NULL;
	int ID = 0;

	printf("Unesite ID trazenog studenta: ");
	scanf(" %d", &ID);
	NadjeniS = nadiPoID(ID, RootS);
	Predmet = NadjeniS->NextP;

	printf("Ocjene studenta/ice: \n\t---->%s<----", NadjeniS->PrezimeIme);

	while (NULL != Predmet){
		NadjeniPre = nadiPoIDPre(Predmet->ID, RootPre);

		if (Predmet->OC > 0){
			printf("\n\t%s: %d", NadjeniPre->ImePre, Predmet->OC);
		}
		if (Predmet->OC == 0){
			printf("\n\t%s: ", NadjeniPre->ImePre);
			printf("Nije upisana ocjena.");
		}

		Predmet = Predmet->NextP;
	}

	printf("\n");
	return SUCCESS;
}


StabloAVL DodajAVL(int ID, char* PI, StabloAVL S, int IDeviPredmeta[BUFFER_LENGTH], char* ocjene, int brPredmeta)
{
	PozicijaP NextPredmet = NULL;
	int n = 0;
	int i = 0;
	int readBytes = 0;
	int tempOC = 0;

	if (NULL == S)
	{
		S = (StabloAVL)malloc(sizeof(CvorAVL));
		S->ID = ID;
		S->visina = 0;
		strcpy(S->PrezimeIme, PI);
		S->L = S->D = NULL;

		S->NextP = NULL;

		for (i = 0; i < brPredmeta; i++)
		{
			NextPredmet = (PozicijaP)malloc(sizeof(struct Predmet));
			NextPredmet->ID = IDeviPredmeta[i];
			sscanf(ocjene, "%d %n", &tempOC, &readBytes);
			ocjene += readBytes;
			NextPredmet->OC = tempOC;
			NextPredmet->NextP = S->NextP;
			S->NextP = NextPredmet;
		}
	}
	else
	{
		if (ID < S->ID){
			S->L = DodajAVL(ID, PI, S->L, IDeviPredmeta, ocjene, brPredmeta);
			n = Visina(S->L) - Visina(S->D);
			if (n == 2){
				if (ID < S->L->ID) S = JednostrukaRL(S);
				else S = DvostrukaRL(S);
			}
		}
		else if (ID > S->ID)
		{
			S->D = DodajAVL(ID, PI, S->D, IDeviPredmeta, ocjene, brPredmeta);
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
// alternativa je da vracaju void* sto je vrlo opasno (nema nekon template-a - C++ ili nesto slicno, polimorfno)
StabloAVL generirajAVL_Student(StabloAVL P)
{
	FILE* fp = NULL;
	char* buff = NULL;
	char red[BUFFER_LENGTH];
	int i = 0;
	int readBytes = 0;

	int id = NULL;
	char str1[NAME_LENGTH / 2];
	char str2[NAME_LENGTH / 2];
	char imenaPredmeta[LONG_BUFFER_LENGTH][NAME_LENGTH];
	int IDeviPredmeta[BUFFER_LENGTH];
	int brPredmeta = 0;
	char* ocjene = NULL;
	int tempNastavakPredmeta = 0;
	char tempNastavakPredmetaC[sizeof(int)];
	char tempNastavakPredmetaS[NAME_LENGTH];
	char tempIDstr[NAME_LENGTH] = "";
	int tempID = 0;
	int stringIsRead = 0; // 0 za ne, bilo sta drugo je da

	fp = OtvoriDatoteku('r', "StudentiPotpunaTablica.txt");

	if (!fp) return NULL;


	fgets(red, BUFFER_LENGTH, fp); // preskocimo prvi red zaglavlja)

	buff = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	ocjene = (char*)malloc(sizeof(char)*BUFFER_LENGTH);

	if (!buff || !ocjene) return ERROR;

	fgets(buff, BUFFER_LENGTH, fp);

	// mozda cemo koristit polje imenaPredmeta, mozda ne, ali smo ih spojili imena u polje
	for (i = 0; sscanf(buff, " %d %s %d %n", &IDeviPredmeta[i], imenaPredmeta[i], &tempNastavakPredmeta, &readBytes) > 0; i++){

		// podrzavanje vise rijeci za ime predmeta
		if (!readBytes)
		{
			sscanf(buff, "%d %n", &tempID, &readBytes);
			buff += readBytes;
			buff += strlen(imenaPredmeta[i]);

			memset(tempNastavakPredmetaS, '\0', 1);
			while (1)
			{
				sscanf(buff, "%s %d %n", tempNastavakPredmetaS, &stringIsRead, &readBytes);
				strcat(imenaPredmeta[i], " ");
				strcat(imenaPredmeta[i], tempNastavakPredmetaS);
				buff += readBytes;
				buff -= sizeof(stringIsRead)+1;
				readBytes = 0;
				if (stringIsRead) break;
			}
		}

		// podrzavanje broja kao nastavka predmeta, npr. 'Fizika 2'
		else if (tempNastavakPredmeta <= 9 && tempNastavakPredmeta >= 1)
		{
			sprintf(tempNastavakPredmetaC, "%d", tempNastavakPredmeta);
			strcat(imenaPredmeta[i], " ");
			strcat(imenaPredmeta[i], tempNastavakPredmetaC);
			tempNastavakPredmeta = 0; // jer iz nekog razloga ako ne resetamo - on zapamti do kraja reda
		}
		else
		{
			buff += readBytes;
			buff -= BUFFER_DECREMENTER;
			brPredmeta++;
			readBytes = 0;
			continue;
		}

		buff += readBytes;
		brPredmeta++;
	}

	while (!feof(fp))
	{
		fgets(buff, BUFFER_LENGTH, fp);

		sscanf(buff, "%d %s %s %[^\n]", &id, str1, str2, ocjene);
		strcat(str1, " ");
		strcat(str1, str2);

		P = DodajAVL(id, str1, P, IDeviPredmeta, ocjene, brPredmeta);
	}
	fclose(fp);


	//free(buff); s njim smo setali -  treba memmove umjesto buff += ...
	free(ocjene);
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


int _printAVLstud(StabloAVL tree, int is_left, int offset, int depth, char s[20][255])
{
	char b[20];
	int width = 5;

	if (!tree) return 0;

	sprintf(b, "(%03d)", tree->ID);

	int left = _printAVLstud(tree->L, 1, offset, depth + 1, s);
	int right = _printAVLstud(tree->D, 0, offset + left + width, depth + 1, s);

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

void printAVLstud(StabloAVL tree)
{
	char s[20][255];
	for (int i = 0; i < 20; i++)
		sprintf(s[i], "%80s", " ");

	_printAVLstud(tree, 0, 0, 0, s);

	for (int i = 0; i < 20; i++)
		printf("%s\n", s[i]);
}