#pragma once
#include "BinarySearchTree.h"

/*
Use Inline Function to make easy to read
Left()	= (nodeinput * 2) + 1
Right() = (nodeinput * 2) + 2
Parent()= (nodeinput - 1) / 2

TreeList is Declared in .cpp and linkd to BST_Class member value Tree in BST Constructor,
so it does not make Linker Error (LNK2005, error about header duplication).
*/

BSTNode TreeList[1000] = { NULL, };

void BinarySearchTree::BST_CreateRootNode(int NewData)
{
	Tree[0].Data = NewData;
	Tree[0].Left = NULL;
	Tree[0].Right = NULL;
	Tree[0].Prev = NULL;
}

void BinarySearchTree::BST_InsertNode(int Nodeidx, int InsertData)
{
	if (Tree[Nodeidx].Data < InsertData)					//if insert data is bigger than node data
	{
		if (Tree[Right(Nodeidx)].Data == NULL)				//and node has no child
			Tree[Right(Nodeidx)].Data = InsertData;			//insert node
		else
			BST_InsertNode(Right(Nodeidx), InsertData);		//if not, recursive

	}
	else if (Tree[Nodeidx].Data > InsertData)				//if insert data is smaller than node data
	{
		if (Tree[Left(Nodeidx)].Data == NULL)
			Tree[Left(Nodeidx)].Data = InsertData;
		else
			BST_InsertNode(Left(Nodeidx), InsertData);
	}
}

int BinarySearchTree::BST_SearchMinNode(int Nodeidx)			//Search Minimum node
{
	if (Tree[Nodeidx].Data == NULL)
		return NULL;

	if (Tree[Left(Nodeidx)].Data == NULL)
		return Nodeidx;
	else
		return BST_SearchMinNode(Left(Nodeidx));
}

int BinarySearchTree::BST_SearchMaxNode(int Nodeidx)			//Search Maximum node
{
	if (Tree[Nodeidx].Data == NULL)
		return NULL;

	if (Tree[Right(Nodeidx)].Data == NULL)
		return Nodeidx;
	else
		return BST_SearchMaxNode(Right(Nodeidx));
}

int BinarySearchTree::BST_SearchNode(int Nodeidx, int Target)	//Search Target Node
{
	if (Tree[Nodeidx].Data == NULL)
		return NULL;

	if (Tree[Nodeidx].Data == Target)							//if find target, return target
		return Nodeidx;

	else if (Tree[Nodeidx].Data > Target)						//if target is bigger than parent
		return BST_SearchNode(Left(Nodeidx), Target);			//recursive left
	else
		return BST_SearchNode(Right(Nodeidx), Target);			//recursive right
}

void BinarySearchTree::BST_InorderPrintTree(int Nodeidx)
{
	if (Tree[Nodeidx].Data == NULL)			//if node has no data return
		return;

	BST_InorderPrintTree(Left(Nodeidx));		//print left tree

	printf("%d ", Tree[Nodeidx].Data);			//print Node data

	BST_InorderPrintTree(Right(Nodeidx));
}

int BinarySearchTree::BST_RemoveNode(int Nodeidx, int Targetinput)		//Remove Node
{
	int Targetidx = NULL;

	Targetidx = BST_SearchNode(Nodeidx, Targetinput);			//Search Target

	BST_Replacement(Targetidx);									//Target should deleted and it need it's replacement

	return Targetidx;
}

void BinarySearchTree::BST_Replacement(int Nodeidx)			//Find Replacement Function | Nodeidx is node that need replacement(Parent)
{
	int Tempidx = NULL;

	if (Tree[Left(Nodeidx)].Data == NULL && Tree[Right(Nodeidx)].Data == NULL)			//Parent is Leaf
	{
		Tree[Nodeidx].Data = NULL;
		return;
	}
	else if (Tree[Left(Nodeidx)].Data == NULL && Tree[Right(Nodeidx)].Data != NULL)		//Parent has only Right node
	{
		Tempidx = BST_SearchMinNode(Right(Nodeidx));			//Find Minimum node from Parent's right node
		Tree[Nodeidx].Data = Tree[Tempidx].Data;				//replace Parent with replacement
		BST_Replacement(Tempidx);								//do Recursive to cover it's child nodes
		return;
	}
	else if (Tree[Left(Nodeidx)].Data != NULL && Tree[Right(Nodeidx)].Data == NULL)		//Left
	{
		Tempidx = BST_SearchMaxNode(Left(Nodeidx));				//Find Maximum node from Parent's Left node
		Tree[Nodeidx].Data = Tree[Tempidx].Data;				//same as Left one
		BST_Replacement(Tempidx);
		return;
	}

	else if (Tree[Left(Nodeidx)].Data != NULL && Tree[Right(Nodeidx)].Data != NULL)		//Both
	{
		Tempidx = BST_SearchMaxNode(Left(Nodeidx));
		Tree[Nodeidx].Data = Tree[Tempidx].Data;
		BST_Replacement(Tempidx);
		return;
	}
}

BinarySearchTree::~BinarySearchTree()
{
}

BinarySearchTree::BinarySearchTree()
{
	Tree = TreeList;
}

