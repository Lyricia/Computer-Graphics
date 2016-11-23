#include<iostream>
#include<time.h>
#include<gl\glut.h>

#include "Object.h"

#define W_Width		800
#define W_Height	600
#define W_Depth		800

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
void DrawObject();
GLvoid DrawPolygon(GLvoid);

float cameray;
float camdist;

float MousePoints[30][3];
float ctrlpoints[30][3][3];
int pointcounter;
int layercounter;
bool IsPerspective;

CObject RectTree;
CObject SphereTree;
CObject TorusBuilding;
CObject ConeBuilding;
CObject DoorBuilding;

float projectionmatrix[16] = {
	1,0,0,0,
	0,0,1,0,
	0,-1,0,0,
	0,0,0,1
};

void main(int, char *)
{
	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	glEnable(GL_DEPTH_TEST);
	RegesterCallBack();

	glutMainLoop();
}

GLvoid init(GLvoid)
{
	srand(unsigned(time(NULL)));
	IsPerspective = false; 

	camdist = -400;
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

	if (IsPerspective) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, 1.0, 1.0, 10000);
		glTranslatef(0.0, 0.0, camdist);
		gluLookAt(
			0, cameray, 0,
			0, 0, 1,
			0, 1, 0
		);
	}
	else {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(W_Width / 2, -W_Width / 2, -W_Height / 2, W_Height / 2, -W_Depth / 2, W_Depth / 2);
		glMultMatrixf(projectionmatrix);
	}

	glMatrixMode(GL_MODELVIEW);

	//DrawSpace();
	glPushMatrix();
	//glScalef(20, 20, 20);
	DrawObject();
	DrawPolygon();

	//glutWireSphere(50, 10, 10);
	glPopMatrix();

	glPointSize(3.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	glVertex3f(100, 100, 0);
	for (int i = 0; i < pointcounter; i++) {
		glVertex3f(MousePoints[i][0], MousePoints[i][1], MousePoints[i][2]);
	}
	glEnd();


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

void DrawObject()
{
	glPushMatrix();
	{
		//DrawSpace();
		glPushMatrix();
		{
			DoorBuilding.DoorBuildingRender();
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

GLvoid DrawPolygon(GLvoid)
{
	for (int i = 0; i < 9; i++)
	{
			glMap2f(GL_MAP2_VERTEX_3,
				0.0, 1.0, 3, 3,
				0.0, 1.0, 9, 4,
				&ctrlpoints[i * 3][0][0]);
	
			glEnable(GL_MAP2_VERTEX_3);
			glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
			glEvalMesh2(GL_LINE, 0, 10, 0, 10);
			glDisable(GL_MAP2_VERTEX_3);
	}

	for (int i = 0; i < 9; i++)
	{
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &MousePoints[i * 3][0]);

		glEnable(GL_MAP1_VERTEX_3);

		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 30; i++)
			glEvalCoord1f((GLfloat)i / 30.0);
		glEnd();

		glDisable(GL_MAP1_VERTEX_3);
	}



	glPointSize(2.0);
	glColor3f(1.0, 1.0, 0.0);
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
	glTranslatef(0.0, 0.0, 300.0);

	glMatrixMode(GL_MODELVIEW);

	gluLookAt(
		0.0, cameray, 0.0,			// eye
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

	case 't':
		cameray += 0.1f;
		break;
	case 'g':
		cameray -= 0.1f;
		break;

	case 'y':
		camdist += 10;
		break;
	case 'h':
		camdist -= 10;
		break;

	case 'e':
		IsPerspective= boolswitch(IsPerspective);
		break;
	}

	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y)
{
}

GLvoid MouseEvent(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			MousePoints[pointcounter][0] = x - 400;
			MousePoints[pointcounter][1] = 0;
			MousePoints[pointcounter][2] = 300 - y;

			ctrlpoints[pointcounter][0][0] = MousePoints[pointcounter][0] - 10;
			ctrlpoints[pointcounter][0][1] = MousePoints[pointcounter][1];
			ctrlpoints[pointcounter][0][2] = MousePoints[pointcounter][2] - 10;

			ctrlpoints[pointcounter][1][0] = MousePoints[pointcounter][0];
			ctrlpoints[pointcounter][1][1] = MousePoints[pointcounter][1];
			ctrlpoints[pointcounter][1][2] = MousePoints[pointcounter][2];

			ctrlpoints[pointcounter][2][0] = MousePoints[pointcounter][0] + 10;
			ctrlpoints[pointcounter][2][1] = MousePoints[pointcounter][1];
			ctrlpoints[pointcounter][2][2] = MousePoints[pointcounter][2] + 10;

			for (int i = pointcounter; i < 30; i++)
			{
				MousePoints[i][0] = x - 400;
				MousePoints[i][1] = 0;
				MousePoints[i][2] = 300 - y;

				ctrlpoints[i][0][0] = MousePoints[i][0] - 10;
				ctrlpoints[i][0][1] = MousePoints[i][1];
				ctrlpoints[i][0][2] = MousePoints[i][2] - 10;

				ctrlpoints[i][1][0] = MousePoints[i][0];
				ctrlpoints[i][1][1] = MousePoints[i][1];
				ctrlpoints[i][1][2] = MousePoints[i][2];

				ctrlpoints[i][2][0] = MousePoints[i][0] + 10;
				ctrlpoints[i][2][1] = MousePoints[i][1];
				ctrlpoints[i][2][2] = MousePoints[i][2] + 10;
			}
			pointcounter++;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	}
	glutPostRedisplay();
}


GLvoid Timer(int val)
{
	RectTree.rotateRect(1);
	SphereTree.scaleSphere(0.01);
	TorusBuilding.moveTorus(1);
	ConeBuilding.scaleCone(0.01);
	DoorBuilding.moveDoor(1);

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

bool boolswitch(bool chker)
{
	if (chker == true)			return false;
	else if (chker == false)	return true;
	return false;
}