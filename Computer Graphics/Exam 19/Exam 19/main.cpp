#include <iostream>
#include <time.h>
#include <gl\glut.h>
#include "Object.h"

#define W_Width		800
#define W_Height	600
#define W_Depth		800
#define PI			3.14159265359

struct Vertex
{
	float x;
	float y;
	float z;
};

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
GLvoid Circle(Vertex P, float radius, float angle);

float cameraz;
float camerax;

CObject RectTree;
CObject SphereTree;
CObject TorusBuilding;
CObject ConeBuilding;
CObject DoorBuilding;

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
	
	cameraz = -700;
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

	glPushMatrix();
	{
		DrawSpace();
		glPushMatrix();
		{
			DoorBuilding.DoorBuildingRender();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(200, 0, 200);
			RectTree.RectTreeRender();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(200, 0, -200);
			SphereTree.SphereTreeRender();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-200, 0, 200);
			TorusBuilding.TorusBuildingRender();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-200, 0, -200);
			ConeBuilding.ConeBuildingRender();
		}
		glPopMatrix();
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

enum COLPOS {LEFT, RIGHT, TOP, BOTTOM};

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

	case 'r':
		cameraz += 10;
		break;
	case 'f':
		cameraz -= 10;
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
	RectTree.rotateRect(1);
	SphereTree.scaleSphere(0.01);
	TorusBuilding.moveTorus(1);
	ConeBuilding.scaleCone(0.01);
	DoorBuilding.moveDoor(1);
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

GLvoid Circle(Vertex P, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex2f(cos(angle)*radius + P.x, sin(angle)*radius + P.y);
}