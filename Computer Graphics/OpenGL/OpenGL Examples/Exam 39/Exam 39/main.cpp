#include <iostream>
#include <time.h>
#include <gl\glut.h>
#include "Camera.h"

#define W_Width		800
#define W_Height	600
#define W_Depth		800
#define PI			3.14159265359

GLvoid RegesterCallBack();


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLvoid Timer(int);
GLvoid Keydown(unsigned char, int, int);
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid init(GLvoid);

bool boolswitch(bool chker);

GLvoid DrawLines();
GLvoid DrawSpace();
GLvoid DrawPolygon(GLvoid);

void EnLighten();

CCamera Camera;

float camdist;
float ambiantlevel1;
float diffuselevel1;
float specularlevel1;

bool light1on;

int angle;
float angle2;

bool mousehold;
bool IsNormalOn;

float camangle;

int fognum;

GLfloat fog_color[4] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat density = 0.7;
GLfloat start = 10.0;
GLfloat end = 10.0;

void main(int, char *)
{
	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	RegesterCallBack();

	glutMainLoop();
}

GLvoid init(GLvoid)
{
	srand(unsigned(time(NULL)));
	camdist = -400;

	ambiantlevel1= 0.3f;
	diffuselevel1= 1.0f;
	specularlevel1= 1.0f;

	light1on = true;

	mousehold = true;
	Camera.SetCameraPosition(50, 50, 50);
}

GLvoid RegesterCallBack()
{
	glutMouseFunc(MouseEvent);
	glutPassiveMotionFunc(MouseMove);
	glutKeyboardFunc(Keydown);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(10, Timer, 1);
}

void EnLighten()
{
	glEnable(GL_NORMALIZE);
	GLfloat SpecularLight1[] = { specularlevel1, specularlevel1, specularlevel1, specularlevel1 };
	GLfloat AmbientLight1[] = { ambiantlevel1, ambiantlevel1, ambiantlevel1, ambiantlevel1 };
	GLfloat DiffuseLight1[] = { diffuselevel1, diffuselevel1, diffuselevel1, diffuselevel1 };

	GLfloat light1_position[] = { 100.0, 10, -100.0, 0.0 };
	GLfloat mat_shininess[] = { 15 };
	glShadeModel(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLight1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, AmbientLight1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, DiffuseLight1);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight1);
	glLightfv(GL_LIGHT0, GL_POSITION, light1_position);

	glEnable(GL_LIGHTING);


	if(light1on)		glEnable(GL_LIGHT0);
	else				glDisable(GL_LIGHT0);
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	Camera.SetLookVector();
	Camera.SetCamera();

	glMatrixMode(GL_MODELVIEW);

	EnLighten();

	glEnable(GL_FOG);

	if (fognum == 1)
		glFogf(GL_FOG_MODE, GL_LINEAR);
	else if (fognum == 2)
		glFogf(GL_FOG_MODE, GL_EXP);
	else if (fognum == 3)
		glFogf(GL_FOG_MODE, GL_EXP2);

	glFogfv(GL_FOG_COLOR, fog_color); // fog_color는 안개의 색을 의미한다. glFogf(GL_FOG_START, start); // start는 world coordinate상에서 안개 시작 위치를 의미한다.
	glFogf(GL_FOG_END, end); // end는 world coordinate상에서 안개 끝 위치를 의미한다.
	glFogf(GL_FOG_DENSITY, density);

	glPushMatrix();
	{
		glColor3f(1, 0, 0);
		glutSolidCube(50);
		glTranslatef(0, 0, -50);
		glColor3f(0, 0, 1);
		glutSolidCube(50);
		glTranslatef(0, 0, -50);
		glColor3f(1, 1, 0);
		glutSolidCube(50);
	}
	glPopMatrix();

	glDisable(GL_FOG);
	glutSwapBuffers();
}

void RotatingCube()
{
	glPushMatrix();
	{
		glColor3f(1.f, 1.f, 1.f);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, -W_Depth);
		glVertex3f(0.0, 0.0, W_Depth);
		glEnd();
		glutSolidCube(50);
	}
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
	{
		glScalef(3, 0.01, 3);
		glutSolidCube(300);
	}
	glPopMatrix();
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

	case '1':
		fognum = 0;
		break;

	case '2':
		fognum = 1;
		break;

	case '3':
		fognum = 2;
		break;

	case 'w':
		Camera.Move(DIRECTION::FRONT, 10);
		break;

	case 's':
		Camera.Move(DIRECTION::BACK, 10);
		break;

	case 'a':
		Camera.Move(DIRECTION::LEFT, 10);
		break;
	case 'd':
		Camera.Move(DIRECTION::RIGHT, 10);
		break;

	case 'z':
		density += 0.1;
		break;
	case 'Z':
		density -= 0.1;
		break;
	case 'x':
		start += 1;
		break;
	case 'X':
		start -= 1;
		break;
	case 'c':
		end += 1;
		break;
	case 'C':
		end -= 1;
		break;


	case 'm':
		mousehold = boolswitch(mousehold);
		break;

	case '`':
		IsNormalOn = boolswitch(IsNormalOn);
		break;
	}
	

	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y)
{
	Camera.getMouse(x, y);
	Camera.SetLookVector();
}

GLvoid MouseEvent(int button, int state, int x, int y)
{
	glutPostRedisplay();
}


GLvoid Timer(int val)
{
	if(mousehold)
		glutWarpPointer(400, 300);

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

bool boolswitch(bool chker)
{
	if (chker == true)			return false;
	else if (chker == false)	return true;
	return false;
}
