#include "bstdb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book{
    char *title;
    int count, ID;
    struct book* left;
    struct book* right;

}book;


book* root;
double num_visits;
double word_count_searches;
int IDs[120000];
int num_books;
static int curr_ID;

int bstdb_init ( void ) 
{
    root = NULL;
    num_visits = 0;
    word_count_searches = 0;
    curr_ID = 0;
    num_books = 0;
    int interval = 131072;
    int counter = 0;
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
    return 1;
    // This function will run once (and only once) when the database first
    // starts. Use it to allocate any memory you want to use or initialize 
    // some globals if you need to. Function should return 1 if initialization
    // was successful and 0 if something went wrong.
}

book* createBook( char *name, int word_count )
{
    book* newbook = malloc(sizeof(book));
    size_t len_name = strlen(name) + 1;;
    if(newbook)
    {
        newbook->ID = IDs[curr_ID];
        curr_ID++;
        newbook->count = word_count;
        newbook->left = NULL;
        newbook->right = NULL;
        
        newbook->title = calloc(len_name, sizeof(char));
        if (newbook->title) 
        {
            strcpy( newbook->title, name );
        }
        else
        {
            printf("Failed to add node\n");
            newbook = NULL;
        }
    }
    return newbook;
}

int bstdb_add ( char *name, int word_count ) 
{
    book* temp = createBook( name, word_count );    
    
    book* curr = root;
    book* prev = root;
    if( root == NULL)
    {
        root = temp;
        return temp->ID;
    }
    else
    {
        while( curr != NULL)
        {
            prev = curr;
            if( temp->ID < curr->ID )
            {
                curr = curr->left;
            }
            else if( temp->ID >= curr->ID)
            {
                curr = curr->right;
            }
        }
        if( temp->ID < prev->ID )
        {
            prev->left = temp;
            return temp->ID;
        }
        else if( temp->ID >= prev->ID)
        {
            prev->right = temp;
            return temp->ID;
        }
    }
    printf("Failed to add node\n");
    return -1;
    // This function should create a new node in the binary search tree, 
    // populate it with the name and word_count of the arguments and store
    // the result in the tree.
    //
    // This function should also generate and return an identifier that is
    // unique to this document. A user can find the stored data by passing
    // this ID to one of the two search functions below.
    //
    // How you generate this ID is up to you, but it must be an integer. Note
    // that this ID should also form the keys of the nodes in your BST, so
    // try to generate them in a way that will result in a balanced tree.
    //
    // If something goes wrong and the data cannot be stored, this function
    // should return -1. Otherwise it should return the ID of the new node
}

/*book* getComps( book* root, int doc_id )
{
    if( !root || root->ID ){ num_visits++; return root;}

    if( root->ID < doc_id){ num_visits+=2; return getComps( root->right, doc_id);}

    return getComps( root->left, doc_id );
}*/


int bstdb_get_word_count ( int doc_id ) 
{
    word_count_searches++;
    book* curr = root;
    num_visits++;
    while( curr != NULL)
    {
        if( curr->ID == doc_id)
        {
            return curr->count;
        }
        else if( doc_id < curr->ID)
        {
            num_visits++;
            curr = curr->left;
        }
        else if( doc_id >= curr->ID)
        {
            num_visits++;
            curr = curr->right;
        }
    }
    return -1;
    // This is a search function. It should traverse the binary search tree
    // and return the word_count of the node with the corresponding doc_id.
    //
    // If the required node is not found, this function should return -1
    
}

char* bstdb_get_name ( int doc_id ) 
{
    book* curr = root;
    while( curr != NULL)
    {
        if( curr->ID == doc_id)
        {
            return curr->title;
        }
        else if( doc_id < curr->ID)
        {
            curr = curr->left;
        }
        else if( doc_id >= curr->ID)
        {
            curr = curr->right;
        }
    }
    return 0;
    // This is a search function. It should traverse the binary search tree
    // and return the name of the node with the corresponding doc_id.
    //
    // If the required node is not found, this function should return NULL or 0
    
}

void numBooks( book* root )
{
    if( root != NULL)
    {
        numBooks( root->left );
        numBooks( root->right );
        num_books++;
    }
}

int max(int a, int b)
{
  return (a >= b)? a: b;
} 

int height( book* root)
{
   /* base case tree is empty */
   if( root == NULL )
       return 0;
 
   /* If tree is not empty then height = 1 + max of left
      height and right heights */
   return (1 + max( height( root->left ), height( root->right ) ) );
} 

int isBalanced( book* root)
{
   int lh; /* for height of left subtree */
   int rh; /* for height of right subtree */ 
 
   /* If tree is empty then return true */
   if(root == NULL)
    return 1; 
 
   /* Get the height of left and right sub trees */
   lh = height(root->left);
   rh = height(root->right);
 
   if( abs(lh-rh) <= 2 && isBalanced(root->left) && isBalanced(root->right))
     return 1;
 
   /* If we reach here then tree is not height-balanced */
   return 0;
}



void bstdb_stat ( void ) 
{
    printf("STATS\n");
    if( isBalanced( root ) )
    { 
        printf("The Tree is balanced\n");
    }
    else
    { 
        printf("The tree is not balanced\n");
    }

    numBooks( root );
    printf("There are %d books in the tree\n", num_books);

    printf("Total word count searches : %f\n", word_count_searches);
    printf("Average number of nodes visits when searching by word count : %f\n", ( num_visits/ word_count_searches) );
    // Use this function to show off! It will be called once after the 
    // profiler ends. The profiler checks for execution time and simple errors,
    // but you should use this function to demonstrate your own innovation.
    //
    // Suggestions for things you might want to demonstrate are given below,
    // but in general what you choose to show here is up to you. This function
    // counts for marks so make sure it does something interesting or useful.
    //
    //  + Check if your tree is balanced and print the result
    //
    //  + Does the number of nodes in the tree match the number you expect
    //    based on the number of insertions you performed?
    //
    //  + How many nodes on average did you need to traverse in order to find
    //    a search result? 
    //
    //  + Can you prove that there are no accidental duplicate document IDs
    //    in the tree?
}

void treeDelete( book* root )
{
    if( root != NULL)
    {
        treeDelete( root->left );
        treeDelete( root->right );
        free(root);
    }
}

void bstdb_quit ( void ) {
    treeDelete( root );
    // This function will run once (and only once) when the program ends. Use
    // it to free any memory you allocated in the course of operating the
    // database.
}