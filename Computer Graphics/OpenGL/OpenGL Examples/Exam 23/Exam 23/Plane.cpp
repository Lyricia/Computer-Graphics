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
	glutSolidCube(250);
	glPopMatrix();
}

void CPlane::Move(float speed)
{
	if (Vertex.y > limit)
	{
		Angle.yaw += speed;
		Vertex.y -= speed;
	}
}

void CPlane::SetLimit(int count)
{
	limit =(count +1)  * 80 - 20;
}

void CPlane::init(int _id)
{
	Vertex.y = 400;
	m_id = _id;
	SetLimit(m_id);
}

