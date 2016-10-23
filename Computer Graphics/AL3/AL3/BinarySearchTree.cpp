#include "BinarySearchTree.h"

BSTNode* BinarySearchTree::BST_CreateNode(int NewData)
{
	BSTNode* NewNode = (BSTNode*)malloc(sizeof(BSTNode));
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = NewData;
	NewNode->Prev = NULL;

	return NewNode;
}

void BinarySearchTree::BST_DestroyNode(BSTNode* Node)
{
	free(Node);
}

BSTNode* BinarySearchTree::BST_SearchMinNode(BSTNode* Tree)
{
	if (Tree == NULL)
		return NULL;

	if (Tree->Left == NULL)
		return Tree;
	else
		return BST_SearchMinNode(Tree->Left);
}


void BinarySearchTree::BST_InsertNode(BSTNode* Tree, BSTNode *Child)
{
	if (Tree->Data < Child->Data)
	{
		if (Tree->Right == NULL)
			Tree->Right = Child;
		else
			BST_InsertNode(Tree->Right, Child);

	}
	else if (Tree->Data > Child->Data)
	{
		if (Tree->Left == NULL)
			Tree->Left = Child;
		else
			BST_InsertNode(Tree->Left, Child);
	}
}


void BinarySearchTree::BST_DestroyTree(BSTNode* Tree)
{
	if (Tree->Right != NULL)
		BST_DestroyTree(Tree->Right);

	if (Tree->Left != NULL)
		BST_DestroyTree(Tree->Left);

	Tree->Left = NULL;
	Tree->Right = NULL;

	BST_DestroyNode(Tree);
}

BSTNode* BinarySearchTree::BST_SearchNode(BSTNode* Tree, int Target)
{
	if (Tree == NULL)
		return NULL;

	if (Tree->Data == Target)
		return Tree;
	else if (Tree->Data > Target)
		return BST_SearchNode(Tree->Left, Target);
	else
		return BST_SearchNode(Tree->Right, Target);
}

void BinarySearchTree::BST_InorderPrintTree(BSTNode* Node)
{
	if (Node == NULL)
		return;

	/*  ���� ���� Ʈ�� ��� */
	BST_InorderPrintTree(Node->Left);

	/*  ��Ʈ ��� ��� */
	printf("%d ", Node->Data);

	/*  ������ ���� Ʈ�� ��� */
	BST_InorderPrintTree(Node->Right);
}

BSTNode* BinarySearchTree::BST_RemoveNode(BSTNode* Node, BSTNode* Parent, int Target)
{
	BSTNode* Removed = NULL;

	if (Node == NULL)
		return NULL;

	if (Node->Data > Target)
		Removed = BST_RemoveNode(Node->Left, Node, Target);

	else if (Node->Data < Target)
		Removed = BST_RemoveNode(Node->Right, Node, Target);

	else /*  ��ǥ ���� ã�� ���. */
	{
		Removed = Node;


		if (Node->Left == NULL && Node->Right == NULL)		/*  �� ����� ��� �ٷ� ���� */
		{
			Node = NULL;
		}
		else
		{
			if (Node->Left != NULL && Node->Right != NULL)		/*  �ڽ��� ���� �� �ִ� ��� */
			{
				/*  �ּҰ� ��带 ã�� ������ �� ������ ��忡 ��ġ��Ų��. */
				
				BSTNode* tmp = Node->Right;
				BSTNode* tmp_parent = tmp;
				while (tmp->Left != NULL)
				{
					tmp_parent = tmp;
					tmp = BinarySearchTree::BST_SearchMinNode(tmp);
				}

				tmp_parent->Left = tmp->Right;
				tmp->Right = Node->Right;
				tmp->Left = Node->Left;

				if (Parent->Data > tmp->Data)
					Parent->Left = tmp;
				else if (Parent->Data < tmp->Data)
					Parent->Right = tmp;
			
			}
			else					/*  �ڽ��� �ϳ��� �ִ� ��� */
			{
				if (Node->Left != NULL && Node->Right == NULL)
				{
					Parent->Left = Node->Left;
					return Removed;
				}
				else if (Node->Right != NULL && Node->Left == NULL)
				{
					Parent->Right = Node->Right;
					return Removed;
				}
			}
		}
	}
	return Removed;
}

BinarySearchTree::~BinarySearchTree()
{
}

BinarySearchTree::BinarySearchTree()
{
}