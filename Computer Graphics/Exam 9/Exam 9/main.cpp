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
	float radius;
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

GLvoid Circle(int, float, float);


Point pt[20];
int pt_index = 0;
int poly_count = 0;

int val_timer = 50;

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
	for (int i = 0; i < 50; i++)
		pt[i] = { 0,};

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
		if (pt_index > 9)
			pt_index = 0;
		pt[pt_index] = { (float)x,(float)W_Height - y};
		pt[pt_index].radius = 0;

		pt_index++;
		if (poly_count<10)
			poly_count++;
	}
	glutPostRedisplay();
}

GLvoid DrawPolygon(GLvoid)
{
	for (int index = 0; index < poly_count; index++)
	{
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glLineWidth(2);
		glPointSize(3);
		glBegin(GL_POINTS);
		for (float angle = 0; angle != 360; angle +=5)
		{
			Circle(index, pt[index].radius, angle);
		}

		glEnd();
	}
}

GLvoid Timer(int val)
{
	for (int index = 0; index < poly_count; index++)
	{
			pt[index].radius += 5;
	}

	glutPostRedisplay();
	glutTimerFunc(val_timer, Timer, 1); 
}

GLvoid Circle(int index, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	float circlex=0;
	float circley=0;
	
	circlex = (cos(angle)*radius + pt[index].x);
	circley = (sin(angle)*radius + pt[index].y);

	glVertex2f((cos(angle)*radius + pt[index].x), (sin(angle)*radius + pt[index].y));
}

