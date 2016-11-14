#include <iostream>
#include <time.h>
#include <gl\glut.h>

#include "Ball.h"
#include "Crane.h"

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

void adjustment();

CBall ball;
CBall wheel[4];
CCrane crane;

float cranespeed;

float camera;
int angle_y;

void main(int, char *)
{
	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	RegesterCallBack();

	for (int i = 0; i < 4; i++)
		wheel[i].setcolor(0, 255, 255);

	glutMainLoop();
}

GLvoid init(GLvoid)
{
	srand(unsigned(time(NULL)));
	
	ball.Render(20);
	ball.setcolor(255, 0, 255);
	ball.Move(180, true, false, false);
	//crane.moveCrane(50);
	cranespeed = 1;
	camera = -300;
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
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 10000);
	glTranslatef(0.0, 0.0, camera);
	gluLookAt(
		0, 1, 0,
		0, 0, 1,
		0, 1, 0
	);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	{
		glRotatef(angle_y, 0, 1, 0);
		glPushMatrix();
		{
			DrawSpace();
			glPushMatrix();
			{
				glTranslatef(0, 20, 0);
				ball.Render(20);
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glPushMatrix();
				glTranslatef(30, 0, -25);
				wheel[0].Render(20);
				glTranslatef(0, 0, 50);
				wheel[1].Render(20);
				glTranslatef(-60, 0, 0);
				wheel[2].Render(20);
				glTranslatef(0, 0, -50);
				wheel[3].Render(20);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0, 20, 0);
				crane.Render();
				glPopMatrix();
			}
			glPopMatrix();
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
	glScalef(1, 0.01, 1);
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

	case 'y':
		angle_y += 5;
		break;

	case 'e':
		crane.moveBottom(10, false, true, false);
		break;

	case 'r':
		camera += 10;
		break;
	case 'f':
		camera -= 10;
		break;
	}
	adjustment();

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
	if (crane.isCollide(ball.GetBB()))
	{
		std::cout << "collide" << std::endl;
		cranespeed = 0;
	}
	else 
	{ 
		crane.moveCrane(cranespeed); 
		for (int i = 0; i < 4; i++)
			wheel[i].Move(-cranespeed * 3 * crane.xdir, false, false, true);
	}

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

GLvoid Circle(Vertex P, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex2f(cos(angle)*radius + P.x, sin(angle)*radius + P.y);
}

void adjustment()
{
	float p_left	= ball.GetBB()[BBPOS::LEFTTOP].x;
	float p_right	= ball.GetBB()[BBPOS::RIGHTBOTTOM].x;
	float p_top		= ball.GetBB()[BBPOS::LEFTTOP].z;
	float p_bottom	= ball.GetBB()[BBPOS::RIGHTBOTTOM].z;
	float q_left	= crane.GetBB() [BBPOS::LEFTTOP].x;
	float q_right	= crane.GetBB() [BBPOS::RIGHTBOTTOM].x;
	float q_top		= crane.GetBB() [BBPOS::LEFTTOP].z;
	float q_bottom	= crane.GetBB() [BBPOS::RIGHTBOTTOM].z;

	if (ball.isCollide(crane.GetBB()))
	{                               
		cranespeed = 0;
		if ((p_right > q_left) && (p_left < q_right))
		{
			if (p_bottom > crane.Vertex.z)
				ball.Vertex.z += 2 * PI * ball.m_scale * 10 / 360;
			else if (p_top < crane.Vertex.z)
				ball.Vertex.z -= 2 * PI * ball.m_scale * 10 / 360;
		}

		if ((p_bottom < q_top) && (p_top > q_bottom))
		{
			if (p_left > crane.Vertex.x)
				ball.Vertex.x += 2 * PI * ball.m_scale * 10 / 360;
			else if (p_right < crane.Vertex.x)
				ball.Vertex.x -= 2 * PI * ball.m_scale * 10 / 360;
		}
	}
	else
		cranespeed = 1;
}