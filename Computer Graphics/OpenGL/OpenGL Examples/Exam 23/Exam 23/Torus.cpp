#include "Torus.h"
#include <GL/glut.h>

CTorus::CTorus()
{
	Vertex.color.setcolor(0, 0, 255);
}

void CTorus::Render(int scale)
{
	glPushMatrix();
	Vertex.color.applycolor();
	Angle.Rotate();
	glTranslatef(scale*3, Vertex.y, 0);
	glRotatef(90, 1, 0, 0);
	glutWireTorus(scale, scale * 4, 10, 10);
	glPopMatrix();
}

void CTorus::Move(float speed)
{
	if (Vertex.y > limit)
	{
		Angle.yaw = speed;
		Vertex.y = 400 - speed;
	}
}

void CTorus::SetLimit(int count)
{
	limit = count * 40;
}

void CTorus::init(int _id)
{
	Vertex.y = 400;
	m_id = _id;
	SetLimit(m_id);
}
