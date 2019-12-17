#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<time.h>

//ovim smo skratili imena
typedef struct Predmeti_P PredmetiP;
typedef struct PredmetiOcjene_PO PredmetiPO;
typedef struct PredmetiProfesora_PP PredmetiPP;
//deklarirali pokazivace
typedef struct Predmeti_P* PozicijaPredmet_P;
typedef struct PredmetiOcjene_PO* PozicijaOcjena_PO;
typedef struct PredmetiOcjene_PO* PozicijaPredmet_PO;
typedef struct PredmetiProfesora_PP* PozicijaPredmet_PP;
typedef struct Stablo* StabloP;

struct Predmeti_P{	//5

	//ovdje ide ID za ime predmeta
	int ID_Ime_P;
	//pokazivac na sljedeci predmet
	PozicijaPredmet_P Next;

};

struct PredmetiOcjene_PO{	//2

	//ovdje ide ID za ime predmeta
	int ID_Ime_PO;
	//pokazivac na ocjenu predmeta
	PozicijaOcjena_PO Next;
	//pokazivac na sljedeci predmet
	PozicijaPredmet_PO Next;
};

struct PredmetiProfesora_PP{	//4

	//ovdje ide ID za ime predmeta
	int ID_Ime_PP;
	//pokazivac na sljedeci predmet
	PozicijaPredmet_PP Next;

};



