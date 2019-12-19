#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "Constants.h"
#include "Studenti.h"
#include "Predmeti.h"


int main()
{
	StabloAVL rootS = NULL, nadjeni = NULL;
	StabloAVLPre rootP = NULL;

	int id;


	//rootS = generirajAVL_Student(rootS);

	rootP = generirajAVL_Predmeti(rootP);

	print_t(rootS);

	//ispisSvihStudenata(rootS);


	system("pause");
	return 0;
}

