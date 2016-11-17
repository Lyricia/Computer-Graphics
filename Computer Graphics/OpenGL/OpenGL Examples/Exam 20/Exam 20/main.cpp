#include <iostream>
#include <time.h>
#include <gl\glut.h>
#include "Object.h"
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
GLvoid RenderCrane();
GLvoid RenderBuildings();
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

CObject RectTree;
CObject SphereTree;
CObject TorusBuilding;
CObject ConeBuilding;
CObject DoorBuilding;
CBall	ball;

CCrane	crane;

float cameraz;
float camerax;
float cranespeed;

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

	ball.Render(20);
	ball.setcolor(0, 0, 255);
	ball.Vertex.x = 200;
	
	crane.Vertex.z = -200;
	cranespeed = 1;

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
		RenderBuildings();
		glPushMatrix();
		{
			glTranslatef(0, 20, 0);
			ball.Render(20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0, 20, 0);
			RenderCrane();
		}
		glPopMatrix();
	}
	glPopMatrix();

	glutSwapBuffers();
}

GLvoid RenderCrane()
{
	glPushMatrix();
	{
		

		glPushMatrix();
		glTranslatef(0, 20, 0);
		crane.Render();
		glPopMatrix();
	}
	glPopMatrix();
}

GLvoid RenderBuildings()
{
	glPushMatrix();
	{
		DoorBuilding.DoorBuildingRender(50);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(200, 0, 200);
		RectTree.RectTreeRender(50);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(200, 0, -200);
		SphereTree.SphereTreeRender(50);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-200, 0, 200);
		TorusBuilding.TorusBuildingRender(50);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-200, 0, -200);
		ConeBuilding.ConeBuildingRender(50);
	}
	glPopMatrix();
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
	RectTree.rotateRect(1);
	SphereTree.scaleSphere(0.01);
	TorusBuilding.moveTorus(1);
	ConeBuilding.scaleCone(0.01);
	DoorBuilding.moveDoor(1);

	if (crane.isCollide(ball.GetBB()))
	{
		std::cout << "collide" << std::endl;
		cranespeed = 0;
	}
	else
	{
		cranespeed = 1;
		crane.moveCrane(cranespeed);
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
	float p_left = ball.GetBB()[BBPOS::LEFTTOP].x;
	float p_right = ball.GetBB()[BBPOS::RIGHTBOTTOM].x;
	float p_top = ball.GetBB()[BBPOS::LEFTTOP].z;
	float p_bottom = ball.GetBB()[BBPOS::RIGHTBOTTOM].z;
	float q_left = crane.GetBB()[BBPOS::LEFTTOP].x;
	float q_right = crane.GetBB()[BBPOS::RIGHTBOTTOM].x;
	float q_top = crane.GetBB()[BBPOS::LEFTTOP].z;
	float q_bottom = crane.GetBB()[BBPOS::RIGHTBOTTOM].z;

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