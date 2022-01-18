#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 20
#define MAX_LINE 1024

typedef struct TreeOfCities* node;
typedef struct TreeOfCities {
	char name[MAX_NAME];
	int population;
	node left;
	node right;
};

typedef struct ListOfStates* state;
typedef struct ListOfStates {
	char name[MAX_NAME];
	state next;
	node city;
};

state AllocateMemoryForState();
int ReadMainFile(state);
int SortedInputOfStates(state, state);
int ReadFile(state, char*);
node inputNodeInTree(char*, int, node);
node inputNode(char*, int);
int PrintStates(state);
int PrintCities(node);
int Search(state, char*, int);
int PrintCitiesWithPopulationAboveNumber(node, int);

int main()
{
	state head = AllocateMemoryForState();
	char name[MAX_NAME] = { 0 };
	int number = 0;

	ReadMainFile(head);
	PrintStates(head->next);

	printf("Enter the name of the state you want to search:\n");
	scanf(" %s", name);

	printf("Enter the number of citizens:\n");
	scanf(" %d", &number);

	Search(head, name, number);

	return 0;
}

state AllocateMemoryForState()
{
	state newState = NULL;

	newState = (state)malloc(sizeof(struct ListOfStates));

	if (!newState)
	{
		perror("Cannot allocate memory!\n");
		return -1;
	}

	strcpy(newState->name, " ");
	newState->next = NULL;
	newState->city = NULL;

	return newState;
}

int ReadMainFile(state head)
{
	state newState = NULL;
	char buffer[MAX_LINE] = { 0 };
	char name[MAX_NAME] = { 0 };
	char fileName[MAX_NAME] = { 0 };
	int status = 0;

	FILE* file = fopen("drzave.txt", "r");

	if (!file)
	{
		perror("Cannot access the file!\n");
		return -2;
	}

	while (!feof(file))
	{
		newState = AllocateMemoryForState();
		fgets(buffer, MAX_LINE, file);
		status = sscanf(buffer, " %s %s", name, fileName);

		if (status == 2)
		{
			strcpy(newState->name, name);
			SortedInputOfStates(head, newState);
			ReadFile(newState, fileName);
		}
		else
		{
			perror("Error in the file!\n");
			return -3;
		}
	}

	return 0;
}

int SortedInputOfStates(state head, state newState)
{
	state temp = head;

	while (temp->next != NULL && strcmp(temp->next->name, newState->name) <= 0)
	{
		temp = temp->next;
	}


	if (strcmp(temp->name, newState->name) != 0)
	{
		newState->next = temp->next;
		temp->next = newState;
	}
	else
	{
		free(newState);
	}

	return 0;
}

int ReadFile(state newState, char* fileName)
{
	node root = NULL;
	char buffer[MAX_LINE] = { 0 };
	int status = 0;
	char name[MAX_NAME] = { 0 };
	int number = 0;

	FILE* file = fopen(fileName, "r");

	if (!file)
	{
		perror("Cannot access the file!\n");
		return -2;
	}

	while (!feof(file))
	{
		fgets(buffer, MAX_LINE, file);
		status = sscanf(buffer, " %s %d", name, &number);

		if (status == 2)
		{
			root = inputNodeInTree(name, number, root);
		}
		else
		{
			perror("Error in the file\n");
			return -3;
		}
	}

	newState->city = root;

	return 0;
}

node inputNodeInTree(char* name, int number, node root)
{
	node newNode = NULL;
	node current = root;

	if (current == NULL)
	{
		newNode = inputNode(name, number);
		return newNode;
	}
	else if (current->population > 0)
	{
		current->left = inputNodeInTree(name, number, current->left);
	}
	else if (current->population < 0)
	{
		current->right = inputNodeInTree(name, number, current->right);
	}
	else
	{
		if (strcmp(current->name, name) > 0)
		{
			current->left = inputNodeInTree(name, number, current->left);
		}
		else if (strcmp(current->name, name) < 0)
		{
			current->right = inputNodeInTree(name, number, current->right);
		}
	}

	return current;
}

node inputNode(char* name, int number)
{
	node newNode = NULL;

	newNode = (node)malloc(sizeof(struct TreeOfCities));

	if (!newNode)
	{
		perror("Cannot allocate memory!\n");
		return -1;
	}

	strcpy(newNode->name, name);
	newNode->population = number;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}


int PrintStates(state head)
{
	if (head == NULL)
	{
		printf("The list is empty!\n");
	}

	while (head->next != NULL)
	{
		printf("%s\n", head->name);
		PrintCities(head->city);
		head = head->next;
	}

	printf("%s\n", head->name);
	PrintCities(head->city);

	return 0;
}

int PrintCities(node root)
{
	if (root != NULL)
	{
		PrintCities(root->left);
		printf("	-%s %d\n", root->name, root->population);
		PrintCities(root->right);
	}

	return 0;
}

int Search(state head, char* name, int number)
{
	state temp = head;

	while (temp->next != NULL && strcmp(temp->next->name, name) < 0)
	{
		temp = temp->next;
	}

	if (strcmp(temp->next->name, name) == 0)
	{
		PrintCitiesWithPopulationAboveNumber(temp->next->city, number);
	}
	else
	{
		printf("State with that name does not exist in the file!\n");
	}

	return 0;
}

int PrintCitiesWithPopulationAboveNumber(node root, int number)
{
	if (root != NULL)
	{
		PrintCitiesWithPopulationAboveNumber(root->left, number);
		if(root->population > number)
				printf(" %s\n", root->name);
		PrintCitiesWithPopulationAboveNumber(root->right, number);
	}

	return 0;
}