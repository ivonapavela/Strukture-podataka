#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 20

typedef struct StackElement* element;
typedef struct StackElement {
	int number;
	element next;
};

element AllocateMemory();
int ReadFile(element);
int Pop(element);
int Push(element, int);
int PerformOperation(element, char);

int main()
{
	element head = AllocateMemory();
	int result = 0;

	ReadFile(head);

	result = Pop(head);

	if (head->next != NULL)
	{
		perror("Error in postfix!\n");
	}
	else
	{
		printf("%d", result);
	}

	return 0;
}

element AllocateMemory()
{
	element newElement = NULL;

	newElement = (element)malloc(sizeof(struct StackElement));

	if (!newElement)
	{
		perror("Error in creating a new element!\n");
		return -1;
	}

	newElement->number = 0;
	newElement->next = NULL;

	return newElement;
}

int ReadFile(element head)
{
	int fileLenght = 0;
	char* buffer = NULL;
	char* currentbuffer = NULL;
	int status = 0;
	int number = 0;
	int numbytes = 0;
	char operator='\0';
	char fileName[MAX_NAME] = { 0 };

	printf("Enter the name of the file:");
	scanf(" %s", fileName);

	FILE* file = fopen(fileName, "rb");

	if (!file)
	{
		perror("Cannot access the file!\n");
		return -2;
	}

	fseek(file, 0, SEEK_END);
	fileLenght = ftell(file);

	buffer = (char*)calloc(fileLenght + 1, sizeof(char));

	if (!buffer)
	{
		perror("Cannot allocate memory!\n");
		return -2;
	}

	rewind(file);
	fread(buffer, sizeof(char), fileLenght, file);

	fclose(file);

	currentbuffer = buffer;

	while (strlen(currentbuffer) > 0)
	{
		status = sscanf(currentbuffer, " %d %n", &number, &numbytes);

		if (status == 1)
		{
			status = Push(head, number);

			if (status != 0)
			{
				perror("Error in postfix!\n");
				free(buffer);
				DeleteAll(head);
				return -3;
			}

			currentbuffer += numbytes;
		}
		else
		{
			status = sscanf(currentbuffer, " %c %n", &operator,&numbytes);
			status = PerformOperation(head, operator);

			if (status != 0)
			{
				perror("Error in postfix!\n");
				free(buffer);
				DeleteAll(head);
				return -3;
			}

			currentbuffer += numbytes;
		}
	}

	free(buffer);

	return 0;
}

int Push(element head, int number)
{
	element newElement = AllocateMemory();

	newElement->number = number;

	newElement->next = head->next;
	head->next = newElement;

	return 0;
}

int Pop(element head)
{
	element deletedElement = NULL;
	int number = 0;

	deletedElement = head->next;
	head->next = deletedElement->next;
	number = deletedElement->number;
	free(deletedElement);

	return number;
}

int PerformOperation(element head, char operator)
{
	int operand1 = 0;
	int operand2 = 0;
	int result = 0;

	operand2 = Pop(head);
	operand1 = Pop(head);

	switch (operator)
	{
	case '+':
		result = operand1 + operand2;
		break;
	case '-':
		result = operand1 - operand2;
		break;
	case '*':
		result = operand1 * operand2;
		break;
	case '/':
		result = operand1 / operand2;
		break;
	default:
		printf("Not valid operator!\n");
	}

	Push(head, result);

	return 0;
}

int DeleteAll(element head)
{
	element deletedElement = NULL;

	while (head->next != NULL)
	{
		deletedElement->next = head->next;
		head->next = deletedElement;
		free(deletedElement);
	}

	return 0;
}