#include "Ball.h"

#define PI			3.14159265359

CBall::CBall()
{
	for (int i = 0; i < 4; i++)
		m_Matrix[i * 4 + i] = 1;
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
		glTranslatef(Vertex.x, Vertex.y, Vertex.z);
		//angle.Rotate();
		glMultMatrixf(m_Matrix);
		Vertex.color.applycolor();
		glutWireSphere(m_scale, 10, 10);
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
		Vertex.z += 2 * PI * m_scale * Speed / 360;
	}
	if (isMovez)
	{
		Angle.roll += Speed;
		Vertex.x -= 2 * PI * m_scale * Speed / 360;
	}
	initBB();
}

