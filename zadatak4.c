#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME 20
#define MAX_LINE 1024

typedef struct ELEMENT* pelement;

typedef struct ELEMENT {
	int koeficijent;
	int eksponent;
	pelement next;
}element;

pelement AlocirajElement();
int CitajDatoteku(pelement, pelement);
int UnosElemenataUListu(pelement, char*);
pelement unos(int, int);
int SortiranUnos(pelement, pelement);
pelement ZbrajanjePolinoma(pelement, pelement);
pelement MnozenjePolinoma(pelement, pelement);
int ispis(pelement);

int main()
{
	pelement head1 = AlocirajElement();
	pelement head2 = AlocirajElement();
	pelement rezultatzbrajanja = AlocirajElement();
	pelement rezultatmnozenja = AlocirajElement();

	CitajDatoteku(head1, head2);
	ispis(head1->next);
	ispis(head2->next);

	rezultatzbrajanja = ZbrajanjePolinoma(head1, head2);
	ispis(rezultatzbrajanja->next);

	rezultatmnozenja = MnozenjePolinoma(head1, head2);
	ispis(rezultatmnozenja->next);

	return 0;
}

pelement AlocirajElement()
{
	pelement novielement = NULL;
	novielement = (pelement)malloc(sizeof(element));

	if (!novielement)
	{
		perror("Greska pri ucitavanju elementa!\n");
	}

	novielement->koeficijent = 0;
	novielement->eksponent = 0;
	novielement->next = NULL;

	return novielement;
}

int CitajDatoteku(pelement head1, pelement head2)
{
	char* nazivdatoteke = NULL;
	char buffer[MAX_LINE] = { 0 };

		printf("Unesi ime datoteke:\n");
		scanf(" %s", nazivdatoteke);

		FILE* datoteka = fopen(nazivdatoteke, "r");

		if (!datoteka)
		{
			perror("Greska pri otvaranju datoteke!\n");
			return -1;
		}

		fgets(buffer, MAX_LINE, datoteka);
		UnosElemenataUListu(head1, buffer);

		fgets(buffer, MAX_LINE, datoteka);
		UnosElemenataUListu(head2, buffer);

		fclose(datoteka);

		return 0;
}

int UnosElemenataUListu(pelement head, char* buffer)
{
	char* temp = buffer;
	int status = 0;
	int koeficijent = 0;
	int eksponent = 0;
	int numbytes = 0;
	pelement novielement = NULL;

	while (strlen(temp) > 0)
	{
		status = sscanf(temp, " %d %d %n", &koeficijent, &eksponent, &numbytes);
		if (status != 2)
		{
			perror("Greska u datoteci!\n");
			return -1;
		}
		novielement = unos(koeficijent, eksponent);

		if (!novielement)
		{
			perror("Greska pri stvaranju elementa!\n");
			return -1;
		}

		SortiranUnos(head, novielement);

		temp += numbytes;
	}

	return 0;
}

pelement unos(int koeficijent, int eksponent)
{
	pelement novielement = NULL;

	novielement=(pelement)malloc(sizeof(element));

	if (!novielement)
	{
		perror("Greska pri stvaranju elementa");
	}

	novielement->koeficijent = koeficijent;
	novielement->eksponent = eksponent;
	novielement->next = NULL;

	return novielement;
}

int SortiranUnos(pelement head, pelement novielement)
{
	pelement temp = head;
	pelement izbrisanielement = NULL;
	int rezultat = 0;

	while (temp->next != NULL && temp->next->eksponent < novielement->eksponent)
	{
		temp = temp->next;
	}

	if (temp->next == NULL || temp->next->eksponent != novielement->eksponent)
	{
		novielement->next = temp->next;
		temp->next = novielement;
	}
	else
	{
		rezultat = temp->next->koeficijent + novielement->koeficijent;
		if (rezultat == 0)
		{
			izbrisanielement = temp->next;
			temp->next = izbrisanielement->next;
			free(izbrisanielement);
		}
		else
		{
			temp->next->koeficijent = rezultat;
		}

		free(novielement);
	}

	return 0;
}

pelement ZbrajanjePolinoma(pelement head1, pelement head2)
{
	pelement rezultat = NULL;
	pelement i = NULL;
	pelement j = NULL;
	pelement novielement = NULL;

	for (i = head1->next; i != NULL; i = i->next)
	{
		novielement = unos(i->koeficijent, i->eksponent);
		if (!novielement)
		{
			perror("Greska pri stvaranju elementa!\n");
		}

		SortiranUnos(rezultat, novielement);
	}

	for (j = head2->next; j != NULL; j = j->next)
	{
		novielement = unos(j->koeficijent, j->eksponent);
		if (!novielement)
		{
			perror("Greska pri stvaranju elementa!\n");
		}

		SortiranUnos(rezultat, novielement);
	}

	return rezultat;
}

pelement MnozenjePolinoma(pelement head1, pelement head2)
{
	pelement rezultat = NULL;
	pelement i = NULL;
	pelement j = NULL;
	pelement novielement = NULL;

	for (i = head1->next; i != NULL; i = i->next)
	{
		for (j = head2->next; j != NULL; j = j->next)
		{
			novielement = unos(i->koeficijent, i->eksponent);
			if (!novielement)
			{
				perror("Greska pri stvaranju elementa!\n");
			}

			SortiranUnos(rezultat, novielement);

		}
	}

	return rezultat;
}

int ispis(pelement novielement)
{
	printf("Polinom:\n");

	if (novielement)
	{
		if (novielement->eksponent < 0)
		{
			if (novielement->koeficijent == 1)
			{
				printf("x^%d", novielement->eksponent);
			}
			else
			{
				printf("%dx^%d", novielement->koeficijent, novielement->eksponent);
			}
		}
		else
		{
			if (novielement->koeficijent == 1)
			{
				printf("x^%d", novielement->eksponent);
			}
			else
			{
				printf("%dx^%d", novielement->koeficijent, novielement->eksponent);
			}
		}

		novielement = novielement->next;
	}

	while (novielement)
	{
		if (novielement->koeficijent < 0)
		{
			if (novielement->eksponent < 0)
			{
				printf(" - %dx^%d", abs(novielement->koeficijent), novielement->eksponent);
			}
			else
			{
				printf(" - %dx^%d", abs(novielement->koeficijent), novielement->eksponent);
			}
		}
		else
		{
			if (novielement->eksponent < 0)
			{
				if (novielement->koeficijent == 1)
				{
					printf("  + x^%d", novielement->eksponent);
				}
				else
				{
					printf(" + %dx^%d", novielement->koeficijent, novielement->eksponent);
				}
			}
			else
			{
				if (novielement->koeficijent == 1)
				{
					printf(" + %dx^%d", novielement->koeficijent, novielement->eksponent);
				}
				else
				{
					printf(" + %dx^%d", novielement->koeficijent, novielement->eksponent);
				}
			}
		}

		novielement = novielement->next;
	}

	printf("\n");
	return 0;
}
