#include<iostream>
#include<time.h>

#include<gl\glut.h>

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

int anglex, angley, anglez;
double move_x, move_y, move_z;
bool f_x, f_y, f_z;
int vertical;

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

	anglex = 0;
	angley = 0;
	anglez = 0;
	move_x = 0;
	move_y = 0;
	move_z = 0;
	f_x = false;
	f_y = false;
	f_z = false;
	vertical = 0;
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
		glTranslatef(0, 30, vertical);
		glTranslated(move_x, move_y, move_z);
		glPushMatrix();
		{
			glTranslatef(0, -30, -vertical);
			glTranslated(-move_x, -move_y, -move_z);

			glRotatef(anglex, 1, 0, 0);
			glRotatef(angley, 0, 1, 0);
			glRotatef(anglez, 0, 0, 1);

			glTranslatef(0, -30, -vertical);
			glTranslated(move_x, move_y, move_z);
			DrawLines();
			glColor3f(1, 0, 0);
			glutWireSphere(30, 10, 10);
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

	case 'y':
		angley += 10;
		break;
	case 'Y':
		angley -= 10;
		break;

	case 'w':
		anglex += 10;
		if (move_z <100)
			move_z += 2 * PI * 30 * 10 / 360;
		f_x = true;
		f_y = false;
		f_z = false;
		break;

	case 's':
		anglex -= 10;
		if (move_z>-100)
			move_z -= 2 * PI * 30 * 10 / 360;
		f_x = true;
		f_y = false;
		f_z = false;
		break;

	case 'a':
		anglez -= 10;
		if (move_x < 100)
			move_x += 2 * PI * 30 * 10 / 360;
		f_x = false;
		f_y = false;
		f_z = true;
		break;

	case 'd':
		anglez += 10;
		if (move_x>-100)
			move_x -= 2 * PI * 30 * 10 / 360;
		f_x = false;
		f_y = false;
		f_z = true;
		break;

	case '+':
		vertical += 10;
		break;
	case '-':
		vertical -= 10;
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

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

GLvoid Circle(Vertex P, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex2f(cos(angle)*radius + P.x, sin(angle)*radius + P.y);
}