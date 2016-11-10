#pragma once
#include<gl\glut.h>

class CBall
{
public:
	CBall();
	~CBall();
public:
	int anglex;
	int angley;
	int anglez;
	
	void movex(int angle);
	void movey(int angle);
	void movez(int angle);


};

