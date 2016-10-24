#pragma once
#include <iostream>

struct BSTNode
{
	int Data;
	//BSTNode *Left;
	//BSTNode *Right;
	//BSTNode *Prev;

	int Left;
	int Right;
	int Prev;
};

BSTNode TreeList[100] = { NULL, };

class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();
	int BST_CreateNode(int NewData, int);
	void BST_InsertNode(int Parent_Nodeidx, int InsertData);
	void BST_DestroyNode(int Nodeidx);
	int BST_SearchMinNode(int Nodeidx);
	void BST_DestroyTree(int Parent_Nodeidx);
	int BST_SearchNode(int Parent_Nodeidx, int Target);
	void BST_InorderPrintTree(int Nodeidx);
	int BST_RemoveNode(int Nodeidx, int Target);
	int BST_ChildMove(int Nodeidx);
	inline int Left(int Nodeidx) { return (Nodeidx * 2) + 1; }
	inline int Right(int Nodeidx) { return (Nodeidx * 2) + 2; }
	inline int Parent(int Nodeidx) { return (Nodeidx - 2) / 2; }
};
