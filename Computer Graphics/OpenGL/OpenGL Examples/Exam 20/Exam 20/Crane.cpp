#include "Crane.h"

#define PI			3.14159265359

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
	if (Vertex.x > 100)			xdir = -1;
	else if (Vertex.x < -100)	xdir = 1;

	if (xdir == 1)			Vertex.x += 2 * PI * 20 * speed * 3 / 360;
	else if (xdir == -1)	Vertex.x -= 2 * PI * 20 * speed * 3 / 360;

	for (int i = 0; i < 4; i++)
		wheel[i].Move(-speed * 3 * xdir, false, false, true);
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
		initBB();
		DrawBB();
		glPushMatrix();
		{
			glTranslatef(0, -20, -200);
			glTranslatef(30, 0, -25);
			wheel[0].Render(20);
			glTranslatef(0, 0, 50);
			wheel[1].Render(20);
			glTranslatef(-60, 0, 0);
			wheel[2].Render(20);
			glTranslatef(0, 0, -50);
			wheel[3].Render(20);
		}
		glPopMatrix();

		glTranslatef(Vertex.x, 0, Vertex.z);
		glPushMatrix();
		{
			glRotatef(bottomangle, 0, 1, 0);
			glScalef(1, 0.5, 1);
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
	glPopMatrix();
}
