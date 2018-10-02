#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct TreeNode TreeNode;
struct TreeNode
{
    char data;
    TreeNode *rightNode;
    TreeNode *leftNode;
};

TreeNode* createNode(char data)
{
    TreeNode *temp= (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = data;
    temp->leftNode = NULL;
    temp->rightNode = NULL;
    return temp;
}

TreeNode* treeNodeInsert(TreeNode* node, char data)
{
    if(node == NULL)
        return createNode(data);
    if(data < node->data)
        node->leftNode = treeNodeInsert(node->leftNode,data);
    else if(data >= node->data)
        node->rightNode = treeNodeInsert(node->rightNode,data);

    return node;
}



//Returns Null if not in tree otherwise returns pointer to location of the FIRST VALUE
TreeNode* treeSearch(TreeNode* root,char data)
{
    if(root == NULL || root->data == data)
        return root;
    if(root->data > data)
        treeSearch(root->leftNode,data);
    else
        treeSearch(root->rightNode,data);
}

void treePrintSortedHelper(TreeNode* root)
{
    if(root != NULL)
    {
        treePrintSortedHelper(root->leftNode);
        printf("%c",root->data);
        treePrintSortedHelper(root->rightNode);
    }
}

void treePrintSorted(TreeNode* root)
{
    printf("Sorted:\t");
    treePrintSortedHelper(root);
    printf("\n");

}

//first node is roo, dfs deletion
void treeDelete(TreeNode* node)
{
    if(node == NULL)
        return;

    treeDelete(node->leftNode);
    treeDelete(node->rightNode);
    free(node);
}

void printIfFound(TreeNode* root,char data)
{
    TreeNode *temp = treeSearch(root,data);

    if(temp!=NULL)
        printf("%c Found\n",temp->data);
    else
        printf("%c Not Found\n",data);
}

int  main(int argc, char *argv[])
{ 
    

    int ARRAYSIZE  = 28;
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    char *arrayOfChars =(char*)malloc(sizeof(ARRAYSIZE*sizeof(char)));
    arrayOfChars = "FLOCCINAUCINIHILIPILIFICATION";
    root = createNode(arrayOfChars[0]);
    int i;
    printf("Adding:\t");
    printf("%c", arrayOfChars[0]);
    for(i=1;i<ARRAYSIZE;i++)
    {
        treeNodeInsert(root,arrayOfChars[i]);
        printf("%c", arrayOfChars[i]);
    }
    printf("\n");
    treePrintSorted(root);
    
    //seed random with time since jan 1 1970
    srand(time(NULL));
    printIfFound(root,'A' + (rand() % 26));
    printIfFound(root,'A' + (rand() % 26));

    //freeshit
    treeDelete(root);
    return 0;
}