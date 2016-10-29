#include <iostream>
#include <ctime>
#include <cmath>
#include <gl\glut.h>

#define W_Width		500
#define W_Height	800

enum Polytype { TRI = 3, RECT, PENTA, HEX };

typedef struct
{
	float x;
	float y;
} Point;

struct Poly
{
	int vertexnum; // using Polytype
	int ypos;
	int dropline;
	Point vertex[100];
};


GLvoid RegesterCallBack();

GLvoid drawScene(GLvoid);
GLvoid LineDraw();
GLvoid DrawPoly();
GLvoid Reshape(int w, int h);

GLvoid Timer(int);
GLvoid Keydown(unsigned char, int, int);
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid initpoly();

Point InterSectPoint(Point func_p1, Point func_p2, Point clip_p1, Point clip_p2);
GLvoid ClippingChk();
bool ChkVertexin(Point target);
GLvoid OrderCWVertex();
Point Circle(float x, float y, float radius, float angle);


Poly poly;
Poly ClipStdPoly;
Poly cliped;
int val_timer = 10;
float radius = 70.0;

void main()
{
	initpoly();

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	RegesterCallBack();

	glutMainLoop();
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

GLvoid initpoly()
{
	ClipStdPoly.dropline = 2;
	ClipStdPoly.vertexnum = RECT;
	ClipStdPoly.ypos = 200;

	for (int i = 0; i < ClipStdPoly.vertexnum; i++)
		ClipStdPoly.vertex[i] = Circle(50 + (ClipStdPoly.dropline - 1) * 100, ClipStdPoly.ypos, radius, 360 / ClipStdPoly.vertexnum * i);

	 
	poly.dropline = 2;
	poly.vertexnum = RECT;
	poly.ypos = 250;

	for (int i = 0; i < poly.vertexnum; i++)
		poly.vertex[i] = Circle(50 + (poly.dropline - 1) * 100, poly.ypos, radius, 360 / poly.vertexnum * i);

	cliped.dropline = NULL;
	cliped.vertexnum = 0;
	cliped.ypos = NULL;
	for (int i = 0; i < cliped.vertexnum; i++)
		cliped.vertex[i] = { 0,0 };

}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	LineDraw();

	DrawPoly();

	glFlush();
}

GLvoid LineDraw()
{
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glLineWidth(2);
	glBegin(GL_LINES); //guide lines
	{
		for (int lineidx = 0; lineidx < 6; lineidx++)
		{
			glVertex2i((W_Width / 5) * lineidx, 0);
			glVertex2i((W_Width / 5) * lineidx, 800);
		}

		glVertex2i(0, (W_Width / 5));
		glVertex2i(W_Width, (W_Width / 5));
	}
	glEnd();
}


GLvoid DrawPoly()
{
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON); 
	for (int i = 0; i < poly.vertexnum; i++)
		glVertex2i(poly.vertex[i].x, poly.vertex[i].y);
	glEnd();


	glColor4f(1.0f, 0.5f, 0.0f, 1.0f);
	glBegin(GL_POLYGON); 
	for (int i = 0; i < ClipStdPoly.vertexnum; i++)
		glVertex2i(ClipStdPoly.vertex[i].x, ClipStdPoly.vertex[i].y);
	glEnd();

	glColor4f(0.0f, 0.5f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN); 
	for (int i = 0; i < cliped.vertexnum; i++)
		glVertex2i(cliped.vertex[i].x, cliped.vertex[i].y);
	glEnd();

}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, W_Width, W_Height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, W_Width, 0.0, W_Height, -1.0, 1.0);
}


GLvoid Keydown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;

	case 'w':
		poly.ypos += 10;
		break;

	case 's':
		poly.ypos -= 10;
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
	glutPostRedisplay();
}


GLvoid Timer(int val)
{
	for (int i = 0; i < ClipStdPoly.vertexnum; i++)
		ClipStdPoly.vertex[i] = Circle(50 + (ClipStdPoly.dropline - 1) * 100, ClipStdPoly.ypos, radius, 360 / ClipStdPoly.vertexnum * i);
	for (int i = 0; i < poly.vertexnum; i++)
		poly.vertex[i] = Circle(50 + (poly.dropline - 1) * 100, poly.ypos, radius, 360 / poly.vertexnum * i);
	
	ClippingChk();

	glutPostRedisplay();
	glutTimerFunc(val_timer, Timer, 1);
}

Point InterSectPoint(Point func_p1, Point func_p2, Point clip_p1, Point clip_p2)		// func = dropping polygon edge, clip = clipping area edge
{
	float func;
	float clip;
	
	Point data;
	data = { -100,-100 };

	float under = (clip_p2.y - clip_p1.y) * (func_p2.x - func_p1.x) - (clip_p2.x - clip_p1.x)*(func_p2.y - func_p1.y);
	if (under == 0) return data;

	float upperfunc = (clip_p2.x - clip_p1.x)*(func_p1.y - clip_p1.y) - (clip_p2.y - clip_p1.y)*(func_p1.x - clip_p1.x);
	float upperclip = (func_p2.x - func_p1.x)*(func_p1.y - clip_p1.y) - (func_p2.y - func_p1.y)*(func_p1.x - clip_p1.x);

	func = upperfunc / under;
	clip = upperclip / under;

	if (clip < 0.0 || clip > 1.0 || func < 0.0 || func > 1.0) return data;
	if (upperfunc == 0 && upperclip == 0) return data;

	data.x = func_p1.x + func * (float)(func_p2.x - func_p1.x);
	data.y = func_p1.y + func * (float)(func_p2.y - func_p1.y);

	return data;
}


GLvoid ClippingChk()
{
	Point tmp;
	cliped.vertexnum = 0;
	memset(cliped.vertex, NULL, sizeof(cliped.vertex));

	if (poly.ypos < 400)
	{
		//chk line intersection from 0 to end step by step
		for (int pt_dropidx = 0; pt_dropidx < poly.vertexnum-1; pt_dropidx++)
		{
			for (int pt_clipidx = 0; pt_clipidx < ClipStdPoly.vertexnum-1; pt_clipidx++)
			{
				tmp = InterSectPoint(poly.vertex[pt_dropidx], poly.vertex[pt_dropidx + 1], ClipStdPoly.vertex[pt_clipidx], ClipStdPoly.vertex[pt_clipidx + 1]);
				if (tmp.x != -100)
				{
					cliped.vertex[cliped.vertexnum] = tmp;
					cliped.vertexnum++;
				}
				tmp = { -100,-100 };
			}
		}

		for (int pt_dropidx = 0; pt_dropidx < poly.vertexnum - 1; pt_dropidx++)
		{
			tmp = InterSectPoint(poly.vertex[pt_dropidx], poly.vertex[pt_dropidx + 1], ClipStdPoly.vertex[ClipStdPoly.vertexnum - 1], ClipStdPoly.vertex[0]);
			if (tmp.x != -100)
			{
				cliped.vertex[cliped.vertexnum] = tmp;
				cliped.vertexnum++;
			}
			tmp = { -100,-100 };
		}

		for (int pt_clipidx = 0; pt_clipidx < ClipStdPoly.vertexnum - 1; pt_clipidx++)
		{
			tmp = InterSectPoint(poly.vertex[poly.vertexnum - 1], poly.vertex[0], ClipStdPoly.vertex[pt_clipidx], ClipStdPoly.vertex[pt_clipidx + 1]);
			if (tmp.x != -100)
			{
				cliped.vertex[cliped.vertexnum] = tmp;
				cliped.vertexnum++;
			}
			tmp = { -100,-100 };
		}
		tmp = InterSectPoint(poly.vertex[poly.vertexnum - 1], poly.vertex[0], ClipStdPoly.vertex[ClipStdPoly.vertexnum - 1], ClipStdPoly.vertex[0]);
		if (tmp.x != -100)
		{
			cliped.vertex[cliped.vertexnum] = tmp;
			cliped.vertexnum++;
		}
		tmp = { -100,-100 };
	}

	for (int i = 0; i < poly.vertexnum; i++)
	{
		if (ChkVertexin(poly.vertex[i]))
		{
			cliped.vertex[cliped.vertexnum] = poly.vertex[i];
			cliped.vertexnum++;
		}
	}

}

bool ChkVertexin(Point target)
{
	//InterSectPoint(Point func_p1, Point func_p2, Point clip_p1, Point clip_p2)
	Point temp;
	for (int i = 0; i < ClipStdPoly.vertexnum; i++)
	{
		temp = InterSectPoint({ 150.0 , 100.0 }, target, ClipStdPoly.vertex[i%ClipStdPoly.vertexnum], ClipStdPoly.vertex[i%ClipStdPoly.vertexnum + 1]);
		if (temp.x != -100)
		{
			return false;
		}
	}
	return true;
}

GLvoid OrderCWVertex()
{
	

}


Point Circle(float x, float y, float radius, float angle)
{
	Point P;
	angle = angle * (3.141592 / 180);

	P.x = cos(angle)*radius + x;
	P.y = sin(angle)*radius + y;

	return P;
}