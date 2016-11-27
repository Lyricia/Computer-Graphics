#include<iostream>
#include<time.h>
#include<gl\glut.h>
#include "Camera.h"

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

bool boolswitch(bool chker);
static float CATMULL_ROM_SPLINE(float u, float u_2, float u_3, float cntrl0, float cntrl1, float cntrl2, float cntrl3);
GLvoid DrawLines();
GLvoid DrawSpace();
GLvoid DrawPolygon(GLvoid);

CCamera Camera;

void main(int, char *)
{
	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	RegesterCallBack();

	glutMainLoop();
}

GLvoid init(GLvoid)
{
	srand(unsigned(time(NULL)));
}

GLvoid RegesterCallBack()
{
	glutMouseFunc(MouseEvent);
	glutPassiveMotionFunc(MouseMove);
	glutKeyboardFunc(Keydown);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(10, Timer, 1);
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Camera.SetLookVector();
	//Camera.SetCamera();
	
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
	glScalef(1, 0.01, 1);
	glutSolidCube(200);
	glPopMatrix();
}

float u, u_2, u_3, f, fy;

float startPointX, endPointX, controlPoint1X, controlPoint2X;
float startPointY, endPointY, controlPoint1Y, controlPoint2Y;

GLvoid DrawPolygon(GLvoid)
{
	glPointSize(4);
	glBegin(GL_POINTS);
	for (int j = 0; j < 20; j++)
	{
		u = (float)j / 20;
		u_2 = u * u;
		u_3 = u_2 * u;
		f = CATMULL_ROM_SPLINE(u, u_2, u_3,
			0,
			100,
			0,
			100
		);

		fy = CATMULL_ROM_SPLINE(u, u_2, u_3,
			0,
			100,
			0,
			100
		);
		glVertex3f(f, fy, 0);
	}
	glEnd();
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
		0.0, 1.0, 0.0,			// eye
		0.0, 0.0, 1.0,			// center
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

	}

	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y)
{

	glutPostRedisplay();
}

GLvoid MouseEvent(int button, int state, int x, int y)
{

	glutPostRedisplay();
}


GLvoid Timer(int val)
{

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

bool boolswitch(bool chker)
{
	if (chker == true)			return false;
	else if (chker == false)	return true;
	return false;
}

static inline float
CATMULL_ROM_SPLINE(float u, float u_2, float u_3, float cntrl0, float cntrl1, float cntrl2, float cntrl3)
{
	return (
		(-1.0f*u_3 + 2.0f*u_2 - 1.0f*u + 0.0f) * cntrl0 +
		(3.0f*u_3 - 5.0f*u_2 + 0.0f*u + 2.0f) * cntrl1 +
		(-3.0f*u_3 + 4.0f*u_2 + 1.0f*u + 0.0f) * cntrl2 +
		(1.0f*u_3 - 1.0f*u_2 + 0.0f*u + 0.0f) * cntrl3
		) / 2.0f;
}