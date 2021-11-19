#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _StackElement* Position;

typedef struct _StackElement {
	double number;
	Position next;
}StackElement;

Position CreateStackElement(double number);
int InsertAfter(Position position, Position newElement);
int Push(Position head, double number);
int DeleteAfter(Position position);
int Pop(double* destination, Position head);
int PerformOperation(Position head, char operation);
int CalculatePostfixFile(double* destination, char* fileName);

int main()
{
	return 0;
}

Position CreateStackElement(double number)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(StackElement));

	if (!newElement)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}

int InsertAfter(Position position, Position newElement)
{
	newElement->next = position->next;
	position->next = newElement;

	return 0;
}

int Push(Position head, double number)
{
	Position newElement = NULL;

	newElement = CreateStackElement(number);

	if (!newElement)
	{
		return -1;
	}

	InsertAfter(head, newElement);

	return 0;
}

int DeleteAfter(Position position)
{
	Position temp = position->next;

	if (!temp)
	{
		return 0;
	}

	position->next = temp->next;
	free(temp);

	return 0;
}

int Pop(double* destination, Position head)
{
	Position temp = head->next;

	if (!temp)
	{
		perror("Postfix not valid! Please check your file!\n");
		return -1;
	}

	*destination = temp->number;

	DeleteAfter(head);

	return 0;
}

int PerformOperation(Position head, char operation)
{
	double operand2 = 0;
	double operand1 = 0;
	int status1 = 0;
	int status2 = 0;
	double result = 0;

	status2 = Pop(&operand2, head);

	if (status2 != 0)
	{
		return -1;
	}

	status1 = Pop(&operand1, head);

	if (status1 != 0)
	{
		return -2;
	}

	switch (operation)
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
		if (operand2 == 0)
		{
			perror("Cannot divide with zero!\n");
			return -3;
		}
		result = operand1 / operand2;
		break;
	default:
		perror("This operation is not supported yet!\n");
		return -4;
	}

	Push(head, result);

	return 0;
}

int CalculatePostfixFile(double* destination, char* fileName)
{
	FILE* file = NULL;
	int fileLenght = 0;
	char* buffer = NULL;
	char* currentbuffer = NULL;
	int numBytes = 0;
	char operation = 0;
	double number = 0;
	int status = 0;
	StackElement head = { .next = NULL, .number = 0 };

	file = fopen(fileName, "rb");
	if (!file)
	{
		perror("Can't open file!\n");
		return -1;
	}

	fseek(file, 0, SEEK_END);
	fileLenght = ftell(file);

	buffer = (char*)calloc(fileLenght + 1, sizeof(char));

	if (!buffer)
	{
		perror("Can't allocate memory!\n");
		return -2;
	}

	rewind(file);
	fread(buffer, sizeof(char), fileLenght, file);
	printf("%s", buffer);
	fclose(file);

	currentbuffer = buffer;

	while (strlen(currentbuffer) > 0)
	{
		status = sscanf(currentbuffer, "%lf %n", &number, &numBytes);

		if (status == 1)
		{
			status=Push(&head, number);
			if (status != 0)
			{
				free(buffer);
				DeleteAll(&head);
				return -3;
			}
			currentbuffer += numBytes;
		}
		else
		{
			sscanf(currentbuffer, "%c %n", &operation, &numBytes);
			status = PerformOperation(&head, operation);

			if (status != 0)
			{
				free(buffer);
				DeleteAll(&head);
				return -4;
			}

			currentbuffer += numBytes;
		}
	}
	free(buffer);

	status = Pop(destination, &head);
	if (status != 0)
	{
		DeleteAll(&head);
		return -5;
	}
	if (head.next)
	{
		printf("Postfix not valid!Please check your file!\n");
		DeleteAll(&head);
		return -6;
	}
	
	return 0;
}

int DeleteAll(Position head)
{
	while (head->next)
	{
		DeleteAfter(head);
	}

	return 0;
}

