#include <iostream>
#include <time.h>
#include <gl\glut.h>
#include "Camera.h"
#include "Object.h"
#include "Orbit.h"

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
void DrawObject();
void DrawOrbit();
void EnLighten();

CObject Pyramid;
COrbit Orbit;

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

	Camera.SetCameraPosition(0, 200, -500);

	mousehold = true;

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
	GLfloat SpecularLight1[] = { specularlevel1, specularlevel1, specularlevel1, specularlevel1 };
	GLfloat AmbientLight1[] = { ambiantlevel1, ambiantlevel1, ambiantlevel1, ambiantlevel1 };
	GLfloat DiffuseLight1[] = { diffuselevel1, diffuselevel1, diffuselevel1, diffuselevel1 };

	GLfloat light1_position[] = { 600.0, 10, -600.0, 0.0 };
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

	//DrawSpace();


	glPushMatrix();
	{

	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(200, 0, 0);
		glPushMatrix();
		{
			DrawLines();
			glColor3f(0.1, 0.2, 0);
			glRotatef(angle, 0, 1, 0);
			glTranslatef(50, 0, 0);
			glutSolidCube(50);
		}
		glPopMatrix();
	}
	glPopMatrix();
	
	glPushMatrix();
	{
		glTranslatef(-200, 0, 0);
		glPushMatrix();
		{
			glRotatef(angle, 1, 0, 0);
			DrawLines();
			glPushMatrix();
			{
				glColor3f(1, 1, 0);
				glRotatef(angle, 0, 1, 0);
				glTranslatef(0, 100, 0);
				glutSolidSphere(50, 10, 10);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(100, 0, -300);
		glRotatef(45, 0, 0, 1);
		glPushMatrix();
		{
			DrawLines();
			glTranslatef(cosf(angle2)*100, 0, sinf(angle2)*100);
			glRotatef(90, 0, 1, 0);
			glPushMatrix();
			{
				glColor3f(1, 0, 1);
				glRotatef(angle, 0, 1, 0);
				glTranslatef(0, 100, 0);
				glutSolidSphere(50, 10, 10);
				glRotatef(-90, 1, 0, 0);
				glutWireTorus(10, 90, 10, 10);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

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
GLvoid DrawPolygon(GLvoid)
{

}

void DrawObject()
{
	if(IsNormalOn)	glEnable(GL_NORMALIZE);
	else glDisable(GL_NORMALIZE);
	glPushMatrix();
	{
		Pyramid.PyramidRender();
	}
	glPopMatrix();
}

void DrawOrbit()
{
	glPushMatrix();
	{
		glColor3f(0, 1, 1);
		//Orbit.DrawOrbit(120);
		glPushMatrix();
		{
			Orbit.DrawPlanet(40, 30, angle, 0);
			//Orbit.DrawOrbit(90);
			Orbit.DrawPlanet(30, 10, angle2, 0);
		}
		glPopMatrix();
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
		light1on = boolswitch(light1on);
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
		ambiantlevel1 += 0.1;
		break;
	case 'Z':
		ambiantlevel1 -= 0.1;
		break;
	case 'x':
		diffuselevel1 += 0.1;
		break;
	case 'X':
		diffuselevel1 -= 0.1;
		break;
	case 'c':
		specularlevel1 += 0.1;
		break;
	case 'C':
		specularlevel1 -= 0.1;
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
	angle = (angle + 1) % 360;
	angle2 = angle2 + 0.01;

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
