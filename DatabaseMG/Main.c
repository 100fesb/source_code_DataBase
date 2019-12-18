#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "AVL.h"
#include "Studenti.h"
#include "Profesori.h"
#include "Predmeti.h"
#include "Ocjene.h"
#include "Constants.h"
#include "TEMP.h"


int main()
{
	PozicijaS rootS = NULL;
	PozicijaAVL rootAVL = NULL;

	

	rootAVL = generirajAVL_Student(rootS);

	print_t(rootAVL);

	system("pause");
	return 0;
}

void Izbornik()
{
	//int Odabir=0;

	//printf("\n\n\t\t\tDOBRODOSLI U BAZU PODATAKA TIMA 100 POSTO");
	//printf("\n\n\t\t\tUnesite svoj izbor:");
	////Izbornik();

	//scanf("%d",&Odabir);

	//if(Odabir != 100)		//100 moze biti broj za izlaz iz izbornika
	//{

	//	switch(Odabir)
	//	{  

	//		case 1:
	//			IspisiSvePredmete(PozicijaPredmet_P->Next);
	//			break;
	//		case 2:
	//			//ime funkcije
	//			break;
	//		case 3:
	//			//ime funkcije
	//			break;
	//		case 4:
	//			//ime funkcije
	//			break;
	//		case 5:
	//			//ime funkcije
	//			break;

	//	}
	//}
	//else printf("\n\n\t\t\tUGODAN DAN ZELI TIM 100 POSTO\n");

	//printf("\n\n\n\n\n");
}
