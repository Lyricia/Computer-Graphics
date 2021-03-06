#include "Object.h"
#define PI			3.14159265359


CObject::CObject()
{
	ydir = 1;
	m_SphereScaleSize = 1;
}


CObject::~CObject()
{
}

void CObject::Move(float Speed, bool isMovex, bool isMovey, bool isMovez)
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

void CObject::rotateRect(int angle)
{
	m_RectTopAngle += angle;
}

void CObject::scaleSphere(float scale)
{
	if (m_SphereScaleSize > 1.5)			ydir = -1;
	else if (m_SphereScaleSize < 1)		ydir = 1;

	if (ydir == 1)
		m_SphereScaleSize += scale;
	else if(ydir == -1)
		m_SphereScaleSize -= scale;
}

void CObject::RectTreeRender(float scale)
{
	glPushMatrix();
	{
		Vertex.color.setcolor(255, 0, 0);
		Vertex.color.applycolor();
		glTranslatef(0, 75, 0);
		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glutSolidCube(scale);
		}
		glPopMatrix();

		glPushMatrix();
		{
			Vertex.color.setcolor(0, 255, 255);
			Vertex.color.applycolor();
			glRotatef(m_RectTopAngle, 0, 1, 0);
			glTranslatef(0, 75, 0);
			glScalef(1, 0.2, 1);
			glutSolidCube(scale*2);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CObject::SphereTreeRender(float scale)
{
	glPushMatrix();
	{
		Vertex.color.setcolor(255, 110, 0);
		Vertex.color.applycolor();
		glTranslatef(0, 75, 0);
		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glutSolidCube(scale);
		}
		glPopMatrix();

		glPushMatrix();
		{
			Vertex.color.setcolor(110, 255, 10);
			Vertex.color.applycolor();
			glTranslatef(0, 75, 0);
			glScalef(m_SphereScaleSize, m_SphereScaleSize, m_SphereScaleSize);
			glutWireSphere(scale, 10, 10);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CObject::TorusBuildingRender(float scale)
{
	glPushMatrix();
	{
		Vertex.color.setcolor(255,0, 255);
		Vertex.color.applycolor();
		glTranslatef(0, 75, 0);
		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glutSolidCube(scale);
		}
		glPopMatrix();

		glPushMatrix();
		{
			Vertex.color.setcolor(0, 255, 0);
			Vertex.color.applycolor();
			glTranslatef(0, 75 + m_TorusMovePos, 0);
			glRotatef(90, 1, 0, 0);
			glutWireTorus(scale/5, scale, 10, 10);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CObject::moveTorus(int speed)
{
	if (m_TorusMovePos > 25)			ydir = -1;
	else if (m_TorusMovePos <-25)			ydir = 1;

	if (ydir == 1)
		m_TorusMovePos += speed;
	else if (ydir == -1)
		m_TorusMovePos -= speed;
}

void CObject::ConeBuildingRender(float scale)
{
	glPushMatrix();
	{
		glPushMatrix();
		{
			Vertex.color.setcolor(0, 0, 255);
			Vertex.color.applycolor();
			glRotatef(-90, 1, 0, 0);
			
			glScalef(m_ConeScaleSize, m_ConeScaleSize, m_ConeScaleSize);
			glutWireCone(scale, 100, 10, 10);
		}
		glPopMatrix();
		glPushMatrix();
		{
			Vertex.color.setcolor(20, 255, 250);
			Vertex.color.applycolor();
			glTranslatef(0, 100, 0);
			glRotatef(90, 1, 0, 0);
			glScalef(1 - m_ConeScaleSize, 1 - m_ConeScaleSize, 1 - m_ConeScaleSize);
			glutWireCone(scale, 100, 10, 10);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CObject::scaleCone(float scale)
{
	if (m_ConeScaleSize > 1)			ydir = -1;
	else if (m_ConeScaleSize < 0)			ydir = 1;

	if (ydir == 1)
		m_ConeScaleSize += scale;
	else if (ydir == -1)
		m_ConeScaleSize -= scale;
}

void CObject::DoorBuildingRender(float scale)
{
	glPushMatrix();
	{
		Vertex.color.setcolor(255, 50, 255);
		Vertex.color.applycolor();
		glTranslatef(0, 75, 0);
		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glTranslated(50, 0, 0);
			glutSolidCube(scale);
			glTranslated(-100, 0, 0);
			glutSolidCube(scale);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0, 50, 0);
			glutSolidCube(scale);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glTranslated(-50 + m_DoorPos, 0, 0);
			glutSolidCube(scale);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glTranslated(50 - m_DoorPos, 0, 0);
			glutSolidCube(scale);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CObject::moveDoor(float speed)
{
	if (m_DoorPos > 25)			ydir = -1;
	else if (m_DoorPos < 0)			ydir = 1;

	if (ydir == 1)
		m_DoorPos += speed;
	else if (ydir == -1)
		m_DoorPos -= speed;
}

