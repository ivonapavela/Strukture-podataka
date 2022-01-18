#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 20
#define MAX_LINE 1024

typedef struct {
	char name[MAX_NAME];
	char surname[MAX_NAME];
	double points;
}student;

int ReadFile(char*);
student* AllocateMemoryAndInputData(int, char*);
int Print(student*, int, double);

int main()
{
	char fileName[MAX_NAME] = { 0 };
	int numberOfStudents = 0;
	student* Students = NULL;
	double maximumPoints = 0;
	int i = 0;

	printf("Enter the name of the file:\n");
	scanf(" %s", fileName);

	numberOfStudents = ReadFile(fileName);

	Students = AllocateMemoryAndInputData(numberOfStudents, fileName);

	for (i = 0; i < numberOfStudents; i++)
	{
		if (maximumPoints < Students[i].points)
		{
			maximumPoints = Students[i].points;
		}
	}

	Print(Students, numberOfStudents, maximumPoints);

	return 0;
}

int ReadFile(char* fileName)
{
	int counter = 0;
	char buffer[MAX_LINE] = { 0 };
	FILE* file = fopen(fileName, "r");

	if (!file)
	{
		perror("Cannot access the file!\n");
		return -1;
	}

	while (!feof(file))
	{
		fgets(buffer, MAX_LINE, file);
		counter++;
	}

	rewind(file);
	fclose(file);

	return counter;
}

student* AllocateMemoryAndInputData(int numberOfStudents, char* fileName)
{
	int i = 0;
	student* Students = NULL;

	Students = (student*)malloc(numberOfStudents * sizeof(student));

	if (!Students)
	{
		perror("Cannot allocate memory!\n");
		return -2;
	}

	FILE* file = fopen(fileName, "r");

	if (!file)
	{
		perror("Cannot access the file!\n");
		return -1;
	}

	for (i = 0; i < numberOfStudents; i++)
	{
		fscanf(file, " %s %s %lf\n", (*(Students + i)).name, (*(Students + i)).surname, &Students[i].points);
	}

	fclose(file);

	return Students;
}

int Print(student* Students, int numberOfStudents, double maximumPoints)
{
	int i = 0;

	printf("List of students:\n");

	for (i = 0; i < numberOfStudents; i++)
	{
		printf("Name:%s\n", Students[i].name);
		printf("Surname:%s\n", Students[i].surname);
		printf("Points:%lf\n", Students[i].points);
		printf("Relative points:%lf\n\n", Students[i].points / maximumPoints * 100);
	}

	return 0;
}