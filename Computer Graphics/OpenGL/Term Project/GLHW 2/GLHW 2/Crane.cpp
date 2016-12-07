#include "Crane.h"
//#include "Ball.h"
#include "gl/glut.h"

CCrane::CCrane()
{
	bottomangle = 0;
	middleanglex = 0;
	middleangley = 0;
	topanglex = 0;
	topanglez = 0;
	m_scale = 40;
	xdir = 1;
	zdir = 1;
}

CCrane::~CCrane()
{
}

void CCrane::moveCrane(float speed)
{
	if (Position.x > 400)			xdir = -1;
	else if (Position.x < -400)		xdir = 1;

	if (xdir == 1)			Position.x += speed;
	else if (xdir == -1)	Position.x -= speed;
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
		glTranslatef(Position.x, Position.y, Position.z);

		glRotatef(angle, 1, 0, 0);
		glPushMatrix();
		{
			glPushMatrix();
			{
				glTranslatef(30, -20, -25);
				wheel[0].Render(20);
				glTranslatef(0, 0, 50);
				wheel[1].Render(20);
				glTranslatef(-60, 0, 0);
				wheel[2].Render(20);
				glTranslatef(0, 0, -50);
				wheel[3].Render(20);
			}
			glPopMatrix();

			glRotatef(bottomangle, 0, 1, 0);
			glScalef(1, 0.5, 1);
			glColor3f(1.0, 0.0, 0);
			glutSolidCube(80);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
