#include "tree.h"

Tree::Tree()
{
	root = NULL;
}

void Tree::insertNode(string nameLast, string nameFirst, int id, double grade)
{
	StudentNode* newNode = new StudentNode(nameLast, nameFirst, id, grade);

	if (root == NULL)
	{
		root = newNode;
		return;
	}

	StudentNode* curr = root;


	while (curr != NULL)
	{
		if (curr->getLastName().compare(newNode->getLastName()) > 0)
		{
			
			if (curr->getLeft() == NULL)
			{
				curr->setLeft(newNode);
				curr = NULL;
			}
			else
				curr = curr->getLeft();
			
		}

		else if (curr->getLastName().compare(newNode->getLastName()) < 0)
		{
			if (curr->getRight() == NULL)
			{
				curr->setRight(newNode);
				curr = NULL;
			}
			else
				curr = curr->getRight();
			
		}

		else
		{
			if (curr->getFirstName().compare(newNode->getFirstName()) > 0)
			{
				if (curr->getLeft() == NULL)
				{
					curr->setLeft(newNode);
					curr = NULL;
				}
				else
					curr = curr->getLeft();
				
			}

			else if (curr->getFirstName().compare(newNode->getFirstName()) < 0)
			{
				if (curr->getRight() == NULL)
				{
					curr->setRight(newNode);
					curr = NULL;
				}
				else
					curr = curr->getRight();
				
			}
			else
			{
				if (curr->getID() < newNode->getID())
				{
					if (curr->getRight() == NULL)
					{
						curr->setRight(newNode);
						curr = NULL;
					}
					else
						curr = curr->getRight();
				
				}
				else
				{
					if (curr->getLeft() == NULL)
					{
						curr->setLeft(newNode);
						curr = NULL;
					}
					else
						curr = curr->getLeft();
			
				}
			}
		}


	}
	
}

void Tree::print()
{
	cout << root->getLastName() << " " << root->getLeft()->getLastName() << " " <<  root->getLeft()->getFirstName() << root->getRight()->getLastName() << " " << root->getRight()->getFirstName();
}


StudentNode * Tree::findStudent(string nameFirst, string nameLast)
{
	numOfComparisons = 0;
	return findStudent(root,nameFirst,nameLast);
}


StudentNode * Tree::findStudent(StudentNode * node, string nameFirst, string nameLast)
{
	numOfComparisons++;
	if(node == NULL)
	{
		return NULL;
	}

	if (node->getFirstName().compare(nameFirst) == 0 && node->getLastName().compare(nameLast) == 0)
	{
		return node;
	}
	
	if (node->getLastName().compare(nameLast) > 0)
	{
		return findStudent(node->getLeft(), nameFirst, nameLast);
	}

	if (node->getLastName().compare(nameLast) < 0)
	{
		return findStudent(node->getRight(), nameFirst, nameLast);
	}

	else
	{
		if (node->getFirstName().compare(nameFirst) > 0)
		{
			return findStudent(node->getLeft(), nameFirst, nameLast);
		}

		if (node->getFirstName().compare(nameFirst) < 0)
		{
			return findStudent(node->getRight(), nameFirst, nameLast);
		}
	}


}