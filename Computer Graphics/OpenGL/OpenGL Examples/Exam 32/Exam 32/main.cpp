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

void InitBlizzard();
void FallingBlizzard();
void RenderBlizzard();

void CameraWalk();

CObject Pyramid;
COrbit Orbit;

CCamera Camera;

float camdist;
float ambiantlevel1;
float diffuselevel1;
float specularlevel1;

float ambiantlevel2;
float diffuselevel2;
float specularlevel2;

float ambiantlevel3;
float diffuselevel3;
float specularlevel3;

float ambiantlevel4;
float diffuselevel4;
float specularlevel4;

bool light1on;
bool light2on;
bool light3on;
bool light4on;

int angle;
int angle2;

bool mousehold;
bool IsNormalOn;

Vec3f snowposition[500];
float snowspeed[500];

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

	ambiantlevel1= 0.0f;
	diffuselevel1= 0.0f;
	specularlevel1= 0.0f;

	ambiantlevel2= 0.1f;
	diffuselevel2= 0.1f;
	specularlevel2= 0.1f;

	ambiantlevel3= 0.0f;
	diffuselevel3= 0.0f;
	specularlevel3= 0.0f;

	ambiantlevel4= 0.0f;
	diffuselevel4= 0.0f;
	specularlevel4= 0.0f;

	light3on = true;

	InitBlizzard();

	Camera.SetCameraPosition(0, 200, -500);

	mousehold = true;

	light2on = true;
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

	GLfloat SpecularLight2[] = { specularlevel2, specularlevel2, specularlevel2, specularlevel2 };
	GLfloat AmbientLight2[] = { ambiantlevel2, ambiantlevel2, ambiantlevel2, ambiantlevel2 };
	GLfloat DiffuseLight2[] = { diffuselevel2, diffuselevel2, diffuselevel2, diffuselevel2 };

	GLfloat SpecularLight3[] = { specularlevel3, specularlevel3, specularlevel3, specularlevel3 };
	GLfloat AmbientLight3[] = { ambiantlevel3, ambiantlevel3, ambiantlevel3, ambiantlevel3 };
	GLfloat DiffuseLight3[] = { diffuselevel3, diffuselevel3, diffuselevel3, diffuselevel3 };

	GLfloat SpecularLight4[] = { specularlevel4, specularlevel4, specularlevel4, specularlevel4 };
	GLfloat AmbientLight4[] = { ambiantlevel4, ambiantlevel4, ambiantlevel4, ambiantlevel4 };
	GLfloat DiffuseLight4[] = { diffuselevel4, diffuselevel4, diffuselevel4, diffuselevel4 };

	GLfloat light1_position[] = { 600.0, 10, 600.0, 0.0 };
	GLfloat light2_position[] = { -600.0,10, 600.0, 0.0 };
	GLfloat light3_position[] = { -600.0,10, -600.0, 0.0 };
	GLfloat light4_position[] = { 600.0, 10, -600.0, 0.0 };
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

	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight2);
	glLightfv(GL_LIGHT1, GL_POSITION, light2_position);

	glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight3);
	glLightfv(GL_LIGHT2, GL_POSITION, light3_position);

	glLightfv(GL_LIGHT3, GL_AMBIENT, AmbientLight4);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, DiffuseLight4);
	glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight4);
	glLightfv(GL_LIGHT3, GL_POSITION, light4_position);

	glEnable(GL_LIGHTING);


	if(light1on)		glEnable(GL_LIGHT0);
	else				glDisable(GL_LIGHT0);

	if (light2on)		glEnable(GL_LIGHT1);
	else				glDisable(GL_LIGHT1);

	if (light3on)		glEnable(GL_LIGHT2);
	else				glDisable(GL_LIGHT2);

	if (light4on)		glEnable(GL_LIGHT3);
	else				glDisable(GL_LIGHT3);

}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	Camera.SetLookVector();
	Camera.SetCamera();

	glMatrixMode(GL_MODELVIEW);

	glRotatef(camangle, 0, 1, 0);

	EnLighten();

	RenderBlizzard();

	DrawSpace();

	glPushMatrix();
	{
		glTranslatef(100, 0, 0);
		DrawObject();
		glTranslatef(-200, 0, 0);
		DrawObject();
	}
	glPopMatrix();
	
	glPushMatrix();
	{
		glTranslatef(-100, 100, 0);
		DrawOrbit();
		glTranslatef(200, 0, 0);
		DrawOrbit();

	}
	glPopMatrix();

	glPushMatrix();
	{
		glLoadIdentity();
		glTranslatef(600, 0, 600);
		glutSolidSphere(10,10,10);
		glLoadIdentity();
		glTranslatef(-600, 0, 600);
		glutSolidSphere(10, 10, 10);
		glLoadIdentity();
		glTranslatef(-600, 0, -600);
		glutSolidSphere(10, 10, 10);
		glLoadIdentity();
		glTranslatef(600, 0, -600);
		glutSolidSphere(10, 10, 10);
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
		
	case '2':
		light2on = boolswitch(light2on);
		break;

	case '3':
		light3on = boolswitch(light3on);
		break;

	case '4':
		light4on = boolswitch(light4on);
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

//	case 'a':
//		ambiantlevel1 += 0.1;
//		break;
//	case 'A':
//		ambiantlevel1 -= 0.1;
//		break;
//	case 'd':
//		diffuselevel1 += 0.1;
//		break;
//	case 'D':
//		diffuselevel1 -= 0.1;
//		break;
//	case 's':
//		specularlevel1 += 0.1;
//		break;
//	case 'S':
//		specularlevel1 -= 0.1;
//		brea;k

	case 'z':
		ambiantlevel2 += 0.1;
		break;
	case 'Z':
		ambiantlevel2 -= 0.1;
		break;
	case 'x':
		diffuselevel2 += 0.1;
		break;
	case 'X':
		diffuselevel2 -= 0.1;
		break;
	case 'c':
		specularlevel2 += 0.1;
		break;
	case 'C':
		specularlevel2 -= 0.1;
		break;

	case 'f':
		ambiantlevel3 += 0.1;
		break;
	case 'F':
		ambiantlevel3 -= 0.1;
		break;
	case 'g':
		diffuselevel3 += 0.1;
		break;
	case 'G':
		diffuselevel3 -= 0.1;
		break;
	case 'h':
		specularlevel3 += 0.1;
		break;
	case 'H':
		specularlevel3 -= 0.1;
		break;


	case 'v':
		ambiantlevel4 += 0.1;
		break;
	case 'V':
		ambiantlevel4 -= 0.1;
		break;
	case 'b':
		diffuselevel4 += 0.1;
		break;
	case 'B':
		diffuselevel4 -= 0.1;
		break;
	case 'n':
		specularlevel4 += 0.1;
		break;
	case 'N':
		specularlevel4 -= 0.1;
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
	angle = (angle + 2) % 360;
	angle2 = (angle2 + 4) % 360;

	FallingBlizzard();

	//CameraWalk();

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

void InitBlizzard()
{
	for (int i = 0; i < 500; i++)
	{
		snowposition[i].x = -600 + (rand() % 1200);
		snowposition[i].y = rand() % 800;
		snowposition[i].z = -600 + (rand() % 1200);
		snowspeed[i] = 1 + (rand() % 5) * 0.1;
	}
}

void FallingBlizzard()
{
	for (int i = 0; i < 500; i++) {
		snowposition[i].y -= snowspeed[i];
		if (snowposition[i].y < 0)
			snowposition[i].y = 800;
	}
}

void RenderBlizzard()
{
	glPushMatrix();
	{
		for (int i = 0; i < 500; i++)
		{
			glPushMatrix();
			glTranslatef(snowposition[i].x, snowposition[i].y, snowposition[i].z);
			glutSolidSphere(5, 10, 10);
			glPopMatrix();
		}
	}
	glPopMatrix();
}

enum phase { one, two, three, end };
int CamTimerCounter;
float anglecounter;
int phase;

void CameraWalk()
{
	if (phase == one)
	{
		CamTimerCounter++;
		if (CamTimerCounter > 350) { phase = two; return; }
		Camera.Move(DIRECTION::FRONT, 2);
	}
	
	if (phase == two)
	{
		if (anglecounter > 180) { 
			phase = three; 
			CamTimerCounter = 0; 
			camangle = 0; 
			return;
		}
		camangle = 0.5;
		anglecounter += camangle;
	}

	if (phase == three)
	{
		CamTimerCounter++;
		if (CamTimerCounter > 350) { phase = end; return; }
		Camera.Move(DIRECTION::BACK, 2);
	}
}