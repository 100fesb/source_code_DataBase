#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<time.h>

//deklarirali pokazivace
typedef struct Ocjene* PozicijaO;

struct Ocjene{	//6
	//ovdje ide ID za ocjenu
	int ID;
	//pokazivac na sljedecu ocjenu
	PozicijaO Next;

};