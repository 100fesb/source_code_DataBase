#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "Assets.h"
#include "Constants.h"
#include "Predmeti.h"
#include "Studenti.h"
#include "Profesori.h"

int main()
{
	StabloAVL rootStudent = NULL;
	StabloAVLPre rootPredmet = NULL;
	StabloAVLPro rootProfesor = NULL;

	srand(time(0));

	rootStudent = generirajAVL_Student(rootStudent);
	rootPredmet = generirajAVL_Predmeti(rootPredmet);
	rootProfesor = generirajAVL_Profesori(rootProfesor);

	ispisIzbornika(rootStudent, rootPredmet, rootProfesor);

	system("pause");
	return 0;
}



