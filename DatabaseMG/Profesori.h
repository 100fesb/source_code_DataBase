#include "Constants.h"

#ifndef PROFESORI
#define PROFESORI

typedef struct cvorAVLProfesori CvorAVLPro;
typedef struct cvorAVLProfesori* StabloAVLPro;
typedef struct cvorAVLProfesori* PozicijaAVLPro;

int VisinaPro(StabloAVLPro);
StabloAVLPro DodajAVLPro(int, char*, char**, StabloAVLPro, int);
PozicijaAVLPro JednostrukaRLPro(PozicijaAVLPro);
PozicijaAVLPro DvostrukaRLPro(PozicijaAVLPro);
PozicijaAVLPro JednostrukaRDPro(PozicijaAVLPro);
PozicijaAVLPro DvostrukaRDPro(PozicijaAVLPro); 
void printAVLprof(StabloAVLPro tree);
int _printAVLprof(StabloAVLPro tree, int is_left, int offset, int depth, char s[20][255]);

int IspisiSveProfesore();

struct cvorAVLProfesori{

	int ID;
	char ImePro[NAME_LENGTH];
	char predmeti[NAME_LENGTH][NAME_LENGTH];
	StabloAVLPro L; // lijevi profesor
	StabloAVLPro D; // desni profesor

	int visina;
};

PozicijaAVLPro nadiPoIDPro(int tempID, PozicijaAVLPro Root);
int unesiProfesora(StabloAVLPro rootPro);
int brisiPoIDuProfesor(StabloAVLPro rootPro);

#endif 