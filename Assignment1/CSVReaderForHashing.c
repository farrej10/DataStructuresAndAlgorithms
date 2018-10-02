#include  <stdio.h>
#include <stdlib.h>
/*global max name size*/
#define MAX_STRING_SIZE 30
typedef struct Name{

	char name[MAX_STRING_SIZE];
	int numberOf;

}Name;

int hash1(char* s)
{
    int hash = 0;
    while (*s)
    {
        hash = hash + *s;
        s++;
    }
    return hash;

}


int next_field(FILE *csv, char *buffer, int max_length)
{

	char current = fgetc(csv);
	int index = 0;
	int is_quote = 0;
	if (current == '"')
		is_quote = 1;

	if (current != EOF)
	{
		while((current != '\n' && current != EOF) && (current != ',' || (current == ',' && is_quote == 1)))
		{
			buffer[index] = current;
			current = fgetc(csv);
			index++;
			if(current == '"')
			{
				switch(is_quote)
				{
					case 0:
						is_quote = 1;
						break;
					case 1:
						is_quote = 0;
						break;
				}
			}

		}

		if (current == ',')
		{
			buffer[index] = '\0';
			return 0;
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

int read_in_everything_and_print(FILE *csv, char *buffer, int max_length)
{

	int exit = 0;
	while (!feof(csv))
	{
		/*Run the loop so that it prints until \n or the end of file*/
		while (exit == 0)
		{
			exit = next_field(csv, buffer, max_length);
			printf("%s", buffer);
			printf("\n");
		}
		exit = 0;
		printf("\n\n");
	}
	
	return 1;

}

int read_in_and_insert(FILE *csv, char *buffer, int max_length,Name* nameList)
{

	int exit = 0;
	while (!feof(csv))
	{
	/*Run the loop so that it prints until \n or the end of file*/
		while (exit == 0)
		{
				exit = next_field(csv, buffer, max_length);
				int index = hash1(buffer);

				if(Name[index]->numberOf == 0)
				{
					Name[index]->name = buffer;
				}
					
				else
				{
					Name[index]->numberOf++;	
				}
					
		}
		
		exit = 0;
	}
		
	return 1;


	return 0;
}




int  main(int argc, char *argv[]) {


	char FILENAME[20];
	FILE * CSV;
	const int max_length = 300;
	char buffer[max_length];
	/*User enters the name of the file*/
	printf("FileName >> ");
	scanf("%s", FILENAME);
	printf("This is the file name: %s\n", FILENAME);
	Name nameList[100];


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
		/*Do something*/


		
	}


	return  0;

}

