#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 128
#define MAX_LINE 1024

typedef struct {
	char ime[MAX_NAME];
	char prezime[MAX_LINE];
	double bodovi;
} student;

int BrojRedakaUDatoteci(char* dat);
student* AlocirajProstorIUcitajPodatke(char*, int);

int main() {

	int brojstudenata = 0;
	char* datoteka = NULL;
	student* stud = NULL;
	double maxbodovi = 0;
	int i = 0;

	brojstudenata = BrojRedakaUDatoteci(datoteka);
	stud = AlocirajProstorIUcitajPodatke(datoteka, brojstudenata);

	for (i = 0; i < brojstudenata; i++)
	{
		if (maxbodovi < stud[i].bodovi)
		{
			maxbodovi = stud[i].bodovi;
		}
	}

	printf("IME\tPREZIME\tAPSOLUTNI\tRELATIVNI\n");

	for (i = 0; i < brojstudenata; i++)
	{
		printf(" %s\t%s\t%lf\t%lf\n", stud[i].ime, stud[i].prezime, stud[i].bodovi, stud[i].bodovi / maxbodovi * 100);
	}

	return 0;
}

int BrojRedakaUDatoteci(char* nazivdatoteke) {

	FILE* datoteka = NULL;
	int brojac = 0;
	char buffer[MAX_LINE] = { 0 };

	datoteka = fopen(nazivdatoteke, "r");

	if (!datoteka)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(datoteka))
	{
		fgets(buffer, MAX_LINE, datoteka);
		brojac++;
	}

	fclose(datoteka);
	return brojac;
}

student* AlocirajProstorIUcitajPodatke(char* nazivdatoteke, int brstud) {

	FILE* datoteka = NULL;
	int brojac = 0;
	student* stud = NULL;

	stud = (student*)malloc(brstud * sizeof(student));

	if (!stud)
	{
		printf("Greska pri alociranju memorije!\n");
		return NULL;
	}

	datoteka = fopen(nazivdatoteke, "r");

	if (!datoteka)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return NULL;
	}

	while (!feof(datoteka))
	{
		fscanf(datoteka, " %s %s %lf\n", stud[brojac].ime, stud[brojac].prezime, stud[brojac].bodovi);
		brojac++;
	}

	fclose(datoteka);

	return stud;

}
