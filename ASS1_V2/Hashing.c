#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

struct People{

	char name[100];
	int count;
	int hashValue;

};
typedef struct People People;


int hash_v1(char* s)
{
	int hash = 0;
	while(*s)
	{
		hash = hash + *s;
		s++;
	}
	return hash;
}

People* createNewPerson(char* name)
{

	People *returnPerson = malloc(1);
	returnPerson->count = 0;
	strcpy(returnPerson->name,name);
	return returnPerson;
}

People* searchPeople(char* name,People* hashTable[],int ARRAYSIZE)
{
	int i = hash_v1(name);

	while(hashTable[i] != NULL)
	{
		//if name is there return that person, else keep looking
		if(strcmp(hashTable[i]->name, name) == 0)
			return hashTable[i];
		else
			i++;
	}

	People* location;
	hashTable[i] = location;
	location->hashValue = i;
	return location;
}

void insertPerson(char* name,People* hashTable[],int ARRAYSIZE,int hashValue)
{
	hashTable[hashValue] = createNewPerson(name);
	hashTable[hashValue]->hashValue = hashValue;
}

void addOrIncrememnt(char* name,People* hashTable[],int ARRAYSIZE)
{
	People* temp;
	temp = searchPeople(name,hashTable,ARRAYSIZE);

	if(strcmp(hashTable[temp->hashValue]->name, name) == 0)
	{
			hashTable[temp->hashValue]->count++;
	}
		
	else
	{
		insertPerson(name,hashTable,ARRAYSIZE, temp->hashValue);
	}
		
}

void printNumberOfOccurencees(char* name)
{

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


	char FILENAME[20];
	FILE * CSV;
	const int maxLength = 300;
	char buffer[maxLength];
	const int ARRAYSIZE = 99929;

	People* hashTable[ARRAYSIZE];
	
	int i;
	for(i=0;i<ARRAYSIZE-1;i++)
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

		/* Print shit
		int success = readInEverythingAndPrint(CSV, buffer, maxLength);
		if (success == 1)
		{
			printf("Success reading in everything\n");
		}
		else
			printf("Failure reading in everything\n");
		*/

		int counter=0;
		int exit = 0;
		while (!feof(CSV))
		{
			while (exit == 0)
			{
				exit = nextField(CSV, buffer, maxLength);
			}
			addOrIncrememnt(buffer,hashTable,ARRAYSIZE);
			printf("%i\n",counter);
			counter++;
			exit = 0;
		}
		
	}
		
	


	return  0;

}

