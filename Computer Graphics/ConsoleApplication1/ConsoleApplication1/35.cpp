#include <gl/glut.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
#define SizeX 800
#define SizeY 600
#define SIZE 600
struct Object{
	int x, y, z;
};
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void SetupRC();
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
void TimerFunction(int value);
GLfloat ctrlPoints1[3][3][3] = { { { -SIZE / 10, 0.0, SIZE / 10 }, { -2.0, 0, SIZE / 10 }, { SIZE / 10, 0.0, SIZE / 10 } },
{ { -SIZE / 10, 0.0, 0.0 }, { -2.0, 0, 0.0 }, { SIZE / 10, 0.0, 0.0 } },
{ { -SIZE / 10, 0.0, -SIZE / 10 }, { -2.0, 0, -SIZE / 10 }, { SIZE / 10, 0.0, -SIZE / 10 } } };

GLfloat AmbientLight[] = { 0.0f, 1.0f, 1.0f, 1.0f };
GLfloat DiffuseLight[] = { 1.0f, 1.0f, 0.0f, 1.0f };
GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightPos[] = { 100.0f, 200.0f, 3.0f, 1.0f };
bool Light;
int wave;
GLuint texture[1];
GLubyte *pBytes;
BITMAPINFO *info;

Object Hero;
int WRotY, WRotX;
int LRotY;
int CarRot;
void main(int argc, char *argv[])
{

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(SizeX, SizeY);
	glutCreateWindow("Example2");
	SetupRC();
	glutTimerFunc(40, TimerFunction, 1);
	glutTimerFunc(50, TimerFunction, 2);
	glutTimerFunc(300, TimerFunction, 4);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(WRotY, 0, 1, 0);
	glRotatef(WRotX, 1, 0, 0);
	//glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	{
		glPushMatrix();
		glTranslatef(Hero.x, Hero.y, Hero.z);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(20, 40, 10, 10);
		glPopMatrix();
	}
	{
		glPushMatrix();
		glTranslatef(150, 150, 0);
		glRotatef(CarRot, 0, 0, 1);
		for (int i = 0; i < 10; i++){
			glPushMatrix();
			glRotatef(36*i, 0, 0, 1);
			glTranslatef(50, 0, 0);
			glScalef(10, 1, 1);
			glutSolidCube(10);
			glPopMatrix();
		}

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		for (int i = 0; i < 10; i++){
			glPushMatrix();
			glRotatef(36 * i, 0, 0, 1);
			glTranslatef(100, 0, 0);
			glRotatef(-36 * i, 0, 0, 1);
			glRotatef(-CarRot, 0, 0, 1);
			glutSolidCube(20);
			glPopMatrix();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();
		glTranslatef(150, 10, 150);
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlPoints1[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		glEvalMesh2(GL_FILL, 0, 10, 0, 10);

		glPointSize(2.0);
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3fv(ctrlPoints1[i][j]);
		glEnd();

		glPushMatrix();
		glTranslatef(-55,0,0);
		glScalef(1, 1, 15);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(55, 0, 0);
		glScalef(1, 1, 15);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(-60, 0, 0);
		glScalef(1, 1, 15);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(60, 0, 0);
		glScalef(1, 1, 15);
		glutSolidCube(10);
		glPopMatrix();

		glPopMatrix();


	}
 
	glPushMatrix();
	glTranslatef(-SIZE / 2, 0, -SIZE / 2);
	{
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);

		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glBegin(GL_QUADS);


		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0, 0, 0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0, 0, SIZE);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(SIZE, 0, SIZE);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(SIZE, 0, 0);

		//zy평면

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0, SIZE, 0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0, 0, 0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(SIZE, 0, 0);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(SIZE, SIZE, 0);



		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-150,100,-150);
	glRotatef(LRotY, 0, 1, 0);
	glRotatef(45, 1, 0, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glColor4f(0.0, 0.0, 1.0, 0.5);
	glutSolidCube(40);
	
	glPushMatrix();

	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	glRotatef(45, 1, 1, 0);
	glutSolidCube(100);
	
	glPopMatrix();

	glDisable(GL_BLEND);
	glPopMatrix(); 

	glPopMatrix();
	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, w / h, 10, 1000);
	gluLookAt(0, 100, 500, 0, 100, 0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);

}


void SpecialKeyboard(int key, int x, int y)
{
	switch (key){
	case GLUT_KEY_RIGHT:
		WRotY += 10;
		if (360 <= WRotY)
			WRotY = 0;
		break;
	case GLUT_KEY_LEFT:
		WRotY -= 10;
		if (WRotY <= -360)
			WRotY = 0;
		break;
	case GLUT_KEY_UP:
		WRotX += 10;
		if (360 <= WRotX)
			WRotX = 0;
		break;
	case GLUT_KEY_DOWN:
		WRotX -= 10;
		if (WRotX <= -360)
			WRotX = 0;
		break;
	
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key){
	case 'l':
		if (Light)
			glDisable(GL_LIGHT0);
		else
			glEnable(GL_LIGHT0);

		Light = !Light;
		break;
	case 'w':
		Hero.z -= 10;
		break;
	case 'a':
		Hero.x -= 10;
		break;
	case 's':
		Hero.z += 10;
		break;
	case 'd':
		Hero.x += 10;
		break;
	case 'z':
		Hero.y += 30;
		glutTimerFunc(100, TimerFunction, 3);
		break;
	}

	glutPostRedisplay();
}
void SetupRC(){

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	Light = true;

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	pBytes = LoadDIBitmap("t6.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	wave = -5;
	LRotY = 0;
	Hero.x = -100;
	Hero.y = 0;
	Hero.z = 100;
}
void TimerFunction(int value)
{
	switch (value)
	{
	case 1:
		LRotY += 10;
		if (360 <= LRotY)
			LRotY = 0;
		glutTimerFunc(40, TimerFunction, 1);
		break;
	case 2:
		for (int i = 0; i<3; i++){
			ctrlPoints1[i][1][1] += wave;
		}

		if (30 <= abs(ctrlPoints1[0][1][1]))
			wave *= -1;
		glutTimerFunc(50, TimerFunction, 2);
		break;
	case 3:
		Hero.y -= 30;
		break;
	case 4:
		CarRot += 10;
		if (360 <= CarRot)
			CarRot = 0;
		glutTimerFunc(300, TimerFunction, 4);
		break;
	default:
		break;
	}
	glutPostRedisplay();

}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if (0 < x && x < SizeX / 3){
			for (int i = 0; i < 3; i++)
				ctrlPoints1[i][1][1] = SizeY - y;
		}
	}
	glutPostRedisplay();
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
	infosize = header.bfOffBits - sizeof (BITMAPFILEHEADER);
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