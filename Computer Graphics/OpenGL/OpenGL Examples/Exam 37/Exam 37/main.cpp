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
#include <Windows.h>
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
void IsCollide();
void DrawCar();
void EnLighten();
GLubyte * LoadDIBitmap(const char * filename, BITMAPINFO ** info);
void bitmapSetup();

GLubyte *pBytes;
BITMAPINFO *info[6];
GLuint texture[6];

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
bool IsNormalOn = true;
bool IsExpoltion;

float camangle;

enum lane { lfall, left, center, right, rfall };

int cranelane;

bool IsJump = false;
bool IsLanejump = false;
bool IsRunning = true;

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
	GLfloat mat_SpecularLight1[] = { 1.f, 1.f, 1.f, 0.0f };
	GLfloat mat_DiffuseLight1[] = { 1.f, 1.f, 1.f, 1.0f };

	GLfloat AmbientLight1[] = { -1.f,-1.f, -1.f, 1.0f };
	GLfloat SpecularLight1[] = { 1.f, 1.f, 1.f, 1.0f };
	GLfloat DiffuseLight1[] = { 2.0f, 2.0f, 2.0f, 1.0f };
	GLfloat spotlightDirection[] = { 0.0f, -1.0f, 0.0f };

	GLfloat AmbientLight2[] = { 0, 0, 0, 1.0f };
	
	if (IsJump) { DiffuseLight1[0] = 0; }

	GLfloat light1_position[] = { crane.Position.z * 2, crane.Position.y + 500, -crane.Position.x * 2, 1.0f };

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

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 5.f);                  // 80도 원뿔
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

	bitmapSetup();

	glPushMatrix();
	{
		glTranslatef(crane.Position.z * 2, crane.Position.y + 500, -crane.Position.x * 2);
		glutSolidSphere(10,50,50);
	}
	glPopMatrix();

	
	glPushMatrix();
	{
		if(!IsExpoltion)		DrawCar();
		else if (IsExpoltion) {
			glTranslatef(crane.Position.z *2, 0, -crane.Position.x * 2);
			glutWireSphere(explosionsize, 50, 50);
		}
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
		glPushMatrix();
		glTranslatef(-500, 0, -400);
		DrawWall();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0, 0, 150);
		DrawWall();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(500, 0, 400);
		DrawWall();
		glPopMatrix();
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
	glEnable(GL_NORMALIZE);


	GLfloat ctrlpoints[3][4][3] = {
		{ { -8.0,-1, 4 },{ -4.0, -1, 4 },	{ 4.0,-1, 4.0 },	{ 8.0,-1, 4.0 } },
		{ { -8.0,-1, 0 },{ -4.0, -1, 0.0 },	{ 4.0,-1, 0.0 },	{ 8.0,-1, 0.0 } },
		{ { -8.0,-1, -4 },{ -4.0,-1, -4 },	{ 4.0,-1, -4.0 },	{ 8.0,-1, -4.0 } }
	};

	glMap2f(GL_MAP2_VERTEX_3,
		0.0, 1.0, 3, 4,
		0.0, 1.0, 12, 3,
		&ctrlpoints[0][0][0]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glEnable(GL_MAP2_VERTEX_3);
	glNormal3f(0, 1, 0);
	glMapGrid2f(50, 0.0, 1.0, 50, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 50, 0, 50);
	glDisable(GL_MAP2_VERTEX_3);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void DrawWall()
{
	glPushMatrix();
	{
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		glColor3f(1, 1, 1);
		glScalef(3, 2, 0.1);
		glutSolidCube(100);

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
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

	case 'j':
		IsLanejump = true;
		break;

	case '`':
		IsNormalOn = boolswitch(IsNormalOn);
		break;
	}
	
	std::cout << ambiantlevel1 << " " << diffuselevel1 << " " << specularlevel1 << std::endl;
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
	const float cranespeed = 2;

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

	if (IsRunning) {
		if (IsExpoltion && !IsJump)
		{
			explosionsize += 2;
			if (explosionsize > 150) {
				explosionsize = 0;
				IsRunning = false;
			}
		}
		else
			crane.moveCrane(cranespeed);

		for (int i = 0; i < 4; i++)
			wheel[i].Move(-cranespeed * 3 * crane.xdir, false, false, true);

		IsCollide();
	}
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
	if (IsJump || IsLanejump) {
		if (xdist > 125 && cranelane != lfall && cranelane != rfall) {
			IsJump = false;
			IsLanejump = false;
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
		if (!IsLanejump)
			crane.Position.z += cranexdir * 2;
		crane.Position.y += craneydir * 4;
		xdist++;
	}
}

void IsCollide()
{
	if (cranelane == left) {
		if (crane.Position.x * 2 >  -400 - 50 && crane.Position.x * 2 < -400 + 50 && !IsLanejump && !IsJump)
			IsExpoltion = true;
	}
	else if (cranelane == center) {
 		if (crane.Position.x*2 > -150 - 50 && crane.Position.x*2 < -150 + 50 && !IsLanejump && !IsJump)
				IsExpoltion = true;
	}

	else if (cranelane == right) {
		if (crane.Position.x * 2 > 400 - 50 && crane.Position.x * 2 < 400 + 50 && !IsLanejump && !IsJump)
			IsExpoltion = true;
	}
}

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

void bitmapSetup()
{
	glGenTextures(2, texture);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	pBytes = LoadDIBitmap("t4.bmp", &info[0]);
	glTexImage2D(
		GL_TEXTURE_2D, 0, 3,
		info[0]->bmiHeader.biWidth, info[0]->bmiHeader.biHeight, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);


	glBindTexture(GL_TEXTURE_2D, texture[1]);
	pBytes = LoadDIBitmap("wall.bmp", &info[1]);
	glTexImage2D(
		GL_TEXTURE_2D, 0, 3,
		info[1]->bmiHeader.biWidth, info[1]->bmiHeader.biHeight, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glEnable(GL_TEXTURE_2D);
}
