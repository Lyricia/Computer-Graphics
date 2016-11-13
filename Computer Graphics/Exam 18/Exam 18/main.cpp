#include <iostream>
#include <time.h>
#include <gl\glut.h>

#include "Ball.h"
#include "Crane.h"

#define W_Width		800
#define W_Height	600
#define W_Depth		800

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

CBall ball;
CCrane crane;

float cranespeed;
CVertex V;

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
	
	ball.setcolor(255, 0, 255);
	cranespeed = 1;
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
	glMatrixMode(GL_MODELVIEW);

	DrawSpace();
	glPushMatrix();
	{
		glTranslatef(0, 20, 0);
		ball.Render(20);
	}
	glPopMatrix();
	glPushMatrix();
	{
		//glScalef(0.5, 0.5, 0.5);
		crane.Render();
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
		0.0, 1, 0.0,			// eye
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

	case 'r':
		init();
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


GLvoid Timer(int  val)
{
	V.x += cranespeed;
	if (V.x >= 100)
		cranespeed = -1;
 	else if (V.x <= -100)
		cranespeed = 1;

	crane.moveCrane(cranespeed);

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

GLvoid Circle(Vertex P, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex2f(cos(angle)*radius + P.x, sin(angle)*radius + P.y);
}