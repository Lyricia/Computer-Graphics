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

GLvoid Menu(int);
GLvoid DrawPolygon(GLvoid);
GLvoid CollideChk(GLvoid);

GLvoid Circle(int, float, float);


struct Point
{
	float x;
	float y;
	int dir_x;
	int dir_y;
	int live;
	float rad;
	float rad_dir;
};


Point pt[20];
int pt_index = 0;
int poly_count = 0;

int val_timer = 150;
int convert = -1;

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
	srand(unsigned(time(NULL)));

	for (int i = 0; i < 50; i++)
		pt[i] = { 0,0,0,0,1,30,5 };

}

GLvoid RegesterCallBack()
{
	glutCreateMenu(Menu);
	glutAddMenuEntry("Rect", 1);
	glutAddMenuEntry("Circle", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMove);
	glutKeyboardFunc(Keydown);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(val_timer, Timer, 1);
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glLineWidth(5);
	glBegin(GL_LINES);
	{
		glVertex2i(150, 150);
		glVertex2i(150, W_Height - 150);
		glVertex2i(W_Width - 150, 150);
		glVertex2i(W_Width - 150, W_Height - 150);

		glVertex2i(150, 150);
		glVertex2i(W_Width - 150, 150);
		glVertex2i(150, W_Height - 150);
		glVertex2i(W_Width - 150, W_Height - 150);
	}
	glEnd();

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

	case 'u':
		val_timer -= 10;
		if (val_timer < 50) val_timer = 50;
		break;

	case 'd':
		val_timer += 10;
		break;

	case 'e':
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
		if (pt_index > 19)	pt_index = 0;

		pt[pt_index] = {
			(float)x,
			(float)W_Height - y
		};

		if (rand() % 2)	pt[pt_index].dir_x = -(rand() % 25);
		else			pt[pt_index].dir_x = rand() % 25;

		if (rand() % 2)	pt[pt_index].dir_y = -(rand() % 25);
		else			pt[pt_index].dir_y = rand() % 25;

		pt[pt_index].live = 1;
		pt[pt_index].rad = 20.0;
		pt[pt_index].rad_dir = 5.0;
		pt_index++;
		if (poly_count<19)
			poly_count++;
	}
	glutPostRedisplay();
}

GLvoid DrawPolygon(GLvoid)
{
	for (int index = 0; index < poly_count; index++)
	{
		if (convert == 1 && pt[index].live == 1)
		{
			glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex2i(pt[index].x, pt[index].y);
			glVertex2i(pt[index].x + 20, pt[index].y);
			glVertex2i(pt[index].x + 20, pt[index].y + 10);
			glVertex2i(pt[index].x, pt[index].y + 10);
			glEnd();
		}
		else if (convert == -1 && pt[index].live == 1)
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glPointSize(3);
			glBegin(GL_POINTS);
			for (int i = 0; i < 360; i += 10)
				Circle(index, pt[index].rad, i);
			glEnd();
		}

	}
}

GLvoid Timer(int val)
{
	//convert *= -1;

	CollideChk();

	for (int i = 0; i < poly_count; i++)
	{
		pt[i].x += pt[i].dir_x;
		pt[i].y += pt[i].dir_y;
		pt[i].rad += pt[i].rad_dir;

		if (pt[i].rad > 30)
			pt[i].rad_dir = -5;
		else if (pt[i].rad < 10)
			pt[i].rad_dir = 5;
	}



	glutPostRedisplay();
	glutTimerFunc(val_timer, Timer, 1);
}


GLvoid CollideChk()
{
	for (int i = 0; i < poly_count; i++)
	{
		if (pt[i].x - 20 < 150 || pt[i].y - 20 < 150 || pt[i].x + 20 > W_Width - 150 || pt[i].y + 20 > W_Height - 150)
		{
			pt[i].live = 0;
			pt[i].rad = 0;
		}
	}

}

GLvoid Menu(int button)
{
	switch (button)
	{
	case 1:
		convert = 1;
		break;
	case 2:
		convert = -1;
		break;
	}
	glutPostRedisplay();
}

GLvoid Circle(int index, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex2f(cos(angle)*radius + pt[index].x, sin(angle)*radius + pt[index].y);
}