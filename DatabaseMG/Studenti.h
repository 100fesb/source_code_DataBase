//#include "Studenti.h"
#include "Constants.h"


struct cvorAVLStudenti;
//deklarirali pokazivace
//typedef struct cvorAVLStudenti* PozicijaS;					//pokazivac na sljedeceg studenta
typedef struct cvorAVLStudenti CvorAVL;
typedef struct cvorAVLStudenti* StabloAVL;
typedef struct cvorAVLStudenti* PozicijaAVL;

int Visina(StabloAVL);
StabloAVL dodajAVL(int, StabloAVL);
int Max(int, int);
PozicijaAVL JednostrukaRL(PozicijaAVL);
PozicijaAVL DvostrukaRL(PozicijaAVL);
PozicijaAVL JednostrukaRD(PozicijaAVL);
PozicijaAVL DvostrukaRD(PozicijaAVL);



struct cvorAVLStudenti{	//1

	//ovdje ide ID za ime studenta
	int ID;
	char PrezimeIme[NAME_LENGTH];
	StabloAVL L; // lijevi student
	StabloAVL D; // desni student
	//PozicijaP NextP; // iduci predmet

	int visina;
};


PozicijaAVL nadiPoID(int id, PozicijaAVL Root)
{
	if (!Root) return NULL;
	if (id == Root->ID) return Root;

	if (id > Root->L) nadiPoID(id, Root->D);
	else if (id < Root->L) nadiPoID(id, Root->L);
}

StabloAVL DodajAVL(int ID, char* PI, StabloAVL S)
{
	int n = 0;
	if (NULL == S)
	{
		S = (StabloAVL)malloc(sizeof(CvorAVL));
		S->ID = ID;
		S->visina = 0;
		strcpy(S->PrezimeIme, PI);
		S->L = S->D = NULL;
	}
	else{
		if (ID < S->ID){
			S->L = DodajAVL(ID, PI, S->L);
			n = Visina(S->L) - Visina(S->D);
			if (n == 2){
				if (ID < S->L->ID) S = JednostrukaRL(S);
				else S = DvostrukaRL(S);
			}
		}
		else if (ID > S->ID){
			S->D = DodajAVL(ID, PI, S->D);
			n = Visina(S->D) - Visina(S->L);
			if (n == 2){
				if (ID > S->D->ID) S = JednostrukaRD(S);
				else S = DvostrukaRD(S);
			}
		}
	}

	S->visina = Max(Visina(S->L), Visina(S->D)) + 1;
	return S;
}


// AVL stablo za studenta - vraca pokazivac na prvi element (root), prima root (do upsisa ce bit NULL)
// funkcije za AVL stabla moraju biti napisane posebno za svako AVLS jer moramo znati koji root vracamo (mogli smo sredit koji primamo preko druge funkcije)
StabloAVL generirajAVL_Student(StabloAVL P)
{
	FILE* fp = NULL;

	//temp variable
	int id = NULL;
	char str1[NAME_LENGTH/2];
	char str2[NAME_LENGTH/2];
	char prezimeIme[NAME_LENGTH];
	if (!str1 || !str2 || !prezimeIme) return ERROR;

	fp = OtvoriDatoteku();

	if (!fp) return NULL;

	while (!feof(fp))
	{

		fscanf(fp, " %d %s %s", &id, str1, str2);
		/*printf("ID: %d Name Acronim: %s\n", id, str);*/

		strcat(str1, " ");
		strcat(str1, str2);

		P = DodajAVL(id, str1, P);

	}


 	fclose(fp);

	// treba vratiti root
	return P;
}



PozicijaAVL findById(int id)
{

}

//int Izbornik()
//{
//	//ovjde cemo unijeti listu potrebnik izbora za nase potrebe
//	printf("\n\n\t\t\t");
//	printf("1-");
//	printf("");
//	printf("");
//	printf("");
//	printf("");
//	printf("");
//	printf("");
//	printf("");
//
//	return 0;
//
//}


int Visina(StabloAVL S)
{

	if (NULL == S) return -1;

	if (NULL == S->L && NULL == S->D) return 0;

	if (NULL == S->L){
		return 1 + Visina(S->D);
	}
	else if (NULL == S->D){
		return 1 + Visina(S->L);
	}
	// slucaj kada imamo dijete i slijeva i zdesna
	else{
		return Max(Visina(S->L), Visina(S->D)) + 1;
	}
}


PozicijaAVL JednostrukaRL(PozicijaAVL K2)
{
	PozicijaAVL K1;

	K1 = K2->L;
	K2->L = K1->D;
	K1->D = K2;

	K2->visina = Max(Visina(K2->L), Visina(K2->D)) + 1;
	K1->visina = Max(Visina(K1->L), K2->visina) + 1;

	return K1;
}

PozicijaAVL JednostrukaRD(PozicijaAVL K2)
{
	PozicijaAVL K1;

	K1 = K2->D;
	K2->D = K1->L;
	K1->L = K2;

	K2->visina = Max(Visina(K2->D), Visina(K2->L)) + 1;
	K1->visina = Max(Visina(K1->D), K2->visina) + 1;

	return K1;
}

PozicijaAVL DvostrukaRL(PozicijaAVL K3)
{
	K3->L = JednostrukaRD(K3->L);

	return JednostrukaRL(K3);
}

PozicijaAVL DvostrukaRD(PozicijaAVL K3)
{
	K3->D = JednostrukaRL(K3->D);

	return JednostrukaRD(K3);
}

