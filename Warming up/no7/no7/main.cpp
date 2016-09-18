#include <iostream>
#include<math.h>

#define movedist 5

using namespace std;

struct sizepoint
{
	int x1;
	int y1;
	int x2;
	int y2;
};


int main()
{
	sizepoint stdfig = { 100,100,300,300 };
	sizepoint userfig = { 0, };

	int shapesel = 0;
	char cmd = 0;
	int stdrad = 100;
	int userrad=0;


	cout << "shape combine : ";
	cin >> shapesel;

	cout << "user fig point (x1 y1 x2 y2) : ";
	cin >> userfig.x1 >> userfig.y1 >> userfig.x2 >> userfig.y2;

	userrad = abs(userfig.x1 - userfig.x2) / 2;

	cout << "shape 1 : (" << stdfig.x1 << ", " << stdfig.y1 << ")  (" << stdfig.x2 << ", " << stdfig.y2 << ")" << endl;
	cout << "shape 1 : (" << userfig.x1 << ", " << userfig.y1 << ")  (" << userfig.x2 << ", " << userfig.y2 << ")" << endl;
	
	while (1)
	{
		cout << "command : ";
		cin >> cmd;

		switch (cmd)
		{
		case 'a':
			userfig.x1 -= movedist;
			userfig.x2 -= movedist;
			break;
		case 'd':
			userfig.x1 += movedist;
			userfig.x2 += movedist;
			break;
		case 's':
			userfig.y1 += movedist;
			userfig.y2 += movedist;
			break;
		case 'w':
			userfig.y1 -= movedist;
			userfig.y2 -= movedist;
			break;
		}

		cout << "shape 1 : (" << stdfig.x1 << ", " << stdfig.y1 << ")  (" << stdfig.x2 << ", " << stdfig.y2 << ")" << endl;
		cout << "shape 1 : (" << userfig.x1 << ", " << userfig.y1 << ")  (" << userfig.x2 << ", " << userfig.y2 << ")" << endl;



		switch (shapesel)
		{
		case 1:
			if ((abs((stdfig.x1 + stdfig.x2) / 2 - (userfig.x1 + userfig.x2) / 2) < userrad + stdrad) && (abs((stdfig.y1 + stdfig.y2) / 2 - (userfig.y1 + userfig.y2) / 2) < userrad + stdrad))
				cout << "rect1, rect2 collide" << endl;
			break;

		case 2:
			if ((stdrad + userrad)*(stdrad + userrad) >																											// (std radius + user radius)^2
				((stdfig.x1 + stdfig.x2) / 2 - (userfig.x1 + userfig.x2) / 2)*((stdfig.x1 + stdfig.x2) / 2 - (userfig.x1 + userfig.x2) / 2)					// x^2
				+ ((stdfig.y1 + stdfig.y2) / 2 - (userfig.y1 + userfig.y2) / 2)*((stdfig.y1 + stdfig.y2) / 2 - (userfig.y1 + userfig.y2) / 2))				// y^2
				cout << "cir1, cir2 collide" << endl;
			break;

		case 3:
			if ((((stdfig.x1 + stdfig.x2) / 2 - (userfig.x1 + userfig.x2) / 2)*((stdfig.x1 + stdfig.x2) / 2 - (userfig.x1 + userfig.x2) / 2)				//x^2
				+ ((stdfig.y1 + stdfig.y2) / 2 - (userfig.y1 + userfig.y2) / 2)*((stdfig.y1 + stdfig.y2) / 2 - (userfig.y1 + userfig.y2) / 2) <				//y^2
				(stdrad + sqrt(2)*userrad)*(stdrad + sqrt(2)*userrad))																						//dist between cir, rect
				&&
				(abs((stdfig.x1 + stdfig.x2) / 2 - (userfig.x1 + userfig.x2) / 2) < userrad + stdrad) && (abs((stdfig.y1 + stdfig.y2) / 2 - (userfig.y1 + userfig.y2) / 2) < userrad + stdrad)
				)																																			//
				cout << "cir1, rect2 collide" << endl;
			break;
		}
		cout<<endl;
	}
}