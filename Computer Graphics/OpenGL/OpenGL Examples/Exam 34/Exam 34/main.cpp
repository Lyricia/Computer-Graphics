//실습34
//실습 33 에 건물과 스포트라이트 추가하기
//
//실습 33의 길에 다양한 크기의 건물을 여러 개 그린다.
//각 길마다 2개 이상의 건물을 그린다.
//스포트라이트 설정하기
//
//움직이는 물체 위에 스포트라이트를 설정하고 물체 방향을 ㅗ빛을 쏜다.
//
//스포트 라이트를 사용하기 위해서는 glLight 함수에서 다음 ㅗㄱ성을 설정한다.
//	GL_POSITION
//	GL_SPOT_DIRECTION : 스포트라이트 방향벡터
//	GL_SPOT_CUTOFF : 확산각도
//	GL_SPOT_EXPONENT : 스포트라이트 지수
//	GL_CONSTANT_ATTENUATION : 흐림지수
//
//	물체가 움직이면 같이 움직인다
//
//	점프 길에서 건물을 건너뛸 수 있는 점프를 구현
//	키보드명령 - 스포트라이트 켜기 / 끄기
//	효과구현
//	자동차가 건물과 충돌하면 폭발
//

#include <iostream>
#include <time.h>
#include <gl\glut.h>
#include "Camera.h"
#include "Ball.h"
#include "Crane.h"

#define W_Width		800
#define W_Height	600
#define W_Depth		800
#define PI			3.14159265359

#define RAD(x)		x * PI / 180

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
void DrawWall();
void carjump();
void DrawCar();
void EnLighten();

CCamera Camera;

float camdist;
float ambiantlevel1;
float diffuselevel1;
float specularlevel1;

bool light1on;

float angle;
float explosionsize;

CBall wheel[4];
CCrane crane;

bool mousehold;
bool IsNormalOn;
bool IsExpoltion;

float camangle;

enum lane { lfall, left, center, right, rfall };

int cranelane;

bool IsJump = false;

float cranexdir = 1;
float craneydir = 1;
float xdist = 0;
void main(int, char *)
{
	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	
	RegesterCallBack();

	glutMainLoop();
}

GLvoid init(GLvoid)
{
	srand(unsigned(time(NULL)));
	camdist = -400;

	ambiantlevel1 = 0.0f;
	diffuselevel1 = 0.0f;
	specularlevel1 = 0.0f;

	light1on = true;

	Camera.SetCameraPosition(0, 400, -800);

	mousehold = true;

	cranelane = 2;
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
	GLfloat mat_AmbientLight1[] = { 1.f, 1.f, 1.f, 1.0f };
	GLfloat mat_SpecularLight1[] = { 1.f, 1.f, 1.f, 1.0f };
	GLfloat mat_DiffuseLight1[] = { 1.f, 1.f, 1.f, 1.0f };

	GLfloat AmbientLight1[] = { ambiantlevel1, ambiantlevel1, ambiantlevel1, 1.0f };
	GLfloat SpecularLight1[] = { 1.f, 1.f, 1.f, 1.0f };
	GLfloat DiffuseLight1[] = { diffuselevel1, diffuselevel1, diffuselevel1, 1.0f };
	GLfloat spotlightDirection[] = { 0.0f, -1.0f, 0.0f };

	if (IsJump) { DiffuseLight1[0] = 0; }


	GLfloat light1_position[] = { crane.Position.z * 2, 200, -crane.Position.x * 2, 1.0f };

	GLfloat mat_shininess[] = { 64 };
	glShadeModel(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_SpecularLight1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_AmbientLight1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseLight1);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight1);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.f);                  // 80도 원뿔
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100.0f);                 // 초점 설정
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlightDirection);   // 방향 설정
	glLightfv(GL_LIGHT0, GL_POSITION, light1_position);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);

	glEnable(GL_LIGHTING);


	if (light1on)		glEnable(GL_LIGHT0);
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

	glPushMatrix();
	{
		glTranslatef(crane.Position.z * 2, 200, -crane.Position.x * 2);
		glutSolidSphere(10,50,50);
	}
	glPopMatrix();

	
	glPushMatrix();
	{
		if(!IsExpoltion)		DrawCar();
		else if (IsExpoltion)	glutWireSphere(explosionsize, 50, 50);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-500, -20, 0);
		DrawSpace();
		glTranslatef(500, 0, 0);
		DrawSpace();
		glTranslatef(500, 0, 0);
		DrawSpace();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0, 0, 70);
		DrawWall();
	}
	glPopMatrix();

	glutSwapBuffers();
}

void DrawCar()
{
	glPushMatrix();
	{
		glRotatef(90, 0, 1, 0);
		glScaled(2, 2, 2);
		glPushMatrix();
		{
			glPushMatrix();
			glTranslatef(0, 20, 0);
			crane.Render();
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
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
		glScalef(20,1,200);
		DrawPolygon();
	}
	glPopMatrix();
}

GLvoid DrawPolygon(GLvoid)
{
	if (IsNormalOn)	glEnable(GL_NORMALIZE);
	else glDisable(GL_NORMALIZE);

	GLfloat ctrlpoints[3][4][3] = {
		{ { -8.0, 0, 4 },{ -4.0, 0, 4 },	{ 4.0, 0, 4.0 },	{ 8.0,0, 4.0 } },
		{ { -8.0, 0, 0 },{ -4.0, 0, 0.0 },	{ 4.0, 0, 0.0 },	{ 8.0,0, 0.0 } },
		{ { -8.0, 0, -4 },{ -4.0,0, -4 },	{ 4.0, 0, -4.0 },	{ 8.0,0, -4.0 } }
	};

	glMap2f(GL_MAP2_VERTEX_3,
		0.0, 1.0, 3, 4,
		0.0, 1.0, 12, 3,
		&ctrlpoints[0][0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glNormal3f(0, 1, 0);
	glMapGrid2f(50, 0.0, 1.0, 50, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 50, 0, 50);
	glDisable(GL_MAP2_VERTEX_3);
}

void DrawWall()
{
	glPushMatrix();
	{
		glColor3f(1, 0, 0);
		glScalef(3, 2, 0.1);
		glutSolidCube(100);
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

	case 'g':
		if (!IsJump) {
			if (cranelane > -1)
				cranelane--;
			cranexdir = 1;
			IsJump = true;
		}
		break;

	case 'h':
		if (!IsJump) {
			if (cranelane < 5)
				cranelane++;
			cranexdir = -1;
			IsJump = true;
		}
		break;

	case 'm':
		mousehold = boolswitch(mousehold);
		break;

	case '`':
		IsNormalOn = boolswitch(IsNormalOn);
		break;
	}
	
	//std::cout << ambiantlevel1 << " " << diffuselevel1 << " " << specularlevel1 << std::endl;
	std::cout << IsNormalOn << std::endl;

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
	const float cranespeed = 1;

	carjump();

	if (!IsJump)
	{
		crane.angle = 0;
		if (cranelane == 1)	crane.Position.z = 250;
		else if (cranelane == 2)	crane.Position.z = 0;
		else if (cranelane == 3)	crane.Position.z = -250;
	}

	if(mousehold)
		glutWarpPointer(400, 300);

	if (IsExpoltion)
	{
		explosionsize++;
	}

	crane.moveCrane(cranespeed);

	for (int i = 0; i < 4; i++)
		wheel[i].Move(-cranespeed * 3 * crane.xdir, false, false, true);

	//std::cout << crane.Position.x << " " << crane.Position.z << std::endl;

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

bool boolswitch(bool chker)
{
	if (chker == true)			return false;
	else if (chker == false)	return true;
	return false;
}

void carjump()
{
	if (IsJump) {
		if (xdist > 125 && cranelane != lfall && cranelane != rfall) {
			IsJump = false;
			xdist = 0;
			cranexdir = 1;
			craneydir = 1;
			crane.angle = 0;
		}
		if (xdist >= 63)
			craneydir = -1;

		if (crane.angle < 360 && crane.angle > -360) {
			if (cranexdir > 0)
				crane.angle += 3;
			else if (cranexdir < 0)
				crane.angle -= 3;
		}
		crane.Position.z += cranexdir * 2;
		crane.Position.y += craneydir * 4;
		xdist++;
	}
}

void IsCollide()
{
	if (cranelane == left) {
		if (crane.Position.z - 70 == 100)
			IsExpoltion = true;
		else if (crane.Position.z + 70 == 100)
			IsExpoltion = true;
	}
	else if (cranelane == center) {
		if (crane.Position.z - 70 == 100)
			IsExpoltion = true;
		else if (crane.Position.z + 70 == 100)
			IsExpoltion = true;
	}
	else if (cranelane == right) {

	}
}