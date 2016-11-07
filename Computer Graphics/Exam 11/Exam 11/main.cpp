#include<iostream>
#include<time.h>

#include<gl\glut.h>

#define W_Width		800
#define W_Height	600
#define RAD(angle)	angle*(3.141592 / 180)

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
GLvoid KeySpecial(int key, int x, int y);
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid init(GLvoid);

GLvoid DrawPolygon(GLvoid);

GLvoid Circle(Vertex V, float, float);

Vertex tmp = { 0,0,0 };
float scale = 1.f;
int angle = 0;
float f_x, f_y, f_z;
int colorval = 0;
bool animationflag = false;
int startrad = 0;
float movex = 0.f;

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
	tmp = { 0,0,0 };
	scale = 1.f;
	angle = 0;
	f_x = 0;
	f_y = 0;
	f_z = 0;
	colorval = 0;
	animationflag = false;
	startrad = 0;
	movex = 0.f;
}

GLvoid RegesterCallBack()
{
	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMove);
	glutKeyboardFunc(Keydown);
	glutSpecialFunc(KeySpecial);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(10, Timer, 1);
}

GLvoid drawScene(GLvoid)
{
	tmp.x = -400;
	colorval = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glPushMatrix();
	{
		glTranslatef(movex, 0, 0);
		glPushMatrix();
		{
			glTranslatef(0.0, -100.0, 0.0);
			glRotatef(angle, f_x, f_y, f_z);
			glScalef(scale, scale, scale);
			glPointSize(1);
			glBegin(GL_LINE_STRIP);
			for (int i = startrad; tmp.x < 400; i++, colorval++, tmp.x += 0.2)
			{
				glColor3f(0.00025*colorval * 1.0, 0.0, (1.0 - 0.00025 * colorval) * 1.0);//color gradation
				Circle(tmp, 50, i);										// spring  tmp.x = 200 tmp += 0.2
				//glVertex3f(tmp.x, sin(RAD(i)) * 100 + tmp.y, 0);				// sin
				//glVertex3f(tmp.x, cos(RAD(i)) * 100 + tmp.y, 0);				// cos
			}
			glEnd();
			tmp.x = -400;
			colorval = 0;
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.0, 50.0, 0.0);
			glRotatef(angle, f_x, f_y, f_z);
			glScalef(scale, scale, scale);
			glPointSize(1);
			glBegin(GL_POINTS);
			for (int i = startrad; tmp.x < 400; i++, colorval++, tmp.x += 0.2)
			{
				glColor3f(0.00025*colorval * 1.0, 0.0, (1.0 - 0.00025 * colorval) * 1.0);
				glVertex3f(tmp.x, sin(RAD(i)) * 30 + tmp.y, 0);				// sin
			}
			glEnd();
			tmp.x = -400;
			colorval = 0;
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.0, 150.0, 0.0);
			glRotatef(angle, f_x, f_y, f_z);
			glScalef(scale, scale, scale);
			glPointSize(1);
			glBegin(GL_POINTS);
			for (int i = startrad; tmp.x < 400; i++, colorval++, tmp.x += 0.2)
			{
				glColor3f(0.00025*colorval * 1.0, 0.0, (1.0 - 0.00025 * colorval) * 1.0);
				glVertex3f(tmp.x, cos(RAD(i)) * 30 + tmp.y, 0);			// 
			}
			glEnd();
			tmp.x = -400;
			colorval = 0;
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.0, -200.0, 0.0);
			glRotatef(angle, f_x, f_y, f_z);
			glScalef(scale, scale, scale);
			glPushMatrix();
			{
				glTranslatef(-200.0, 0.0, 0.0);
				glPointSize(1);
				glBegin(GL_POINTS);
				for (int i = 0; i < 10; ++i)
				{
					glColor3f(1.0, 1.0, 0.0);
					glTranslatef(50.0, 0.0, 0.0);
					glutWireCube(20);
				}
				glEnd();
				tmp.x = -400;
				colorval = 0;
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	glEnd();
	glutSwapBuffers();
}

GLvoid DrawLine()
{
}

GLvoid DrawPolygon(GLvoid)
{
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-W_Width / 2, W_Width / 2, -W_Height / 2, W_Height / 2, -400, 400);
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

	case 'a':
		if(!animationflag)
			animationflag = true;
		else
			animationflag = false;
		break;

	case 's':
		scale+=0.2;
		break;
	case 'd':
		scale-=0.2;
		break;

	case 'z':
		angle = (angle + 10)%360;
		f_x = 1.0;
		f_y = 0.0;
		f_z = 0.0;
		break;

	case 'x':
		angle = (angle + 10) % 360;
		f_x = 0.0;
		f_y = 1.0;
		f_z = 0.0;
		break;
	case 'c':
		angle = (angle + 10) % 360;
		f_x = 0.0;
		f_y = 0.0;
		f_z = 1.0;
		break;
	case 'e':
		break;
	}

	glutPostRedisplay();
}

GLvoid KeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		movex -= 10;
		break;

	case GLUT_KEY_RIGHT:
		movex += 10;
		break;
	}
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
	if (animationflag)
		startrad = (startrad + 10) % 360;

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

GLvoid Circle(Vertex V, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex3f(cos(angle)*radius + V.x, sin(angle)*radius + V.y, 0);
}