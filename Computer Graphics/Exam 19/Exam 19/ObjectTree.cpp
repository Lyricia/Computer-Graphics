#include "ObjectTree.h"
#define PI			3.14159265359


CObjectTree::CObjectTree()
{
	ydir = 1;
}


CObjectTree::~CObjectTree()
{
}

void CObjectTree::Move(float Speed, bool isMovex, bool isMovey, bool isMovez)
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
		if (Vertex.z < 150 && Vertex.z > -150)
			Vertex.z += 2 * PI * m_scale * Speed / 360;
	}
	if (isMovez)
	{
		Angle.roll += Speed;
		if (Vertex.x < 150 && Vertex.x > -150)
			Vertex.x -= 2 * PI * m_scale * Speed / 360;
	}
	initBB();
}

void CObjectTree::rotateRect(int angle)
{
	m_RectTopAngle += angle;
}

void CObjectTree::moveSphere(int pos)
{
	if (m_SphereTopPos > 50)			ydir = -1;
	else if (m_SphereTopPos < 0)		ydir = 1;

	if (ydir = 1)
		m_SphereTopPos += pos;
	else if(ydir = -1)
		m_SphereTopPos -= pos;
}

void CObjectTree::RectTreeRender()
{
	glPushMatrix();
	{
		Vertex.color.setcolor(255, 0, 0);
		Vertex.color.applycolor();
		glTranslatef(0, 75, 0);
		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glutSolidCube(50);
		}
		glPopMatrix();

		glPushMatrix();
		{
			Vertex.color.setcolor(0, 255, 0);
			Vertex.color.applycolor();
			glRotatef(m_RectTopAngle, 0, 1, 0);
			glTranslatef(0, 75, 0);
			glScalef(1, 0.2, 1);
			glutSolidCube(100);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CObjectTree::SphereTreeRender()
{
	glPushMatrix();
	{
		Vertex.color.setcolor(255, 0, 0);
		Vertex.color.applycolor();
		glTranslatef(0, 75, 0);
		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glutSolidCube(50);
		}
		glPopMatrix();

		glPushMatrix();
		{
			Vertex.color.setcolor(0, 255, 0);
			Vertex.color.applycolor();
			glTranslatef(0, 75, 0);
			glutWireSphere(50, 10, 10);
		}
		glPopMatrix();
	}
	glPopMatrix();
}