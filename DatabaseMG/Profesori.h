#include "Constants.h"

#ifndef PROFESORI
#define PROFESORI

//deklarirali pokazivace
//typedef struct cvorAVLProfesori* PozicijaS;					//pokazivac na sljedeceg studenta
typedef struct cvorAVLProfesori CvorAVLPro;
typedef struct cvorAVLProfesori* StabloAVLPro;
typedef struct cvorAVLProfesori* PozicijaAVLPro;

int VisinaPro(StabloAVLPro);
StabloAVLPro DodajAVLPro(int, char*, StabloAVLPro);
int Max(int, int);
PozicijaAVLPro JednostrukaRLPro(PozicijaAVLPro);
PozicijaAVLPro DvostrukaRLPro(PozicijaAVLPro);
PozicijaAVLPro JednostrukaRDPro(PozicijaAVLPro);
PozicijaAVLPro DvostrukaRDPro(PozicijaAVLPro);



struct cvorAVLProfesori{	//1

	//ovdje ide ID za ime profesora
	int ID;
	char ImePro[NAME_LENGTH];
	StabloAVLPro L; // lijevi profesor
	StabloAVLPro D; // desni profesor
	//PozicijaP NextP; // iduci profesor

	int visina;
};

PozicijaAVLPro nadiPoIDPro(int tempID, PozicijaAVLPro Root);


#endif 