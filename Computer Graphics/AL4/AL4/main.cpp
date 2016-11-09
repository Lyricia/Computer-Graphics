#include "BinarySearchTree.h"
using namespace std;

int main(void)
{
	BinarySearchTree Bst;
	
	int menu = 0;
	int targetinput = 0;

	Bst.BST_CreateRootNode(50);
	Bst.BST_InsertNode(0, 24);
	Bst.BST_InsertNode(0, 22);
	Bst.BST_InsertNode(0, 120);
	Bst.BST_InsertNode(0, 17);
	Bst.BST_InsertNode(0, 3);
	Bst.BST_InsertNode(0, 98);
	Bst.BST_InsertNode(0, 34);
	Bst.BST_InsertNode(0, 100);
	Bst.BST_InsertNode(0, 80);
	Bst.BST_InsertNode(0, 45);
	Bst.BST_InsertNode(0, 40);
	Bst.BST_InsertNode(0, 43);
	Bst.BST_InsertNode(0, 36);
	
	Bst.BST_InorderPrintTree(0);
	//
	//cout << endl;
	//
	//Bst.BST_RemoveNode(0,22);			//delete node
	//Bst.BST_RemoveNode(0, 50);		//delete root node
	//Bst.BST_InsertNode(0, 50);		//insert node
	//
	//Bst.BST_InorderPrintTree(0);

	while (1)
	{
		system("cls");

		cout << "1. Create\n2. Insert\n3. Delete\n4. Print ALL"<<endl;
		cin >> menu;

		switch (menu)
		{
		case 1:
			cout << "1. Create\n";
			cout << "Root Value : ";
			cin >> targetinput;

			Bst.BST_CreateRootNode(targetinput);
			break;

		case 2:
			cout << "2. Insert\n";
			cout << "Insert Value : ";
			cin >> targetinput;

			Bst.BST_InsertNode(0, targetinput);
			break;

		case 3:
			cout << "3. Delete\n";
			cout << "Delete Value : ";
			cin >> targetinput;

			Bst.BST_RemoveNode(0, targetinput);
			break;

		case 4:
			Bst.BST_InorderPrintTree(0);
			cout << endl;
			break;

		default:
			cout << "incorrect menu input" << endl;
			break;
		}
		system("pause");
	}
	return 0;
}