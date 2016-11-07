#include<iostream>
#include<time.h>

#include<gl\glut.h>

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
GLvoid DrawPolygon(GLvoid);
GLvoid Circle(Vertex P, float radius, float angle);

Vertex v_Model;

int m_x;
int xdir;
int m_y;

void main(int, char *)
{
	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	RegesterCallBack();

	glutMainLoop();
}

GLvoid init(GLvoid)
{
	srand(unsigned(time(NULL)));
	m_x = 0;
	m_y = 100;
	xdir = 1;
}

GLvoid RegesterCallBack()
{
	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMove);
	glutKeyboardFunc(Keydown);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(50, Timer, 1);
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glRotatef(1, 0, 1, 0);
	DrawLines();
	glPushMatrix();
	{
		glRotatef(90, 0, 1, 0);
		DrawLines();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(m_x, m_y, 0);
		DrawPolygon();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0, m_y, m_x);
		glRotatef(90, 0, 1, 0);
		DrawPolygon();
	}
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

GLvoid DrawLines()
{
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.f, 100.f, 0.0f);
	glVertex3f(100.f, -100.f, 0.0f);
	glVertex3f(-100.f, -100.f, 0.0f);
	glVertex3f(0.f, 100.f, 0.0f);
	glEnd();
}

GLvoid DrawPolygon(GLvoid)
{
	glColor3f(1.f, 1.f, 0.f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 3; i++)
		Circle(v_Model, 30, 90 + (120 * i));
	glEnd();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-W_Width / 2, W_Width / 2, -W_Height / 2, W_Height / 2, -W_Depth / 2, W_Depth / 2);
	glMatrixMode(GL_MODELVIEW);
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

	case 'u':
		break;

	case 'd':
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
	if (xdir == 1)
	{
		if (m_x > 0)
			m_y -= 2;
		else if (m_x < 0)
			m_y += 2;
		m_x += xdir;
		if (m_x == 100)
		{
			xdir = -1;
		}
	}
	else if (xdir == -1)
	{
		m_x += xdir;
		if (m_x == -100)
		{
			xdir = 1;
		}
	}
	

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

GLvoid Circle(Vertex P, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex2f(cos(angle)*radius + P.x, sin(angle)*radius + P.y);
}