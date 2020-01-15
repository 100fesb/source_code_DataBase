#include "Constants.h"

#ifndef PROFESORI
#define PROFESORI

//deklarirali pokazivace
typedef struct cvorAVLProfesori CvorAVLPro;
typedef struct cvorAVLProfesori* StabloAVLPro;
typedef struct cvorAVLProfesori* PozicijaAVLPro;

int VisinaPro(StabloAVLPro);
StabloAVLPro DodajAVLPro(int, char*, char**, StabloAVLPro, int);
int Max(int, int);
PozicijaAVLPro JednostrukaRLPro(PozicijaAVLPro);
PozicijaAVLPro DvostrukaRLPro(PozicijaAVLPro);
PozicijaAVLPro JednostrukaRDPro(PozicijaAVLPro);
PozicijaAVLPro DvostrukaRDPro(PozicijaAVLPro);



struct cvorAVLProfesori{	

	int ID;
	char ImePro[NAME_LENGTH];
	char predmeti[NAME_LENGTH][NAME_LENGTH];
	StabloAVLPro L; // lijevi profesor
	StabloAVLPro D; // desni profesor
	//PozicijaAVLPro NextPre; // iduci predmet, ako bude potrebno

	int visina;
};

PozicijaAVLPro nadiPoIDPro(int tempID, PozicijaAVLPro Root);
int unesiProfesora(StabloAVLPro rootPro);

#endif 