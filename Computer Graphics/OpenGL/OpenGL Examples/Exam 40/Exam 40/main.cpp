#include <iostream>
#include <time.h>
#include <Windows.h>
#include <gl\glut.h>
#include "Camera.h"

#define W_Width		800
#define W_Height	600
#define W_Depth		800
#define PI			3.14159265359

GLvoid RegesterCallBack();


GLvoid drawScene(GLvoid);
void DrawBase();
void DrawMASSIVE();
void DrawHammock(bool snowman);
void DrawSnowman();
GLvoid Reshape(int w, int h);

GLvoid Timer(int);
GLvoid Keydown(unsigned char, int, int);
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid init(GLvoid);

bool boolswitch(bool chker);

GLubyte * LoadDIBitmap(const char * filename, BITMAPINFO ** info);

void bitmapSetup();

void Circle(Vec3f P, float radius, float angle);


GLvoid DrawLines();
GLvoid DrawSpace();
GLvoid DrawPolygon(GLvoid);

void EnLighten();
void DrawQuad(const Vec3f & ptPosition, float fScale, bool isXY);

CCamera Camera;

float camdist;
float ambiantlevel1;
float diffuselevel1;
float specularlevel1;

bool light1on;

int angle;
float angle2;
int angle3;
int angledir = 1;

bool mousehold;
bool IsNormalOn;

float camangle;

int fognum;

GLfloat fog_color[4] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat density = 0.7;
GLfloat start = 10.0;
GLfloat end = 10.0;

GLubyte *pBytes;
BITMAPINFO *info;
GLuint texture[6];

bool snowman[2];

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

	ambiantlevel1= 0.3f;
	diffuselevel1= 1.0f;
	specularlevel1= 1.0f;

	light1on = true;

	mousehold = true;
	Camera.SetCameraPosition(50, 50, -150);

	snowman[0] = true;
	snowman[1] = false;
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

	//EnLighten();

	bitmapSetup();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	DrawBase();

	glPushMatrix();
	{
		glTranslatef(30, 40, -40);
		glScalef(0.5, 0.5, 0.5);
		glRotatef(90, 1, 0, 0);
		DrawMASSIVE();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(100, 90, -80);
		glPushMatrix();
		{
			glScalef(0.5, 0.5, 0.5);
			glRotatef(angle3, 0, 0, 1);
			glTranslatef(0, -100, 0);
			DrawHammock(snowman[0]);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0, 90, -80);
		glPushMatrix();
		{
			glScalef(0.5, 0.5, 0.5);
			glRotatef(-angle3, 0, 0, 1);
			glTranslatef(0, -100, 0);
			DrawHammock(snowman[1]);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glutSwapBuffers();
}

void DrawBase()
{
	glPushMatrix();
	{
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.f, 1.0f);
			glVertex3f(0.0, 100.0, 0.0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(100.0, 100.0, 0.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(100.0, 0.0, 0.0);
			glTexCoord2f(0.f, 0.0f);
			glVertex3f(0.0, 0.0, 0.0);
			glEnd();
		}
		glPopMatrix();
		glRotatef(-90, 1, 0, 0);
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.f, 1.0f);
			glVertex3f(0.0, 100.0, 0.0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(100.0, 100.0, 0.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(100.0, 0.0, 0.0);
			glTexCoord2f(0.f, 0.0f);
			glVertex3f(0.0, 0.0, 0.0);
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glEnable(GL_BLEND);
	glPushMatrix();
	{
		glTranslatef(80, 25, -30);
		glRotatef(angle2, 0, 1, 0);
		glPushMatrix();
		{
			//glBlendFunc(GL_ONE, GL_ZERO);
			//glRotatef(90, 1, 1, 0);
			//glColor4f(1.f, 0.f, 0.f, 0.0f);
			//glutSolidCube(20);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(80, 25, -30);
		glRotatef(angle, 0, 1, 0);
		glPushMatrix();
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
			glRotatef(90, 1, 1, 0);
			glColor4f(1.0f, 1.0f, 0.0f, 0.8);
			glutSolidCube(40);		
		}
		glPopMatrix();
	}
	glPopMatrix();
	glDisable(GL_BLEND);
}

void DrawMASSIVE()
{
	glPushMatrix();
	{
		glRotatef(-angle, 0, 1, 0);
		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glScalef(0.5f, 0.5f, 10);
			glutSolidCube(10);
		}
		glPopMatrix();
		glRotatef(45, 0, 1, 0);
		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glScalef(0.5f, 0.5f, 10);
			glutSolidCube(10);
		}
		glPopMatrix();
		glRotatef(45, 0, 1, 0);
		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glScalef(0.5f, 0.5f, 10);
			glutSolidCube(10);
		}
		glPopMatrix();
		glRotatef(45, 0, 1, 0);
		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glScalef(0.5f, 0.5f, 10);
			glutSolidCube(10);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glTranslatef(cos((0 + angle) * (3.141592 / 180)) * 50, 0, sin((0 + angle)* (3.141592 / 180)) * 50);
			glutSolidCube(10);
		}
		glPopMatrix();
	
		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glTranslatef(cos((45 + angle) * (3.141592 / 180)) * 50, 0, sin((45 + angle)* (3.141592 / 180)) * 50);
			glutSolidCube(10);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glTranslatef(cos((90 + angle) * (3.141592 / 180)) * 50, 0, sin((90 + angle)* (3.141592 / 180)) * 50);
			glutSolidCube(10);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glTranslatef(cos((135 + angle) * (3.141592 / 180)) * 50, 0, sin((135 + angle)* (3.141592 / 180)) * 50);
			glutSolidCube(10);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glTranslatef(cos((180 + angle) * (3.141592 / 180)) * 50, 0, sin((180 + angle)* (3.141592 / 180)) * 50);
			glutSolidCube(10);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glTranslatef(cos((225 + angle) * (3.141592 / 180)) * 50, 0, sin((225 + angle)* (3.141592 / 180)) * 50);
			glutSolidCube(10);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glTranslatef(cos((270 + angle) * (3.141592 / 180)) * 50, 0, sin((270 + angle)* (3.141592 / 180)) * 50);
			glutSolidCube(10);
		}
		glPopMatrix();		
		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glTranslatef(cos((315 + angle) * (3.141592 / 180)) * 50, 0, sin((315 + angle)* (3.141592 / 180)) * 50);
			glutSolidCube(10);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void DrawHammock(bool snowman)
{
	glPushMatrix();
	{
		glPushMatrix();
		{
			glScalef(0.6, 0.6, 0.6);
			glTranslatef(0, 20, 0);
			if(snowman)
				DrawSnowman();
		}
		glPopMatrix();

		glColor3f(1, 1, 0);
		glPushMatrix();
		{
			glTranslatef(22, 45, 0);
			glRotatef(30, 0, 0, 1);
			glScalef(0.01, 2, 0.01);
			glutSolidCube(50);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-22, 45, 0);
			glRotatef(-30, 0, 0, 1);
			glScalef(0.01, 2, 0.01);
			glutSolidCube(50);
		}
		glPopMatrix();

		glScalef(2.0, 0.001, 1.0);
		glutSolidCube(50);
	}
	glPopMatrix();
}

void DrawSnowman()
{
	glPushMatrix();
	{
		glColor3f(1, 1, 1);
		glutSolidSphere(20, 50, 50);
		glTranslatef(0, 30, 0);
		glutSolidSphere(15, 50, 50);
	}
	glPopMatrix();
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

	angle++;
	angle2--;
	
	if (angle3 >= 45 || angle3 <= -45)
		angledir *= -1;

	if (angle3 == -45) {
		bool tmp = snowman[1];
		snowman[1] = snowman[0];
		snowman[0] = tmp;
	}
	
	angle3 += angledir;


	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

bool boolswitch(bool chker)
{
	if (chker == true)			return false;
	else if (chker == false)	return true;
	return false;
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
	glGenTextures(1, texture);

	glBindTexture(GL_TEXTURE_2D, texture[0]);

	pBytes = LoadDIBitmap("t4.bmp", &info);

	glTexImage2D(
		GL_TEXTURE_2D, 0, 3,
		info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glEnable(GL_TEXTURE_2D);
}

void Circle(Vec3f P, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex3f(cos(angle)*radius + P.x, sin(angle)*radius + P.y, 0);
}