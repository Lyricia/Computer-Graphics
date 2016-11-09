#include "BinarySearchTree.h"

BSTNode* BinarySearchTree::BST_CreateNode(int NewData)
{
	BSTNode* NewNode = (BSTNode*)malloc(sizeof(BSTNode));
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = NewData;
	NewNode->Parent = NULL;

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
		{
			Tree->Right = Child;
			Child->Parent = Tree;
		}
		else
			BST_InsertNode(Tree->Right, Child);
	}
	else if (Tree->Data > Child->Data)
	{
		if (Tree->Left == NULL)
		{
			Tree->Left = Child;
			Child->Parent = Tree;
		}
		else
			BST_InsertNode(Tree->Left, Child);
	}
}

void insert_case1(struct BSTNode* n)
{
	if (n->Parent == NULL)
		n->color = BLACK;
	else insert_case2(n);
}

void insert_case2(struct BSTNode * n)
{
	if (n->Parent->color == BLACK)
		return;
	else insert_case3(n);
}

void insert_case3(struct BSTNode * n)
{
	BSTNode * u = uncle(n), *g;
	if ((u != NULL) && (u->color == RED))
	{
		n->Parent->color = BLACK;
		u->color = BLACK;
		g = grandparent(n);
		g->color = RED;
		insert_case1(g);
	}
	else
		insert_case4(n);
}

void insert_case4(BSTNode * n)
{
	BSTNode * g = grandparent(n);

	if ((n == n->Parent->Right) && (n->Parent == g->Left))
	{
		rotate_left(n->Parent);
		n = n->Left;
	}
	else if ((n == n->Parent->Left) && (n->Parent == g->Right))
	{
		rotate_right(n->Parent);
		n = n->Right;
	}
	insert_case5(n);
}

void insert_case5(BSTNode * n)
{
	BSTNode* g = grandparent(n);
	n->Parent->color = BLACK;
	g->color = RED;
	if (n == n->Parent->Left)
		rotate_right(g);
	else
		rotate_left(g);
}

void rotate_right(BSTNode * n)
{

}

void rotate_left(BSTNode *n)
{

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

	/*  왼쪽 하위 트리 출력 */
	BST_InorderPrintTree(Node->Left);

	/*  루트 노드 출력 */
	printf("%d ", Node->Data);

	/*  오른쪽 하위 트리 출력 */
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

	else /*  목표 값을 찾은 경우. */
	{
		Removed = Node;


		if (Node->Left == NULL && Node->Right == NULL)		/*  잎 노드인 경우 바로 삭제 */
		{
			Node = NULL;
		}
		else
		{
			if (Node->Left != NULL && Node->Right != NULL)		/*  자식이 양쪽 다 있는 경우 */
			{
				/*  최소값 노드를 찾아 제거한 뒤 현재의 노드에 위치시킨다. */
				
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
			else					/*  자식이 하나만 있는 경우 */
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