#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


int swaps;
int comps;
int testcounter;



typedef struct Game Game;
struct Game {

	char title[100];
	char platform[100];
	int score;
	int year;

};

//const int NUMOFGAMES = 500;//18626
//Game gamesArray[NUMOFGAMES];

void nextField(char *buffer, FILE *csv, int max_length) {

	int quoteOff = 0;
	int quoteOn = 1;
	int isQuote = 0;
	int i = 0;
	for (i=0;i<max_length;i++)
	{
		buffer[i] = '\0';
	}
	i = 0;
	for (;;)
	{
		buffer[i] = fgetc(csv);// get next character from file
		if (buffer[i] == '\"')
		{
			isQuote = (quoteOff + quoteOn) - isQuote;
		}
		if ((buffer[i] == ',') && (isQuote == 0))
		{ break; } // only load letters and numbers
		if (buffer[i] == '\n') { break; }
		if (feof(csv)) { break; }          // file ended?
		if (i < (max_length - 1)) { ++i; }// truncate strings that are too long
		if (buffer[i] == '\"')
		{
			isQuote = (quoteOff + quoteOn) - isQuote;
		}
	}
	buffer[i] = '\0'; // NULL terminate the string
}

int read_in_everything_and_print(FILE *csv, char *buffer, int max_length)
{

	while (!feof(csv))
	{
		nextField(buffer, csv, max_length);
		printf("%s\n", buffer);
	}

	return 1;

}

void readInGames(FILE *csv, char *buffer, int max_length, Game *gamesArray, int NUMOFGAMES)
{



	int i;
	for (i = 0;i<NUMOFGAMES;i++)
	{
		nextField(buffer, csv, max_length);
		strcpy(gamesArray[i].title, buffer);

		nextField(buffer, csv, max_length);
		strcpy(gamesArray[i].platform, buffer);

		nextField(buffer, csv, max_length);
		gamesArray[i].score = atoi(buffer);

		nextField(buffer, csv, max_length);
		gamesArray[i].year = atoi(buffer);
	}


}

void printGamesArray(Game *gamesArray, int NUMOFGAMES)
{
	int i = 0;
	for (i = 0;i<NUMOFGAMES;i++)
	{
		printf("Title: %s\n", gamesArray[i].title);
		printf("Platform: %s\n", gamesArray[i].platform);
		printf("Score: %i\n", gamesArray[i].score);
		printf("Year: %i\n\n", gamesArray[i].year);

	}
}

void printGamesArrayBetween(Game *gamesArray, int NUMOFGAMES,int a, int b)
{
	int i;
	for (i = a;i<b;i++)
	{
		printf("Title: %s\n", gamesArray[i].title);
		printf("Platform: %s\n", gamesArray[i].platform);
		printf("Score: %i\n", gamesArray[i].score);
		printf("Year: %i\n\n", gamesArray[i].year);

	}
}

//Fill with Unique Random Numbers
void uniquerandomFill(int *arrayOfInts, int ARRAYSIZE)
{
	int i, j, temp;
	int fin = 0;
	for (i = 0;i<ARRAYSIZE;i++)
	{
		temp = rand();
		while (fin == 0)
		{
			for (j = 0;j<i;j++)
			{
				if (temp == arrayOfInts[j])
					break;
			}
			if (j == i)
				break;
			temp = rand();
		}
		arrayOfInts[i] = temp;
	}

}
//Fill with Random Numbers
void RandomFill(int *arrayOfInts, int ARRAYSIZE)
{
	int i;
	for (i = 0;i<ARRAYSIZE;i++)
	{
		arrayOfInts[i] = rand() % ARRAYSIZE;
	}
}

void ascendingFill(int *arrayOfInts, int ARRAYSIZE)
{
	int i;
	for (i = 0;i<ARRAYSIZE;i++)
	{
		arrayOfInts[i] = i;
	}
}

void descendingFill(int *arrayOfInts, int ARRAYSIZE)
{
	int i;
	for (i = 0;i<ARRAYSIZE;i++)
	{
		arrayOfInts[i] = ARRAYSIZE - i;
	}
}

void uniformFill(int *arrayOfInts, int ARRAYSIZE)
{
	int i;
	for (i = 0;i<ARRAYSIZE;i++)
	{
		arrayOfInts[i] = 3;
	}
}

//Print All Values in an array
void printIntArray(int *arrayOfInts, int ARRAYSIZE)
{
	int i;
	for (i = 0;i<ARRAYSIZE;i++)
	{
		printf("%i\n", arrayOfInts[i]);
	}
}

//swap variables
void swap(int *arrayOfInts, int a, int b)
{
	swaps++;
	int temp = arrayOfInts[a];
	arrayOfInts[a] = arrayOfInts[b];
	arrayOfInts[b] = temp;
}

void swapGames(Game *arrayOfGames, int a, int b)
{
	swaps++;
	
	Game temp;

	
	temp = arrayOfGames[a];
	arrayOfGames[a] = arrayOfGames[b];
	arrayOfGames[b] = temp;
	

}


//part of the quicksort
int partition(int *arrayOfInts, int ARRAYSIZE, int low, int high)
{
	int pivot = arrayOfInts[low];

	int left = low + 1;
	int right = high;

	for (;;)
	{
		while (arrayOfInts[left] <= pivot && left <= right)
		{
			left = left + 1;
			++comps;
		}

		while (arrayOfInts[right] >= pivot && right >= left)
		{
			right = right - 1;
			++comps;
		}


		if (right < left)
		{
			swap(arrayOfInts, low, right);
			return right;
		}
		else
		{
			swap(arrayOfInts, left, right);
		}




	}

}

int partitionGameArray(Game *arrayOfGames, int ARRAYSIZE, int low, int high)
{
	testcounter++;
	int pivot = arrayOfGames[low].score;

	int left = low + 1;
	int right = high;

	for (;;)
	{
		while (arrayOfGames[left].score <= pivot && left <= right)
		{
			left = left + 1;
			++comps;
		}

		while (arrayOfGames[right].score >= pivot && right >= left)
		{
			right = right - 1;
			++comps;
		}


		if (right < left)
		{
			swapGames(arrayOfGames, low, right);
			return right;
		}
		else
		{
			swapGames(arrayOfGames, left, right);
		}



	}

}

//Recursive Quicksort
void quickSort(int *arrayOfInts, int ARRAYSIZE, int low, int high)
{
	int pivot;

	if (low < high)
	{
		pivot = partition(arrayOfInts, ARRAYSIZE, low, high);
		quickSort(arrayOfInts, ARRAYSIZE, low, pivot - 1);
		quickSort(arrayOfInts, ARRAYSIZE, pivot + 1, high);
	}
}

void quickSortGameArray(Game *arrayOfGames, int ARRAYSIZE, int low, int high)
{
	int pivot;

	if (low < high)
	{
		pivot = partitionGameArray(arrayOfGames, ARRAYSIZE, low, high);
		quickSortGameArray(arrayOfGames, ARRAYSIZE, low, pivot - 1);
		quickSortGameArray(arrayOfGames, ARRAYSIZE, pivot + 1, high);
	}
}

void merge(int *arrayOfInts, int ARRAYSIZE, int low, int middle, int high)
{
	int i, j, k;

	//sizes of temp arrays
	int const size1 = middle - low + 1;
	int const size2 = high - middle;

	//temp arrays
	int temp1[size1];
	int temp2[size2];

	//copy values into each array
	for (i = 0;i<size1;i++)
		temp1[i] = arrayOfInts[low + i];
	for (j = 0;j<size2;j++)
		temp2[j] = arrayOfInts[middle + 1 + j];

	i = 0;
	j = 0;
	k = low;
	//sorting bit
	while (i < size1 && j < size2)
	{
		if (temp1[i] < temp2[j])
		{
			arrayOfInts[k] = temp1[i];
			swaps++;
			i++;


		}
		else
		{
			arrayOfInts[k] = temp2[j];
			swaps++;
			j++;
		}

		comps++;
		comps++;
		k++;
	}


	while (i<size1)
	{
		arrayOfInts[k] = temp1[i];
		i++;
		k++;
	}

	while (j <size2)
	{
		arrayOfInts[k] = temp2[j];
		j++;
		k++;
	}

}
void mergeSort(int *arrayOfInts, int ARRAYSIZE, int low, int high)
{
	int middle;
	if (low < high)
	{
		//this ways stops it from getting messed up for very large arrays 
		middle = low + (high - low) / 2;

		mergeSort(arrayOfInts, ARRAYSIZE, low, middle);
		mergeSort(arrayOfInts, ARRAYSIZE, middle + 1, high);
		merge(arrayOfInts, ARRAYSIZE, low, middle, high);
	}
}

//checks if the array is sorted
char isSorted(int *arrayOfInts, int ARRAYSIZE)
{

	int i;

	for (i = 0;i<ARRAYSIZE - 1;i++)
	{
		if (arrayOfInts[i] > arrayOfInts[i + 1])
			return 'N';
	}
	return 'Y';
}

void quickSortAndPrintOutcome(int *arrayOfInts, int ARRAYSIZE, char *testName)
{
	swaps = 0;
	comps = 0;
	char check;
	quickSort(arrayOfInts, ARRAYSIZE, 0, ARRAYSIZE - 1);
	printf("Test: %s\n", testName);
	check = isSorted(arrayOfInts, ARRAYSIZE);
	printf("Sorted: %c\n", check);
	printf("Swaps: %i\n", swaps);
	printf("COMPS: %i\n\n", comps);
}

void mergeSortAndPrintOutcome(int *arrayOfInts, int ARRAYSIZE, char *testName)
{
	swaps = 0;
	comps = 0;
	char check;
	mergeSort(arrayOfInts, ARRAYSIZE, 0, ARRAYSIZE - 1);
	printf("Test: %s\n", testName);
	check = isSorted(arrayOfInts, ARRAYSIZE);
	printf("Sorted: %c\n", check);
	printf("Swaps: %i\n", swaps);
	printf("COMPS: %i\n\n", comps);
}

void quickSortAndPrintArray(int *arrayOfInts, int ARRAYSIZE)
{
	printIntArray(arrayOfInts, ARRAYSIZE);
	printf("\n");
	quickSort(arrayOfInts, ARRAYSIZE, 0, ARRAYSIZE - 1);
	printIntArray(arrayOfInts, ARRAYSIZE);
	printf("\n");
}


int  main(int argc, char *argv[])
{
	char FILENAME[20];
	FILE * CSV;
	const int max_length = 500;
	char buffer[max_length];
	const int NUMOFGAMES = 18626;//18626
	Game *gamesArray = (Game*) malloc(NUMOFGAMES*sizeof(Game));
	int testcounter=0;

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
		printf("File opened correctly\n\n");
		readInGames(CSV, buffer, max_length, gamesArray, NUMOFGAMES);
		//printGamesArray(gamesArray, NUMOFGAMES);
		quickSortGameArray(gamesArray, NUMOFGAMES, 0, NUMOFGAMES-1);
		//printGamesArray(gamesArray, NUMOFGAMES);
		printGamesArrayBetween(gamesArray, NUMOFGAMES, NUMOFGAMES - 10, NUMOFGAMES);

	}

	free(gamesArray);

	return  0;

}