#pragma once
#include <iostream>


typedef struct
{
	int Data;
	int Left;
	int Right;
	int Prev;
}BSTNode;


class BinarySearchTree
{
private:
	BSTNode * Tree;
public:
	BinarySearchTree();
	~BinarySearchTree();

	void	BST_CreateRootNode(int NewData);
	void	BST_InsertNode(int Parent_Nodeidx, int InsertData);
	int		BST_SearchMinNode(int Nodeidx);
	int		BST_SearchMaxNode(int Nodeidx);
	int		BST_SearchNode(int Parent_Nodeidx, int Target);
	void	BST_InorderPrintTree(int Nodeidx);
	int		BST_RemoveNode(int Nodeidx, int Target);
	void	BST_Replacement(int Nodeidx);

	inline int Left(int Nodeidx) { return (Nodeidx * 2) + 1; }
	inline int Right(int Nodeidx) { return (Nodeidx * 2) + 2; }
	inline int Parent(int Nodeidx) { return (Nodeidx - 1) / 2; }
};
