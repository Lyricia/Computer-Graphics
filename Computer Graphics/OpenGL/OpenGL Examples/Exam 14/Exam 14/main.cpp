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
GLvoid DrawPolygon(int sel);
GLvoid Circle(Vertex P, float radius, float angle);

enum poly { SPHERE, CUBE, CONE, TEAPOT };

int angle1; 
int angle2;
int angle_a;
int polysel;
bool f_x, f_y, f_z;

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
	f_x = false;
	f_y = true;
	f_z = false;
	angle1 = 0;
	angle2 = 0;
	angle_a = 0;
	polysel = poly::CUBE;
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
	DrawLines();
	//glTranslatef(0,-50, 0);

	glPushMatrix();
	{
		glRotatef(angle_a, f_x, f_y, f_z);
		DrawSpace();
		glPushMatrix();
		{
			glTranslatef(50.f, 50.f, 0.f);
			glRotatef(angle1, f_x, f_y, f_z);
			glScalef(1.f, 2.f, 1.f);
			DrawPolygon(1);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-50.f, 50.f, 0.f);
			glRotatef(angle2, f_x, f_y, f_z);
			glScalef(2.f, 1.f, 1.f);
			DrawPolygon(2);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glutSwapBuffers();
}

GLvoid DrawLines()
{
	glColor3f(1.f, 1.f, 1.f );
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

GLvoid DrawPolygon(int sel)
{
	glColor3f(1.f, 0.f, 0.f);
	switch (polysel)
	{
	case poly::CUBE:
		if (sel == 1)
			glutSolidCube(50);
		else if (sel == 2)
			glutWireCube(50);
		break;
	case poly::SPHERE:
		if (sel == 1)
			glutSolidSphere(20, 10,10);
		else if (sel == 2)
			glutWireSphere(20, 10, 10);
		break;
	case poly::CONE:
		if (sel == 1)
			glutSolidCone(20, 50, 10, 10);
		else if (sel == 2)
			glutWireCone(20, 50, 10, 10);
		break;
	case poly::TEAPOT:
		if (sel == 1)
			glutSolidTeapot(20);
		else if (sel == 2)
			glutWireTeapot(20);
		break;
	}
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
		0.0, 0.8, 0.0,			// eye
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

	case '1':	polysel = poly::CUBE;		break;
	case '2':	polysel = poly::SPHERE;		break;
	case '3':	polysel = poly::CONE;		break;
	case '4':	polysel = poly::TEAPOT;		break;

	case 's':
		angle1 += 10;
		break;

	case 'd':
		angle2 += 10;
		break;

	case 'z':
		angle_a += 5;
		f_x = true;
		f_y = false;
		f_z = false;
		break;
	case 'x':
		angle_a += 5;
		f_x = false;
		f_y = true;
		f_z = false;
		break;
	case 'c':
		angle_a += 5;
		f_x = false;
		f_y = false;
		f_z = true;
		break;

	case 'Z':
		if (!f_x)	f_x = true;
		else f_x = false;
		break;
	case 'X':
		if (!f_y)	f_y = true;
		else f_y = false;
		break;
	case 'C':
		if (!f_z)	f_z = true;
		else f_z = false;
		break;
	case 'v':
		if (f_x || f_y || f_z)
			angle_a += 5;
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