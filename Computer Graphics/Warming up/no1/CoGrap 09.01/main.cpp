#pragma warning (disable :4996)

#include <iostream>
#include <time.h>

int main()
{
	// Çà·Ä 3,3
	// a µ¡¼À
	// d »¬¼À
	// m °ö¼À
	// r determinant
	// 3x3 -> 4x4
	//

	// int arr1[3][3] = { 0, };
	// int arr2[3][3] = { 0, };
	int arr3[3][3] = { 0, };

	int arr1[3][3] = {
		{ 0,0,1 },
		{1,1,1},
		{0,1,0}
	};

	int arr2[3][3] = {
		{ 1,0,1 },
		{ 0,0,0 },
		{ 0,1,0 }
	};

	int arr4[4][4] = { 0, };

	int temp = 0;

	char menuchk = 0;
	
	srand(time(NULL));

	//for (int i = 0; i < 3; i++)
	//{
	//	arr1[i][0] = rand() % 2;
	//	arr1[i][1] = rand() % 2;
	//	arr1[i][2] = rand() % 2;
	//	arr2[i][2] = rand() % 2;
	//	arr2[i][2] = rand() % 2;
	//	arr2[i][2] = rand() % 2;
	//}

	for (int i = 0; i < 3; i++)
	{
		printf("%d %d %d   ", arr1[i][0], arr1[i][1], arr1[i][2]);

		printf("%d %d %d\n", arr2[i][0], arr2[i][1], arr2[i][2]);
	}


	while (1)
	{
		scanf("%c", &menuchk);
		switch (menuchk)
		{
		case 'a':
			for (int i = 0; i < 3; i++) 
			{
				printf("%d %d %d   ", arr1[i][0], arr1[i][1], arr1[i][2]);
		
				printf("%d %d %d   ", arr2[i][0], arr2[i][1], arr2[i][2]);
		
				printf("%d %d %d\n", arr1[i][0] + arr2[i][0], arr1[i][1] + arr2[i][1], arr1[i][2] + arr2[i][2]);
			}
			break;

		case 'd':
			for (int i = 0; i < 3; i++)
			{
				printf("%d %d %d   ", arr1[i][0], arr1[i][1], arr1[i][2]);

				printf("%d %d %d   ", arr2[i][0], arr2[i][1], arr2[i][2]);

				printf("%d %d %d\n", arr1[i][0] - arr2[i][0], arr1[i][1] - arr2[i][1], arr1[i][2] - arr2[i][2]);
			}
			break;

		case 'm':
			for (int i = 0; i < 3; i++)
			{
				printf("%d %d %d   ", arr1[i][0], arr1[i][1], arr1[i][2]);

				printf("%d %d %d   ", arr2[i][0], arr2[i][1], arr2[i][2]);

				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						temp += arr1[i][k] * arr2[k][j];
					}
					arr3[i][j] = temp;
					temp = 0;
				}
				printf("%d %d %d   ", arr3[i][0], arr3[i][1], arr3[i][2]);
				printf("\n");
			}
			temp = 0;
			break;

		case 'r':
			temp = arr1[0][0] * arr1[1][1] * arr1[2][2] +
				arr1[0][1] * arr1[1][2] * arr1[2][0] +
				arr1[0][2] * arr1[1][0] * arr1[2][1] -
				arr1[0][2] * arr1[1][1] * arr1[2][0] -
				arr1[0][0] * arr1[1][2] * arr1[2][1] -
				arr1[0][1] * arr1[1][0] * arr1[2][2];

			printf("%d\n", temp);
			break;

		case 'h':
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					arr4[i][3] = 0;
					arr4[3][i] = 0;
					arr4[i][j] = arr1[i][j];
				}
			}
			arr4[3][3] = 1;

			for (int i = 0; i < 4; i++)
			{
				printf("%d %d %d %d\n", arr4[i][0], arr4[i][1], arr4[i][2], arr4[i][3]);
			} 

			break;


		case 'q':
			return 0;
		}
	}

	return 0;
}