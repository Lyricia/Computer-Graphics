#include <iostream>
#include <time.h>
#include <gl\glut.h>
#include "Torus.h"
#include "Plane.h"

#define W_Width		800
#define W_Height	600
#define W_Depth		800
#define PI			3.14159265359

GLvoid RegesterCallBack();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLvoid Timer(int);
GLvoid Keydown(unsigned char, int, int);
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid init(GLvoid);

bool boolswitch(bool chker);

void initobj();

GLvoid DrawLines();
GLvoid DrawSpace();
GLvoid DrawPolygon(GLvoid);

float cameraz;
float camerax;

CTorus Torus[10];
CPlane* Plane[5];

float speed[10];
int toruscount;
int planecount;
int objcount;
bool IsCull;
bool IsDepth;

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

	for (int i = 0; i < 5; i++)
	{
		Plane[i] = nullptr;
		Plane[i] = new CPlane(i);
	}

	initobj();

	cameraz =-1000;
	camerax = 1;
}

GLvoid RegesterCallBack()
{
	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMove);
	glutKeyboardFunc(Keydown);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(10, Timer, 1);
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 10000);
	glTranslatef(0.0, 0.0, cameraz);
	gluLookAt(
		0, camerax, 0,
		0, 0, 1,
		0, 1, 0
	);

	glMatrixMode(GL_MODELVIEW);
	const int TORUSSIZE = 20;
	glPushMatrix();
	{
		DrawSpace();
		for (int i = 0; i < planecount; i++) {
			Plane[i]->Render();
		}
		for (int i = 0; i < toruscount; i++){
			glPushMatrix(); 
			{
				Torus[i].Render(20);
			}
			glPopMatrix();
		}
	}
	glPopMatrix();

	glutSwapBuffers();
}


GLvoid DrawLines()
{
	glColor3f(0.f, 0.f, 1.f);
	glBegin(GL_LINES);
	glVertex3f(-W_Width, 0.0, 0.0);
	glVertex3f(W_Width, 0.0, 0.0);

	glVertex3f(0.0, -W_Height, 0.0);
	glVertex3f(0.0, W_Height, 0.0);

	glVertex3f(0.0, 0.0, -W_Depth);
	glVertex3f(0.0, 0.0, W_Depth);
	glEnd();
}

GLvoid DrawSpace()
{
	glColor3f(1.0, 1.0, 0);
	glPushMatrix();
	glTranslatef(0, -20, 0);
	glScalef(3, 0.01, 3);
	glutSolidCube(300);
	glPopMatrix();

	glColor3f(0.f, 0.f, 1.f);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0, 0.0);
	glVertex3f(0.0, 400, 0.0);
	glEnd();
}
GLvoid DrawPolygon(GLvoid)
{

}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -500);

	//glMatrixMode(GL_MODELVIEW);

	gluLookAt(
		0.0, 1, 0,			// eye
		0.0, 0, 1,			// center
		0.0, 1.0, 0.0);			// up
}


GLvoid Keydown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;

	case 'i':
		init();
		break;

	case 't':
		camerax += 0.1;
		break;
	case 'g':
		camerax -= 0.1;
		break;

	case 'a':
		objcount++;
		if (objcount % 3 == 0) {
			planecount++;
			break;
		}
		else toruscount++;
		if (objcount > 15)
		{
			toruscount = 0;
			planecount = 0;
			objcount = 0;
			initobj();
		}
		break;

	case 'r':
		cameraz += 10;
		break;
	case 'f':
		cameraz -= 10;
		break;

	case '1':
		IsCull = boolswitch(IsCull);
		if (IsCull)			glEnable(GL_CULL_FACE);
		else if (!IsCull)	glDisable(GL_CULL_FACE);
		break;

	case '2':
		IsDepth = boolswitch(IsDepth);
		if (IsDepth)		glEnable(GL_DEPTH_TEST);
		else if (!IsDepth)	glDisable(GL_DEPTH_TEST);
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
	for (int i = 0; i < toruscount; i++) {
		speed[i] += 2;
		Torus[i].Move(speed[i]);
	}
	for (int i = 0; i < planecount; i++) {
		Plane[i]->Move(2);
	}
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

bool boolswitch(bool chker)
{
	if (chker == true)			return false;
	else if (chker == false)	return true;
	return false;
}

void initobj()
{
	for (int i = 0; i < 10; i++) {
		speed[i] = 0;
		Torus[i].init(i);
	}
	for (int i = 0; i < 5; i++) {
		Plane[i]->init(i);
	}
	toruscount = 0;
	planecount = 0;
	objcount = 0;
}