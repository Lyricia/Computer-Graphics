#include<iostream>
#include<time.h>
#include<math.h>

#include<gl\glut.h>

#define W_Width		800
#define W_Height	600


enum motion{ stop = 0, move };

struct Point
{
	float x;
	float y;
	int Rect_x;
	int Rect_y;
	int dir_x;
	int dir_y;
	int dir;				// 1 right 2 left 3 up 4 down
	float rad;
};

GLvoid RegesterCallBack();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLvoid Timer(int);
GLvoid Keydown(unsigned char, int, int);
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid init(GLvoid);

GLvoid DrawPolygon(GLvoid);
GLvoid CollideChk(GLvoid);

GLvoid Circle(int, float, float);

int space_x;
int space_y;

Point pt[20];
int pt_index = 0;
int poly_count = 0;

int val_timer = 50;
int convert = 1;

int targetx = 0;
int targety = 0;

int moveval = motion::stop;

void main(int, char *)
{
	srand(unsigned(time(NULL)));

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
	space_x = W_Width / 3;
	space_y = W_Height / 3;

	for (int i = 0; i < 50; i++)
		pt[i] = { 0,0,0,0,0,0,2,20.0 };

}

GLvoid RegesterCallBack()
{
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

	case 'u':
		val_timer -= 10;
		if (val_timer < 20) val_timer = 20;
		break;

	case 'd':
		val_timer += 10;
		break;

	case 'e':
		break;
	}

	glutPostRedisplay();
}

GLvoid MouseMove(int mouse_x, int mouse_y)
{
	targetx = mouse_x;
	targety = mouse_y;
}

GLvoid MouseEvent(int button, int state, int mouse_x, int mouse_y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pt_index > 9)
			pt_index = 0;
		pt[pt_index] = { (float)mouse_x,(float)W_Height - mouse_y };
		pt[pt_index].Rect_x = 20 + rand() % 40;
		pt[pt_index].Rect_y = 10 + rand() % 40;
		pt_index++;
		if (poly_count<10)
			poly_count++;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		moveval = motion::move;
		targetx = mouse_x;
		targety = mouse_y;
	}
	if (state == GLUT_UP)
		moveval = motion::stop;
	
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
			glVertex2i(pt[j].x - pt[j].Rect_x, pt[j].y - pt[j].Rect_y);
			glVertex2i(pt[j].x + pt[j].Rect_x, pt[j].y - pt[j].Rect_y);
			glVertex2i(pt[j].x + pt[j].Rect_x, pt[j].y + pt[j].Rect_y);
			glVertex2i(pt[j].x - pt[j].Rect_x, pt[j].y + pt[j].Rect_y);
			glEnd();
		}
		else if (convert == -1)
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glPointSize(3);
			glBegin(GL_POINTS);
			for (int i = 0; i < 360; i += 5)
				Circle(j, pt[j].rad, i);
			glEnd();
		}
	}
}

GLvoid Timer(int val)
{
	if (moveval)
	{
		for (int i = 0; i < poly_count; i++)
		{
			pt[i].x = (targetx + pt[i].x * 9) / 10;
			pt[i].y = ((W_Height-targety) + pt[i].y * 9) / 10;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(val_timer, Timer, 1);
}


GLvoid CollideChk()
{
	for (int i = 0; i < poly_count; i++)
	{
		if (pt[i].x < 0)
		{
			pt[i].dir_x = 10;
			pt[i].dir_y = 0;
		}

		else if (pt[i].y < 0)
		{
			pt[i].dir_y = 10;
			pt[i].dir_x = 0;
		}

		else if (pt[i].x > W_Width)
		{
			pt[i].dir_x = -10;
			pt[i].dir_y = 0;
		}
		else if (pt[i].y > W_Height)
		{
			pt[i].dir_y = -10;
			pt[i].dir_x = 0;
		}
	}
}

GLvoid Circle(int index, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex2f(cos(angle)*radius + pt[index].x, sin(angle)*radius + pt[index].y);
}