#include<iostream>
#include<time.h>

#include<gl\glut.h>

#define W_Width 800
#define W_Height 600


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keydown(unsigned char, int, int);



int w = 0;
int h = 0;
int rw = 0;
int rh = 0;
int chk = 1;


void main(int, char *)
{
	srand(unsigned(time(NULL)));
	w = rand() % 8 + 3;
	h = rand() % 8 + 3;
	rw = W_Width / w;
	rh = W_Height / h;


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");
	glutKeyboardFunc(Keydown);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	/*

	//실습 1
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glRectf(-1.0f, 1.0f, -0.5f, 0.5f);

	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glRectf(-1.0f, -1.0f, -0.5f, -0.5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRectf(-0.3f, 0.3f, 0.3f, -0.3f);

	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	glRectf(0.5f, 1.0f, 1.0f, 0.5f);

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glRectf(0.5f, -0.5f, 1.0f, -1.0f);
	glFlush();

	*/

	//실습 2

	for (int i = 0; i < h + 1; i++)
	{
		for (int j = 0; j < w + 1; j++)
		{
			if (chk == 1)
			{
				glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
				glRectf((float)j*rw, (float)i*rh, (float)(j + 1)*rw, (float)(i + 1)*rh);
				chk *= -1;
			}
			else
			{
				glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
				glRectf((float)j*rw, (float)i*rh, (float)(j + 1)*rw, (float)(i + 1)*rh);
				chk *= -1;
			}
		}
		if (w % 2 != 0)
			chk *= -1;
	}


	//glColor4f(0.0, 0.1, 0.1, 1.0);
	//glRectf(100, 100, 300, 300);

	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}


GLvoid Keydown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;
	case 'r':
		w = rand() % 8 + 3;
		h = rand() % 8 + 3;
		rw = W_Width / w;
		rh = W_Height / h;
		break;


	}
	glutPostRedisplay();
}