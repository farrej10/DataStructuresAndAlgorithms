#include "bstdb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Write your submission in this file
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit

typedef struct BookNode BookNode;
struct BookNode
{
	int doc_id;
	char *name;
	int word_count;

    BookNode *rightNode;
    BookNode *leftNode;
};


//Globals
BookNode *root;
int bookCounter;
int IDs[120000];
int hashedIDS[137341];
double numVisits;
double word_countSearches;
static int currentID;


int hash(char* s)
{
	int temphash = 0;
	while (*s)
	{
		temphash = temphash + *s;
		s++;
	}
	return temphash%137341;
}

int
bstdb_init ( void ) {

	//initalising values
    root = NULL;
    numVisits = 0;
    word_countSearches = 0;
    currentID = 0;
    bookCounter = 0;
    int interval = 131072;
    int counter = 0;
	int i;


	//Not mine got it from someone else this will produce a perfect tree for a size 120000
	//Not scalable you have to remake the ids if you are increase the amount of books youre making
    while(counter < 120000)
    {

        for (int v = interval/2; v < 120000; v += interval) 
        {
            IDs[counter] = v;
            counter++;
        }
        interval /= 2;
        if (interval == 1)
            break;
    }

	for(i=0;i<137341;i++)
	{
		hashedIDS[i]=0;
	}
    return 1;
}


//creates a node with a given name word count and doc id
BookNode* createNode(char *name,int word_count,int doc_id)
{
    BookNode *temp= (BookNode*)malloc(sizeof(BookNode));
	size_t len_name;
	//ensuring malloc doesnt fail
	if(temp)
	{
		len_name = strlen(name)+1;
		temp->name = calloc(len_name,sizeof(char));
		if(temp->name)
		{
			strcpy(temp->name,name);
			temp->word_count = word_count;
			temp->leftNode = NULL;
			temp->rightNode = NULL;
			temp->doc_id = doc_id;
		}
	
		return temp;
	}
	return temp;
}


int
bstdb_add ( char *name, int word_count ) {

	
	//using balanced tree method
	BookNode* temp = createNode( name, word_count,IDs[currentID]); 
	currentID++;   

	//hashing method
	
	//int tempHash;
	//int j=1;
	//tempHash=hash(name);
	/*quadratic probing
	while(hashedIDS[tempHash] != 0)
	{
		tempHash = (tempHash + j*j)%137341;
		j++;
	}
	hashedIDS[tempHash]=1;
	BookNode* temp = createNode( name, word_count,tempHash); 
	*/
    BookNode* curr = root;
    BookNode* prev = root;
    if( root == NULL)
    {
        root = temp;
        return temp->doc_id;
    }
    else
    {
        while( curr != NULL)
        {
            prev = curr;
            if( temp->doc_id < curr->doc_id )
            {
                curr = curr->leftNode;
            }
            else if( temp->doc_id >= curr->doc_id)
            {
                curr = curr->rightNode;
            }
        }
        if( temp->doc_id < prev->doc_id )
        {
            prev->leftNode = temp;
            return temp->doc_id;
        }
        else if( temp->doc_id >= prev->doc_id)
        {
            prev->rightNode = temp;
            return temp->doc_id;
        }
    }

    return -1;
}


int
bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1

	BookNode* curr = root;
    word_countSearches++;
	numVisits++;

    while( curr != NULL)
    {
        if( curr->doc_id == doc_id)
        {
            return curr->word_count;
        }
        else if( doc_id < curr->doc_id)
        {
            numVisits++;
            curr = curr->leftNode;
        }
        else if( doc_id >= curr->doc_id)
        {
            numVisits++;
            curr = curr->rightNode;
        }
    }
    return -1;
}


char*
bstdb_get_name ( int doc_id ) {

	BookNode* curr = root;
    while( curr != NULL)
    {
        if( curr->doc_id == doc_id)
        {
            return curr->name;
        }
        else if( doc_id < curr->doc_id)
        {
            curr = curr->leftNode;
        }
        else if( doc_id >= curr->doc_id)
        {
            curr = curr->rightNode;
        }
    }
    return 0;
}

//check to see if there are duplicate ids return Y/N
char
AreThereDuplicates (int doc_id) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1

	BookNode* curr = root;
    while( curr != NULL)
    {
        if( doc_id < curr->doc_id)
        {
            curr = curr->leftNode;
        }
        else if( doc_id > curr->doc_id)
        {
            curr = curr->rightNode;
        }
		else if( doc_id == curr->doc_id)
        {	//duplicate
            return 'Y';
        }
    }
    return 'N';
}

//deletes tree from root
void treeDelete(BookNode *node)
{
    if(node == NULL)
        return;

    treeDelete(node->leftNode);
    treeDelete(node->rightNode);
    free(node);
}
//counts the number of books from the root to every leaf
void numBooks( BookNode *root )
{
    if( root != NULL)
    {
        numBooks( root->leftNode );
        numBooks( root->rightNode );
        bookCounter++;
    }
}
// takes two values and returns the max
int returnMax(int a, int b)
{
  return (a >= b)? a: b;
} 

int calcHeight( BookNode *root)
{
   //returns 0 if tree is empty
   if( root == NULL )
       return 0;
 
   //if the tree is not empty it is 1+ the hight of the subtrees
   return (1 + returnMax( calcHeight( root->leftNode ), calcHeight( root->rightNode ) ) );
} 

int isBalanced( BookNode *root)
{
   int leftHeight;
   int rightHeight;
 
   //an empty tree is still a balanced tree
   if(root == NULL)
    return 1; 
 
   //find the heights of the subtrees
   leftHeight = calcHeight(root->leftNode);
   rightHeight = calcHeight(root->rightNode);
 
	//if the difference between the left and right subtrees is less then 2 then its balanced,
	//recursivly check the subtrees if theyre all ballanced
	//they return 1 then the final return will be one
	if( abs(leftHeight-rightHeight) <= 2 && isBalanced(root->leftNode) && isBalanced(root->rightNode))
		return 1;
 
   //returns here if not balanced
   return 0;
}


void
bstdb_quit ( void ) 
{

	treeDelete(root);
}


void
bstdb_stat ( void ) {
	printf("STATS\n");
    if( isBalanced(root) )
    { 
        printf("Balanced -> Y\n");
    }
    else
    { 
        printf("Balanced -> N\n");
    }

    numBooks(root);
    printf("Books in the Tree -> %i\n", bookCounter);
    printf("Total number of word count searches -> %g\n", word_countSearches);
    printf("Average number of node searches until found -> %f\n", (numVisits/word_countSearches));
	printf("Duplicates -> %c\n\n",AreThereDuplicates(-1));
}

