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
GLvoid DrawSpace();
GLvoid DrawPolygon(GLvoid);
GLvoid Circle(Vertex P, float radius, float angle);

int xpos;
int bottomangle;
int middleanglex;
int middleangley;
int topanglex;
int topanglez;

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
	xpos = 0;
	bottomangle = 0;
	middleanglex = 0;
	middleangley = 0;
	topanglex = 0;
	topanglez = 0;
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
		glTranslatef(xpos, 0, 0);
		glRotatef(bottomangle, 0, 1, 0);
		glScalef(1, 0.5, 0.8);
		glColor3f(1.0, 0.0, 0);
		glutSolidCube(80);

		glTranslatef(0, 40, 0);
		DrawLines();

		glPushMatrix();
		{
			glRotatef(middleanglex, 1, 0, 0);
			glRotatef(middleangley, 0, 1, 0);
			glTranslatef(0, 25, 0);
			glScalef(0.5, 1.5, 1);
			glColor3f(0.0, 0.0, 1);
			glutSolidCube(50);
			glTranslatef(0, 25, 0);
			DrawLines();
			glPushMatrix();
			{
				glRotatef(topanglex, 1, 0, 0);
				glRotatef(topanglez, 0, 0, 1);
				glTranslatef(0, 25, 0);
				glScalef(0.5, 1.0, 0.5);
				glColor3f(1.0, 0.0, 1.0);
				glutSolidCube(50);
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
	glPushMatrix();
	glScalef(1, 0.01, 1);
	glColor3f(1.0, 1.0, 0);
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
		0.0, 0.2, 0.0,			// eye
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
		middleanglex += 5;
		break;
	case 'W':
		middleanglex -= 5;
		break;

	case 's':
		middleangley += 5;
		break;
	case 'S':
		middleangley -= 5;
		break;

	case 'x':
		topanglex += 5;
		break;
	case 'X':
		topanglex -= 5;
		break;

	case 'z':
		topanglez += 5;
		break;
	case 'Z':
		topanglez -= 5;
		break;


	case 'a':
		if (xpos < 100)		xpos += 5;
		break;

	case 'd':
		if (xpos > -100)		xpos -= 5;
		break;

	case 'e':
		bottomangle += 10;
		break;
	case 'E':
		bottomangle -= 10;
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