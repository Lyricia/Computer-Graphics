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
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid init(GLvoid);

GLvoid DrawPolygon(GLvoid);

GLvoid Circle(Vertex V, float, float);

Vertex tmp = { 0,300,0 };
int scale = 50;

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
	tmp.x = 0;
	glClear(GL_COLOR_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glPointSize(1);
	glBegin(GL_LINE_STRIP);

	for (int i = 0; tmp.x<800; i++, tmp.x +=0.2)
	{
		glColor3f((tmp.x / 800) * 1.0, 0.0, (1 - (tmp.x / 800)) * 1.0);	//color gradation
		Circle(tmp, scale, i);											// spring  tmp.x = 200 tmp += 0.2
		//glVertex3f(tmp.x, sin(RAD(i)) * 100 + tmp.y, 0);				// sin
		//glVertex3f(tmp.x, cos(RAD(i)) * 100 + tmp.y, 0);				// cos

	}
	glEnd();
	glutSwapBuffers();
}

GLvoid DrawLine()
{




}
GLvoid DrawPolygon(GLvoid)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 0.0, 0.0); // 빨강색
	glutSolidCube(0.3);
	glPushMatrix();
	{
		glRotatef(30.0, 0.0, 0.0, 1.0);
		glTranslatef(0.5, 0.0, 0.0);
		glColor3f(0.0, 1.0, 0.0); // 초록색
		glutSolidCube(0.3);
		glPushMatrix();
		{
			glRotatef(45.0, 0.0, 0.0, 1.0);
			glTranslatef(0.3, 0.0, 0.0);
			glColor3f(1.0, 0.0, 1.0); // 보라색
			glutSolidCube(0.1);
		}
		glPopMatrix();
	}
	glPopMatrix();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, W_Width, 0.0, W_Height, -1.0, 1.0);
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
		scale += 10;
		break;
	case 's':
		scale -= 10;
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

GLvoid Circle(Vertex V, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex3f(cos(angle)*radius + V.x, sin(angle)*radius + V.y, 0);
}