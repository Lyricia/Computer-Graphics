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

	//DrawSpace();
	glPushMatrix();
	glScalef(10, 10, 10);
	DrawPolygon();
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
	GLfloat ctrlpoints[3][3][3] = { { { -4.0, 0.0, 4.0 },{ -2.0, 4.0, 4.0 },{ 4.0, 0.0, 4.0 } },
	{ { -4.0, 0.0, 0.0 },{ -2.0, 4.0, 0.0 },{ 4.0, 0.0, 0.0 } },
	{ { -4.0, 0.0, -4.0 },{ -2.0, 4.0, -4.0 },{ 4.0, 0.0, -4.0 } } };

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[0][0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);
	glDisable(GL_MAP2_VERTEX_3);

	glPointSize(2.0);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3fv(ctrlpoints[i][j]);
	glEnd();
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

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

GLvoid Circle(Vertex P, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex2f(cos(angle)*radius + P.x, sin(angle)*radius + P.y);
}