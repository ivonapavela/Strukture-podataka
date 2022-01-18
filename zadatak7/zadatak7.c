#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 20

typedef struct Directory* directory;
typedef struct Directory {
	char name[MAX_NAME];
	directory next;
	directory subDirectory;
};

typedef struct StackElement* position;
typedef struct StackElement {
	position next;
	directory parent;
};

directory AllocateMemoryForDirectory();
position AllocateMemoryForStackElement();
int DOSCommands();
int MakeDirectory(directory, position);
int SortedInput(directory, position, directory);
position ChangeDirectory(directory, position, position);
int Push(position, position);
position ExitDirectory(directory, position, position);
position Pop(directory,position);
int PrintSubdirectories(position);


int main()
{
	directory C = AllocateMemoryForDirectory();
	position currentDirectory = AllocateMemoryForStackElement();
	position StackHead = AllocateMemoryForStackElement();
	int numberOfOption = 0;

	strcpy(C->name, "C:");

	currentDirectory->parent = C;

	Push(StackHead, currentDirectory);

	while (numberOfOption != 5)
	{
		DOSCommands();
		printf("Enter your choice:\n");
		scanf(" %d", &numberOfOption);

		switch (numberOfOption)
		{
		case 1:
			MakeDirectory(C, currentDirectory);
			break;
		case 2:
			currentDirectory = ChangeDirectory(C, currentDirectory, StackHead);
			break;
		case 3:
			currentDirectory = ExitDirectory(C, currentDirectory, StackHead);
			break;
		case 4:
			PrintSubdirectories(currentDirectory);
			break;
		case 5:
			printf("Exit!\n");
			break;
		default:
			printf("You entered the wrong option!\n");
		}
	}

	return 0;
}

directory AllocateMemoryForDirectory()
{
	directory newDirectory = NULL;

	newDirectory = (directory)malloc(sizeof(struct Directory));

	if (!newDirectory)
	{
		perror("Cannot allocate memory!\n");
		return -1;
	}

	strcpy(newDirectory->name, " ");
	newDirectory->next = NULL;
	newDirectory->subDirectory = NULL;

	return newDirectory;
}

position AllocateMemoryForStackElement()
{
	position newStackElement = NULL;

	newStackElement = (position)malloc(sizeof(struct StackElement));

	if (!newStackElement)
	{
		perror("Cannot allocate memory!\n");
		return -1;
	}

	newStackElement->next = NULL;
	newStackElement->parent = NULL;

	return newStackElement;
}

int DOSCommands()
{
	printf("1.Make new directory\n");
	printf("2.Change directory\n");
	printf("3.Exit directory\n");
	printf("4.List subdirectories\n");
	printf("5.Exit the program\n");

	return 0;
}

int MakeDirectory(directory C, position current)
{
	directory newDirectory = AllocateMemoryForDirectory();
	char name[MAX_NAME] = { 0 };

	printf("Enter the name of the new directory:");
	scanf(" %s", name);

	strcpy(newDirectory->name, name);

	SortedInput(C, current, newDirectory);

	return 0;
}

int SortedInput(directory C, position current, directory newDirectory)
{
	directory temp = current->parent;

	if (temp->subDirectory == NULL)
	{
		newDirectory->subDirectory = temp->subDirectory;
		temp->subDirectory = newDirectory;
	}
	else
	{
		temp = temp->subDirectory;
		while (temp->next != NULL && strcmp(newDirectory->name, temp->next->name) > 0)
		{
			temp = temp->next;
		}

		if (temp->next == NULL || strcmp(temp->next->name, newDirectory->name) != 0)
		{
			newDirectory->next = temp->next;
			temp->next = newDirectory;
		}
	}

	return 0;
}

position ChangeDirectory(directory C, position current, position StackHead)
{
	char name[MAX_NAME] = { 0 };
	directory temp = current->parent->subDirectory;

	printf("Enter the name of the directory:\n");
	scanf(" %s", name);

	while (temp->next != NULL && strcmp(temp->name, name) != 0)
	{
		temp = temp->next;
	}

	if (strcmp(temp->name, name) == 0)
	{
		current->parent = temp;
		printf("Current directory is %s\n", current->parent->name);
		Push(StackHead, current);

	}
	else
	{
		printf("Directory with that name does not exist!\n");
		return 1;
	}

	return current;
}

int Push(position StackHead, position StackElement)
{
	position newStackElement = AllocateMemoryForStackElement();

	newStackElement->parent = StackElement->parent;

	newStackElement->next = StackHead->next;
	StackHead->next = newStackElement;

	return 0;
}

position ExitDirectory(directory C, position current, position StackHead)
{
	current = Pop(C,StackHead);

	printf("Current directory is:%s\n", current->parent->name);

	return current;
}

position Pop(directory C,position StackHead)
{
	position deletedElement = NULL;
	position newCurrent = NULL;

	if (StackHead->next->parent == C)
	{
		printf("Cannot exit the root of directories!\n");
		return 2;
	}
	else
	{
		deletedElement = StackHead->next;
		newCurrent = deletedElement->next;
		StackHead->next = deletedElement->next;
		free(deletedElement);
	}

	return newCurrent;
}

int PrintSubdirectories(position current)
{
	directory temp = current->parent->subDirectory;

	while (temp->next != NULL)
	{
		printf("-%s\n", temp->name);

		temp = temp->next;
	}

	printf("-%s\n", temp->name);

	return 0;
}