#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 20
#define MAX_LINE 128

typedef struct OSOBA* posoba;

typedef struct OSOBA {

	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int godinarodenja;
	posoba next;

}osoba;

posoba AlocirajOsobu();
int ispis();
int DinamickiDodajNoviElementNaPocetakListe(posoba);
int IspisListe(posoba);
int DinamickiDodajNoviElementNaKrajListe(posoba);
posoba PronadiElementUListi(posoba, char*);
int BrisiOdredeniElementIzListe(posoba, int);
int unos(posoba);
int DinamickiDodajElementIzaOdredenogElementa(posoba, int);
int DinamickiDodajElementIspredOdredenogElementa(posoba, int);
int SortiraniUnos(posoba);
int UpisListeUDatoteku(posoba, char*);
int CitanjeListeIzDatoteke(posoba, char*);

int main()
{
	int i = 1;
	char odabir = '\0';
	char* prezime = { 0 };
	int pozicija = 0;
	posoba head = AlocirajOsobu();
	posoba temp = NULL;
	FILE* datoteka = NULL;

	while (i)
	{
		ispis();
		printf("Unesite svoj odabir:\n");
		scanf(" %c", &odabir);

		switch (odabir)
		{
		case 'A':
		case 'a':
			DinamickiDodajNoviElementNaPocetakListe(head);
			break;
		case 'B':
		case 'b':
			IspisListe(head);
			break;
		case 'C':
		case 'c':
			DinamickiDodajNoviElementNaKrajListe(head);
			break;
		case 'D':
		case 'd':
			printf("Unesi prezime po kojem zelite pronaci element iz liste:\n");
			scanf(" %s", prezime);
			temp = PronadiElementUListi(head, prezime);
			printf("Osoba sa trazenim prezimenom:\nIME:%s\tPREZIME:%s\tGODINA RODENJA:%d\n", temp->ime, temp->prezime, temp->godinarodenja);
			break;
		case 'E':
		case 'e':
			printf("Unesite poziciju na kojoj zelite izbrisati element iz liste:\n");
			scanf("%d", &pozicija);
			BrisiOdredeniElementIzListe(head, pozicija);
			break;
		case 'F':
		case 'f':
			printf("Izlaz!\n");
			i = 0;
			break;
		case '1':
			printf("Unesite poziciju iza koje zelite unijeti element:\n");
			scanf("%d", &pozicija);
			DinamickiDodajElementIzaOdredenogElementa(head, pozicija);
			break;
		case '2':
			printf("Unesite poziciju ispred koje zelite unijeti element:\n");
			scanf("%d", &pozicija);
			DinamickiDodajElementIspredOdredenogElementa(head, pozicija);
			break;
		case '3':
			SortiraniUnos(head);
			break;
		case '4':
			UpisListeUDatoteku(head, datoteka);
			break;
		case '5':
			CitanjeListeIzDatoteke(head, datoteka);
			break;
		default:
			perror("Unijeli ste krivi odabir!\n");
		}
	}
	return 0;
}

posoba AlocirajOsobu()
{
	posoba novaosoba = NULL;
	novaosoba = (posoba)malloc(sizeof(osoba));

	if (!novaosoba)
	{
		perror("Greska pri alokaciji osobe!\n");
	}

	strcpy(novaosoba->ime, " ");
	strcpy(novaosoba->prezime, " ");
	novaosoba->godinarodenja = 0;
	novaosoba->next = NULL;

	return novaosoba;
}

int ispis()
{
	printf("Odaberi:\n");
	printf("A.dinamicki dodaje novi element na pocetak liste\n");
	printf("B.ispisuje listu\n");
	printf("C.dinamicki dodaje novi element na kraj liste\n");
	printf("D.pronalazi element u listi po prezimenu\n");
	printf("E.brise odredeni element iz liste\n");
	printf("F.Izlaz!\n");
	printf("1.dinamicki dodaje novi element iza odredenog elementa\n");
	printf("2.dinamicki dodaje novi element ispred odredenog elementa\n");
	printf("3.sortira listu po prezimenima osoba\n");
	printf("4.upisuje listu u datoteku\n");
	printf("5.cita listu iz datoteke\n");

	return 0;
}

int DinamickiDodajNoviElementNaPocetakListe(posoba head)
{
	posoba novaosoba = AlocirajOsobu();

	unos(novaosoba);

	novaosoba->next = head->next;
	head->next = novaosoba;

	return 0;
}

int unos(posoba novaosoba)
{
	char buffer[MAX_NAME] = { 0 };

	printf("Unesite ime osobe:\n");
	scanf(" %s", buffer);
	strcpy(novaosoba->ime, buffer);

	printf("Unesite prezime osobe:\n");
	scanf(" %s", buffer);
	strcpy(novaosoba->prezime, buffer);

	printf("Unesite godinu rodenja:\n");
	scanf("%d", &novaosoba->godinarodenja);

	return 0;
}

int IspisListe(posoba head)
{
	head = head->next;
	while (head->next)
	{
		printf("IME:%s\tPREZIME:%s\tGODINA RODENJA:%d\n", head->ime, head->prezime, head->godinarodenja);
		head = head->next;
	}

	printf("IME:%s\tPREZIME:%s\tGODINA RODENJA:%d\n", head->ime, head->prezime, head->godinarodenja);

	return 0;
}

int DinamickiDodajNoviElementNaKrajListe(posoba head)
{
	posoba novaosoba = AlocirajOsobu();
	posoba temp = head;

	unos(novaosoba);

	while (temp->next)
	{
		temp = temp->next;
	}

	novaosoba->next = temp->next;
	temp->next = novaosoba;

	return 0;
}

posoba PronadiElementUListi(posoba head, char* prezime)
{
	posoba temp = head;

	if (temp->next == NULL)
	{
		printf("Lista je prazna!\n");
		return 0;
	}

	while (temp)
	{
		if (strcmp(temp->prezime, prezime) == 0)
		{
			return temp;
		}

		temp = temp->next;
	}

	return temp;
}

int BrisiOdredeniElementIzListe(posoba head, int pozicija)
{
	posoba temp = head;
	posoba prethodnaosoba = NULL;
	int i = 0;

	for (i = 0; i < pozicija - 1; i++)
	{
		prethodnaosoba = temp;
		temp = temp->next;
	}

	prethodnaosoba->next = temp->next;

	free(temp);

	return 0;
}

int DinamickiDodajElementIzaOdredenogElementa(posoba head, int pozicija)
{
	posoba temp = head;
	posoba novaosoba = AlocirajOsobu();
	int i = 0;

	for (i = 0; i < pozicija; i++)
	{
		temp = temp->next;
	}

	unos(novaosoba);

	novaosoba->next = temp->next;
	temp->next = novaosoba;

	return 0;
}

int DinamickiDodajElementIspredOdredenogElementa(posoba head, int pozicija)
{
	posoba temp = head;
	posoba novaosoba = AlocirajOsobu();
	int i = 0;

	for (i = 0; i < pozicija - 1; i++)
	{
		temp = temp->next;
	}

	unos(novaosoba);

	temp->next = novaosoba;
	novaosoba->next = temp->next;

	return 0;
}

int SortiraniUnos(posoba head)
{
	posoba temp = head;
	posoba novaosoba = AlocirajOsobu();

	unos(novaosoba);

	for (temp; temp->next != NULL; temp = temp->next)
	{
		if (strcmp(temp->prezime, novaosoba->prezime) > 0)
			break;
		if (strcmp(temp->prezime, novaosoba->prezime) == 0)
		{
			if (strcmp(temp->ime, novaosoba->ime) > 0)
				break;
			if (strcmp(temp->ime, novaosoba->ime) == 0)
			{
				if (temp->godinarodenja > novaosoba->godinarodenja)
					break;
			}
		}
	}

	novaosoba->next = temp->next;
	temp->next = novaosoba;

	return 0;
}

int UpisListeUDatoteku(posoba head, FILE* datoteka)
{
	posoba temp = head->next;
	char* nazivdatoteke = NULL;

	printf("Unesite naziv datoteke:\n");
	scanf(" %s", nazivdatoteke);
	
	datoteka = fopen(nazivdatoteke, "w");

	if (!datoteka)
	{
		perror("Greska pri ucitavanju datoteke!\n");
	}

	while (temp)
	{
		fprintf(datoteka, "IME:%s\tPREZIME:%s\tGODINA RODENJA:%d\n", temp->ime, temp->prezime, temp->godinarodenja);
		temp = temp->next;
	}

	fclose(datoteka);

	return 0;
}

int CitanjeListeIzDatoteke(posoba head, FILE* datoteka)
{
	char buffer[MAX_NAME] = { 0 };
	posoba novaosoba = AlocirajOsobu();
	char* nazivdatoteke = NULL;

	printf("Unesite naziv datoteke:\n");
	scanf(" %s", nazivdatoteke);
	
	datoteka = fopen(nazivdatoteke, "r");

	if (!datoteka)
	{
		perror("Greska pri ucitavanju datoteke!\n");
		return -1;
	}

	while (!feof(datoteka))
	{
		fscanf(datoteka, " %s", buffer);
		strcpy(novaosoba->ime, buffer);

		fscanf(datoteka, " %s", buffer);
		strcpy(novaosoba->prezime, buffer);

		fscanf(datoteka, "%d", &novaosoba->godinarodenja);
	}

	fclose(datoteka);

	return 0;
}
