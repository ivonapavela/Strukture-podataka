#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NAME 20

typedef struct tree* node;
typedef struct tree {
	int number;
	node left;
	node right;
};

typedef struct StackElement* element;
typedef struct StackElement {
	int number;
	element next;
};

element AllocateMemoryForStack();
node InsertArray(node, int[]);
node Insert(node, int);
node InsertRandomArray(node);
int Operation(element, node);
node CreateNewNode(int);
int Inorder(element, node);
int Push(element, int);
int PrintInFile(element);
int Pop(element);
int Replace(node);

int main()
{
	node root = NULL;
	element head = AllocateMemoryForStack();
	int array[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	char choice = '\0';

	printf("Enter 'A' for given array or enter 'B' for random array:\n");
	scanf(" %c", &choice);

	switch (choice)
	{
	case 'a':
	case 'A':
		root = InsertArray(root, array);
		Operation(head, root);
		break;
	case 'b':
	case 'B':
		root = InsertRandomArray(root);
		Operation(head, root);
		break;
	default:
		printf("You entered the wrong option!\n");
	}

	return 0;
}

element AllocateMemoryForStack()
{
	element newElement = NULL;

	newElement = (element)malloc(sizeof(struct StackElement));

	if (!newElement)
	{
		perror("Cannot allocate memory!\n");
		return -1;
	}

	newElement->number = 0;
	newElement->next = NULL;

	return newElement;
}

node InsertArray(node root, int array[])
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		root = Insert(root, array[i]);
	}

	return root;
}

node Insert(node root, int number)
{
	if (root == NULL)
	{
		root = CreateNewNode(number);
		return root;
	}
	else if (root->number <= number)
	{
		root->left = Insert(root->left, number);
	}
	else if (root->number > number)
	{
		root->right = Insert(root->right, number);
	}

	return root;
}

int Operation(element head, node root)
{
	Inorder(head, root);
	PrintInFile(head);

	printf("\n");

	Replace(root);
	Inorder(head, root);
	PrintInFile(head);

	return 0;
}
node CreateNewNode(int number)
{
	node newNode = NULL;

	newNode = (node)malloc(sizeof(struct tree));

	if (!newNode)
	{
		perror("Cannot allocate memory!\n");
		return -1;
	}

	newNode->number = number;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

node InsertRandomArray(node root)
{
	int i = 0;

	srand(time(NULL));

	for (i = 0; i < 10; i++)
	{
		root = Insert(root, 10 + rand() % 80);
	}

	return root;
}

int Inorder(element head, node root)
{
	node currentNode = root;

	if (currentNode != NULL)
	{
		Inorder(head, currentNode->left);
		printf("%d	", currentNode->number);
		Push(head, currentNode->number);
		Inorder(head, currentNode->right);
	}

	return 0;
}

int Push(element head, int number)
{
	element newElement = AllocateMemoryForStack();

	newElement->number = number;

	newElement->next = head->next;
	head->next = newElement;

	return 0;
}

int PrintInFile(element head)
{
	int number = 0;
	char fileName[MAX_NAME] = { 0 };

	printf("Enter the name of the file:");
	scanf(" %s", fileName);

	FILE* file = fopen(fileName, "a");

	if (!file)
	{
		perror("Cannot access the file!\n");
		return -2;
	}

	while (head->next != NULL)
	{

		fprintf(file, "%d	", number);
		number = Pop(head);
	}

	fprintf(file, "%d	", number);

	fprintf(file, "\n");

	return 0;
}

int Pop(element head)
{
	int number = 0;
	element deletedElement = NULL;

	deletedElement = head->next;
	number = deletedElement->number;
	head->next = deletedElement->next;
	free(deletedElement);

	return number;
}

int Replace(node root)
{
	int temp = 0;
	node currentNode = root;

	if (currentNode == NULL)
		return 0;
	else
	{
		temp = currentNode->number;
		currentNode->number = Replace(currentNode->left) + Replace(currentNode->right);
		return temp + currentNode->number;
	}
}