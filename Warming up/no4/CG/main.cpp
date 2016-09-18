#include<iostream>
#include<math.h>

#pragma warning (disable :4996)


struct vertex
{
	int x;
	int y;
	int z;
};

float dist(vertex a, vertex b);
int check(vertex m, int a, int b, int c, int d);


int main()
{
	vertex v1 = { 0,0,0 };
	vertex v2 = { 0,0,0 };
	vertex v3 = { 0,0,0 };
	vertex v4 = { 0,0,0 };

	printf("input 4 vertex : ");
	scanf("%d %d %d", &v1.x, &v1.y, &v1.z);
	scanf("%d %d %d", &v2.x, &v2.y, &v2.z);
	scanf("%d %d %d", &v3.x, &v3.y, &v3.z);
	scanf("%d %d %d", &v4.x, &v4.y, &v4.z);

	int a;
	int b;
	int c;
	int d;

	a = v1.y*(v2.z - v2.z) + v2.y*(v3.z - v1.z) + v3.y*(v1.z - v2.z);
	b = v1.z*(v2.x - v3.x) + v2.z*(v3.x - v1.x) + v3.z*(v1.x - v2.x);
	c = v1.x*(v2.y - v3.y) + v2.x*(v3.y - v1.y) + v3.x*(v1.y - v2.y);
	d = v1.x*(v2.y*v3.z - v3.y*v2.z) + v2.x*(v3.y*v1.z - v1.y*v3.z) + v3.x*(v1.y*v2.z - v2.y*v1.z);

	if (!check(v4, a, b, c, d))
		printf("not matching vertex\n");
	else
	{
		printf("polygon : %dx + %dy + %dz + %d = 0\n", a, b, c, d);

		printf("length :\n");
		printf("(%d, %d, %d)  (%d, %d, %d) = %f\n", v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, dist(v1, v2));
		printf("(%d, %d, %d)  (%d, %d, %d) = %f\n", v2.x, v2.y, v2.z, v3.x, v3.y, v3.z, dist(v2, v3));
		printf("(%d, %d, %d)  (%d, %d, %d) = %f\n", v3.x, v3.y, v3.z, v4.x, v4.y, v4.z, dist(v3, v4));
		printf("(%d, %d, %d)  (%d, %d, %d) = %f\n", v4.x, v4.y, v4.z, v1.x, v1.y, v1.z, dist(v4, v1));

		printf("(%d, %d, %d)  (%d, %d, %d)  ", v1.x, v1.y, v1.z, v2.x, v2.y, v2.z);
		printf("(%d, %d, %d)  (%d, %d, %d)  \n", v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
	}
	return 0;
}

float dist(vertex a, vertex b)
{
	float dist = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z);
	return sqrtf(dist);
}

int check(vertex m, int a, int b, int c, int d)
{
	if (d == a*m.x + b*m.y + c*m.z)
		return 1;
	else
		return 0;
}