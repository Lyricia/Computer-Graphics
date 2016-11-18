#include<iostream>
#include <math.h>

#pragma warning(disable:4996)


struct func
{
	int x;
	int y;
	int z;
	float dist;
};



int main()
{
	func point[10];
	func userinput;
	
	char menu = 0;
	int index = 0;
	int temp = 0;  //index
	float dist = 0; // distance


	for (int i = 0; i < 10; i++)
	{
		point[i].x = 0;
		point[i].y = 0;
		point[i].z = 0;
		point[i].dist = 0;
	}


	while (1)
	{
		menu = NULL;

		printf("menu : ");
		menu = getchar();


		switch (menu)
		{
		case '+':
			if (index >= 10)
			{
				printf("LIST IS FULL\n");
				break;
			}

			printf("put x, y, z (quit to q) : ");
			scanf("%d %d %d", &userinput.x, &userinput.y, &userinput.z);
			if (userinput.x == 'q') break;
			
			point[index] = userinput;

			dist = powf((float)userinput.x, 2) + powf((float)userinput.y, 2) + powf((float)userinput.z, 2);
			point[index].dist = sqrtf(dist);
			printf("input : (%d, %d, %d)\ndistance : %f\n", point[index].x, point[index].y, point[index].z, point[index].dist);
			index++;
			printf("list size index = %d\n", index);
			break;

		case '-':
			if (index <= 0)
			{
				printf("LIST IS EMPTY\n");
				break;
			}
			point[index-1].x = 0;
			point[index-1].y = 0;
			point[index-1].z = 0;
			point[index-1].dist = 0;

			index--;

			printf("index = %d\n", index);
			break;

		case 'e':
			if (index >= 10)
			{
				printf("LIST IS FULL\n");
				break;
			}

			if (index != 0)
			{
				temp = index; 

				point[9].x = 0;
				point[9].y = 0;
				point[9].z = 0;
				point[9].dist = 0;

				for (int i = temp; temp > 0; i--,temp--)
				{
					point[i] = point[temp-1];
				}
			}

			printf("put x, y, z (quit to q) : ");
			scanf("%d %d %d", &userinput.x, &userinput.y, &userinput.z);
			if (userinput.x == 'q') break;

			point[0] = userinput;

			dist = powf((float)userinput.x, 2) + powf((float)userinput.y, 2) + powf((float)userinput.z, 2);
			point[0].dist = sqrtf(dist);
			
			printf("input : (%d, %d, %d)\ndistance : %f\n", point[0].x, point[0].y, point[0].z, point[0].dist);
			index++;
			printf("index = %d\n", index);
			break;

		case 'd':
			if (index <= 0)
			{
				printf("LIST IS EMPTY\n");
				break;
			}

			if (index != 0)
			{
				temp = index;

				for (int i = 0; i<index; i++)
				{
					point[i] = point[i + 1];
				}

				point[9].x = 0;
				point[9].y = 0;
				point[9].z = 0;
				point[9].dist = 0;
			}

			index--;
			printf("index = %d\n", index);
			break;

		case 'l':
			for (int i = index - 1; i > -1; i--)
			{
				printf("input : (%d, %d, %d)\ndistance : %f\n", point[i].x, point[i].y, point[i].z, point[i].dist);
			}
			printf("List Size : %d \n", index);

			break;

		case 'c':
			for (int i = 0; i < 10; i++)
			{
				point[i].x = 0;
				point[i].y = 0;
				point[i].z = 0;
				point[i].dist = 0;
			}
			index = 0;
			break;

		case 'm':
			dist = point[0].dist;
			for (int i = 0; i < index; i++)
			{
				if (point[i].dist > (float)dist)
					dist = point[i].dist;
			}

			printf("Longist is : %f\n", dist);
			break;

		case 'n':
			dist = point[0].dist;
			for (int i = 0; i < index; i++)
			{
				if (point[i].dist <(float)dist)
					dist = point[i].dist;
			}

			printf("shortest is : %f\n", dist);
			break;


		case 'q':
			exit(0);
			break;
		}
		printf("\n");
		getchar();
	}
	return 0;
}