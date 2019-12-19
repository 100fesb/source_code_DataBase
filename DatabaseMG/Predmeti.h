#include "Constants.h"


struct cvorAVLPredmeti;
//deklarirali pokazivace
//typedef struct cvorAVLPredmeti* PozicijaS;					//pokazivac na sljedeceg studenta
typedef struct cvorAVLPredmeti CvorAVLPre;
typedef struct cvorAVLPredmeti* StabloAVLPre;
typedef struct cvorAVLPredmeti* PozicijaAVLPre;

int VisinaPre(StabloAVLPre);
StabloAVLPre DodajAVLPre(int, char*, StabloAVLPre);
int Max(int, int);
PozicijaAVLPre JednostrukaRLPre(PozicijaAVLPre);
PozicijaAVLPre DvostrukaRLPre(PozicijaAVLPre);
PozicijaAVLPre JednostrukaRDPre(PozicijaAVLPre);
PozicijaAVLPre DvostrukaRDPre(PozicijaAVLPre);



struct cvorAVLPredmeti{	//1

	//ovdje ide ID za ime predmeta
	int ID;
	char ImePre[NAME_LENGTH];
	StabloAVLPre L; // lijevi predmet
	StabloAVLPre D; // desni predmet
	//PozicijaP NextP; // iduci predmet

	int visina;
};

PozicijaAVLPre nadiPoIDPre(int id, PozicijaAVLPre Root);
StabloAVLPre generirajAVL_Predmeti(StabloAVLPre P);
//int ispisStudenta(PozicijaAVLPre S);
//int ispisSvihStudenata(PozicijaAVLPre Root);
