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

	/*  왼쪽 하위 트리 출력 */
	BST_InorderPrintTree(Left(Parent_Nodeidx));

	/*  루트 노드 출력 */
	printf("%d ", TreeList[Parent_Nodeidx].Data);

	/*  오른쪽 하위 트리 출력 */
	BST_InorderPrintTree(Right(Parent_Nodeidx));
}

int BinarySearchTree::BST_RemoveNode(int Nodeidx, int Targetval)
{
	int Targetidx = NULL;

	TreeList[Nodeidx].Data;
	TreeList[Left(Nodeidx)].Data;
	TreeList[Right(Nodeidx)].Data;

	Targetidx = BST_SearchNode(Nodeidx, Targetval);

	else /*  목표 값을 찾은 경우. */
	{
		Removed = Nodeidx;


		if (TreeList[Left(Nodeidx)].Data == NULL && TreeList[Right(Nodeidx)].Data == NULL)		/*  잎 노드인 경우 바로 삭제 */
		{
			TreeList[Nodeidx].Data = NULL;
		}
		else
		{
			if (TreeList[Left(Nodeidx)].Data != NULL && TreeList[Right(Nodeidx)].Data != NULL)		/*  자식이 양쪽 다 있는 경우 */
			{
				/*  최소값 노드를 찾아 제거한 뒤 현재의 노드에 위치시킨다. */
				
				int tmp = Right(Nodeidx);
				int tmp_parent = tmp;
				while (TreeList[Left(Nodeidx)].Data != NULL)
				{
					tmp_parent = tmp;
					tmp = BST_SearchMinNode(tmp);
				}


				if (TreeList[Left(tmp)].Data == NULL && TreeList[Right(tmp)].Data == NULL)
					TreeList[Nodeidx].Data = TreeList[tmp].Data;


				else
					BST_ChildMove(Nodeidx);
			}
			else					/*  자식이 하나만 있는 경우 */
			{
				if (TreeList[Left(Nodeidx)].Data != NULL && TreeList[Right(Nodeidx)].Data != NULL)
				{
					TreeList[(Nodeidx-1)/2].Data = TreeList[];
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

int BinarySearchTree::BST_ChildMove(int Nodeidx)
{
	TreeList[Parent(Nodeidx)].Data = TreeList[Nodeidx].Data;
	
	if (TreeList[Left(Nodeidx)].Data != NULL)
		BST_ChildMove(Left(Nodeidx));

	if (TreeList[Right(Nodeidx)].Data != NULL)
		BST_ChildMove(Right(Nodeidx));
}

BinarySearchTree::~BinarySearchTree()
{
}

BinarySearchTree::BinarySearchTree()
{
}