#include <iostream>
#include <time.h>
#include <gl\glut.h>
#include "Camera.h"
#include "Object.h"

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
void EnLighten();


CObject RectTree;
CObject SphereTree;
CObject TorusBuilding;
CObject ConeBuilding;
CObject Pyramid;

CCamera Camera;
float camdist;
float ambiantlevel;
float diffuselevel;
float specularlevel;
bool light1on;
bool light2on;

bool mousehold;

void main(int, char *)
{
	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
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

	ambiantlevel = 0.0f;
	diffuselevel = 0.0f;
	specularlevel = 0.0f;
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
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//
	//GLfloat AmbientLightValue[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	//GLfloat DiffuseLightValue[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	//GLfloat SpecularLightValue[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//GLfloat PositionLightValue[] = { 100.0f, 0.0f, 1.0f, 0.0f };
	//
	//glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLightValue); //Ambient 조명의 성질을 설정한다.
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLightValue); //Diffuse 조명의 성질을 설정한다.
	//glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLightValue); //Specular 조명의 성질을 설정한다. 
	//glLightfv(GL_LIGHT0, GL_POSITION, PositionLightValue); //조명의 위치(광원)를 설정한다.


	GLfloat SpecularLight[] = { specularlevel, specularlevel, specularlevel, specularlevel };
	GLfloat AmbientLight[] = { ambiantlevel, ambiantlevel, ambiantlevel, ambiantlevel };
	GLfloat DiffuseLight[] = { diffuselevel, diffuselevel, diffuselevel, diffuselevel };
	GLfloat light1_position[] = { 300.0, 100.0, 00.0, 0.0 };
	GLfloat light2_position[] = { -300.0, 100.0, 0.0, 0.0 };
	GLfloat mat_shininess[] = { 15 };
	glShadeModel(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLight);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, AmbientLight);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, DiffuseLight);

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, light1_position);

	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, light2_position);

	glEnable(GL_LIGHTING);


	if(light1on)		glEnable(GL_LIGHT0);
	else				glDisable(GL_LIGHT0);

	if (light2on)		glEnable(GL_LIGHT1);
	else				glDisable(GL_LIGHT1);

}


GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_DEPTH_TEST);

	Camera.SetLookVector();
	Camera.SetCamera();

	glMatrixMode(GL_MODELVIEW);
	EnLighten();

	glPushMatrix();
	{
		DrawLines();
		DrawObject();
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
	glScalef(3, 0.01, 3);
	glutSolidCube(300);
	glPopMatrix();
}
GLvoid DrawPolygon(GLvoid)
{

}

void DrawObject()
{
	glEnable(GL_NORMALIZE);
	glPushMatrix();
	{
		DrawSpace();
		glPushMatrix();
		{
			Pyramid.PyramidRender();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(200, 0, 200);
			RectTree.RectTreeRender();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(200, 0, -200);
			SphereTree.SphereTreeRender();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-200, 0, 200);
			TorusBuilding.TorusBuildingRender();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-200, 0, -200);
			ConeBuilding.ConeBuildingRender();
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
		
	case '2':
		light2on = boolswitch(light2on);
		break;

	case 'r':
		Camera.Move(DIRECTION::FRONT, 10);
		break;

	case 'f':
		Camera.Move(DIRECTION::BACK, 10);
		break;

	case 'a':
		ambiantlevel += 0.1;
		break;
	case 'A':
		ambiantlevel -= 0.1;
		break;
	case 'd':
		diffuselevel += 0.1;
		break;
	case 'D':
		diffuselevel -= 0.1;
		break;
	case 's':
		specularlevel += 0.1;
		break;
	case 'S':
		specularlevel -= 0.1;
		break;

	case 'm':
		mousehold = boolswitch(mousehold);
		break;
	}
	
	std::cout << ambiantlevel << " " << diffuselevel << " " << specularlevel << std::endl;

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
	RectTree.rotateRect(1);
	SphereTree.scaleSphere(0.01);
	TorusBuilding.moveTorus(1);
	ConeBuilding.scaleCone(0.01);
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