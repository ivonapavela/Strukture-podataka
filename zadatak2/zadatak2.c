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


int main()
{
	int numberOfOption = 0;
	char surname[MAX_NAME] = { 0 };
	person head = AllocateMemory();
	person temp = NULL;

	while (numberOfOption != 6)
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
	printf("6.Exit\n");
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
