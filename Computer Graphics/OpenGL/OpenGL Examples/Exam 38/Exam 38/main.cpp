#include <gl/glut.h>
#include <cmath>
#include <string.h>

#define SizeX 900
#define SizeY 600

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void SetUpRc();

float WRotX = 0, WRotY = 0, WRotZ = 0;
float LRotX = 30, LRotY = 30, LRotZ = 0;
float WTransX = 0, WTransY = 0, LTransX = 0, LTransY = 0;
float WScaleX = 1, WScaleY = 1, LScaleX = 1, LScaleY = 1;
char *String;

float teapotalpha[9];
float conealpha[9] = { 0.5f, };
int currentteapot;
int currentcone;

void main(int argc, char *argv[])
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(SizeX, SizeY);
	glutCreateWindow("Example2");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	SetUpRc();
	glutSpecialFunc(SpecialKeyboard);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClearColor(0.3f, 0.3f, 0.3f,0.8f);
	glClearColor(0.6f, 0.6f, 0.6f, 0.6f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	{
		glBlendFunc(GL_ONE, GL_ZERO);
		glTranslatef(-300, 200, 0);
		glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
		glPushMatrix();
		glutSolidSphere(50, 50, 10);
		glPopMatrix();


		glColor4f(0.0f, 1.0f, 0.0f, 0.3f);
		glPushMatrix();
		glTranslatef(-10, 0, 0);
		glutSolidTeapot(50);
		glPopMatrix();

		glColor4f(0.0f, 0.0f, 1.0f, conealpha[0]);
		glPushMatrix();
		glTranslatef(10, 0, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(40, 80, 10, 10);
		glPopMatrix();

		glBlendFunc(GL_ONE, GL_ZERO);
		glRasterPos2f(-50, -100);
		String = "GL_ONE,GL_ZERO";
		int len = (int)strlen(String);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, String[i]);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-300, 0, 0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
		glPushMatrix();
		glutSolidSphere(50, 50, 10);
		glPopMatrix();

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
		glPushMatrix();
		glTranslatef(-10, 0, 0);
		glutSolidTeapot(50);
		glPopMatrix();

		glColor4f(0.0f, 0.0f, 1.0f, conealpha[3]);
		glPushMatrix();
		glTranslatef(10, 0, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(40, 80, 10, 10);
		glPopMatrix();

		glBlendFunc(GL_ONE, GL_ZERO);
		glRasterPos2f(-100, -100);
		String = "GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA";
		int len = (int)strlen(String);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, String[i]);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-300, -200, 0);
		glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
		glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
		glPushMatrix();
		glutSolidSphere(50, 50, 10);
		glPopMatrix();

		glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
		glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
		glPushMatrix();
		glTranslatef(-10, 0, 0);
		glutSolidTeapot(50);
		glPopMatrix();

		glColor4f(0.0f, 0.0f, 1.0f, conealpha[6]);
		glPushMatrix();
		glTranslatef(10, 0, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(40, 80, 10, 10);
		glPopMatrix();

		glBlendFunc(GL_ONE, GL_ZERO);
		glRasterPos2f(-100, -100);
		String = "GL_ONE_MINUS_DST_COLOR, GL_ZERO";
		int len = (int)strlen(String);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, String[i]);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0, 200, 0);
		glBlendFunc(GL_ZERO, GL_ONE);
		glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
		glPushMatrix();
		glutSolidSphere(50, 50, 10);
		glPopMatrix();

		glColor4f(0.0f, 1.0f, 0.0f, 0.3f);
		glPushMatrix();
		glTranslatef(-10, 0, 0);
		glutSolidTeapot(50);
		glPopMatrix();

		glColor4f(0.0f, 0.0f, 1.0f, conealpha[1]);
		glPushMatrix();
		glTranslatef(10, 0, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(40, 80, 10, 10);
		glPopMatrix();

		glBlendFunc(GL_ONE, GL_ZERO);
		glRasterPos2f(-50, -100);
		String = "GL_ZERO, GL_ONE";
		int len = (int)strlen(String);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, String[i]);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0, 0, 0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
		glPushMatrix();
		glutSolidSphere(50, 50, 10);
		glPopMatrix();

		glColor4f(0.0f, 1.0f, 0.0f, 0.3f);
		glPushMatrix();
		glTranslatef(-10, 0, 0);
		glutSolidTeapot(50);
		glPopMatrix();

		glColor4f(0.0f, 0.0f, 1.0f, conealpha[4]);
		glPushMatrix();
		glTranslatef(10, 0, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(40, 80, 10, 10);
		glPopMatrix();

		glBlendFunc(GL_ONE, GL_ZERO);
		glRasterPos2f(-50, -100);
		String = "GL_SRC_ALPHA, GL_ONE";
		int len = (int)strlen(String);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, String[i]);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0, -200, 0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
		glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
		glPushMatrix();
		glutSolidSphere(50, 50, 10);
		glPopMatrix();

		glColor4f(0.0f, 1.0f, 0.0f, 0.3f);
		glPushMatrix();
		glTranslatef(-10, 0, 0);
		glutSolidTeapot(50);
		glPopMatrix();

		glColor4f(0.0f, 0.0f, 1.0f, conealpha[7]);
		glPushMatrix();
		glTranslatef(10, 0, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(40, 80, 10, 10);
		glPopMatrix();

		glBlendFunc(GL_ONE, GL_ZERO);
		glRasterPos2f(-100, -100);
		String = "GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR";
		int len = (int)strlen(String);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, String[i]);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(300, 200, 0);
		glBlendFunc(GL_ONE, GL_ONE);
		glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
		glPushMatrix();
		glutSolidSphere(50, 50, 10);
		glPopMatrix();

		glColor4f(0.0f, 1.0f, 0.0f, 0.3f);
		glPushMatrix();
		glTranslatef(-10, 0, 0);
		glutSolidTeapot(50);
		glPopMatrix();

		glColor4f(0.0f, 0.0f, 1.0f, conealpha[2]);
		glPushMatrix();
		glTranslatef(10, 0, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(40, 80, 10, 10);
		glPopMatrix();

		glBlendFunc(GL_ONE, GL_ZERO);
		glRasterPos2f(-50, -100);
		String = "GL_ONE, GL_ONE";
		int len = (int)strlen(String);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, String[i]);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(300, 0, 0);
		glBlendFunc(GL_ZERO, GL_SRC_COLOR);
		glColor4f(1.0f, 0.0f, 0.0f, 0.8f);
		glPushMatrix();
		glutSolidSphere(50, 50, 10);
		glPopMatrix();

		glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
		glPushMatrix();
		glTranslatef(-10, 0, 0);
		glutSolidTeapot(50);
		glPopMatrix();

		glColor4f(0.0f, 0.0f, 1.0f, conealpha[5]);
		glPushMatrix();
		glTranslatef(10, 0, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(40, 80, 10, 10);
		glPopMatrix();

		glBlendFunc(GL_ONE, GL_ZERO);
		glRasterPos2f(-50, -100);
		String = "GL_ZERO, GL_SRC_COLOR";
		int len = (int)strlen(String);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, String[i]);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(300, -200, 0);
		glBlendFunc(GL_ONE, GL_ONE);
		glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
		glPushMatrix();
		glutSolidSphere(50, 50, 10);
		glPopMatrix();

		glColor4f(0.0f, 1.0f, 0.0f, 0.3f);
		glPushMatrix();
		glTranslatef(-10, 0, 0);
		glutSolidTeapot(50);
		glPopMatrix();

		glColor4f(0.0f, 0.0f, 1.0f, conealpha[8]);
		glPushMatrix();
		glTranslatef(10, 0, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(40, 80, 10, 10);
		glPopMatrix();

		glBlendFunc(GL_ONE, GL_ZERO);
		glRasterPos2f(-50, -100);
		String = "GL_ONE, GL_ONE";
		int len = (int)strlen(String);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, String[i]);
	}
	glPopMatrix();

	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-SizeX / 2, SizeX / 2, -SizeY / 2, SizeY / 2, -300.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
		exit(0);
		break;

	case '1':
		currentcone = 0;
		currentteapot = 0;
		break;
	case '2':
		currentcone = 1;
		currentteapot = 1;
		break;
	case '3':
		currentcone = 2;
		currentteapot = 2;
		break;

	case '4':
		currentcone = 3;
		currentteapot = 3;
		break;
	case '5':
		currentcone = 4;
		currentteapot = 4;
		break;
	case '6':
		currentcone = 5;
		currentteapot = 5;
		break;

	case '7':
		currentcone = 6;
		currentteapot = 6;
		break;
	case '8':
		currentcone = 7;
		currentteapot = 7;
		break;
	case '9':
		currentcone = 8;
		currentteapot = 8;
		break;

		
	case 'F':
		if (conealpha[currentcone] > 0.0f )
			conealpha[currentcone] -= 0.1;
		break;

	case 'f':
		if (conealpha[currentcone] < 1.0f)
			conealpha[currentcone] += 0.1;
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y) {
	switch (key) {

	default:
		break;
	}
	glutPostRedisplay();
}

void SetUpRc() {
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
}