#include "Constants.h"


struct cvorAVLStudenti;
//deklarirali pokazivace
//typedef struct cvorAVLStudenti* PozicijaS;					//pokazivac na sljedeceg studenta
typedef struct cvorAVLStudenti CvorAVL;
typedef struct cvorAVLStudenti* StabloAVL;
typedef struct cvorAVLStudenti* PozicijaAVL;

int Visina(StabloAVL);
StabloAVL DodajAVL(int, StabloAVL);
int Max(int, int);
PozicijaAVL JednostrukaRL(PozicijaAVL);
PozicijaAVL DvostrukaRL(PozicijaAVL);
PozicijaAVL JednostrukaRD(PozicijaAVL);
PozicijaAVL DvostrukaRD(PozicijaAVL);



struct cvorAVLStudenti{	//1

	//ovdje ide ID za ime studenta
	int ID;
	char PrezimeIme[NAME_LENGTH];
	StabloAVL L; // lijevi student
	StabloAVL D; // desni student
	//PozicijaP NextP; // iduci predmet

	int visina;
};

PozicijaAVL nadiPoID(int id, PozicijaAVL Root);
int ispisStudenta(PozicijaAVL S);
int ispisSvihStudenata(PozicijaAVL Root);
//FILE* ispisZaglavljaStudenti(); // daje error ako je otkomentiran
