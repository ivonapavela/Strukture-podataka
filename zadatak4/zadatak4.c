#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_NAME 20

typedef struct polynomialElement* element;
typedef struct polynomialElement {
	int coefficient;
	int exponent;
	element next;
};

element AllocateMemory();
int ReadFile(element, element);
int InputElementsIntoTheList(element, char*);
element input(int, int);
int SortedInput(element, element);
element SummationOfPolynomials(element, element);
element AdditionOfPolynomials(element, element);
int Print(element);

int main()
{
	element head1 = AllocateMemory();
	element head2 = AllocateMemory();
	element resultOfSummation = AllocateMemory();
	element resultOfAddition = AllocateMemory();

	ReadFile(head1, head2);

	printf("First polynomial:\n");
	Print(head1->next);
	printf("Second polynomial:\n");
	Print(head2->next);

	resultOfSummation = SummationOfPolynomials(head1, head2);

	printf("Result of summation:\n");
	Print(resultOfSummation->next);

	resultOfAddition = AdditionOfPolynomials(head1, head2);

	printf("Result of addition:\n");
	Print(resultOfAddition->next->next);

	return 0;
}

element AllocateMemory()
{
	element newElement = NULL;

	newElement = (element)malloc(sizeof(struct polynomialElement));

	if (!newElement)
	{
		printf("Cannot allocate memory!\n");
		return -1;
	}

	newElement->coefficient = 0;
	newElement->exponent = 0;
	newElement->next = NULL;

	return newElement;
}

int ReadFile(element head1, element head2)
{
	char buffer[MAX_LINE] = { 0 };
	char fileName[MAX_NAME] = { 0 };

	printf("Enter the name of the file:");
	scanf(" %s", fileName);

	FILE* file = fopen(fileName, "r");

	if (!file)
	{
		printf("Cannot access the file!\n");
		return -2;
	}

	fgets(buffer, MAX_LINE, file);
	InputElementsIntoTheList(head1, buffer);

	fgets(buffer, MAX_LINE, file);
	InputElementsIntoTheList(head2, buffer);

	fclose(file);

	return 0;
}

int InputElementsIntoTheList(element head, char* buffer)
{
	char* temp = buffer;
	int coefficient = 0;
	int exponent = 0;
	int numbytes = 0;
	int status = 0;
	element newElement = NULL;

	while (strlen(temp) > 2)
	{
		status = sscanf(temp, " %d %d %n", &coefficient, &exponent, &numbytes);

		if (status != 2)
		{
			printf("Error in the file!\n");
			return -3;
		}

		newElement = input(coefficient, exponent);

		if (!newElement)
		{
			printf("Error in creating new element");
			return -4;
		}

		SortedInput(head, newElement);

		temp += numbytes;
	}

	return 0;
}

element input(int coefficient, int exponent)
{
	element newElement = AllocateMemory();

	newElement->coefficient = coefficient;
	newElement->exponent = exponent;

	return newElement;
}

int SortedInput(element head, element newElement)
{
	element temp = head;
	int result = 0;
	element deletedElement = NULL;

	while (temp->next != NULL && temp->next->exponent < newElement->exponent)
	{
		temp = temp->next;
	}

	if (temp->next == NULL || temp->next->exponent != newElement->exponent)
	{
		newElement->next = temp->next;
		temp->next = newElement;
	}
	else
	{
		result = temp->next->coefficient + newElement->coefficient;

		if (result == 0)
		{
			deletedElement = temp->next;
			temp->next = deletedElement->next;
			free(deletedElement);
		}
		else
		{
			temp->next->coefficient = result;
		}

		free(newElement);
	}

	return 0;
}

element SummationOfPolynomials(element head1, element head2)
{
	element temp1 = head1;
	element temp2 = head2;
	element result = AllocateMemory();
	element newElement = NULL;

	while (temp1 != NULL)
	{
		newElement = input(temp1->coefficient, temp1->exponent);

		if (!newElement)
		{
			printf("Error in creating newElement");
			return -4;
		}

		SortedInput(result, newElement);

		temp1 = temp1->next;
	}

	while (temp2 != NULL)
	{
		newElement = input(temp2->coefficient, temp2->exponent);

		if (!newElement)
		{
			printf("Error in creating new element!\n");
			return -4;
		}

		SortedInput(result, newElement);

		temp2 = temp2->next;
	}

	return result;
}

element AdditionOfPolynomials(element head1, element head2)
{
	element temp1 = head1;
	element temp2 = head2;
	element result = AllocateMemory();
	element newElement = NULL;

	while (temp1 != NULL)
	{
		while (temp2 != NULL)
		{
			newElement = input(temp1->coefficient * temp2->coefficient, temp1->exponent + temp2->exponent);

			if (!newElement)
			{
				printf("Error in creating new element!\n");
				return -4;
			}

			SortedInput(result, newElement);

			temp2 = temp2->next;
		}

		temp2 = head2;
		temp1 = temp1->next;
	}

	return result;
}

int Print(element head)
{
	if (head->coefficient < 0)
	{
		if (head->exponent == 1)
		{
			printf("- %dx ", abs(head->coefficient));
		}
		else
		{
			printf("- %dx^%d ", abs(head->coefficient), head->exponent);
		}
	}
	else if (head->coefficient == 1)
	{
		if (head->exponent == 1)
		{
			printf("x ");
		}
		else
		{
			printf("x^%d ", head->exponent);
		}
	}
	else
	{
		if (head->exponent == 1)
		{
			printf("%dx ", head->coefficient);
		}
		else
		{
			printf("%dx^%d ", head->coefficient, head->exponent);
		}
	}

	head = head->next;

	while (head)
	{
		if (head->coefficient < 0)
		{
			if (head->exponent == 1)
			{
				printf("- %dx ", abs(head->coefficient));
			}
			else
			{
				printf("- %dx^%d ", abs(head->coefficient), head->exponent);
			}
		}
		else if (head->coefficient == 1)
		{
			if (head->exponent == 1)
			{
				printf("+ x ");
			}
			else
			{
				printf(" + x^%d ", head->exponent);
			}
		}
		else
		{
			if (head->exponent == 1)
			{
				printf("+ %dx ", head->coefficient);
			}
			else
			{
				printf("+ %dx^%d ", head->coefficient, head->exponent);
			}
		}

		head = head->next;
	}

	printf("\n");

	return 0;
}