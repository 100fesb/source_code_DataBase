#include <stdbool.h>
#include "Constants.h"
#include "Predmeti.h"

#ifndef STUDENTI
#define STUDENTI

struct cvorAVLStudenti;
typedef struct cvorAVLStudenti CvorAVL;
typedef struct cvorAVLStudenti* StabloAVL;
typedef struct cvorAVLStudenti* PozicijaAVL;

int Visina(StabloAVL);
StabloAVL DodajAVL(int, char*, StabloAVL, int[BUFFER_LENGTH], char*, int);
PozicijaAVL JednostrukaRL(PozicijaAVL);
PozicijaAVL DvostrukaRL(PozicijaAVL);
PozicijaAVL JednostrukaRD(PozicijaAVL);
PozicijaAVL DvostrukaRD(PozicijaAVL);
void printAVLstud(StabloAVL tree); 
int _printAVLstud(StabloAVL tree, int is_left, int offset, int depth, char s[20][255]);

int IspisiSveStudente();
int IspisiSve();

typedef struct Predmet* PozicijaP;


struct cvorAVLStudenti{	//1

	//ovdje ide ID za ime studenta
	int ID;
	char PrezimeIme[NAME_LENGTH];
	StabloAVL L; // lijevi student
	StabloAVL D; // desni student
	PozicijaP NextP; // iduci predmet

	int visina;
};

struct Predmet{
	int ID;
	int OC;
	PozicijaP NextP;
};

PozicijaAVL nadiPoID(int tempID, PozicijaAVL Root);
int ispisSvihOcjenaStudenta(PozicijaAVL RootS, PozicijaAVLPre RootPre);
int unesiStudenta(StabloAVL rootS);
int brisiPoIDuStudent(StabloAVL rootS);
StabloAVL brisiAVLElement(StabloAVL P, int ID);
StabloAVL traziNajmanjiID(StabloAVL P);

#endif

