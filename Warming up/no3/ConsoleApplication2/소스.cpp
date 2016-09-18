#include <iostream>
#include<math.h>

#pragma warning (disable :4996)


struct vector
{
	int x;
	int y;
	int z;
};

int main()
{
	vector vec1;
	vector vec2;

	char menu = 0;
	float cos = 0;

	vec1 = { 0,0,0 };
	vec2 = { 0,0,0 };
	
	printf("input vec : ");
	scanf("%d %d %d", &vec1.x, &vec1.y, &vec1.z);

	printf("input vec : ");
	scanf("%d %d %d", &vec2.x, &vec2.y, &vec2.z);

	
	while(1)
	{
		printf("menu : ");
		getchar();
		scanf("%c", &menu);
		switch (menu)
		{
		case '+':
			printf("(%d, %d, %d) + (%d, %d, %d) = (%d, %d, %d)\n", vec1.x, vec1.y, vec1.z, vec2.x, vec2.y, vec2.z, vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
			break;

		case '-':
			printf("(%d, %d, %d) + (%d, %d, %d) = (%d, %d, %d)\n", vec1.x, vec1.y, vec1.z, vec2.x, vec2.y, vec2.z, vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
			break;

		case 'd':
			printf("(%d, %d, %d) o (%d, %d, %d) = %d \n", vec1.x, vec1.y, vec1.z, vec2.x, vec2.y, vec2.z, vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);

			cos = (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z) /
				(sqrtf(powf((float)vec1.x, 2) + powf((float)vec1.y, 2) + powf((float)vec1.z, 2))*
					sqrtf(powf((float)vec2.x, 2) + powf((float)vec2.y, 2) + powf((float)vec2.z, 2)));

			printf("cos = %f", cos);
			break;

		case 'c':
			printf("(%d, %d, %d) + (%d, %d, %d) = (%d, %d, %d)\n", vec1.x, vec1.y, vec1.z, vec2.x, vec2.y, vec2.z, vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z, vec1.x*vec2.y - vec1.y*vec2.x);

			break;

		case 'l':
			printf("root (%d, %d, %d) = %f\n", vec1.x, vec1.y, vec1.z, sqrtf(powf((float)vec1.x, 2) + powf((float)vec1.y, 2) + powf((float)vec1.z, 2)));
			printf("root (%d, %d, %d) = %f\n", vec2.x, vec2.y, vec2.z, sqrtf(powf((float)vec2.x, 2) + powf((float)vec2.y, 2) + powf((float)vec2.z, 2)));
			break;
		}
	}
	return 0;
}

