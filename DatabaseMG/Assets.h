FILE* OtvoriDatoteku()
{
	char *fileName = NULL;
	FILE *fp = NULL;

	fileName = (char*)malloc(sizeof(char)* BUFFER_LENGTH);
	if (fileName == NULL) return NULL;
	memset(fileName, '\0', BUFFER_LENGTH);

	/*
	printf("\r\n\tEnter file name : ");
	scanf(" %s", fileName);
	*/

	strcpy(fileName, "testnaDatoteka"); // ZA TEST SAMO, ODKOMENTIRAT IZNAT U PRODUKCIJI

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("\r\n\tError!\r\n\t%s The file couldn't be opened.", fileName);
		return NULL;
	}

	return fp;
}

int Max(int a, int b)
{
	return a > b ? a : b;
}