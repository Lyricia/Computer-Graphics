#include "Ball.h"
#include <iostream>

#define PI			3.14159265359

CBall::CBall()
{
	for (int i = 0; i < 4; i++)
		m_Matrix[i * 4 + i] = 1;

	Position.x = rand() % 30;
	Position.y = rand() % 30;
	Position.z = rand() % 30;

	if (rand() % 2)		MoveVector.x = 1;
	else				MoveVector.x = -1;
	if (rand() % 2)		MoveVector.y = 1;
	else				MoveVector.y = -1;
	if (rand() % 2)		MoveVector.z = 1;
	else				MoveVector.z = -1;
	MoveVector = MoveVector *(rand() % 5)* 0.3;
	color.setcolor(100, 100, 100);
}

CBall::~CBall()
{
}

void CBall::Render(float scale)
{
	m_scale = scale;
	initBB();
	glPushMatrix();
	{
		//DrawBB();
		glTranslatef(Position.x, Position.y, Position.z);
		glMultMatrixf(m_Matrix);
		color.applycolor();
		glutSolidSphere(m_scale, 10, 10);
	}
	glPopMatrix();
}

void CBall::Rotate(float Speed, bool isMovex, bool isMovey, bool isMovez)
{
	glPushMatrix();
	glLoadIdentity();
	if (isMovey)
		glRotatef(Speed, 0, 1, 0);
	if (isMovez)
		glRotatef(Speed, 0, 0, 1);
	if (isMovex)
		glRotatef(Speed, 1, 0, 0);
	glMultMatrixf(m_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Matrix);
	glPopMatrix();
}

void CBall::Move(float speed)
{
	Position = Position + MoveVector * speed;
}

void CBall::ChangeDir(CColor * color)
{
	if (Position.x > 50)
	{
		MoveVector.x *= -1;
		color[3].flag = boolswitch(color[3].flag);
		if (color[3].flag)
			color[3].setcolor(255, 0, 0);
		else if (!color[3].flag)
			color[3].setcolor(255, 255, 0);
	}
	else if (Position.x < -50)
	{
		MoveVector.x *= -1;
		color[1].flag = boolswitch(color[1].flag);
		if (color[1].flag)
			color[1].setcolor(255, 100, 255);
		else if (!color[1].flag)
			color[1].setcolor(0, 255, 255);
	}
	if (Position.y > 50)
	{
		MoveVector.y *= -1;
		color[4].flag = boolswitch(color[4].flag);
		if (color[4].flag)
			color[4].setcolor(255, 115, 0);
		else if (!color[4].flag)
			color[4].setcolor(5, 255, 112);
	}
	else if (Position.y < -50)
	{
		MoveVector.y *= -1;
		color[5].flag = boolswitch(color[5].flag);
		if (color[5].flag)
			color[5].setcolor(255, 0, 110);
		else if (!color[5].flag)
			color[5].setcolor(23, 255, 10);
	}
	if (Position.z > 50)
	{
		MoveVector.z *= -1;
		color[0].flag = boolswitch(color[0].flag);
		if (color[0].flag)
			color[0].setcolor(1, 25, 66);
		else if (!color[0].flag)
			color[0].setcolor(1, 1, 255);
	}
	else if (Position.z < -50)
	{
		MoveVector.z *= -1;
		color[2].flag = boolswitch(color[2].flag);
		if (color[2].flag)
			color[2].setcolor(255, 0, 66);
		else if (!color[2].flag)
			color[2].setcolor(11, 1, 223);
	}
}

