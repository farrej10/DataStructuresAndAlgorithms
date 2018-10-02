	
#include  <stdio.h>

//char read_in_till_end(FILE *csv, char *buffer, int max_length, char current, int index)
//{
//	if (current != EOF)
//	{
//		/*Add each character to the buffer string*/
//		buffer[index] = current;
//		current = fgetc(csv);
//		index++;
//	}
//
//	else
//	{
//		/*If end of file still need to do the end string character or else it will print the empty part of the buffer*/
//		buffer[index] = '\0';
//		return 1;
//
//	}
//}



int next_field(FILE *csv, char *buffer, int max_length)
{

	char current = fgetc(csv);
	int index = 0;
	
	if (current == '"')
	{
		while (current != '\n')
		{

			if (current != EOF)
			{
				/*Add each character to the buffer string*/
				buffer[index] = current;
				current = fgetc(csv);
				index++;
			}

			else
			{
				/*If end of file still need to do the end string character or else it will print the empty part of the buffer*/
                buffer[index] = '\n';
				buffer[index+1] = '\0';
				return 1;

            }

			
		}

		buffer[index] = '\n';
		buffer[index+1] = '\0';
		return 1;
        
	}
	else 
	{
		if(current != '\n')
		{

			while (current != ',')
			
			{
				if (current != EOF)
				{
					/*Add each character to the buffer string*/
					buffer[index] = current;
					current = fgetc(csv);
					index++;
				}
				else
				{
					/*If end of file still need to do the end string character or else it will print the empty part of the buffer*/
					buffer[index] = '\n';
					buffer[index+1] = '\0';
					return 1;

				}
			}
		
		}
		else
		{
			buffer[index] = '\n';
			buffer[index+1] = '\0';
			return 1;
		}
	}

	printf("This current %c", current);

	
}
	







int  main(int argc, char *argv[]) {

	
	char FILENAME[20];
	FILE * CSV;
	const int max_length = 250;
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
		int exit = 0;
		
		/*Run the loop so that it prints until the end of file*/
		while(exit == 0)
        {
			exit = next_field(CSV, buffer, max_length);
			printf("%s", buffer);
        }




	}



	return  0;

}

