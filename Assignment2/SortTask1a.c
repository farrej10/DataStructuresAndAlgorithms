#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>


int swaps;
int comps;

//Fill with Unique Random Numbers
void uniquerandomFill(int *arrayOfInts, int ARRAYSIZE)
{
    int i,j,temp;
    int fin = 0;
    for(i=0;i<ARRAYSIZE;i++)
    {
        temp = rand();
        while(fin == 0)
        {
            for(j=0;j<i;j++)
            {  
                if(temp == arrayOfInts[j])
                    break;
            }
            if(j==i)
                break;
            temp = rand();
        }
        arrayOfInts[i]=temp;
    }

} 
//Fill with Random Numbers
void RandomFill(int *arrayOfInts, int ARRAYSIZE)
{
    int i;
    for(i=0;i<ARRAYSIZE;i++)
    {
        arrayOfInts[i] = rand()%ARRAYSIZE;
    }
} 

void ascendingFill(int *arrayOfInts,int ARRAYSIZE)
{
    int i;
    for(i=0;i<ARRAYSIZE;i++)
    {
       arrayOfInts[i] = i; 
    }
}

void descendingFill(int *arrayOfInts,int ARRAYSIZE)
{
    int i;
    for(i=0;i<ARRAYSIZE;i++)
    {
       arrayOfInts[i] = ARRAYSIZE -i; 
    }
}

void uniformFill(int *arrayOfInts,int ARRAYSIZE)
{
    int i;
    for(i=0;i<ARRAYSIZE;i++)
    {
       arrayOfInts[i] = 3; 
    }
}

//Print All Values in an array
void printIntArray(int *arrayOfInts, int ARRAYSIZE)
{
    int i;
    for(i=0;i<ARRAYSIZE;i++)
    {
        printf("%i\n",arrayOfInts[i]);      
    }
}

//swap variables
void swap(int *arrayOfInts,int a,int b)
{
    swaps++;
    int temp = arrayOfInts[a];
    arrayOfInts[a] = arrayOfInts[b];
    arrayOfInts[b] = temp;
}

//part of the quicksort
int partition(int *arrayOfInts, int ARRAYSIZE, int low, int high)
{   
    int pivot = arrayOfInts[low];
    
    int left = low+1;
    int right = high;

    for(;;)
    {   
        while (arrayOfInts[left] <= pivot && left <= right)
        {
            left = left +1;
            ++comps;
        }

        while (arrayOfInts[right] >= pivot && right >= left)
        {
            right = right -1; 
            ++comps;
        }


        if (right < left)
        {
            swap(arrayOfInts,low,right);
            return right;
        }
        else
        {
            swap(arrayOfInts,left, right);
        }
        
        

        
    }

}

//Recursive Quicksort
void quickSort(int *arrayOfInts,int ARRAYSIZE,int low,int high)
{
    int pivot;

    if(low < high)
    {
        pivot = partition(arrayOfInts, ARRAYSIZE, low, high);
        quickSort(arrayOfInts,ARRAYSIZE,low,pivot-1);
        quickSort(arrayOfInts,ARRAYSIZE,pivot+1,high);
    }
}
void merge(int *arrayOfInts,int ARRAYSIZE,int low, int middle, int high)
{
    int i,j,k;

    //sizes of temp arrays
    int size1 = middle - low + 1;
    int size2 = high - middle;

    //temp arrays
    int temp1[size1],temp2[size2];

    //copy values into each array
    for(i=0;i<size1;i++)
        temp1[i] = arrayOfInts[low +i];
    for(j=0;j<size2;j++)
        temp2[j] = arrayOfInts[middle +1+j];

    i=0;
    j=0;
    k=low;
    //sorting bit
    while(i < size1 && j < size2)
    {
        if(temp1[i] < temp2[j])
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
        k++;
    }


    while(i<size1)
    {
        arrayOfInts[k] = temp1[i];
        i++;
        k++;
    }

    while(j <size2)
    {
        arrayOfInts[k]= temp2[j];
        j++;
        k++;
    }

}
void mergeSort(int *arrayOfInts,int ARRAYSIZE,int low, int high)
{
    int middle;
    if(low < high)
    {
        //this ways stops it from getting messed up for very large arrays 
        middle = low+(high-low)/2;

        mergeSort(arrayOfInts,ARRAYSIZE,low,middle);
        mergeSort(arrayOfInts,ARRAYSIZE,middle+1,high);
        merge(arrayOfInts,ARRAYSIZE,low,middle,high);
    }
}

//checks if the array is sorted
char isSorted(int *arrayOfInts,int ARRAYSIZE)
{
    
    int i;

    for (i=0;i<ARRAYSIZE-1;i++)
    {
        if(arrayOfInts[i] > arrayOfInts[i+1])
            return 'N';
    }
    return 'Y';
}

void quickSortAndPrintOutcome(int *arrayOfInts, int ARRAYSIZE,char *testName)
{
    swaps = 0;
    comps = 0;
    char check;
    quickSort(arrayOfInts,ARRAYSIZE,0,ARRAYSIZE-1);
    printf("Test: %s\n",testName);
    check = isSorted(arrayOfInts,ARRAYSIZE);
    printf("Sorted: %c\n",check);
    printf("Swaps: %i\n", swaps);
    printf("COMPS: %i\n\n", comps);
}

void mergeSortAndPrintOutcome(int *arrayOfInts,int ARRAYSIZE,char *testName)
{
    swaps = 0;
    comps = 0;
    char check;
    mergeSort(arrayOfInts,ARRAYSIZE,0,ARRAYSIZE-1);
    printf("Test: %s\n",testName);
    check = isSorted(arrayOfInts,ARRAYSIZE);
    printf("Sorted: %c\n",check);
    printf("Swaps: %i\n", swaps);
    printf("COMPS: %i\n\n", comps);
}

void quickSortAndPrintArray(int *arrayOfInts,int ARRAYSIZE)
{
    printIntArray(arrayOfInts,ARRAYSIZE);
    printf("\n");
    quickSort(arrayOfInts,ARRAYSIZE,0,ARRAYSIZE-1);
    printIntArray(arrayOfInts,ARRAYSIZE);
    printf("\n");
}


int  main(int argc, char *argv[])
{
    //arrays
    int ARRAYSIZE = 10000;

    int test1[ARRAYSIZE];
    int test2[ARRAYSIZE];
    int test3[ARRAYSIZE];
    int test4[ARRAYSIZE];
    int test5[ARRAYSIZE];

    int test6[ARRAYSIZE];
    int test7[ARRAYSIZE];
    int test8[ARRAYSIZE];
    int test9[ARRAYSIZE];
    int test10[ARRAYSIZE];

    //arrayNames
    char test1Name[50] = "Unique Random Values";
    char test2Name[50] = "Random Values";
    char test3Name[50] = "Ascending Sorted List";
    char test4Name[50] = "Descending Sorted List";
    char test5Name[50] = "Uniform List";

    uniquerandomFill(test1,ARRAYSIZE);
    RandomFill(test2,ARRAYSIZE);
    ascendingFill(test3,ARRAYSIZE);
    descendingFill(test4,ARRAYSIZE);
    uniformFill(test5,ARRAYSIZE);

    uniquerandomFill(test6,ARRAYSIZE);
    RandomFill(test7,ARRAYSIZE);
    ascendingFill(test8,ARRAYSIZE);
    descendingFill(test9,ARRAYSIZE);
    uniformFill(test10,ARRAYSIZE);



    
    printf("\n\n");
   
    printf("QuickSort\n");
    quickSortAndPrintOutcome(test1,ARRAYSIZE,test1Name);
    //printf("MergeSort\n");
    //mergeSortAndPrintOutcome(test6,ARRAYSIZE,test1Name);

    printf("QuickSort\n");
    quickSortAndPrintOutcome(test2,ARRAYSIZE,test2Name);
    //printf("MergeSort\n");
    //mergeSortAndPrintOutcome(test7,ARRAYSIZE,test2Name);

    printf("QuickSort\n");
    quickSortAndPrintOutcome(test3,ARRAYSIZE,test3Name);
    //printf("MergeSort\n");
    //mergeSortAndPrintOutcome(test8,ARRAYSIZE,test3Name);

    printf("QuickSort\n");
    quickSortAndPrintOutcome(test4,ARRAYSIZE,test4Name);
    //printf("MergeSort\n");
   //mergeSortAndPrintOutcome(test9,ARRAYSIZE,test4Name);

    printf("QuickSort\n");
    quickSortAndPrintOutcome(test5,ARRAYSIZE,test5Name);
   // printf("MergeSort\n");
   // mergeSortAndPrintOutcome(test10,ARRAYSIZE,test5Name); 

    
       
	return  0;

}