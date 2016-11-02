#pragma once
#include <iostream>

struct BSTNode
{
	int Data;
	BSTNode *Left;
	BSTNode *Right;
	BSTNode *Parent;

	int Left;
	int Right;
	int Prev;
};

class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();
	BSTNode* BST_CreateNode(int NewData);
	BSTNode * grandparent(BSTNode * n);
	void BST_DestroyNode(BSTNode* Node);
	BSTNode* BST_SearchMinNode(BSTNode* Tree);
	void BST_DestroyTree(BSTNode* Tree);
	BSTNode* BST_SearchNode(BSTNode* Tree, int Target);
	void BST_InorderPrintTree(BSTNode* Node);
	BSTNode* BST_RemoveNode(BSTNode* Tree, BSTNode* Parent, int Target);
	void BST_InsertNode(BSTNode* Tree, BSTNode *Child);
};
