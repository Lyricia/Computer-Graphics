#include <iostream>
#include <time.h>

#include "Ball.h"
#include <gl\glut.h>

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

void drawText(char * string, float x, float y, float z);

GLvoid Timer(int);
GLvoid Keydown(unsigned char, int, int);
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid init(GLvoid);

GLvoid DrawLines();
GLvoid DrawSpace();
GLvoid DrawPolygon(GLvoid);
GLvoid Circle(Vertex P, float radius, float angle);

CBall ball;

float zpos;

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

	ball.setcolor(255, 0, 0);
	zpos = 30;
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

	DrawSpace();

	glPushMatrix();
	{
		glTranslatef(0, 0, zpos);
		ball.Render(50);
	}
	glPopMatrix();

	glutSwapBuffers();
}           

GLvoid DrawLines()
{
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_LINES);
	glVertex3f(-0.5, 0.0, 0.0);
	glVertex3f(0.5, 0.0, 0.0);

	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.0, -0.5, 0.0);
	glVertex3f(0.0, 0.5, 0.0);

	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.0, 0.0, -0.5);
	glVertex3f(0.0, 0.0, 0.5);
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
		0.0, 0.5, 0.0,			// eye
		0.0, 0.0, 1.0,			// center
		0.0, 1.0, 0.0);			// up
}

void drawText(char *string, float x, float y, float z)
{
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
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

	case 'r':
		ball.Move(10, false, true, false);
		break;
	case 'e':
		ball.Move(-10, false, true, false);
		break;

	case 'w':
		ball.Move(10, true, false, false);
		break;
	case 's':	
		ball.Move(-10, true, false, false);
		break;

	case 'a':	
		ball.Move(-10, false, false, true);
		break;
	case 'd':
		ball.Move(10, false, false, true);
		break;

	case '+':
		zpos += 10;
		break;
	case '-':
		zpos -= 10;
		break;

	default:
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

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

GLvoid Circle(Vertex P, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex2f(cos(angle)*radius + P.x, sin(angle)*radius + P.y);
}