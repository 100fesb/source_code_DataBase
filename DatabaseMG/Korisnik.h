#include <stdlib.h>
#include <stdio.h>

#include "Studenti.h"
#include "Predmeti.h"
#include "Profesori.h"

#ifndef KORISNIK
#define KORISNIK

int ispisIzbornika(StabloAVL rootS, StabloAVLPre rootPre, StabloAVLPro rootPro);
int ispisPodIzbornika(StabloAVL rootS, StabloAVLPre rootPre, StabloAVLPro rootPro, int izbor, char* TEMP_NAME_HOLDER);

#endif