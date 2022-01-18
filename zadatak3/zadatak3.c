#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 20
#define MAX_LINE 1024

typedef struct _person* person;
typedef struct _person {
	char name[MAX_NAME];
	char surname[MAX_NAME];
	int yearOfBirth;
	person next;
};

person AllocateMemory();
int option();
int input(person);
int AddElementAtTheBegginingOfTheList(person);
int PrintList(person);
int print(person);
int AddElementAtTheEndOfTheList(person);
person FindElementBySurname(person, char*);
int PrintOfSearchedElement(person);
int DeleteElementFromTheList(person, person);
int AddElementAfterAnotherElementInTheList(person, person);
int AddElementBeforeAnotherElementInTheList(person, person);
int SortedInput(person);
int InputTheListInFile(person);
int ReadTheListFromTheFile(person);

int main()
{
	int numberOfOption = 0;
	char surname[MAX_NAME] = { 0 };
	person head = AllocateMemory();
	person temp = NULL;

	while (numberOfOption != 11)
	{
		option();
		scanf("%d", &numberOfOption);

		switch (numberOfOption)
		{
		case 1:
			AddElementAtTheBegginingOfTheList(head);
			break;
		case 2:
			PrintList(head->next);
			break;
		case 3:
			AddElementAtTheEndOfTheList(head);
			break;
		case 4:
			printf("Enter the surname of the person you want to find:\n");
			scanf(" %s", surname);
			temp = FindElementBySurname(head, surname);
			PrintOfSearchedElement(temp);
			break;
		case 5:
			printf("Enter the surname of the person you want to delete:\n");
			scanf(" %s", surname);
			temp = FindElementBySurname(head, surname);
			DeleteElementFromTheList(head, temp);
			break;
		case 6:
			printf("Enter the surname of the person after whom you want to add a new person to the list:\n");
			scanf(" %s", surname);
			temp = FindElementBySurname(head, surname);
			AddElementAfterAnotherElementInTheList(head, temp);
			break;
		case 7:
			printf("Enter the surname of the person before whom you want to add a new person to the list:\n");
			scanf(" %s", surname);
			temp = FindElementBySurname(head, surname);
			AddElementBeforeAnotherElementInTheList(head, temp);
			break;
		case 8:
			SortedInput(head);
			break;
		case 9:
			InputTheListInFile(head->next);
			break;
		case 10:
			ReadTheListFromFile(head);
			break;
		case 11:
			printf("You exited the file!\n");
			break;
		default:
			printf("You entered the wrong option!\n");
		}
	}
	return 0;
}

person AllocateMemory()
{
	person newElement = NULL;

	newElement = (person)malloc(sizeof(struct _person));

	if (!newElement)
	{
		printf("Cannot allocate memory!\n");
		return -1;
	}

	strcpy(newElement->name, " ");
	strcpy(newElement->surname, " ");
	newElement->yearOfBirth = 0;
	newElement->next = NULL;

	return newElement;
}

int option()
{
	printf("1.Add element at the beggining of the list\n");
	printf("2.Print the list\n");
	printf("3.Add element at the end of the list\n");
	printf("4.Find element by the surname\n");
	printf("5.Delete the element from the list\n");
	printf("6.Add element after the chosen element in the list\n");
	printf("7.Add element before the chosen element in the list\n");
	printf("8.Add the element in sorted way\n");
	printf("9.Input the list in a file\n");
	printf("10.Read the list from the file\n");
	printf("11.Exit\n");
	printf("Choose one of the options:\n");

	return 0;
}

int input(person newElement)
{
	char buffer[MAX_NAME] = { 0 };

	printf("Enter the name of the person:\n");
	scanf(" %s", buffer);
	strcpy(newElement->name, buffer);
	printf("Enter the surname of the person:\n");
	scanf(" %s", buffer);
	strcpy(newElement->surname, buffer);
	printf("Enter the year of the birth of the person:\n");
	scanf(" %d", &newElement->yearOfBirth);

	newElement->next = NULL;

	return 0;
}

int AddElementAtTheBegginingOfTheList(person head)
{
	person newElement = AllocateMemory();

	input(newElement);

	newElement->next = head->next;
	head->next = newElement;

	printf("You successfully enter the person at the beggining of the list!\n");

	return 0;
}

int PrintList(person head)
{
	if (head == NULL)
		printf("The list is empty!\n");

	while (head->next != NULL)
	{
		print(head);
		head = head->next;
	}

	print(head);
	return 0;
}

int print(person head)
{
	printf("Name:%s\n", head->name);
	printf("Surname:%s\n", head->surname);
	printf("Year of birth:%d\n", head->yearOfBirth);
	printf("------------------------------------------\n");

	return 0;
}

int AddElementAtTheEndOfTheList(person head)
{
	person newElement = AllocateMemory();

	while (head->next != NULL)
	{
		head = head->next;
	}

	input(newElement);

	newElement->next = head->next;
	head->next = newElement;

	printf("You successfully enter the person at the end of the list!\n");

	return 0;
}

person FindElementBySurname(person head, char* surname)
{
	person temp = head;

	while (temp != NULL)
	{
		if (strcmp(temp->surname, surname) == 0)
			return temp;
		temp = temp->next;
	}
	return temp;
}

int PrintOfSearchedElement(person temp)
{
	if (temp == NULL)
	{
		printf("The person you searched for by surname does not exist in the list!\n");
		return -2;
	}
	else
	{
		printf("The person you searched for by surname:\n");
		printf("Name:%s\n", temp->name);
		printf("Surname:%s\n", temp->surname);
		printf("Year of birth:%d\n", temp->yearOfBirth);
	}

	return 0;
}

int DeleteElementFromTheList(person head, person deletedPerson)
{
	person temp = head;
	while (temp->next != deletedPerson)
	{
		temp = temp->next;
	}

	temp->next = deletedPerson->next;
	free(deletedPerson);

	return 0;
}

int AddElementAfterAnotherElementInTheList(person head, person previous)
{
	person newElement = AllocateMemory();
	person temp = head;

	while (temp != previous)
	{
		temp = temp->next;
	}

	input(newElement);

	newElement->next = temp->next;
	temp->next = newElement;

	printf("You successfully enter the person after the chosen element in the list!\n");
	return 0;
}

int AddElementBeforeAnotherElementInTheList(person head, person nextperson)
{
	person newElement = AllocateMemory();
	person temp = head;

	while (temp->next != nextperson)
	{
		temp = temp->next;
	}

	input(newElement);

	newElement->next = temp->next;
	temp->next = newElement;

	printf("You successfully enter the person before the chosen element in the list!\n");

	return 0;
}

int SortedInput(person head)
{
	person temp = head;
	person newElement = AllocateMemory();

	input(newElement);

	for (temp; temp->next != NULL; temp = temp->next)
	{
		if (strcmp(temp->next->surname, newElement->surname) > 0)
			break;
		if (strcmp(temp->next->surname, newElement->surname) == 0)
		{
			if (strcmp(temp->next->name, newElement->name) > 0)
				break;
			if (strcmp(temp->next->name, newElement->name) == 0)
			{
				if (temp->next->yearOfBirth > newElement->yearOfBirth)
					break;
			}
		}
	}

	newElement->next = temp->next;
	temp->next = newElement;

	return 0;
}

int InputTheListInFile(person head)
{
	person temp = head;
	char fileName[MAX_NAME] = { 0 };

	printf("Enter the name of the file:");
	scanf(" %s", fileName);

	FILE* file = fopen(fileName, "w");

	if (!file)
	{
		printf("Cannot open the file!\n");
		return -3;
	}

	while (temp->next != NULL)
	{
		fprintf(file, "Name:%s\n", temp->name);
		fprintf(file, "Surname:%s\n", temp->surname);
		fprintf(file, "Year of birth:%d\n", temp->yearOfBirth);
		fprintf(file, "------------------------------------------\n");

		temp = temp->next;
	}

	fprintf(file, "Name:%s\n", temp->name);
	fprintf(file, "Surname:%s\n", temp->surname);
	fprintf(file, "Year of birth:%d\n", temp->yearOfBirth);
	fprintf(file, "------------------------------------------\n");

	fclose(file);

	return 0;
}

int ReadTheListFromFile(person head)
{
	person newElement = NULL;
	person temp = head;
	char fileName[MAX_NAME] = { 0 };

	printf("Enter the name of the file:");
	scanf(" %s", fileName);

	FILE* file = fopen(fileName, "r");

	if (!file)
	{
		printf("Cannot open the file!\n");
		return -3;
	}

	while (!feof(file))
	{
		newElement = AllocateMemory();
		fscanf(file, " %s %s %d", newElement->name, newElement->surname, &newElement->yearOfBirth);
		newElement->next = temp->next;
		temp->next = newElement;
		temp = temp->next;
	}
	fclose(file);

	return 0;
}