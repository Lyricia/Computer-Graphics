#include <iostream>
#include <time.h>
#include <gl\glut.h>
#include "Camera.h"

#define W_Width		800
#define W_Height	600
#define W_Depth		800
#define PI			3.14159265359

GLvoid RegesterCallBack();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLvoid Timer(int);
bool boolswitch(bool chker);
GLvoid Keydown(unsigned char, int, int);
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid init(GLvoid);

GLvoid DrawLines();
GLvoid DrawSpace();
GLvoid DrawPolygon(GLvoid);

float cameraz;
float camerax;

float angle;
float angle2;
float angle3;

bool IsSmooth;
bool IsDepth;
bool IsCull;

CCamera Camera;

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

	cameraz = -300;
	camerax = 1;

	IsSmooth = true;
	IsDepth = true;
	IsCull = true;
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
	
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(110.0, 1.0, 1.0, 10000);
	//glTranslatef(0.0, 0.0, cameraz);
	//gluLookAt(
	//	0, camerax, 0,
	//	0, 0, 1,
	//	0, 1, 0
	//);
	Camera.SetLookVector(0, 0);
	Camera.SetCamera();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		DrawPolygon();
	}
	glPopMatrix();

	glutSwapBuffers();
}

GLvoid DrawLines()
{
	glColor3f(1.f, 1.f, 1.f);
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
	glScalef(3, 0.01, 3);
	glutSolidCube(300);
	glPopMatrix();
}
GLvoid DrawPolygon(GLvoid)
{
	glRotatef(angle, 0, 1, 0);
	glPushMatrix();
	{
		glTranslatef(-50, -50, 50);
		//1
		glPushMatrix();
		{
			if (IsSmooth)					glShadeModel(GL_SMOOTH);
			else if (!IsSmooth)				glShadeModel(GL_FLAT);
			glBegin(GL_QUADS);
			glColor3f(0.0f, 1.0f, 0.0f);		//green
			glVertex3f(0.0, 100.0, 0.0);
			glColor3f(1.0f, 1.0f, 0.0f);		//yellow
			glVertex3f(100.0, 100.0, 0.0);
			glColor3f(1.0f, 0.0f, 0.0f);		//red
			glVertex3f(100.0, 0.0, 0.0);
			glColor3f(0.0f, 0.0f, 0.0f);		//black	
			glVertex3f(0.0, 0.0, 0.0);
			glEnd();
		}
		glPopMatrix();
		//2
		glPushMatrix();
		{
			if (IsSmooth)					glShadeModel(GL_SMOOTH);
			else if (!IsSmooth)				glShadeModel(GL_FLAT);
			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 1.0f);		//blue
			glVertex3f(0.0, 0.0, -100.0);
			glColor3f(0.0f, 1.0f, 1.0f);		//cyan
			glVertex3f(0.0, 100.0, -100.0);
			glColor3f(0.0f, 1.0f, 0.0f);		//green
			glVertex3f(0.0, 100.0, 0.0);
			glColor3f(0.0f, 0.0f, 0.0f);		//black	
			glVertex3f(0.0, 0.0, 0.0);
			glEnd();
		}
		glPopMatrix();
		//3 front
		glPushMatrix();
		{
			glTranslatef(0, 0, -100);
			glRotatef(-angle3, 1, 0, 0);
			glPushMatrix();
			{
				if (IsSmooth)					glShadeModel(GL_SMOOTH);
				else if (!IsSmooth)				glShadeModel(GL_FLAT);
				glBegin(GL_QUADS);
				glColor3f(1.0f, 1.0f, 1.0f);		//white
				glVertex3f(100.0, 100.0, 0);
				glColor3f(0.0f, 1.0f, 1.0f);		//cyan
				glVertex3f(0.0, 100.0, 0);
				glColor3f(0.0f, 0.0f, 1.0f);		//blue
				glVertex3f(0.0, 0.0, 0);
				glColor3f(0.0f, 0.0f, 1.0f);		//magenta
				glVertex3f(100.0, 0.0, 0);
				glEnd();
			}
			glPopMatrix();
		}
		glPopMatrix();
		//4
		glPushMatrix();
		{
			if (IsSmooth)					glShadeModel(GL_SMOOTH);
			else if (!IsSmooth)				glShadeModel(GL_FLAT);
			glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 0.0f);		//yellow
			glVertex3f(100.0, 100.0, 0.0);
			glColor3f(1.0f, 1.0f, 1.0f);		//white
			glVertex3f(100.0, 100.0, -100.0);
			glColor3f(0.0f, 0.0f, 1.0f);		//magenta
			glVertex3f(100.0, 0.0, -100.0);
			glColor3f(1.0f, 0.0f, 0.0f);		//red
			glVertex3f(100.0, 0.0, 0.0);
			glEnd();
		}
		glPopMatrix();
		//5 top
		glPushMatrix();
		{
			glTranslatef(0, 100, 0);
			glRotatef(angle2, 0, 0, 1);
			glPushMatrix();
			{
				if (IsSmooth)					glShadeModel(GL_SMOOTH);
				else if (!IsSmooth)				glShadeModel(GL_FLAT);
				glBegin(GL_QUADS);
				glColor3f(1.0f, 1.0f, 0.0f);		//yellow
				glVertex3f(100.0, 0, 0.0);
				glColor3f(0.0f, 1.0f, 0.0f);		//green
				glVertex3f(0.0, 0, 0.0);
				glColor3f(0.0f, 1.0f, 1.0f);		//cyan
				glVertex3f(0.0, 0, -100.0);
				glColor3f(1.0f, 1.0f, 1.0f);		//white
				glVertex3f(100.0, 0, -100.0);
				glEnd();
			}
			glPopMatrix();
		}
		glPopMatrix();
		//6 bottom
		glPushMatrix();
		{
			if (IsSmooth)					glShadeModel(GL_SMOOTH);
			else if (!IsSmooth)				glShadeModel(GL_FLAT);
			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);		//red
			glVertex3f(100.0, 0.0, 0.0);
			glColor3f(0.0f, 0.0f, 1.0f);		//magenta
			glVertex3f(100.0, 0.0, -100.0);
			glColor3f(0.0f, 0.0f, 1.0f);		//blue
			glVertex3f(0.0, 0.0, -100.0);
			glColor3f(0.0f, 0.0f, 0.0f);		//black	
			glVertex3f(0.0, 0.0, 0.0);
			glEnd();
		}
		glPopMatrix();

	}
	glPopMatrix();
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

	case 'a':
		camerax += 1;
		break;
	case 'd':
		camerax -= 1;
		break;
		
	case 't':
		camerax += 0.1;
		break;
	case 'g':
		camerax -= 0.1;
		break;

	case 'r':
		cameraz += 10;
		break;
	case 'f':
		cameraz -= 10;
		break;

	case 'y':
		angle += 5;
		break;
	case 'u':
		angle -= 5;
		break;
	case 'o':
		if (angle2 <90)
			angle2 += 1;
		break;
	case 'O':
		if (angle2 >0)
			angle2 -= 1;
		break;
	case 'k':
		if (angle3 <90)
			angle3 += 1;
		break;
	case 'K':
		if (angle3 >0)
			angle3 -= 1;
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

	case '3':
		IsSmooth = boolswitch(IsSmooth);
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
	//angle += 0.1;
	if (angle > 360) angle = 0;

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

bool boolswitch(bool chker)
{
	if (chker == true)			return false;
	else if (chker == false)	return true;
	return false;
}