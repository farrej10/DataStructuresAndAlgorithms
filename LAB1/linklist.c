#include  <stdio.h>
#include <stdlib.h>

 typedef struct Node {

    char data;
    struct Node* next_node;

}Node;


void add_node(Node** list, char data){

    Node *new_node;
    new_node = (Node*)malloc(sizeof(Node));

    if(list == NULL)
    {
        list = &new_node;
        new_node->data = data;
    }
    else
    {
        Node *prev_head;
        prev_head = list->next_node;
        list = &new_node;
        new_node->data = data;
        new_node->next_node = prev_head;
    }

}



int  main(int argc, char *argv[]) {



	

	return  0;

}

