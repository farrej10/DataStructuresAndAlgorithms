#include  <stdio.h>
#include <stdlib.h>

/*Pokemon struct,     #,Name,Type 1,Type 2,Total,HP,Attack,Defense,Sp. Atk,Sp. Def,Speed,Generation,Legendary,Pokedex Entry
struct Pokemon
{
	int pokemon_num;
	char name[40];
	char type1[20];
	char type2[20];
	int total;
	int hp;
	int attack;
	int defense;
	int sp_atk;
	int sp_def;
	int speed;
	int generation;
	char legendary[6];
	char pokedex_entry[200];

};*/

struct Node
{
	struct Pokemon Pokemon;
	struct Pokemon *nextPokemon
};

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
/*
int read_in_everything_and_store_pokemon_node(FILE *csv, char *buffer, int max_length)
{

	int exit = 0;
	int case_num = 0;
	int index = 0;
	while (!feof(csv))
	{
		Run the loop so that it prints until \n or the end of file
		while (exit == 0)
		{
			exit = next_field(csv, buffer, max_length);
			
			switch (case_num)
			{
				case 0:
					pokearry[index]->pokemon_num = atoi(buffer);
					break;
				case 2:

					break;
				case 3:

					break;
				case 4:

					break;
				case 5:

					break;
				case 6:

					break;
				case 7:

					break;
				case 8:

					break;
				case 9:

					break;
				case 10:

					break;
				case 11:

					break;
				case 12:

					break;
				case 13:

					break;
			}

			case_num++;

		}
		index++;
		exit = 0;
	}
	
	return 1;

}
*/






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

