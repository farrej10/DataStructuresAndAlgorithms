#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

int collision = 0;
typedef struct Person Person;
struct Person {

	int personID;
	char depositionID[40];
	char surname[100];
	char forename[100];
	int age;
	char personType[40];
	char gender[40];
	char nationality[40];
	char religion[40];
	char occupation[40];
	Person* nextPerson;



};

struct People {

	char name[100];
	int hashValue;
	Person *firstPerson;

};
typedef struct People People;
//this is hash1
int hash_v2(char* s,int ARRAYSIZE)
{
	int hash = 0;
	while (*s)
	{
		hash = hash + *s;
		s++;
	}
	return hash%ARRAYSIZE;
}//101384178 collisions with engwales_surnames.csv , 26 names.csv,10 with rehashing
//this is hash2 from http://www.cse.yorku.ca/~oz/hash.html
int hash_v1(char* s,int ARRAYSIZE)
{
	unsigned long hash = 42;//meaning of life
	int c;

	while (c = *s++)
		hash = ((hash << 4) + hash) + c; //bitshifting

	return (hash % ARRAYSIZE);
}//1337 collisions with engwales_surnames.csv, 9 with names.csvm,10 with rehashing

//this is hash3
int hash_v3(char* s, int ARRAYSIZE)
{
	int hash = hash_v1(s,ARRAYSIZE);
	
	return ((11-hash%11));
}


People* createNewPeople(char* name)
{

	People *returnPerson = (People*)malloc(sizeof(struct People));
	strcpy(returnPerson->name, name);
	return returnPerson;
}

People* searchPeople(Person* person, People* hashTable[], int ARRAYSIZE)
{
	int i = hash_v1(person->surname,ARRAYSIZE);
	while (hashTable[i%ARRAYSIZE] != NULL)
	{
		//if name is there return that person, else keep looking
		if (strcmp(hashTable[i%ARRAYSIZE]->name, person->surname) == 0)
		{
			return hashTable[i%ARRAYSIZE];
		}
		else
		{
			i = (i*(hash_v3(person->surname, ARRAYSIZE))+1) % ARRAYSIZE;
			//i++;
			collision++;
		}
	}

	People* location = (People*)malloc(sizeof(struct People));
	hashTable[i%ARRAYSIZE] = location;
	location->hashValue = i%ARRAYSIZE;
	return location;
}

Person* searchPerson(char* name, People* hashTable[], int ARRAYSIZE)
{
	int i = hash_v1(name, ARRAYSIZE);
	while (hashTable[i%ARRAYSIZE] != NULL)
	{
		//if name is there return that person, else keep looking
		if (strcmp(hashTable[i%ARRAYSIZE]->name, name) == 0)
		{
			return hashTable[i%ARRAYSIZE]->firstPerson;
		}
		else
		{
			i = (i*(hash_v3(name, ARRAYSIZE)) + 1) % ARRAYSIZE;
			//i++;
			collision++;
		}
	}

	//return NULL if not there
	return NULL;
}

void insertPerson(Person* person, People* hashTable[], int ARRAYSIZE, int hashValue)
{
	hashTable[hashValue] = createNewPeople(person->surname);
	hashTable[hashValue]->hashValue = hashValue;
	hashTable[hashValue]->firstPerson = person;
	person->nextPerson = NULL;


}

void addOrIncrememnt(Person* person, People* hashTable[], int ARRAYSIZE)
{
	Person* nextperson = searchPerson(person->surname,hashTable,ARRAYSIZE);
	Person* prevperson = NULL;
	People* temp= searchPeople(person,hashTable,ARRAYSIZE);
	if(nextperson !=NULL)
	{
		while (nextperson != NULL)
		{	
			prevperson = nextperson;
			nextperson = nextperson->nextPerson;
		}
		prevperson->nextPerson = person;
		person->nextPerson = NULL;
	}
	else
		insertPerson(person, hashTable, ARRAYSIZE,temp->hashValue);


}

void printNumberOfOccurencees(People* hashTable[],int ARRAYSIZE)
{
	//People* temp;
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

		Person* tempperson = (Person*)malloc(sizeof(struct Person));

		strcpy(tempperson->surname, searchOrExit);
		tempperson = searchPerson(searchOrExit, hashTable, ARRAYSIZE);

		if (strcmp(searchOrExit, "quit") == 0)
			break;
		else if (tempperson == NULL)
			printf("Not in Table\n");
		else
		{
			Person* nextpersoninlist = tempperson;
			while (nextpersoninlist != NULL)
			{
				printf("%i\t", nextpersoninlist->personID);
				printf("%s\t", nextpersoninlist->depositionID);
				printf("%s\t", nextpersoninlist->surname);
				printf("%s\t", nextpersoninlist->forename);
				printf("%i\t", nextpersoninlist->age);
				printf("%s\t", nextpersoninlist->personType);
				//printf("%s\t", nextpersoninlist->gender);
				//printf("%s\t", nextpersoninlist->nationality);
				//printf("%s\t", nextpersoninlist->religion);
				//printf("%s\t", nextpersoninlist->occupation);
				printf("\n");
				nextpersoninlist = nextpersoninlist->nextPerson;

			}
			

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
	const int ARRAYSIZE = 76157;//16651 use this for engwales_surnames.csv 97 for names.csv ,

	People* hashTable[ARRAYSIZE];

	int i;
	for (i = 0;i<ARRAYSIZE;i++)
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
		char tempchars[50];
		Person* temp = (Person*)malloc(sizeof(struct Person));
		while (!feof(CSV))
		{
			temp= (Person*)malloc(sizeof(struct Person));
			exit = nextField(CSV, buffer, maxLength);
			strcpy(tempchars, buffer);
			temp->personID = atoi(tempchars);

			exit = nextField(CSV, buffer, maxLength);
			strcpy(temp->depositionID, buffer);

			exit = nextField(CSV, buffer, maxLength);
			strcpy(temp->surname, buffer);

			exit = nextField(CSV, buffer, maxLength);
			strcpy(temp->forename, buffer);

			exit = nextField(CSV, buffer, maxLength);
			strcpy(tempchars, buffer);
			temp->age = atoi(tempchars);

			exit = nextField(CSV, buffer, maxLength);
			strcpy(temp->personType, buffer);

			exit = nextField(CSV, buffer, maxLength);
			strcpy(temp->gender, buffer);

			exit = nextField(CSV, buffer, maxLength);
			strcpy(temp->nationality, buffer);

			exit = nextField(CSV, buffer, maxLength);
			strcpy(temp->religion, buffer);

			exit = nextField(CSV, buffer, maxLength);
			strcpy(temp->occupation, buffer);


			addOrIncrememnt(temp, hashTable, ARRAYSIZE);
			//counter++;
			//printf("%i", counter);
			exit = 0;
		}
		printf("Number of Collisions: %i\n\n", collision);
		tempchars[0] ='\0';

		printNumberOfOccurencees(hashTable, ARRAYSIZE);
		fclose(CSV);

	}



	return  0;

}
