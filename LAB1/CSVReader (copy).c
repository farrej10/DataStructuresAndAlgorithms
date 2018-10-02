#include  <stdio.h>


int next_field(FILE *csv, char *buffer, int max_length)
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








int  main(int argc, char *argv[]) {


	char FILENAME[20];
	FILE * CSV;
	const int max_length = 300;
	char buffer[max_length];


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

		int success = read_in_everything_and_print(CSV, buffer, max_length);
		if (success == 1)
		{
			printf("Success reading in everything\n");
		}
		else
			printf("Failure reading in everything\n");
		
	}


	return  0;

}

