#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 20
#define MAX_LINE 1024


typedef struct ListOfCities* city;
typedef struct ListOfCities {
	char name[MAX_NAME];
	int population;
	city next;
};

typedef struct TreeOfStates* node;
typedef struct TreeOfStates {
	char name[MAX_NAME];
	node left;
	node right;
	city firstCity;
};

node ReadMainFile(node);
node inputNodeInTree(node, char*, char*);
node inputNode(char*);
int ReadFile(node, char*);
city AllocateMemoryForCity();
int SortedInputOfCities(city, city);
int PrintStates(node);
int PrintCities(city);
node searchNode(node, char*);
int Search(node, int);

int main()
{
	node root = NULL;
	node state = NULL;
	char name[MAX_NAME] = { 0 };
	int number = 0;

	root = ReadMainFile(root);

	PrintStates(root);

	printf("Enter the name of the state you want to search:\n");
	scanf(" %s", name);

	printf("Enter the number of citizens:\n");
	scanf(" %d", &number);

	state = searchNode(root, name);

	Search(state, number);
	
	return 0;
}

node ReadMainFile(node root)
{
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
		fgets(buffer, MAX_LINE, file);
		status=sscanf(buffer, " %s %s", name, fileName);

		if (status == 2)
		{
			root = inputNodeInTree(root, name,fileName);
		}
		else
		{
			perror("Error in the file!\n");
			return -3;
		}
	}

	return root;
}

node inputNodeInTree(node root, char* name,char* fileName)
{
	node newNode = NULL;
	node current = root;

	if (current == NULL)
	{
		newNode = inputNode(name);
		ReadFile(newNode, fileName);
		return newNode;
	}
	else if (strcmp(current->name, name) > 0)
	{
		current->left = inputNodeInTree(current->left, name,fileName);
	}
	else if (strcmp(current->name, name) < 0)
	{
		current->right = inputNodeInTree(current->right, name,fileName);
	}

	return current;
}

node inputNode(char* name)
{
	node newNode = NULL;

	newNode = (node)malloc(sizeof(struct TreeOfStates));

	if (!newNode)
	{
		perror("Cannot allocate memory!\n");
		return -1;
	}

	strcpy(newNode->name, name);
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

int ReadFile(node newNode, char* fileName)
{
	city head = AllocateMemoryForCity();
	city newCity = NULL;
	char buffer[MAX_LINE] = { 0 };
	char name[MAX_LINE] = { 0 };
	int number = 0;
	int status = 0;

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
			newCity = AllocateMemoryForCity();
			strcpy(newCity->name, name);
			newCity->population = number;
			SortedInputOfCities(head, newCity);
			newNode->firstCity = head;
		}
		else
		{
			perror("Error in the file!\n");
			return -3;
		}
	}

	return 0;
}

city AllocateMemoryForCity()
{
	city newCity = NULL;

	newCity = (city)malloc(sizeof(struct ListOfCities));

	if (!newCity)
	{
		perror("Cannot allocate memory!\n");
		return -1;
	}

	strcpy(newCity->name, " ");
	newCity->population = 0;
	newCity->next = NULL;

	return newCity;
}

int SortedInputOfCities(city head, city newCity)
{
	city temp = head;

	while (temp->next != NULL && temp->next->population <= newCity->population)
	{
		temp = temp->next;
	}

	if (temp->population == newCity->population)
	{
		while (temp->next != NULL && strcmp(temp->next->name,newCity->name) > 0)
		{
			temp = temp->next;
		}
	}

	newCity->next = temp->next;
	temp->next = newCity;

	return 0;
}

int PrintStates(node root)
{
	node current = root;

	if (current != NULL)
	{
		PrintStates(current->left);
		printf(" %s\n", current->name);
		PrintCities(current->firstCity->next);
		PrintStates(current->right);
	}

	return 0;
}

int PrintCities(city head)
{
	if (head == NULL)
	{
		printf("The list is empty!\n");
	}

	while (head->next != NULL)
	{
		printf("	-%s %d\n", head->name, head->population);
		head = head->next;
	}

	printf("	-%s %d\n", head->name, head->population);

	return 0;
}

node searchNode(node root, char* name)
{
	node searchedNode = NULL;

	if (strcmp(root->name, name) == 0)
	{
		searchedNode = root;
		return searchedNode;
	}
	else
	{
		if (strcmp(root->name, name) > 0)
		{
			root->left = searchNode(root->left, name);
		}
		else if (strcmp(root->name, name) < 0)
		{
			root->right = searchNode(root->right, name);
		}
	}

	return searchedNode;
}

int Search(node state, int number)
{
	city temp = state->firstCity;

	while (temp->next != NULL && temp->population <= number)
	{
		temp = temp->next;
	}

	if (temp->next == NULL)
	{
		printf("No city in state has a population above entered number\n");
	}
	else
	{
		printf("Cities in state with population above entered number:\n");

		while (temp->next != NULL)
		{
			printf("-%s %d\n", temp->name, temp->population);
			temp = temp->next;
		}

		printf("-%s %d\n", temp->name, temp->population);
	}

	return 0;
}