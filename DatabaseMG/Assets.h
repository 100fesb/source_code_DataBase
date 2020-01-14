#include <stdlib.h>
#include <stdio.h>

#include "Studenti.h"
#include "Predmeti.h"
#include "Profesori.h"

#ifndef ASSETS
#define ASSETS



FILE* OtvoriDatoteku(char* fileName);
int Max(int a, int b);
int generirajID(int MIN, int MAX);
int nadjiIdPoImenu(char* buff, char* ime);


int ispisIzbornika(StabloAVL rootS, StabloAVLPre rootPre, StabloAVLPro rootPro);
int ispisPodIzbornika(StabloAVL rootS, StabloAVLPre rootPre, StabloAVLPro rootPro, int izbor, char* TEMP_NAME_HOLDER);





#endif