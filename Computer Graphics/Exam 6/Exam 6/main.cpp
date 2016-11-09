#include<iostream>
#include<time.h>

#include<gl\glut.h>

#define W_Width		800
#define W_Height	600
#define RectSize_X	30
#define RectSize_Y	20

struct Point
{
	float x;
	float y;
	float prev_x;
	float prev_y;
	int dir_x;
	int dir_y;
	int dir;				// 1 right 2 left 3 up 4 down
};

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


Point RectMove(Point);

int space_x;
int space_y;

Point pt[20];
int pt_index = 0;
int poly_count = 0;

int val_timer = 150;
int convert = 1;

int moveval = 0;	// 1 move 0 stop

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
		pt[i] = { 0,0,0,0,0,0,2 };

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

GLvoid MouseMove(int x, int y)
{

}

GLvoid MouseEvent(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < poly_count; i++)
		{
			if (x < pt[i].x + RectSize_X && x>pt[i].x - RectSize_X && W_Height - y > pt[i].y - 20 && W_Height - y < pt[i].y + 20)
			{
				moveval = 1;
				for (int j = 0; j < poly_count; j++) pt[j].dir = 1;
				return;
			}
		}

		if (pt_index > 9)	
			pt_index = 0;
		pt[pt_index] = { (float)x,(float)W_Height - y,(float)x,(float)W_Height - y };
		if (moveval) pt[pt_index].dir = 1;
		pt_index++;
		if (poly_count<10)
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
			glVertex2i(pt[j].x -RectSize_X, pt[j].y-RectSize_Y);
			glVertex2i(pt[j].x + RectSize_X, pt[j].y-RectSize_Y);
			glVertex2i(pt[j].x + RectSize_X, pt[j].y + RectSize_Y);
			glVertex2i(pt[j].x-RectSize_X, pt[j].y + RectSize_Y);
			glEnd();
		}
		else if (convert == -1)
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			for (int i = 0; i < 360; i++)
				Circle(j, 20.0, i);
			glEnd();
		}
	}
}

GLvoid Timer(int val)
{
	//convert *= -1;

	//CollideChk();

	for (int i = 0; i < poly_count; i++)
	{
		pt[i]=RectMove(pt[i]);
		pt[i].x += pt[i].dir_x;
		pt[i].y += pt[i].dir_y;
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

Point RectMove(Point P)
{
	enum dir { stop = 0, right, left, up, down };

	switch (P.dir)
	{
	case right:	//right
		P.x += 10;
		if (P.x + RectSize_X > W_Width)
		{
			P.x = W_Width - RectSize_X;
			P.dir = down;
		}
		
		break;

	case left:	//left
		P.x -= 10;
		if (P.x - RectSize_X < 0)
		{
			P.x = RectSize_X;
			P.dir = up;
			moveval = 2;
		}
		break;

	case up:	//up
		P.y += 10;
		if (P.y + RectSize_Y > P.prev_y)
		{
			P.y = P.prev_y;
			P.dir = right;
		}
		break;

	case down:	//down
		P.y -= 10;
		if (P.y - RectSize_Y < 0)
		{
			P.y = RectSize_Y;
			P.dir = left;
		}
		break;
	}
	if (moveval == 2 && P.x > P.prev_x && P.y == P.prev_y)
	{
		P.dir = stop;
	}

	return P;
}