#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "Constants.h"
<<<<<<< HEAD
#include "Studenti.h"
=======
#include "Assets.h"
//#include "AVL.h"
#include "Studenti.h"
#include "Profesori.h"
#include "Predmeti.h"
#include "Ocjene.h"
#include "TEMP.h"
>>>>>>> 657985a592cb5b98ca06daeab3fc6b3c62ceebf5


int main()
{
	StabloAVL rootS = NULL, nadjeni = NULL;

	int res, id;

	/*rootS = (PozicijaS)malloc(sizeof(struct Studenti));
	rootS->Next = NULL;
	*/

	rootS = generirajAVL_Student(rootS);

	print_t(rootS);

<<<<<<< HEAD

	do{
		printf("unesite ID za pretragu (0 za izlaz): ");
		scanf(" %d", &id);

		nadjeni = nadiPoID(id, rootS);

		if (!nadjeni){
			printf("Nismo nasli studenta!");
			continue;
		}
		printf("Nadjeni student: %d %s", nadjeni->ID, nadjeni->PrezimeIme);
	} while (id != 0);
=======
	printf("unesite ID za pretragu: ");
	scanf(" %d", &id);

	nadjeni = nadiPoID(id, rootS);

	if (!nadjeni){
		printf("Nismo nasli studenta!");
		system("pause");
		return ERROR;
	}
	printf("Nadjeni student: %d %s", nadjeni->ID, nadjeni->PrezimeIme);
>>>>>>> 657985a592cb5b98ca06daeab3fc6b3c62ceebf5

	printf("Res of strcmp: %d\n", strcmp("aaaa", "aaa"));

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
