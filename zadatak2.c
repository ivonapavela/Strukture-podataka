#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 128

typedef struct OSOBA* posoba;

typedef struct OSOBA {
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int godinarodenja;
	posoba next;
}osoba;

posoba AlocirajOsobu();
void odabir();
int DodajOsobuNaPocetakListe(posoba);
void unos(posoba);
void ispis(posoba);
void IspisListe(posoba);
int DodajOsobuNaKrajListe(posoba);
posoba PronadiOsobuUListiPoPrezimenu(posoba, char*);
void ObrisiOsobuIzListe(posoba, posoba);

int main()
{
	posoba head = AlocirajOsobu();
	int i = 1;
	char opcija = '\0';
	char prezime[MAX_NAME] = "";
	int mjesto = 0;
	posoba temp = NULL;

	while (i)
	{
		odabir();
		printf("Unesite vas odabir!\n");
		scanf(" %c", &opcija);

		switch (opcija)
		{
		case 'a':
		case 'A':
			DodajOsobuNaPocetakListe(head);
			break;
		case 'b':
		case 'B':
			IspisListe(head);
			break;
		case 'c':
		case 'C':
			DodajOsobuNaKrajListe(head);
			break;
		case 'd':
		case 'D':
			printf("Unesi prezime osobe!\n");
			scanf(" %s", prezime);
			temp=PronadiOsobuUListiPoPrezimenu(head, prezime);
			ispis(temp);
			break;
		case 'e':
		case 'E':
			printf("Unesi prezime osobe koju zelite izbrisati s liste!\n");
			scanf(" %s", prezime);
            temp=PronadiOsobuUListiPoPrezimenu(head, prezime);
			ObrisiOsobuIzListe(head, temp);
			break;
		case 'f':
		case 'F':
			printf("Izlaz!");
			i = 0;
			break;
		default:
			printf("Krivi unos!");
		}
	}

	return 0;
}

posoba AlocirajOsobu() {

	posoba novaosoba = NULL;
	novaosoba = (posoba)malloc(sizeof(osoba));

	if (!novaosoba)
	{
		perror("Greska pri alokaciji memorije!\n");
	}

	strcpy(novaosoba->ime, " ");
	strcpy(novaosoba->prezime, " ");
	novaosoba->godinarodenja = 0;
	novaosoba->next = NULL;

	return novaosoba;
}

int DodajOsobuNaPocetakListe(posoba head) {

	posoba novaosoba = AlocirajOsobu();

	if (!novaosoba)
	{
		perror("Greska pri ucitavanju osobe!\n");
		return -1;
	}
	unos(novaosoba);
	novaosoba->next = head->next;
	head->next = novaosoba;
	printf("Unijeli ste osobu na pocetak liste!\n");

	return 0;
}

void unos(posoba novaosoba) {

	char buffer[MAX_NAME] = { 0 };

	printf("Unesi ime osobe!\n");
	scanf(" %s", buffer);
	strcpy(novaosoba->ime, buffer);

	printf("Unesi prezime osobe!\n");
	scanf(" %s", buffer);
	strcpy(novaosoba->prezime, buffer);

	printf("Unesi godinu rodenja!\n");
	scanf("%d", &novaosoba->godinarodenja);
}

void ispis(posoba head) {

	printf("\n\nIME: %s\n", head->ime);
	printf("PREZIME: %s\n", head->prezime);
	printf("GODINA RODENJA: %d\n", head->godinarodenja);
}

void IspisListe(posoba head) {

	if (head->next == NULL)
	{
		printf("Lista je prazna!");
		return;
	}

	head = head->next;
	while (head->next != NULL)
	{
		ispis(head);
		head = head->next;
	}
	ispis(head);
}

int DodajOsobuNaKrajListe(posoba head) {

	while (head->next != NULL)
	{
		head = head->next;
	}

	posoba novaosoba = AlocirajOsobu();

	if (!novaosoba)
	{
		perror("Greska pri ucitavanju osobe!\n");
		return -1;
	}

	unos(novaosoba);
	novaosoba->next = head->next;
	head->next = novaosoba;
	printf("Unijeli ste osobu na kraj liste!\n");

	return 0;
}

posoba PronadiOsobuUListiPoPrezimenu(posoba head, char* prezime) {

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

void ObrisiOsobuIzListe(posoba head, posoba obrisi) {

    posoba prethodna = NULL;
    posoba temp = head;

    while(temp!=obrisi)
    {
        prethodna = temp;
        temp = temp->next;
    }

    prethodna->next = obrisi->next;
    free(obrisi);

}

void odabir() {

	printf("Odaberi:\n");
	printf("A. Dodaj osobu na pocetku liste!\n");
	printf("B. Ispisi listu!\n");
	printf("C. Dodaj osobu na kraju liste!\n");
	printf("D. Pronadi osobu s liste pomocu prezimena\n");
	printf("E. Izbrisi osobu s liste\n");
	printf("F. Nijedna od opcija!\n");
}
