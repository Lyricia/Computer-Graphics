#include <iostream>
#include <time.h>
#include <windows.h>
#define number 10000

using namespace std;

void insertsort();
int bubblesort(int);
int selectionsort(int);
void heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);

int arr[number] = { 90, 30, 50, 20, 40, 10, 80, 60, 70 };
// 10, 20, 30, 40, 50, 60, 70, 80, 90
// 90, 30, 50, 20, 40, 10, 80, 60, 70
int arrindex = 0;


int main()
{
	int count = 0;
	double start = 0;
	double end = 0;

	int bRun = true;
	int menu = 0;

	srand((unsigned)time(NULL));

	for (int i = 0; i < number; ++i)
		arr[i] = rand() % 10000;
	while (true)
	{
		system("cls");
		cout << "Heap : 1 \nInsert : 2\nRandomaize : 3\nSelect : ";
		cin >> menu;

		switch (menu)
		{
		case 1:
			start = clock();
			heapSort(arr, number);
			end = clock();

			for (int i = 0; i < number; ++i)
				cout << arr[i] << endl;
			cout << "time cast : " << end - start << endl;
			break;

		case 2:
			start = clock();
			insertsort();
			end = clock();

			for (int i = 0; i < number; ++i)
				cout << arr[i] << endl;
			cout << "time cast : " << end - start << endl;
			break;

		case 3:
			for (int i = 0; i < number; ++i)
				arr[i] = rand() % 10000;
			break;

		default:
			break;
		}

		system("pause");
	}
}

void heapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(arr, n, i);
	}

	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

void heapify(int arr[], int n, int i)
{
	int index = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && arr[left] > arr[index])
		index = left;

	if (right < n && arr[right] > arr[index])
		index = right;

	if (index != i)
	{
		swap(arr[i], arr[index]);
		heapify(arr, n, index);
	}
}

void insertsort()
{
	int sortindex = 0;
	int tmp = 0;
	int i, j;

	for (i = 1; i < number; ++i)
	{
		tmp = arr[i];
		for (j = i - 1; j >= 0, tmp < arr[j]; --j)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = tmp;
	}
}

int bubblesort(int arrindex)
{
	int sortindex = number - 1;
	int temp = 0;
	int count = 0;

	for (int j = sortindex; j > 0; --j)
	{
		temp = 0;
		for (int i = 0; i < number - 1; ++i)
		{
			if (arr[i] < arr[i + 1])
				temp++;
			if (temp == number - 1)
				return count;
		}

		temp = 0;
		for (int i = 0; i < number - 1; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				count++;
			}
			sortindex -= 1;
		}
	}
	return count;
}

int selectionsort(int arrindex)
{
	int sortindex = number;
	int temp = 0;
	int maximum = 0; 
	int index = 0;


	for (int j = 0; j < number; ++j)
	{
		temp = 0;
		for (int i = 0; i < number - 1; ++i)
		{
			if (arr[i] < arr[i + 1])
				temp++;
			if (temp == number - 1)
			{
				int arrtemp[number] = { 0, };
				for (int k = 0; k < number; ++k)
				{
					arrtemp[k] = arr[number - 1 - k];
				}
				for (int k = 0; k < number; ++k)
				{
					arr[k] = arrtemp[k];
				}
				return true;
			}
		}

		maximum = 0;
		for (int i = 0; i < sortindex; ++i)
		{
			if (maximum < arr[i])
			{
				maximum = arr[i];
				index = i;
			}
		}
		swap(arr[index], arr[sortindex - 1]);
		sortindex--;
	}
	return 0;
}