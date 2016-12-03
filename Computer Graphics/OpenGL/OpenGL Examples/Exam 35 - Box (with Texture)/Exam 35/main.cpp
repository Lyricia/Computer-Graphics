#include <iostream>
#include <time.h>
#include <Windows.h>
#include <gl\glut.h>

#define W_Width		800
#define W_Height	600
#define W_Depth		800
#define PI			3.14159265359

GLvoid RegesterCallBack();

void EnLighten();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLvoid Timer(int);
bool boolswitch(bool chker);
GLvoid Keydown(unsigned char, int, int);
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid init(GLvoid);

GLvoid DrawLines();
GLvoid DrawSpace();
GLvoid DrawPolygon(GLvoid);
GLubyte * LoadDIBitmap(const char * filename, BITMAPINFO ** info);

void bitmapSetup();

float cameraz;
float camerax;

GLubyte *pBytes;
BITMAPINFO *info;
GLuint texture[6];

float angle;
float angle2;
float angle3;

bool IsSmooth;
bool IsDepth;
bool IsCull;

float ambiantlevel1;
float diffuselevel1;
float specularlevel1;

bool light1on = true;

void main(int, char *)
{
	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	RegesterCallBack();

	glutMainLoop();
}

GLvoid init(GLvoid)
{
	srand(unsigned(time(NULL)));

	cameraz = -300;
	camerax = 1;
	IsCull = true;
	IsDepth = true;
	IsSmooth = true;
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	bitmapSetup();
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

void EnLighten()
{
	GLfloat AmbientLight1[] = { 0.3, 0.3, 0.3, 1.0f };
	GLfloat DiffuseLight1[] = { 1.0, 1.0, 1.0, 1.0f };
	GLfloat SpecularLight1[] = { 1.0, 1.0, 1.0, 1.0f };

	GLfloat light1_position[] = { 600.0, 10, 600.0, 0.0 };
	GLfloat mat_shininess[] = { 15 };
	glShadeModel(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_AMBIENT, AmbientLight1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, DiffuseLight1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLight1);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight1);
	glLightfv(GL_LIGHT0, GL_POSITION, light1_position);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 10000);
	glTranslatef(0.0, 0.0, cameraz);
	gluLookAt(
		0, camerax, 0,
		0, 0, 1,
		0, 1, 0
	);

	glMatrixMode(GL_MODELVIEW);
	EnLighten();

	bitmapSetup();
	
	glPushMatrix();
	{
		glRotatef(angle, 0, 1, 0);
		glPushMatrix();
		{
			glTranslatef(-50, -50, 50);
			//1
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
			//2
			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, texture[0]);
				glBegin(GL_QUADS);
				glTexCoord2f(0.f, 0.0f);
				glVertex3f(0.0, 0.0, -100.0);
				glTexCoord2f(1.f, 0.0f);
				glVertex3f(0.0, 100.0, -100.0);
				glTexCoord2f(1.f, 1.0f);
				glVertex3f(0.0, 100.0, 0.0);
				glTexCoord2f(0.f, 1.0f);
				glVertex3f(0.0, 0.0, 0.0);
				glEnd();
			}
			glPopMatrix();
			//3 front
			glPushMatrix();
			{
				glTranslatef(0, 0, -100);
				glRotatef(-angle3, 1, 0, 0);
				glPushMatrix();
				{
					glBindTexture(GL_TEXTURE_2D, texture[0]);
					glBegin(GL_QUADS);
					glTexCoord2f(1.f, 1.0f);
					glVertex3f(100.0, 100.0, 0);
					glTexCoord2f(0.f, 1.0f);
					glVertex3f(0.0, 100.0, 0);
					glTexCoord2f(0.f, 0.0f);
					glVertex3f(0.0, 0.0, 0);
					glTexCoord2f(1.f, 0.0f);
					glVertex3f(100.0, 0.0, 0);
					glEnd();
				}
				glPopMatrix();
			}
			glPopMatrix();
			//4
			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, texture[0]);
				glBegin(GL_QUADS);
				glTexCoord2f(1.f, 1.0f);
				glVertex3f(100.0, 100.0, 0.0);
				glTexCoord2f(1.f, 0.0f);
				glVertex3f(100.0, 100.0, -100.0);
				glTexCoord2f(0.f, 0.0f);
				glVertex3f(100.0, 0.0, -100.0);
				glTexCoord2f(0.f, 1.0f);
				glVertex3f(100.0, 0.0, 0.0);
				glEnd();
			}
			glPopMatrix();
			//5 top
			glPushMatrix();
			{
				glTranslatef(0, 100, 0);
				glRotatef(angle2, 0, 0, 1);
				glPushMatrix();
				{
					glBindTexture(GL_TEXTURE_2D, texture[0]);
					glBegin(GL_QUADS);
					glTexCoord2f(1.f, 1.0f);
					glVertex3f(100.0, 0.0, 0.0);
					glTexCoord2f(0.f, 1.0f);
					glVertex3f(0.0, 0.0, 0.0);
					glTexCoord2f(0.f, 0.0f);
					glVertex3f(0.0, 0.0, -100.0);
					glTexCoord2f(1.f, 0.0f);
					glVertex3f(100.0, 0.0, -100.0);
					glEnd();
				}
				glPopMatrix();
			}
			glPopMatrix();
			//6 bottom
			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, texture[0]);
				glBegin(GL_QUADS);
				glTexCoord2f(1.f, 1.0f);
				glVertex3f(100.0, 0.0, 0.0);
				glTexCoord2f(1.f, 0.0f);
				glVertex3f(100.0, 0.0, -100.0);
				glTexCoord2f(0.f, 0.0f);
				glVertex3f(0.0, 0.0, -100.0);
				glTexCoord2f(0.f, 1.0f);
				glVertex3f(0.0, 0.0, 0.0);
				glEnd();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
	//RenderScene();

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

	case 't':
		camerax += 0.1;
		break;
	case 'g':
		camerax -= 0.1;
		break;

	case 'r':
		cameraz += 10;
		break;
	case 'f':
		cameraz -= 10;
		break;

	case 'y':
		angle += 5;
		break;
	case 'u':
		angle -= 5;
		break;
	case 'o':
		if (angle2 <90)
			angle2 += 1;
		break;
	case 'O':
		if (angle2 >0)
			angle2 -= 1;
		break;
	case 'k':
		if (angle3 <90)
			angle3 += 1;
		break;
	case 'K':
		if (angle3 >0)
			angle3 -= 1;
		break;

	case '1':
		IsCull = boolswitch(IsCull);
		if (IsCull)			glEnable(GL_CULL_FACE);
		else if (!IsCull)	glDisable(GL_CULL_FACE);
		break;

	case '2':
		IsDepth = boolswitch(IsDepth);
		if (IsDepth)		glEnable(GL_DEPTH_TEST);
		else if (!IsDepth)	glDisable(GL_DEPTH_TEST);
		break;

	case '3':
		IsSmooth = boolswitch(IsSmooth);
		break;
	}


	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y)
{

}

GLvoid MouseEvent(int button, int state, int x, int y)
{
	glutPostRedisplay();
}

GLvoid Timer(int val)
{
	angle += 0.1;
	if (angle > 360) angle = 0;

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