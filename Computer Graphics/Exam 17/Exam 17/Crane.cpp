#include "Crane.h"
#include "gl/glut.h"

CCrane::CCrane()
{
	bottomangle = 0;
	middleanglex = 0;
	middleangley = 0;
	topanglex = 0;
	topanglez = 0;
}


CCrane::~CCrane()
{
}

void CCrane::moveCrane(float speed)
{
	Vertex.x += speed;
	if (Vertex.x > 100)
		Vertex.x = 100;
	else if (Vertex.x < -100)
		Vertex.x = -100;
}

void CCrane::moveBottom(int angle, bool isX, bool isY, bool isZ)
{
	bottomangle += angle;
}

void CCrane::moveMiddle(int angle, bool isX, bool isY, bool isZ)
{
	if (isX)	middleanglex += angle;
	if (isY)	middleangley += angle;
}

void CCrane::moveTop(int angle, bool isX, bool isY, bool isZ)
{
	if (isX)	topanglex += angle;
	if (isZ)	topanglez += angle;
}

void CCrane::Render()
{
	glPushMatrix();
	{
		glTranslatef(0, 20, 0);
		glTranslatef(Vertex.x, 0, 0);
		glRotatef(bottomangle, 0, 1, 0);
		glScalef(1, 0.5, 0.8);
		glColor3f(1.0, 0.0, 0);
		glutSolidCube(80);
		glTranslatef(0, 40, 0);
		glPushMatrix();
		{
			glRotatef(middleanglex, 1, 0, 0);
			glRotatef(middleangley, 0, 1, 0);
			glTranslatef(0, 25, 0);
			glScalef(0.5, 1.5, 1);
			glColor3f(0.0, 0.0, 1);
			glutSolidCube(50);
			glTranslatef(0, 25, 0);
			glPushMatrix();
			{
				glRotatef(topanglex, 1, 0, 0);
				glRotatef(topanglez, 0, 0, 1);
				glTranslatef(0, 25, 0);
				glScalef(0.5, 1.0, 0.5);
				glColor3f(1.0, 0.0, 1.0);
				glutSolidCube(50);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}
