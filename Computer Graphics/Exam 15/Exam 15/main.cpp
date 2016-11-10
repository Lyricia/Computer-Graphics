#include <iostream>
#include <time.h>
#include "Orbit.h"

#include <gl\glut.h>

#define W_Width		800
#define W_Height	600
#define W_Depth		800

GLvoid RegesterCallBack();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLvoid Timer(int);
GLvoid Keydown(unsigned char, int, int);
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid init(GLvoid);

GLvoid DrawLines();
GLvoid DrawSpace();
GLvoid DrawPolygon(GLvoid);

int angle = 0;
int angle2 = 0;
int angle3 = 0;

float camera_x;
float camera_y;
float camera_z;

COrbit Orbit;

void main(int, char *)
{
	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	RegesterCallBack();

	glutMainLoop();
}

GLvoid init(GLvoid)
{
	srand(unsigned(time(NULL)));
	camera_x = 0.0;
	camera_y = 0.0;
	camera_z = 0.0;
}

GLvoid RegesterCallBack()
{
	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMove);
	glutKeyboardFunc(Keydown);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	//glutTimerFunc(10, Timer, 1);
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	{
		glColor3f(1, 1, 1);
		glRotatef(45, 0, 0, 1);
		Orbit.DrawOrbit(120);
		glPushMatrix();
		{
			Orbit.DrawPlanet(40, 30, angle,-45);
			glRotatef(-45, 0, 0, 1);
			Orbit.DrawOrbit(90);
			Orbit.DrawPlanet(30, 10, angle,0);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glColor3f(1, 1, 1);
		glRotatef(-45, 0, 0, 1);
		Orbit.DrawOrbit(120);
		glPushMatrix();
		{
			Orbit.DrawPlanet(40, 30, angle2, 45);
			glRotatef(45, 0, 0, 1);
			Orbit.DrawOrbit(90);
			Orbit.DrawPlanet(30, 10, angle2, 0);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glColor3f(1, 1, 1);
		Orbit.DrawOrbit(120);
		glPushMatrix();
		{
			Orbit.DrawPlanet(40, 30, angle3,0 );
			Orbit.DrawOrbit(90);
			Orbit.DrawPlanet(30, 10, angle3, 0);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glutSwapBuffers();
}

GLvoid DrawLines()
{
	glColor3f(1.f, 0.f, 0.f);			// x axis 
	glBegin(GL_LINES);
	glVertex3f(-W_Width, 0.0, 0.0);
	glVertex3f(W_Width, 0.0, 0.0);
	
	glColor3f(0.f, 1.f, 0.f);			// y axis
	glVertex3f(0.0, -W_Height, 0.0);
	glVertex3f(0.0, W_Height, 0.0);
	
	glColor3f(0.f, 0.f, 1.f);			// z axis
	glVertex3f(0.0, 0.0, -W_Depth);
	glVertex3f(0.0, 0.0, W_Depth);
	glEnd();
}

GLvoid DrawSpace()
{
	glColor3f(1.0, 1.0, 0);
	glPushMatrix();
	glScalef(1, 0.01, 1);
	glutSolidCube(200);
	glPopMatrix();
}
GLvoid DrawPolygon(GLvoid)
{
	glColor3f(1, 0, 0);
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -300.0);

	glMatrixMode(GL_MODELVIEW);

	gluLookAt(
		camera_x, 0.5, camera_z,			// eye
		0.0, 0.0, 1.0,							// center
		0.0, 1.0, 0.0);							// up
}


GLvoid Keydown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;

	case 'r':
		init();
		break;

	case 'w':
		camera_y += 0.1;
		break;

	case 's':
		camera_y -= 0.1;
		break;

	case 'd':
		angle += 10;
		angle2 += 3;
		angle3 += 5;
		break;

	case 'e':
		break;
	}

	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y)
{

}

GLvoid MouseEvent(int button, int state, int x, int y)
{
	glutPostRedisplay();
}


GLvoid Timer(int val)
{
	//angle++;
	//angle2 -= 1;
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}