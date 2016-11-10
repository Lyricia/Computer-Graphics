#include "Ball.h"

CBall::CBall()
{
}


CBall::~CBall()
{
}

void CBall::movex(int angle)
{
	glPushMatrix();
	{
		glRotatef(angle, 1, 0, 0);
		glTranslatef(10, 0, 0);
		glColor3f(1, 0, 0);
		glutWireSphere(50, 10, 10);
	}
	glPopMatrix();
}


void CBall::movey(int angle)
{
}

void CBall::movez(int angle)
{
	glPushMatrix();
	{
		glRotatef(angle, 0, 0, 1);
		glTranslatef(10, 0, 0);
		glColor3f(1, 0, 0);
		glutWireSphere(50, 10, 10);
	}
	glPopMatrix();
}
