#pragma once
#include "gl/glut.h"
#include "Vector3D.h"

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
	void setcolor(unsigned char _red, unsigned char _green, unsigned char _blue) {
		red = _red;
		green = _green;
		blue = _blue;
	}
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
enum DIRECTION { FRONT, BACK, RIGHT, LEFT };

class ObjProp
{
public:
	ObjProp();
	~ObjProp();
	Vec3f Position;
	CVertex BoundingBox[4];
	CAngle Angle;
	float m_scale;

	void initBB();
	void DrawBB();

	CVertex * GetBB();
	bool isCollide(CVertex * P);
};

