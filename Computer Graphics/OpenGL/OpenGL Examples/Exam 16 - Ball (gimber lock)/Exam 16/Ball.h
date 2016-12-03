#pragma once
#include<gl\glut.h>
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

class CBall
{
public:
	CBall();
	~CBall();

private:
	CAngle angle;
	CVertex Vertex;
	float m_radius;
	float m_Matrix[16];

public:
	void Render(float scale);
	void SetRotate(float pitch, float yaw, float roll);
	void Move(float Speed, bool isMovex, bool isMovey, bool isMovez);
	void setcolor(unsigned char red, unsigned char green, unsigned char blue) {
		Vertex.color.red = red;
		Vertex.color.green = green;
		Vertex.color.blue = blue;
	}
};
