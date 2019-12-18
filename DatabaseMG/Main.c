#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "Constants.h"
#include "Studenti.h"


int main()
{
	StabloAVL rootS = NULL, nadjeni = NULL;

	int id;


	//rootS = generirajAVL_Student(rootS);

	//print_t(rootS);

	ispisSvihStudenata(rootS);


	system("pause");
	return 0;
}

