// bezveze
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<time.h>

//deklarirali pokazivace
typedef struct Profesori* PozicijaProfesor;					//pokazivac na sljedeceg profesora
typedef struct PredmetiProfesora_PP* PozicijaPredmet_PP;	//pokazivac na predmete profesora

struct Profesori{	//3
	//ovdje ide ID za ime profesora
	int ID_Ime;
	//pokazivac na sljedeceg profesora
	PozicijaProfesor Next;
	//pokazivac na predmete profesora
	PozicijaPredmet_PP Next;

};
