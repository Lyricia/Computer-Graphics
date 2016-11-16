#include<iostream>
#include<time.h>

#include<gl\glut.h>

#define W_Width		800
#define W_Height	600

GLvoid RegesterCallBack();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLvoid Timer(int);
GLvoid Keydown(unsigned char, int, int);
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid init(GLvoid);


GLvoid DrawPolygon(GLvoid);


struct Point
{
	int x;
	int y;
	int end;
};



int space_x;
int space_y;

Point pt[10];
int pt_index = 0;
int poly_count = 0;

int val_timer = 150;
int convert = 1;

void main(int, char *)
{
	init();

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	RegesterCallBack();

	glutMainLoop();
}

GLvoid init(GLvoid)
{
	space_x = W_Width/ 3;
	space_y = W_Height / 3;

	for (int i = 0; i < 50; i++)
		pt[i] = { 0,0,2 };

}

GLvoid RegesterCallBack()
{
	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMove);
	glutKeyboardFunc(Keydown);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(val_timer,Timer,1);
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	//glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	//glLineWidth(5);
	//glBegin(GL_LINES);
	//{
	//	glVertex2i(space_x, 0);
	//	glVertex2i(space_x, W_Height);
	//	glVertex2i(space_x * 2, 0);
	//	glVertex2i(space_x * 2, W_Height);
	//
	//	glVertex2i(0, space_y);
	//	glVertex2i(W_Width, space_y);
	//	glVertex2i(0, space_y * 2);
	//	glVertex2i(W_Width, space_y * 2);
	//}
	//glEnd();

	DrawPolygon();

	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, W_Width, 0.0, W_Height, -1.0, 1.0);
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

	case 'e':
		if (pt_index > 0)
			pt[pt_index - 1].end = 1;
		break;
	}

	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y)
{

}

GLvoid MouseEvent(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pt_index > 9)	pt_index = 0;

		pt[pt_index] = { x,W_Height - y,0 };
		pt_index++;
		if(poly_count<10)
			poly_count++;
	}
	glutPostRedisplay();
}

GLvoid DrawPolygon(GLvoid)
{
	for (int j = 0; j < poly_count; j++)
	{
		if (convert == 1)
		{
			glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex2i(pt[j].x, pt[j].y);
			glVertex2i(pt[j].x + 20, pt[j].y);
			glVertex2i(pt[j].x + 20, pt[j].y + 10);
			glVertex2i(pt[j].x, pt[j].y + 10);
			glEnd();
		}
		else if (convert == -1)
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex2i(pt[j].x, pt[j].y);
			glVertex2i(pt[j].x + 10, pt[j].y);
			glVertex2i(pt[j].x + 10, pt[j].y + 20);
			glVertex2i(pt[j].x, pt[j].y + 20);
			glEnd();
		}

	}
}

GLvoid Timer(int val)
{
	convert *= -1;
	glutPostRedisplay();
	glutTimerFunc(val_timer, Timer, 1);
}
