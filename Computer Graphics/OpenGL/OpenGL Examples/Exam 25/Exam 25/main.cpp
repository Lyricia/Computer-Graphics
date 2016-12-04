#include <iostream>
#include <time.h>
#include <string>
#include <gl\glut.h>

#define W_Width		800
#define W_Height	600
#define W_Depth		800

struct Vertex
{
	float x;
	float y;
	float z;
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
GLvoid Circle(Vertex P, float radius, float angle);

void drawText(char * string, float x, float y, float z);


float ctrlpoints[30][3];
int pointcounter;
char text[2];

void main(int, char *)
{
	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	RegesterCallBack();

	glutMainLoop();
}

GLvoid init(GLvoid)
{
	srand(unsigned(time(NULL)));

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

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	DrawPolygon();

	drawText("STRING", 0, 0, 0);
	glutSwapBuffers();
}

GLvoid DrawLines()
{

}

GLvoid DrawPolygon(GLvoid)
{
	for (int i = 0; i < 9; i++)
	{
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[i * 3][0]);

		glEnable(GL_MAP1_VERTEX_3);

		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 30; i++)
			glEvalCoord1f((GLfloat)i / 30.0);
		glEnd();

		glDisable(GL_MAP1_VERTEX_3);
	}

	glPointSize(5.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < pointcounter; i++)
		glVertex3fv(&ctrlpoints[i][0]);
	glEnd();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-W_Width / 2, W_Width / 2, -W_Height / 2, W_Height / 2, -W_Depth / 2, W_Depth / 2);
	glMatrixMode(GL_MODELVIEW);
}


GLvoid Keydown(unsigned char key, int x, int y)
{
	switch (key){
	case 'q':
		exit(0);
		break;

	case 'r':
		init();
		break;

	case 'u':
		break;

	case 'd':
		break;

	case 'e':
		memset(ctrlpoints, 0, sizeof(ctrlpoints));
		pointcounter = 0;
		break;
	}

	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y)
{

}

GLvoid MouseEvent(int button, int state, int x, int y)
{
	switch (button) 
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) 
		{
			ctrlpoints[pointcounter][0] = x - 400;
			ctrlpoints[pointcounter][1] = 300 - y;
			ctrlpoints[pointcounter][2] = 0;

			if(pointcounter<27)
				pointcounter++;	

			for (int i = pointcounter; i < 30; i++)
			{
				ctrlpoints[i][0] = x - 400;
				ctrlpoints[i][1] = 300 - y;
				ctrlpoints[i][2] = 0;
			}
		}
		break;
	case GLUT_RIGHT_BUTTON: 
		break;
	}
	glutPostRedisplay();
}


GLvoid Timer(int val)
{
 	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

GLvoid Circle(Vertex P, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex2f(cos(angle)*radius + P.x, sin(angle)*radius + P.y);
}

void drawText(char *string, float x, float y, float z)
{
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}
