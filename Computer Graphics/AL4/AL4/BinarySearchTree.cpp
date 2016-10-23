#include "BinarySearchTree.h"

int BinarySearchTree::BST_CreateNode(int NewData, int Nodeidx)
{
	TreeList[Nodeidx].Data = NewData;
	TreeList[Nodeidx].Left = NULL;
	TreeList[Nodeidx].Right = NULL;
	TreeList[Nodeidx].Prev = NULL;

	return Nodeidx;
}

void BinarySearchTree::BST_InsertNode(int Parent_Nodeidx, int InsertData)
{
	if (TreeList[Parent_Nodeidx].Data < InsertData)
	{
		if (TreeList[Right(Parent_Nodeidx)].Data == NULL)
			TreeList[Right(Parent_Nodeidx)].Data = InsertData;
		else
			BST_InsertNode(Right(Parent_Nodeidx), InsertData);

	}
	else if (TreeList[Parent_Nodeidx].Data > InsertData)
	{
		if (TreeList[Left(Parent_Nodeidx)].Data == NULL)
			TreeList[Left(Parent_Nodeidx)].Data = InsertData;
		else
			BST_InsertNode(Left(Parent_Nodeidx), InsertData);
	}
}


void BinarySearchTree::BST_DestroyNode(int Nodeidx)
{
	TreeList[Nodeidx].Data = NULL;
}

int BinarySearchTree::BST_SearchMinNode(int Nodeidx)
{
	int Left = (Nodeidx * 2) + 1;

	if (TreeList[Nodeidx].Data == NULL)
		return NULL;

	if (TreeList[Left].Data == NULL)
		return Left;
	else
		return BST_SearchMinNode(Left);
}

void BinarySearchTree::BST_DestroyTree(int Parent_Nodeidx)
{
	

	if (TreeList[Right(Parent_Nodeidx)].Data != NULL)
		BST_DestroyTree(Right(Parent_Nodeidx));

	if (TreeList[Left(Parent_Nodeidx)].Data != NULL)
		BST_DestroyTree(Left(Parent_Nodeidx));

	TreeList[Left(Parent_Nodeidx)].Data = NULL;
	TreeList[Right(Parent_Nodeidx)].Data = NULL;

	BST_DestroyNode(Parent_Nodeidx);
}

int BinarySearchTree::BST_SearchNode(int Parent_Nodeidx, int Target)
{
	int Left = (Parent_Nodeidx * 2) + 1;
	int Right = (Parent_Nodeidx * 2) + 2;

	if (TreeList[Parent_Nodeidx].Data == NULL)
		return NULL;

	if (TreeList[Parent_Nodeidx].Data == Target)
		return Parent_Nodeidx;

	else if (TreeList[Parent_Nodeidx].Data > Target)
		return BST_SearchNode(Left, Target);
	else
		return BST_SearchNode(Right, Target);
}

void BinarySearchTree::BST_InorderPrintTree(int Parent_Nodeidx)
{


	if (TreeList[Parent_Nodeidx].Data == NULL)
		return;

	/*  ���� ���� Ʈ�� ��� */
	BST_InorderPrintTree(Left(Parent_Nodeidx));

	/*  ��Ʈ ��� ��� */
	printf("%d ", TreeList[Parent_Nodeidx].Data);

	/*  ������ ���� Ʈ�� ��� */
	BST_InorderPrintTree(Right(Parent_Nodeidx));
}

int BinarySearchTree::BST_RemoveNode(int Nodeidx, int Target)
{
	int Removed = NULL;

	TreeList[Nodeidx].Data;
	TreeList[Left(Nodeidx)].Data;
	TreeList[Right(Nodeidx)].Data;

	if (TreeList[Nodeidx].Data == NULL)
		return NULL;

	if (TreeList[Nodeidx].Data > Target)
		Removed = BST_RemoveNode(Left(Nodeidx), Target);

	else if (TreeList[Nodeidx].Data < Target)
		Removed = BST_RemoveNode(Right(Nodeidx), Target);

	else /*  ��ǥ ���� ã�� ���. */
	{
		Removed = Nodeidx;


		if (TreeList[Left(Nodeidx)].Data == NULL && TreeList[Right(Nodeidx)].Data == NULL)		/*  �� ����� ��� �ٷ� ���� */
		{
			TreeList[Nodeidx].Data = NULL;
		}
		else
		{
			if (TreeList[Left(Nodeidx)].Data != NULL && TreeList[Right(Nodeidx)].Data != NULL)		/*  �ڽ��� ���� �� �ִ� ��� */
			{
				/*  �ּҰ� ��带 ã�� ������ �� ������ ��忡 ��ġ��Ų��. */
				
				int tmp = Right(Nodeidx);
				int tmp_parent = tmp;
				while (TreeList[Left(Nodeidx)].Data != NULL)
				{
					tmp_parent = tmp;
					tmp = BinarySearchTree::BST_SearchMinNode(tmp);
				}


				if (TreeList[Left(tmp)].Data == NULL && TreeList[Right(tmp)].Data == NULL)
					TreeList[Nodeidx].Data = TreeList[tmp].Data;

				else
				{

				}
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