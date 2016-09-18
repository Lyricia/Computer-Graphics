#include<iostream>
#include <math.h>

#pragma warning(disable :4996)
#define PI 3.141592654

using namespace std;

struct point
{
	double x;
	double y;
};

int main()
{
	point P = { 0,0 };

	point arr[16] = { 0, };
	point sort[16] = { 0, };

	char cmd = 0;
	int num = 0;
	int temp = 0;
	int index = 15;

	// double 오차 반올림으로 계산

	for (int i = 0, j = 0; i < 360; i += 30, j++)
	{
		arr[j].x = round(cos(i*(PI / 180))*1000)/1000;
		arr[j].y = round(sin(i*(PI / 180))*1000)/1000;
	}

	for (int i = 45, j = 12; i < 360; i += 90, j++)
	{
		arr[j].x = round(cos(i*(PI / 180))*1000)/1000;
		arr[j].y = round(sin(i*(PI / 180))*1000)/1000;
	}


	//for (int i = 0; i < index+1; i += 4)
	//{
	//	//arr[i].x = cos((i * 90) * (PI / 180));		arr[i].y = sin((i * 90)  * (PI / 180));
	//	printf("%f\n", cos((30 + (i * 90)) * (PI / 180)));
	//
	//	arr[i + 1].x = cos((30 + (i * 90)) * (PI / 180));		arr[i + 1].y = sin((30 + (i * 90)) * (PI / 180));
	//	arr[i + 2].x = cos((45 + (i * 90)) * (PI / 180));		arr[i + 2].y = sin((45 + (i * 90)) * (PI / 180));
	//	arr[i + 3].x = cos((60 + (i * 90)) * (PI / 180));		arr[i + 3].y = sin((60 + (i * 90)) * (PI / 180));
	//}
	//arr[0] = { 1,0 };	arr[4] = { 0,1 };	arr[8] = { -1,0 };	arr[12] = { 0,-1 };


	arr[0] = { 1,0 };	arr[3] = { 0,1 };	arr[6] = { -1,0 };	arr[9] = { 0,-1 };

	for (int i = 0; i < 16; i++)
	{
		temp = 0;
		for (int j = 0; j < index + 1; j++)
		{
			if (arr[temp].y < arr[j].y)
				temp = j;
			if (arr[temp].y == arr[j].y && arr[temp].x > arr[j].x)
				temp = j;
		}
		sort[i] = arr[temp];

		arr[temp] = arr[index];
		arr[index] = { 0,0 };
		index--;
	}

	while (1)
	{
		printf("command, num: ");
		scanf("%c %d", &cmd, &num);

		switch (cmd)
		{
		case'c':
			P.x = P.x + num;
			printf("moved point : (%.3f, %.3f)\n", P.x, P.y);
			break;
		case 'x':
			printf("(%.3f, %.3f)\n", sort[0].x + num, sort[0].y);
			for (int i = 1; i < 15; i += 2)
				printf("(%.3f, %.3f)      (%.3f, %.3f) \n", sort[i].x + num, sort[i].y, sort[i + 1].x + num, sort[i + 1].y);
			printf("(%.3f, %.3f)\n", sort[15].x + num, sort[15].y);
			break;


		case 'y':
			printf("(%.3f, %.3f)\n", sort[0].x, sort[0].y + num);
			for (int i = 1; i < 15; i += 2)
				printf("(%.3f, %.3f)      (%.3f, %.3f) \n", sort[i].x, sort[i].y + num, sort[i + 1].x, sort[i + 1].y + num);
			printf("(%.3f, %.3f)\n\n", sort[15].x, sort[15].y + num);
			break;
		}
		getchar();
	}
	
	return 0;
}
