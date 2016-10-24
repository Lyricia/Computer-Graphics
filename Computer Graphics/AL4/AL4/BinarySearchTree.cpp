#pragma once
#include "BinarySearchTree.h"

BSTNode TreeList[1000] = { NULL, };

void BinarySearchTree::BST_CreateRootNode(int NewData)
{
	Tree[0].Data = NewData;
	Tree[0].Left = NULL;
	Tree[0].Right = NULL;
	Tree[0].Prev = NULL;
}

void BinarySearchTree::BST_InsertNode(int Parent_Nodeidx, int InsertData)
{
	if (Tree[Parent_Nodeidx].Data < InsertData)
	{
		if (Tree[Right(Parent_Nodeidx)].Data == NULL)
			Tree[Right(Parent_Nodeidx)].Data = InsertData;
		else
			BST_InsertNode(Right(Parent_Nodeidx), InsertData);

	}
	else if (Tree[Parent_Nodeidx].Data > InsertData)
	{
		if (Tree[Left(Parent_Nodeidx)].Data == NULL)
			Tree[Left(Parent_Nodeidx)].Data = InsertData;
		else
			BST_InsertNode(Left(Parent_Nodeidx), InsertData);
	}
}

int BinarySearchTree::BST_SearchMinNode(int Nodeidx)
{
	if (Tree[Nodeidx].Data == NULL)
		return NULL;

	if (Tree[Left(Nodeidx)].Data == NULL)
		return Nodeidx;
	else
		return BST_SearchMinNode(Left(Nodeidx));
}

int BinarySearchTree::BST_SearchMaxNode(int Nodeidx)
{
	if (Tree[Nodeidx].Data == NULL)
		return NULL;

	if (Tree[Right(Nodeidx)].Data == NULL)
		return Nodeidx;
	else
		return BST_SearchMaxNode(Right(Nodeidx));
}

int BinarySearchTree::BST_SearchNode(int Parent_Nodeidx, int Target)
{
	if (Tree[Parent_Nodeidx].Data == NULL)
		return NULL;

	if (Tree[Parent_Nodeidx].Data == Target)
		return Parent_Nodeidx;

	else if (Tree[Parent_Nodeidx].Data > Target)
		return BST_SearchNode(Left(Parent_Nodeidx), Target);
	else
		return BST_SearchNode(Right(Parent_Nodeidx), Target);
}

void BinarySearchTree::BST_InorderPrintTree(int Parent_Nodeidx)
{
	if (Tree[Parent_Nodeidx].Data == NULL)
		return;

	/*  왼쪽 하위 트리 출력 */
	BST_InorderPrintTree(Left(Parent_Nodeidx));

	/*  루트 노드 출력 */
	printf("%d ", Tree[Parent_Nodeidx].Data);

	/*  오른쪽 하위 트리 출력 */
	BST_InorderPrintTree(Right(Parent_Nodeidx));
}

int BinarySearchTree::BST_RemoveNode(int Nodeidx, int Targetinput)
{
	int Targetidx = NULL;

	Targetidx = BST_SearchNode(Nodeidx, Targetinput);

	BST_Replacement(Targetidx);

	return Targetidx;
}

void BinarySearchTree::BST_Replacement(int Nodeidx)
{
	int Tempidx = NULL;

	if (Tree[Left(Nodeidx)].Data == NULL && Tree[Right(Nodeidx)].Data == NULL)			//Leaf
	{
		Tree[Nodeidx].Data = NULL;
		return;
	}
	else if (Tree[Left(Nodeidx)].Data == NULL && Tree[Right(Nodeidx)].Data != NULL)		//Right
	{
		Tempidx = BST_SearchMinNode(Right(Nodeidx));
		Tree[Nodeidx].Data = Tree[Tempidx].Data;
		BST_Replacement(Tempidx);
		return;
	}
	else if (Tree[Left(Nodeidx)].Data != NULL && Tree[Right(Nodeidx)].Data == NULL)		//Left
	{
		Tempidx = BST_SearchMaxNode(Left(Nodeidx));
		Tree[Nodeidx].Data = Tree[Tempidx].Data;
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

