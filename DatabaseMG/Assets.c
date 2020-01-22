#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#include "Constants.h"
#include "Assets.h"
#include "Studenti.h"
#include "Predmeti.h"
#include "Profesori.h"

int izbrisiLinijuPoImenu(char* datoteka, char* trazenoIme)
{
	FILE* fr = NULL;
	FILE* fw = NULL;
	int i = 0;
	int tempID = 0;
	int readBytes = 0;
	char tempIme[NAME_LENGTH] = "";
	char* buff = NULL;
	char* temp = NULL;

	buff = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	temp = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (!buff || !temp) return ERROR;

	fr = OtvoriDatoteku('r', datoteka);
	fw = OtvoriDatoteku('w', "temp.txt");

	while (!feof(fr))
	{
		fgets(buff, BUFFER_LENGTH, fr);
		temp = buff;
		for (i = 0; temp[i]; temp[i] == ':' ? i++ : *temp++);
		if (i == 0){
			sscanf(buff, "%d %[^\n]", &tempID, tempIme);
			if (!strcmp(tempIme, trazenoIme)) continue;
			else fprintf(fw, "%s", buff);
		}
		else {
			sscanf(buff, "%d %[^ :]", &tempID, tempIme);
			if (!strcmp(tempIme, trazenoIme)) continue;
			else fprintf(fw, "%s", buff);
		}
	}


	fclose(fr);
	fclose(fw);
	
	remove(datoteka);
	rename("temp.txt", datoteka);
	
	free(buff);

	return SUCCESS;
}

int izbrisiLinijuPoID(char* datoteka, int trazeniID)
{
	FILE* fr = NULL;
	FILE* fw = NULL;
	int procitaniID = 0;
	int prosliID = -1;
	char* tempStr = NULL;
	char* tempStr2 = NULL;
	char* buff = NULL;

	tempStr = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	tempStr2 = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	buff = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (!tempStr || !tempStr2 || !buff) return ERROR;

	fr = OtvoriDatoteku('r', datoteka);
	fw = OtvoriDatoteku('w', "temp.txt");

	while (!feof(fr))
	{
		fgets(buff, BUFFER_LENGTH, fr);
		sscanf(buff, "%d", &procitaniID);

		if (procitaniID == trazeniID) continue;
		if (procitaniID == prosliID) continue; // uvjet zbog \n na kraju datoteke
		fprintf(fw, "%s", buff);
		prosliID = procitaniID;
	}
	fclose(fr);
	fclose(fw);

	remove(datoteka);
	rename("temp.txt", datoteka);

	free(tempStr);
	free(tempStr2);
	free(buff);
	return SUCCESS;
}

int getNthItemFromString(int INDEX, char* STR)
{
	int i = 0;
	int tempItem = -1;
	int readBytes = 0;

	while (i <= INDEX){
		sscanf(STR, " %d %n", &tempItem, &readBytes);
		STR += readBytes;
		i++;
	}

	return tempItem;
}


FILE* OtvoriDatoteku(char mode, char* fileName)
{
	FILE *fp = NULL;

	if (NULL == fileName){
		printf("\r\n\tUnesite ime datoteke : ");
		scanf(" %s", fileName);
	}


	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	if (mode == 'r') fp = fopen(fileName, "r");
	else if (mode == 'w') fp = fopen(fileName, "w");
	else if (mode == 'a') fp = fopen(fileName, "a");

	if (fp == NULL)
	{
		printf("\r\n\tError!\r\n\tNije moguce ucitavanje datoteke '%s', molimo pokusajte ponovno.", fileName);
		return NULL;
	}

	return fp;
}

char* readLine()
{
	char placeholder[NAME_LENGTH] = "";
	fflush(stdin);
	fgets(placeholder, sizeof(placeholder), stdin);
	if (placeholder[strlen(placeholder) - 1] == '\n') placeholder[strlen(placeholder) - 1] = NULL;

	return placeholder;
}


int Max(int a, int b)
{
	return a > b ? a : b;
}

int generirajID(int MIN, int MAX)
{
	int DIVIDER = MAX - MIN;
	return rand() % DIVIDER + MIN;
}

int nadjiIdPoImenu(FILE* fp, char* ime)
{
	int ID = 0;
	char tempStr[BUFFER_LENGTH] = "";

	while (!feof(fp))
	{
		fscanf(fp, "%d %[^\n]", &ID, tempStr);
		if (!strcmp(tempStr, ime)) return ID;
	}


	return ERROR;
}