#include <stdlib.h>
#include <stdio.h>

#include "Studenti.h"
#include "Predmeti.h"
#include "Profesori.h"

#ifndef ASSETS
#define ASSETS



FILE* OtvoriDatoteku(char mode, char* fileName);
int Max(int a, int b);
int generirajID(int MIN, int MAX);
int nadjiIdPoImenu(char* buff, char* ime);
int getNthItemFromString(int INDEX, char* STR);

int izbrisiLinijuPoID(char* datoteka, int ID);
int izbrisiLinijuPoImenu(char* datoteka, char* trazenoIme);




#endif