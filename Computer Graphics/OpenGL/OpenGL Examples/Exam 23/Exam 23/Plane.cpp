#include "Plane.h"

CPlane::CPlane(int id)
{
	m_id = id;
	SetLimit(m_id);
	Vertex.color.setcolor(255, 0, 0);
	Vertex.y = 400;
}

CPlane::~CPlane()
{
}

void CPlane::Render()
{
	glPushMatrix();
	Vertex.color.applycolor();
	Angle.Rotate();
	glTranslatef(0, Vertex.y, 0);
	glScalef(1, 0.01f, 1);
	glutSolidCube(100);
	glPopMatrix();
}

void CPlane::Move(float speed)
{
	if (Vertex.y > limit)
	{
		Angle.yaw += speed;
		Vertex.y = 400 - speed;
	}
}

void CPlane::SetLimit(int count)
{
	limit = count * 80;
}

void CPlane::ActivePlane()
{
	isActivated = true;
}
