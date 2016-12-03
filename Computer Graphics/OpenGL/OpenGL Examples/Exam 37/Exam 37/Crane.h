#pragma once
#include "ObjProp.h"
#include "Ball.h"
class CBall;

class CCrane : public ObjProp
{
public:
	CCrane();
	~CCrane();

private:
	int bottomangle;
	int middleanglex;
	int middleangley;
	int topanglex;
	int topanglez;
	int zdir;
	
	CBall wheel[4];

public:
	int angle = 0;
	int xdir;
	void moveCrane(float speed);
	void moveBottom(int angle, bool isX, bool isY, bool isZ);
	void moveMiddle(int angle, bool isX, bool isY, bool isZ);
	void moveTop(int angle, bool isX, bool isY, bool isZ);
	void Render();
};

