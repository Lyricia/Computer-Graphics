#pragma once
#include <iostream>

struct BSTNode
{
	int Data;
	int color;
	BSTNode *Left;
	BSTNode *Right;
	BSTNode *Parent;

	int Left;
	int Right;
	int Prev;
};

struct BSTNode *grandparent(struct BSTNode *n)
{
	if ((n != NULL) && (n->Parent != NULL))
		return n->Parent->Parent;
	else
		return NULL;
}

struct BSTNode* uncle(BSTNode* n)
{
	struct BSTNode* g = grandparent(n);
	if (g == NULL)
		return NULL;
	if (n->Parent == g->Left)
		return g->Right;
	else
		return g->Left;
}

enum color { BLACK, RED };

class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();
	BSTNode* BST_CreateNode(int NewData);
	void BST_DestroyNode(BSTNode* Node);
	BSTNode* BST_SearchMinNode(BSTNode* Tree);
	void BST_DestroyTree(BSTNode* Tree);
	BSTNode* BST_SearchNode(BSTNode* Tree, int Target);
	void BST_InorderPrintTree(BSTNode* Node);
	BSTNode* BST_RemoveNode(BSTNode* Tree, BSTNode* Parent, int Target);
	void BST_InsertNode(BSTNode* Tree, BSTNode *Child);
};

void insert_case5(BSTNode * n);

void rotate_right(BSTNode * n);

void rotate_left(BSTNode * n);
