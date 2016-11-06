#include<iostream>
#include<time.h>

#include<gl\glut.h>

#define W_Width		800
#define W_Height	600
#define W_Depth		800
#define RAD(angle)	angle*(3.141592 / 180)

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

GLvoid DrawLines();
GLvoid Circle(Vertex P, float radius, float angle);
GLvoid DrawPolygon(GLvoid);

int TimerVal = 10;

Vertex v_Model = { 0, };
float Scale = 1;
int Angle = 0;

float xpos = 0;
float xdir = 1;
float ypos = 0;
float ydir = 1;

float tor_angle = 0;
float tor_angle_dir = 0.5;
float angledir = 1;

enum Mov {Round, Sin, Tornado, ZigZag, Userpath};

bool ScaleReverse = false;
bool isRect = false;

int Path = Mov::Round;
bool Obj_Movement = false;

Vertex UserPoint[5] = { 0, };
int PointIdx = 0;
bool isRunning = false;

int PathMoveCounter = 0;
int timecount = 0;

void main()
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
	glutTimerFunc(TimerVal, Timer, 1);
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	DrawLines();

	glLoadIdentity();
	if (Path == Round)
	{
		glPushMatrix();
		{
			if (Obj_Movement)
			{
				glRotatef(Angle, 0, 0, 1);
				glTranslatef(0, 200, 0);
			}
			else if (!Obj_Movement)
			{
				glTranslatef(cos(RAD((float)Angle)) * 200, sin(RAD((float)Angle)) * 200, 0.f);
			}
			glScalef(Scale, Scale, Scale);
			DrawPolygon();
		}
		glPopMatrix();
	}
	else if (Path == Sin)
	{
		glPushMatrix();
		{
			glTranslatef(xpos, sin(RAD((float)xpos)) * 100, 0.f);
			glScalef(Scale, Scale, Scale);
			DrawPolygon();
		}
		glPopMatrix();
	}
	else if (Path == Tornado)
	{
		glScalef(0.5, 0.5, 0.5);
		glPushMatrix();
		{
			if (Obj_Movement)
			{
				glRotatef(Angle, 0, 0, 1);
				glTranslatef(tor_angle, 0, 0);
			}
			else if (!Obj_Movement)
			{
				glTranslatef(cos(RAD((float)Angle)) * tor_angle, sin(RAD((float)Angle)) * tor_angle, 0.f);
			}
			glScalef(Scale, Scale, Scale);
			DrawPolygon();
		}
		glPopMatrix();
	}
	else if (Path == ZigZag)
	{
		glPushMatrix();
		{
			glTranslatef(xpos, ypos, 0.f);
			glScalef(Scale, Scale, Scale);
			DrawPolygon();
		}
		glPopMatrix();
	}
	else if (Path == Userpath && isRunning)
	{
		glPushMatrix();
		{
			glTranslatef(xpos, ypos, 0.f);
			glScalef(Scale, Scale, Scale);
			DrawPolygon();
		}
		glPopMatrix();
	}

	glutSwapBuffers();
}

GLvoid DrawPolygon()
{
	glPointSize(10);
	glBegin(GL_POLYGON);
	if (!isRect)
	{
		for (int i = 0; i < 3; i++)
			Circle(v_Model, 50, 90 + (120 * i));
	}
	else
	{
		for (int i = 0; i < 4; i++)
			Circle(v_Model, 50, 45 + (90 * i));
	}
	glEnd();
}

GLvoid DrawLines()
{
	glBegin(GL_LINES);
		glVertex3f(-W_Width, 0.0,0.0);
		glVertex3f(W_Width, 0.0, 0.0);
		 
		glVertex3f(0.0, -W_Height, 0.0);
		glVertex3f(0.0, W_Height, 0.0);

		glVertex3f(0.0, 0.0, -W_Depth);
		glVertex3f(0.0, 0.0, W_Depth);
	glEnd();

	glBegin(GL_LINE_STRIP);
	if (Path == Round)
	{
		for (int i = 0; i < 360; i++)
			Circle(v_Model, 200, i);
	}
	else if(Path == Sin)
	{
		for (float angle= -400.f; angle < 400.f; angle++)
			glVertex2f(angle, sin((float)RAD(angle))*100);
	}
	else if (Path == Tornado)
	{
		float rad = 0;
		for (int i = 0; i < 360 * 3; i++)
		{
			Circle(v_Model, rad, i);
			rad += 0.5;
		}
	}
	else if (Path == ZigZag)
	{
		int ypos = 100;
		for (int i = 0; i < 10; i++)
		{
			glVertex3f(-400 + (100 * i), ypos, 0);
			ypos *= -1;
		}
	}
	else if (Path == Userpath)
	{
		for (int i = 0; i < PointIdx; i++) 
		{
			glVertex3f(UserPoint[i].x, UserPoint[i].y, UserPoint[i].z);
 		}
	}
	glEnd();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-W_Width / 2, W_Width / 2, -W_Height / 2, W_Height / 2, -W_Depth/2, W_Depth/2);
	glMatrixMode(GL_MODELVIEW);
}

 
GLvoid Keydown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;

	case 'r':
		if (isRect) isRect = false;
		else isRect = true;
		break;

	case 'u':
		Angle += 10;
		break;

	case 'd':
		if (Obj_Movement) Obj_Movement = false;
		else Obj_Movement = true;
		break;

	case '1':
		Path = Round;
		Angle = 0;
		Scale = 1.5;
		break;
	case '2':
		Path = Sin;
		Angle = 0;
		Scale = 1.5;
		xpos = 0;
		xdir = 1;
		break;
	case '3':
		Path = Tornado;
		Angle = 0;
		tor_angle = 0;
		tor_angle_dir = 0.5;
		Scale = 1.5;
		break;
	case '4':
		Path = ZigZag;
		Angle = 0;
		Scale = 1.5;
		xpos = 0;
		ypos = 100;
		xdir = 1;
		ydir = -2;
		break;
	case '5':
		Path = Userpath;
		memset(UserPoint, 0, sizeof(UserPoint));
		PointIdx = 0;
		break;
	}
	glutPostRedisplay();
} 

GLvoid MouseMove(int x, int y)
{

}

GLvoid MouseEvent(int button, int state, int x, int y)
{
	if (Path == Userpath)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (PointIdx < 5)
			{
				UserPoint[PointIdx] = { (float)x - 400, 300 - (float)y, 0 };
				PointIdx++;
			}
		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			isRunning = true;
			xpos = UserPoint[0].x;
			ypos = UserPoint[0].y;
			xdir = (UserPoint[1].x - UserPoint[0].x) / 50;
			ydir = (UserPoint[1].y - UserPoint[0].y) / 50;
			PathMoveCounter = 0;
			timecount = 0;
		}
	}
	glutPostRedisplay();
}

GLvoid Timer(int val)
{
	
	if (Scale < 2 && ScaleReverse == false)		Scale += 0.05;
	else if (Scale > 1 && ScaleReverse == true) Scale -= 0.05;

	if (Scale > 2)	ScaleReverse = true;
	else if (Scale < 1) ScaleReverse = false;
	
	if (Path == Round)
		Angle = (Angle + 1) % 360;
	else if (Path == Sin)
	{
		Angle = (Angle + 1) % 360;
		if (xpos < -400)		xdir = 1;
		else if (xpos > 400)	xdir = -1;
		xpos += xdir;
	}
	else if (Path == Tornado)
	{
		if (tor_angle < 0)
		{
			tor_angle_dir = 0.5;
			angledir = 1;
		}
		else if (tor_angle > 360 * 1.5)
		{
			tor_angle_dir = -0.5;
			angledir = -1;
		}
		tor_angle += tor_angle_dir;
		Angle += angledir;
	}
	else if (Path == ZigZag)
	{
		if (xpos < -400)		xdir = 1;
		else if (xpos > 400)	xdir = -1;
		xpos += xdir;
		
		if (ypos < -100)		ydir = 2;
		else if (ypos > 100)	ydir = -2;
		ypos += ydir;
	}
	else if (Path == Userpath)
	{
		if (timecount > 50 && PathMoveCounter < PointIdx)
		{
			timecount = 0;
			PathMoveCounter++;
			xdir = (UserPoint[PathMoveCounter+1].x - UserPoint[PathMoveCounter].x) / 50;
			ydir = (UserPoint[PathMoveCounter+1].y - UserPoint[PathMoveCounter].y) / 50;
		}
		else if (PathMoveCounter == PointIdx-1)
		{
			xdir = 0;
			ydir = 0;
		}
		xpos += xdir;
		ypos += ydir;
		if (isRunning && xdir != 0)
			timecount++;
	}
	glutPostRedisplay();
	glutTimerFunc(TimerVal, Timer, 1);
}

GLvoid Circle(Vertex P, float radius, float angle)
{
	angle = angle * (3.141592 / 180);

	glVertex2f(cos(angle)*radius + P.x, sin(angle)*radius + P.y);
}