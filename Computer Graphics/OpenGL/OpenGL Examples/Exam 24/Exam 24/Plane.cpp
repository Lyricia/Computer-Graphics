#include <iostream>
#include "Plane.h"

CPlane::CPlane()
{
	for (int i = 0; i < 4; i++)
		m_Matrix[i * 4 + i] = 1;
}

CPlane::~CPlane()
{
}

void CPlane::SetPlane()
{
	
	SetNormalVector(Vec3f(50.0f, 0.0f, 50.0f),Vec3f(-50.0f, 0.0f, 50.0f));
}

void CPlane::SetNormalVector(Vec3f a, Vec3f b)
{
	const Vec3f origin(0, 0, 0);
	m_NormalVector = CrossProduct((origin - a), (origin - b));
	float _x = m_NormalVector.x * m_Matrix[0] + m_NormalVector.y * m_Matrix[1] + m_NormalVector.z * m_Matrix[2];
	float _y = m_NormalVector.x * m_Matrix[4] + m_NormalVector.y * m_Matrix[5] + m_NormalVector.z * m_Matrix[6];
	float _z = m_NormalVector.x * m_Matrix[8] + m_NormalVector.y * m_Matrix[9] + m_NormalVector.z * m_Matrix[10];
	m_NormalVector = { _x, _y, _z };
	m_NormalVector.Normalize();
}

Vec3f CPlane::GetNormalVector()
{ 
	return m_NormalVector;
}
 
float CPlane::GetPosition(float x)
{
	return (-(m_NormalVector.x * x) / m_NormalVector.y);
}

void CPlane::VectorRotate(float Speed, bool isMovex, bool isMovey, bool isMovez)
{
	glMatrixMode(GL_MODELVIEW);
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
	angle += Speed;
}

void CPlane::Render()
{
	glPushMatrix();
	{
		glColor3f(1.f, 0.f, 0.f);
		glTranslatef(Position.x, Position.y, Position.z);
		glRotated(-angle, 0, 0, 1);
		glScalef(1, 0.01, 1);
		glutSolidCube(100);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glLoadIdentity();
		glColor3f(0.f, 0.f, 1.f);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(m_NormalVector.x, m_NormalVector.y, m_NormalVector.z);
		glEnd();
	}
	glPopMatrix();
}

