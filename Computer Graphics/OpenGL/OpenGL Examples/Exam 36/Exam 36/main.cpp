#include <iostream>
#include <Windows.h>
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

GLubyte * LoadDIBitmap(const char * filename, BITMAPINFO ** info);
void bitmapSetup();


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

float lightangle;

GLubyte *pBytes;
BITMAPINFO *info[6];
GLuint texture[6];

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

	ambiantlevel2= 0.0f;
	diffuselevel2= 0.0f;
	specularlevel2= 0.0f;

	ambiantlevel3= 0.0f;
	diffuselevel3= 0.0f;
	specularlevel3= 0.0f;

	ambiantlevel4= 0.0f;
	diffuselevel4= 0.0f;
	specularlevel4= 0.0f;

	light3on = true;

	InitBlizzard();

	Camera.SetCameraPosition(0, 200, -300);

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
	GLfloat AmbientLight1[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat DiffuseLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat SpecularLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat SpecularLight2[] = { specularlevel2, specularlevel2, specularlevel2, specularlevel2 };
	GLfloat AmbientLight2[] = { ambiantlevel2, ambiantlevel2, ambiantlevel2, ambiantlevel2 };
	GLfloat DiffuseLight2[] = { diffuselevel2, diffuselevel2, diffuselevel2, diffuselevel2 };

	GLfloat SpecularLight3[] = { specularlevel3, specularlevel3, specularlevel3, specularlevel3 };
	GLfloat AmbientLight3[] = { ambiantlevel3, ambiantlevel3, ambiantlevel3, ambiantlevel3 };
	GLfloat DiffuseLight3[] = { diffuselevel3, diffuselevel3, diffuselevel3, diffuselevel3 };

	GLfloat SpecularLight4[] = { specularlevel4, specularlevel4, specularlevel4, specularlevel4 };
	GLfloat AmbientLight4[] = { ambiantlevel4, ambiantlevel4, ambiantlevel4, ambiantlevel4 };
	GLfloat DiffuseLight4[] = { diffuselevel4, diffuselevel4, diffuselevel4, diffuselevel4 };

	GLfloat light1_position[] = { 600.0, 100, 600.0, 0.0 };
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


	glEnable(GL_LIGHT0);

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

	bitmapSetup();

	glPushMatrix();
	{
		//glRotatef(lightangle, 0, 1, 0);
		EnLighten();
	}
	glPopMatrix();

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
	glEnable(GL_NORMALIZE);

	glPushMatrix();
	{

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		Pyramid.PyramidRender();

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
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
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glBindTexture(GL_TEXTURE_2D, texture[0]);

			Orbit.DrawPlanet(40, 30, angle, 0);
			//Orbit.DrawOrbit(90);
			Orbit.DrawPlanet(30, 10, angle2, 0);

			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
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

	lightangle++;

	FallingBlizzard();

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
		glColor3f(1, 1, 1);
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
	pBytes = LoadDIBitmap("texture5.bmp", &info[1]);
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