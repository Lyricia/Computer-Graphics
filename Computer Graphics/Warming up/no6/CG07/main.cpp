#include<iostream>

#pragma warning(disable:4996)
#define dist 5

using namespace std;

struct point
{
	int x;
	int y;
};

int main()
{
	int size_x = 0;
	int size_y = 0;


	point p[25] = { 0, };
	
	printf("size x, y: ");
	
	cin >> size_x >> size_y;

	for (int i = 0; i < 25; i++)
		p[i] = { rand() % size_x, rand() % size_y };

	while (1)
	{
		if (getchar()=='q')
			break;
		for (int i = 0; i < 25; i++)
		{
			if (p[i].x - dist < 0)
				p[i].x += dist;
			else if (p[i].x + dist > size_x)
				p[i].x -= dist;
			else
				if (rand() % 2)
					p[i].x += dist;
				else
					p[i].x -= dist;


			if (p[i].y - dist < 0)
				p[i].y += dist;
			else if (p[i].y + dist > size_y)
				p[i].y -= dist;
			else
				if (rand() % 2)
					p[i].y += dist;
				else
					p[i].y -= dist;
		}

		for (int i = 0; i < 25; i++)
		{
			printf("(%.3d, %.3d)  ", p[i].x, p[i].y);
			if (i % 5 == 4)
				printf("\n");
		}


	}



}