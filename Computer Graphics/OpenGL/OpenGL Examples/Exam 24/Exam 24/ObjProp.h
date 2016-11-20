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
	bool flag;

	void applycolor() { glColor3f(red / 255.0f, green / 255.0f, blue / 255.0f); }
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

class ObjProp
{
public:
	ObjProp();
	~ObjProp();
public:
	Vec3f		Position;
	CVertex		BoundingBox[4];
	CAngle		Angle;
	CColor		color;
	float		m_scale;

	void		initBB();
	void		DrawBB();
	CVertex *	GetBB();
	bool		isCollide(CVertex * P);
};

