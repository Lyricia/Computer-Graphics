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
		if (Position.z < 150 && Position.z > -150)
			Position.z += 2 * PI * m_scale * Speed / 360;
	}
	if (isMovez)
	{
		Angle.roll += Speed;
		if (Position.x < 150 && Position.x > -150)
			Position.x -= 2 * PI * m_scale * Speed / 360;
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
	else if (m_SphereScaleSize <1 )		ydir = 1;

	if (ydir == 1)
		m_SphereScaleSize += scale;
	else if(ydir == -1)
		m_SphereScaleSize -= scale;
}

void CObject::RectTreeRender()
{
	glPushMatrix();
	{
		Color.setcolor(255, 0, 0);
		Color.applycolor();
		glTranslatef(0, 75, 0);
		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glutSolidCube(50);
		}
		glPopMatrix();

		glPushMatrix();
		{
			Color.setcolor(0, 255, 0);
			Color.applycolor();
			glRotatef(m_RectTopAngle, 0, 1, 0);
			glTranslatef(0, 75, 0);
			glScalef(1, 0.2, 1);
			glutSolidCube(100);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CObject::SphereTreeRender()
{
	glPushMatrix();
	{
		Color.setcolor(255, 0, 0);
		Color.applycolor();
		glTranslatef(0, 75, 0);
		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glutSolidCube(50);
		}
		glPopMatrix();

		glPushMatrix();
		{
			Color.setcolor(0, 255, 0);
			Color.applycolor();
			glTranslatef(0, 75, 0);
			glScalef(m_SphereScaleSize, m_SphereScaleSize, m_SphereScaleSize);
			glutSolidSphere(50, 50, 50);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CObject::TorusBuildingRender()
{
	glPushMatrix();
	{
		Color.setcolor(255, 0, 0);
		Color.applycolor();
		glTranslatef(0, 75, 0);
		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glutSolidCube(50);
		}
		glPopMatrix();

		glPushMatrix();
		{
			Color.setcolor(0, 255, 0);
			Color.applycolor();
			glTranslatef(0, 75 + m_TorusMovePos, 0);
			glRotatef(90, 1, 0, 0);
			glutWireTorus(10, 50, 10, 10);
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

void CObject::ConeBuildingRender()
{
	glPushMatrix();
	{
		glPushMatrix();
		{
			Color.setcolor(255, 0, 0);
			Color.applycolor();
			glRotatef(-90, 1, 0, 0);
			
			glScalef(m_ConeScaleSize, m_ConeScaleSize, m_ConeScaleSize);
			glutWireCone(50, 100, 10, 10);
		}
		glPopMatrix();
		glPushMatrix();
		{
			Color.setcolor(255, 0, 0);
			Color.applycolor();
			glTranslatef(0, 100, 0);
			glRotatef(90, 1, 0, 0);
			glScalef(1 - m_ConeScaleSize, 1 - m_ConeScaleSize, 1 - m_ConeScaleSize);
			glutWireCone(50, 100, 10, 10);
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

void CObject::DoorBuildingRender()
{
	glPushMatrix();
	{
		Color.setcolor(255, 0, 0);
		Color.applycolor();
		glTranslatef(0, 75, 0);
		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glTranslated(50, 0, 0);
			glutSolidCube(50);
			glTranslated(-100, 0, 0);
			glutSolidCube(50);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0, 50, 0);
			glutSolidCube(50);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glTranslated(-50 + m_DoorPos, 0, 0);
			glutSolidCube(50);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glScalef(1, 3, 1);
			glTranslated(50 - m_DoorPos, 0, 0);
			glutSolidCube(50);
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

void CObject::PyramidRender()
{
	glPushMatrix();
	{
		Color.setcolor(255, 0, 255);
		Color.applycolor();
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(100, 100, 4, 4);
	}
	glPopMatrix();
}