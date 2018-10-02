#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

int collision = 0;

struct People {

	char name[100];
	int count;
	int hashValue;

};
typedef struct People People;
//this is hash1
int hash_v2(char* s)
{
	int hash = 0;
	while (*s)
	{
		hash = hash + *s;
		s++;
	}
	return hash;
}//101384178 collisions with engwales_surnames.csv
//this is hash2 from http://www.cse.yorku.ca/~oz/hash.html
int hash_v1(char* s)
{
	unsigned long hash = 42;//meaning of life
	int c;

	while (c = *s++)
		hash = ((hash << 5) + hash) + c; //bitshifting

	return (hash % 99927);
}//1339 collisions with engwales_surnames.csv

//this is hash3
int hash_v3(char* s)
{
	int hash = 0;
	while (*s)
	{
		hash = hash + *s;
		s++;
	}
	return hash;
}


People* createNewPerson(char* name)
{

	People *returnPerson = (People*)malloc(sizeof(struct People));
	returnPerson->count = 0;
	strcpy(returnPerson->name, name);
	return returnPerson;
}

People* searchPeople(char* name, People* hashTable[], int ARRAYSIZE)
{
	int i = hash_v1(name);

	while (hashTable[i] != NULL)
	{
		//if name is there return that person, else keep looking
		if (strcmp(hashTable[i]->name, name) == 0)
		{
			return hashTable[i];
		}
		else
		{
			i++;
			collision++;
		}
	}

	People* location = (People*)malloc(sizeof(struct People));;
	hashTable[i] = location;
	location->hashValue = i;
	return location;
}

void insertPerson(char* name, People* hashTable[], int ARRAYSIZE, int hashValue)
{
	hashTable[hashValue] = createNewPerson(name);
	hashTable[hashValue]->hashValue = hashValue;
	hashTable[hashValue]->count++;


}

void addOrIncrememnt(char* name, People* hashTable[], int ARRAYSIZE)
{
	People* temp;
	temp = searchPeople(name, hashTable, ARRAYSIZE);

	if (strcmp(hashTable[temp->hashValue]->name, name) == 0)
	{
		hashTable[temp->hashValue]->count++;
		//collision++;

	}

	else
	{
		insertPerson(name, hashTable, ARRAYSIZE, temp->hashValue);
	}
}

void printNumberOfOccurencees(People* hashTable[],int ARRAYSIZE)
{
	People* temp;
	char searchOrExit[50];
	fgets(searchOrExit, 50, stdin);

	while (strcmp(searchOrExit, "quit") != 0)
	{
		printf("Enter term to get frequency or type \"quit\" to escape\n");
		fgets(searchOrExit, 50, stdin);

		int t = 0;
		while (searchOrExit[t] != '\n')
		{
			t++;
		}
		searchOrExit[t] = '\0';
		temp = searchPeople(searchOrExit, hashTable, ARRAYSIZE);

		if (strcmp(searchOrExit, "quit") == 0)
			break;
		else if (strcmp(searchOrExit, temp->name) != 0)
			printf("Not in Table\n");
		else
		{
			printf("Name: %s\n", temp->name);
			printf("frequency: %i\n", temp->count);

		}


	}
}

int nextField(FILE *csv, char *buffer, int max_length)
{

	char current = fgetc(csv);
	int index = 0;

	if (current != EOF)
	{
		while (current != ',' && current != '\n' && current != EOF && current != '"')
		{
			buffer[index] = current;
			current = fgetc(csv);
			index++;
		}

		if (current == ',')
		{
			buffer[index] = '\0';
			return 0;
		}
		else if (current == '"')
		{
			while (current != '\n' && current != EOF)
			{
				buffer[index] = current;
				current = fgetc(csv);
				index++;
			}

			buffer[index] = '\0';
			return 1;


		}
		else
		{
			buffer[index] = '\0';
			return 1;
		}

	}
	else
	{
		buffer[index] = '\0';
		return 1;
	}

}

int readInEverythingAndPrint(FILE *csv, char *buffer, int max_length)
{

	int exit = 0;
	while (!feof(csv))
	{
		/*Run the loop so that it prints until \n or the end of file*/
		while (exit == 0)
		{
			exit = nextField(csv, buffer, max_length);
			printf("%s", buffer);
			printf("\n");
		}
		exit = 0;
		printf("\n");
	}

	return 1;

}

int  main(int argc, char *argv[])
{


	char FILENAME[30];
	FILE * CSV;
	const int maxLength = 300;
	char buffer[maxLength];
	const int ARRAYSIZE = 99929;

	People* hashTable[ARRAYSIZE];

	int i;
	for (i = 0;i<ARRAYSIZE - 1;i++)
	{
		hashTable[i] = NULL;
	}




	/*User enters the name of the file*/
	printf("FileName >> ");
	scanf("%s", FILENAME);
	printf("This is the file name: %s\n", FILENAME);


	/*Open the csv file*/
	CSV = fopen(FILENAME, "r");


	/*Check for errors opening the file and run the next_field function*/
	if (CSV == NULL) {
		perror("ERROR OPENING FILE(CHECK FILE NAME)");
	}
	else
	{
		/*Tell the user that the file opened correctly*/
		printf("File opened correctly\n");

		int counter = 0;
		int exit = 0;
		while (!feof(CSV))
		{
			while (exit == 0)
			{
				exit = nextField(CSV, buffer, maxLength);
			}
			addOrIncrememnt(buffer, hashTable, ARRAYSIZE);
			exit = 0;
		}
		printf("Number of Collisions: %i\n\n", collision);

		printNumberOfOccurencees(hashTable, ARRAYSIZE);

	}

	fclose(CSV);


	char var[10];
	scanf("%s", var);


	return  0;

}
