#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Constants.h"
#include "Assets.h"
#include "Studenti.h"
#include "Predmeti.h"
#include "Profesori.h"
#include "Korisnik.h"


int ispisIzbornika(StabloAVL rootS, StabloAVLPre rootPre, StabloAVLPro rootPro)
{
	int izbor = 0;
	int izbor2 = 0;
	char* TEMP_NAME_HOLDER = NULL;

	TEMP_NAME_HOLDER = (char*)malloc(sizeof(char)*NAME_LENGTH);


	do{
		printf("\n\n\t1 - Studenti\n\t2 - Predmeti\n\t3 - Profesori\n\t0 - Kraj Aplikacije\n\t\Unos: ");
		scanf("%d", &izbor);

		switch (izbor)
		{
		case 1:
			TEMP_NAME_HOLDER = "student";
			break;
		case 2:
			TEMP_NAME_HOLDER = "predmet";
			break;
		case 3:
			TEMP_NAME_HOLDER = "profesor";
			break;
		}
		if (izbor == 0) break;

		ispisPodIzbornika(rootS, rootPre, rootPro, izbor, TEMP_NAME_HOLDER);

	} while (izbor != 0);

	return SUCCESS;
}

int ispisPodIzbornika(StabloAVL rootS, StabloAVLPre rootPre, StabloAVLPro rootPro, int izbor, char* TEMP_NAME_HOLDER)
{
	int izbor2 = 0;

	do{
		printf("\n\n\t1 - Unos jednog %sa\n\t2 - Unos liste %sa\n\t3 - Ispis %sa\n\t4 - Ispis svega %sa\n\t5 - Ispis AVL Stabla %sa\n\t6 - Brisanje %sa\n\t0 - Nazad\n\t\Unos: ", TEMP_NAME_HOLDER, TEMP_NAME_HOLDER, TEMP_NAME_HOLDER, TEMP_NAME_HOLDER, TEMP_NAME_HOLDER, TEMP_NAME_HOLDER);

		scanf("%d", &izbor2);

		switch (izbor2)
		{
		case 1:
			// unos jednog
			if (izbor == 1) unesiStudenta(rootS);
			if (izbor == 2) unesiPredmet(rootPre);
			if (izbor == 3) unesiProfesora(rootPro);

			break;
		case 2:
			// unos liste
			printf("\n\t~~Unesite kraj za prekid~~\n");

			if (izbor == 1){
				while (unesiStudenta(rootS) != END){ /*system("cls || clear");*/ }
			}
			else if (izbor == 2){
				while (unesiPredmet(rootPre) != END){ /*system("cls || clear");*/ }
			}
			else if (izbor == 3){
				while (unesiProfesora(rootPro) != END){ /*system("cls || clear");*/ }
			}


			break;
		case 3:		//ispis
			if (izbor == 1) IspisiSveStudente();
			else if (izbor == 2) IspisiSvePredmete();
			else if (izbor == 3) IspisiSveProfesore();
			//else if (izbor2 == 4) 
			break;
		case 4:
			IspisiSve();
			break;
		case 5:
			if (izbor == 1) printAVLstud(rootS);
			else if (izbor == 2) printAVLpred(rootPre);
			else if (izbor == 3) printAVLprof(rootPro);
			break;
		case 6:
			if (izbor == 1) brisiPoIDuStudent(rootS);
			else if (izbor == 2) brisiPoIDuPredmet(rootPre);
			break;
		}

	} while (izbor2 != 0);

	return SUCCESS;
}