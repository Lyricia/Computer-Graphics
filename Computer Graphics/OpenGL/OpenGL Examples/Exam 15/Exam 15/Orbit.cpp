#include "Orbit.h"
#include<gl\glut.h>
#include<iostream>
#include<time.h>

COrbit::COrbit()
{
}


COrbit::~COrbit()
{
}

void COrbit::DrawOrbit(int radius)
{
	glPushMatrix();
	{
		glRotatef(90, 1, 0, 0);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 360; i++) {
			Circle({ 0,0,0 }, radius, i);
		}
		glEnd();
	}
	glPopMatrix();
}

void COrbit::DrawPlanet(int orbitradius, int sphereradius, int angle,int shaftangle)
{
	glTranslatef(cos(angle * (3.141592 / 180)) * 3 * orbitradius, 0, sin(angle * (3.141592 / 180)) * 3 * orbitradius);
	glPushMatrix();
	{
		glRotatef(shaftangle, 0, 0, 1);
		glRotatef(angle, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glutWireSphere(sphereradius, 10, 10);
	}
	glPopMatrix();
}

GLvoid COrbit::Circle(Vertex P, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex3f(cos(angle)*radius + P.x, sin(angle)*radius + P.y,0);
}