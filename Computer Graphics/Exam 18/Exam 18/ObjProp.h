#pragma once
#include "gl/glut.h"

class CAngle
{
public:
	float roll;		// z axis
	float yaw;		// y axis
	float pitch;	// x axis

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
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	void applycolor() { glColor3f(red / 255, green / 255, blue / 255); }
};

class CVertex
{
public:
	float x;
	float y;
	float z;

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

