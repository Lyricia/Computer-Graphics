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
	m_radius = scale;
	glPushMatrix();
	{
		glTranslatef(Vertex.x, Vertex.y, Vertex.z);
		//angle.Rotate();
		glMultMatrixf(m_Matrix);
		Vertex.color.applycolor();
		glutWireSphere(m_radius, 10, 10);
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
		if (Vertex.z < 100 && Vertex.z > -100)
			Vertex.z += 2 * PI * m_radius * Speed / 360;
		if (Vertex.z > 100) Vertex.z = 99.9;
		if (Vertex.z < -100) Vertex.z = -99.9;
	}
	if (isMovez)
	{
		Angle.roll += Speed;
		if (Vertex.x < 100 && Vertex.x > -100)
			Vertex.x -= 2 * PI * m_radius * Speed / 360;
		if (Vertex.x > 100) Vertex.x = 99.9;
		if (Vertex.x < -100) Vertex.x = -99.9;
	}
}