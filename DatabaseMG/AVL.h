struct cvorStablaAVL;
typedef struct cvorStablaAVL CvorAVL; 
typedef struct cvorStablaAVL* StabloAVL; 
typedef struct cvorStablaAVL* PozicijaAVL;

int Visina(StabloAVL);
StabloAVL dodajAVL(int, StabloAVL);
int Max(int, int);
PozicijaAVL JednostrukaRL(PozicijaAVL);
PozicijaAVL DvostrukaRL(PozicijaAVL);
PozicijaAVL JednostrukaRD(PozicijaAVL);
PozicijaAVL DvostrukaRD(PozicijaAVL);

struct cvorStablaAVL{
	int ID;				// po ID-u se slaze AVL stablo
	StabloAVL L;
	StabloAVL D;
	int visina;
};




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

/*

StabloAVL DodajAVL(int ID, StabloAVL S)
{
	int n = 0;
	if (NULL == S)
	{
		S = (StabloAVL)malloc(sizeof(CvorAVL));
		S->ID = ID;
		S->visina = 0;
		S->L = S->D = NULL;
	}
	else{
		if (ID < S->ID){
			S->L = DodajAVL(ID, S->L);
			n = Visina(S->L) - Visina(S->D);
			if (n == 2){
				if (ID < S->L->ID) S = JednostrukaRL(S);
				else S = DvostrukaRL(S);
			}
		}
		else if (ID > S->ID){
			S->D = DodajAVL(ID, S->D);
			n = Visina(S->D) - Visina(S->L);
			if (n == 2){
				if (ID > S->D->ID) S = JednostrukaRD(S);
				else S = DvostrukaRD(S);
			}
		}
	}

	S->visina = Max(Visina(S->L), Visina(S->D))+1;
	return S;
}


*/

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

