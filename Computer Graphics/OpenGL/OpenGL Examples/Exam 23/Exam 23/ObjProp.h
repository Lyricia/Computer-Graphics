#pragma once
#include "gl/glut.h"

class CAngle
{
public:
	float roll{ 0 };		// z axis
	float yaw{ 0 };		// y axis
	float pitch{ 0 };	// x axis

	void Rotate()
	{
		glRotatef(yaw, 0, 1, 0);
		glRotatef(roll, 0, 0, 1);
		glRotatef(pitch, 1, 0, 0);
	}
};

class CColor
{
public:
	unsigned char red{ 0 };
	unsigned char green{ 0 };
	unsigned char blue{ 0 };

	void applycolor() { glColor3f(red / 255, green / 255, blue / 255); }
	void setcolor(unsigned char _red, unsigned char _green, unsigned char _blue) {
		red = _red;
		green = _green;
		blue = _blue;
	}
};

class CVertex
{
public:
	float x{ 0 };
	float y{ 0 };
	float z{ 0 };

	CColor color;
};

enum BBPOS { LEFTTOP, RIGHTTOP, RIGHTBOTTOM, LEFTBOTTOM };

class ObjProp
{
public:
	ObjProp();
	~ObjProp();
	CVertex Vertex;
	CVertex BoundingBox[4];
	CAngle Angle;
	float m_scale;

	void initBB();
	void DrawBB();

	CVertex * GetBB();
	bool isCollide(CVertex * P);
};

