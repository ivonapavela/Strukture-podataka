#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct tree* node;
typedef struct tree {
	int element;
	node left;
	node right;
};

int option();
node CreateNewNode(int);
node InputNode(int, node);
int Inorder(node);
int Preorder(node);
int Postorder(node);
int Levelorder(node);
int DepthOfTree(node);
int PrintCurrentLevel(node, int);
node FindElement(int, node);
node DeleteElement(int, node);
node FindMinimum(node);

int main()
{
	node root = NULL;
	int numberOfOption = 0;
	int element = 0;
	node foundElement = NULL;

	while (numberOfOption != 8)
	{
		option();
		printf("Enter the number of your choice:\n");
		scanf(" %d", &numberOfOption);

		switch (numberOfOption)
		{
		case 1:
			printf("Enter the element you want to input into the tree:\n");
			scanf(" %d", &element);
			root = InputNode(element, root);
			break;
		case 2:
			Inorder(root);
			printf("\n");
			break;
		case 3:
			Preorder(root);
			printf("\n");
			break;
		case 4:
			Postorder(root);
			printf("\n");
			break;
		case 5:
			Levelorder(root);
			printf("\n");
			break;
		case 6:
			printf("Enter the element you want to find:\n");
			scanf(" %d", &element);
			foundElement = FindElement(element, root);
			if (foundElement == NULL)
			{
				printf("Element does not exist in the tree!\n");
			}
			else
			{
				printf("The element you looked for is %d\n", foundElement->element);
			}
			break;
		case 7:
			printf("Enter the element you want to delete:\n");
			scanf(" %d", &element);
			root = DeleteElement(element, root);
			break;
		case 8:
			printf("Exit!\n");
			break;
		default:
			printf("You entered the wrong option!\n");
		}
	}
	return 0;
}

int option()
{
	printf("1.Input the new node\n");
	printf("2.Inorder print\n");
	printf("3.Preorder print\n");
	printf("4.Postorder print\n");
	printf("5.Level order print\n");
	printf("6.Find element\n");
	printf("7.Delete element\n");
	printf("8.Exit\n");

	return 0;
}

node CreateNewNode(int element)
{
	node newNode = NULL;

	newNode = (node)malloc(sizeof(struct tree));

	if (!newNode)
	{
		perror("Cannot allocate memory!\n");
		return 0;
	}

	newNode->element = element;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

node InputNode(int element, node root)
{
	node newNode = NULL;
	node currentNode = root;

	if (currentNode == NULL)
	{
		newNode = CreateNewNode(element);
		return newNode;
	}
	else if (currentNode->element < element)
	{
		currentNode->right = InputNode(element, currentNode->right);
	}
	else if (currentNode->element > element)
	{
		currentNode->left = InputNode(element, currentNode->left);
	}

	return currentNode;
}

int Inorder(node root)
{
	node currentNode = root;

	if (currentNode != NULL)
	{
		Inorder(currentNode->left);
		printf("%d	", currentNode->element);
		Inorder(currentNode->right);
	}

	return 0;
}

int Preorder(node root)
{
	node currentNode = root;

	if (currentNode != NULL)
	{
		printf("%d	", currentNode->element);
		Preorder(currentNode->left);
		Preorder(currentNode->right);
	}

	return 0;
}

int Postorder(node root)
{
	node currentNode = root;

	if (currentNode != NULL)
	{
		Postorder(currentNode->left);
		Postorder(currentNode->right);
		printf("%d	", currentNode->element);
	}

	return 0;
}

int Levelorder(node root)
{
	int depth = DepthOfTree(root);
	int i = 0;

	for (i = 1; i <= depth; i++)
	{
		PrintCurrentLevel(root, i);
		printf("\n");
	}

	return 0;
}

int DepthOfTree(node root)
{
	int leftDepth = 0;
	int rightDepth = 0;

	if (root == NULL)
		return 0;
	else
	{
		leftDepth = DepthOfTree(root->left);
		rightDepth = DepthOfTree(root->right);
	}

	if (leftDepth > rightDepth)
		return leftDepth + 1;
	else
		return rightDepth + 1;
}

int PrintCurrentLevel(node root, int level)
{
	if (root == NULL)
		return 0;

	if (level == 1)
		printf("%d", root->element);
	else if (level > 1)
	{
		PrintCurrentLevel(root->left, level - 1);
		PrintCurrentLevel(root->right, level - 1);
	}
}


node FindElement(int element, node root)
{
	node currentNode = root;

	if (currentNode == NULL)
	{
		return currentNode;
	}
	else if (currentNode->element > element)
	{
		return FindElement(element, currentNode->left);
	}
	else if (currentNode->element < element)
	{
		return FindElement(element, currentNode->right);
	}
	else
		return currentNode;
}

node DeleteElement(int element, node root)
{
	node current = root;
	node temp = NULL;

	if (current == NULL)
	{
		return root;
	}
	else if (current->element > element)
	{
		current->left = DeleteElement(element, current->left);
	}
	else if (current->element < element)
	{
		current->right = DeleteElement(element, current->right);
	}
	else if (current->left != NULL && current->right != NULL)
	{
		temp = FindMinimum(current->right);
		current->element = temp->element;
		current->right = DeleteElement(current->element, current->right);
	}
	else
	{
		temp = current;
		if (current->left == NULL)
		{
			current = current->right;
		}
		else
		{
			current = current->left;
		}

		free(temp);
	}

	return current;
}

node FindMinimum(node root)
{
	node current = root;

	if (current != NULL)
	{
		while (current->left != NULL)
		{
			current = current->left;
		}
		return current;
	}

	return root;
}