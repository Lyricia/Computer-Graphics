#pragma once
#include "ObjProp.h"

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

public:
	void moveCrane(float speed);
	void moveBottom(int angle, bool isX, bool isY, bool isZ);
	void moveMiddle(int angle, bool isX, bool isY, bool isZ);
	void moveTop(int angle, bool isX, bool isY, bool isZ);
	void Render();
};

