#include "Ball.h"

#define PI			3.14159265359

CBall::CBall()
{
	for (int i = 0; i < 4; i++)
		m_Matrix[i * 4 + i] = 1;
	Color.setcolor(0, 255, 255);
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
		DrawBB();
		glTranslatef(Position.x, Position.y, Position.z);
		//angle.Rotate();
		glMultMatrixf(m_Matrix);
		Color.applycolor();
		glutSolidSphere(m_scale, 10, 10);
	}
	glPopMatrix();
}

void CBall::SetRotate(float pitch, float yaw, float roll)
{
	Angle.pitch = pitch;
	Angle.roll = roll;
	Angle.yaw = yaw;
}

void CBall::Move(float Speed, bool isMovex, bool isMovey, bool isMovez)
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

	if (isMovex)
	{
		Angle.pitch += Speed;
		if (Position.z < 400 && Position.z > -400)
			Position.z += 2 * PI * m_scale * Speed / 360;
		if (Position.z > 400) Position.z = 399.9;
		if (Position.z < -400) Position.z = -399.9;
	}
	if (isMovez)
	{
		Angle.roll += Speed;
		if (Position.x < 400 && Position.x > -400)
			Position.x -= 2 * PI * m_scale * Speed / 360;
		if (Position.x > 400) Position.x = 399.9;
		if (Position.x < -400) Position.x = -399.9;
	}
	initBB();
}

