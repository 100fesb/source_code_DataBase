#include "Constants.h"

#ifndef PREDMETI
#define PREDMETI

typedef struct cvorAVLPredmeti CvorAVLPre;
typedef struct cvorAVLPredmeti* StabloAVLPre;
typedef struct cvorAVLPredmeti* PozicijaAVLPre;

int VisinaPre(StabloAVLPre);
StabloAVLPre DodajAVLPre(int, char*, char*, StabloAVLPre);
PozicijaAVLPre JednostrukaRLPre(PozicijaAVLPre);
PozicijaAVLPre DvostrukaRLPre(PozicijaAVLPre);
PozicijaAVLPre JednostrukaRDPre(PozicijaAVLPre);
PozicijaAVLPre DvostrukaRDPre(PozicijaAVLPre);
void printAVLpred(StabloAVLPre tree);
int _printAVLpred(StabloAVLPre tree, int is_left, int offset, int depth, char s[20][255]);

int IspisiSvePredmete();


struct cvorAVLPredmeti{

	int ID;
	char ImePre[NAME_LENGTH];
	char ImePrezimeProfesora[NAME_LENGTH];
	StabloAVLPre L; // lijevi predmet
	StabloAVLPre D; // desni predmet

	int visina;
};

PozicijaAVLPre nadiPoIDPre(int tempID, PozicijaAVLPre Root);
int unesiPredmet(StabloAVLPre rootPre);
int brisiPoIDuPredmet(StabloAVLPre rootPre);
StabloAVLPre brisiAVLElementPre(StabloAVLPre P, int ID);
StabloAVLPre traziNajmanjiIDPre(StabloAVLPre P);

#endif