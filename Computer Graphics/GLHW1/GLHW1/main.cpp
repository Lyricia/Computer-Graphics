#include <iostream>
#include <ctime>
#include <cmath>
#include <gl\glut.h>

#define W_Width		600
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
	int xpos;
	int ypos;
	int dropline;
	Point vertex[100];
	int rot;
	int scale;
	int shear;
};


GLvoid RegesterCallBack();

Point shearing(Point p, int val);

GLvoid drawScene(GLvoid);
GLvoid LineDraw();
GLvoid DrawPoly();
GLvoid Reshape(int w, int h);

GLvoid Timer(int);
GLvoid Keydown(unsigned char, int, int);
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid initpoly();

Poly VertexSetting(Poly srtpoly);

Point rotate(Point p, int angle);
Point scale(Point p, int val);

bool InterSectPoint(const Point func_p1, const Point func_p2, const Point clip_p1, const Point clip_p2, Point &Vertex);
GLvoid ClippingChk(int index);
bool ChkVertexin(Point target);
GLvoid OrderCWVertex();
Point Circle(float x, float y, float radius, float angle);


Poly poly[20];
Poly ClipStdPoly;
Poly cliped;
int val_timer = 10;
float radius = 40.0;

void main()
{
	srand((unsigned)time(NULL));

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
	int srt = 0;

	ClipStdPoly.dropline = 2;
	ClipStdPoly.vertexnum = RECT;
	ClipStdPoly.ypos = 50;

	for (int i = 0; i < ClipStdPoly.vertexnum; i++)
		ClipStdPoly.vertex[i] = Circle(50 + (ClipStdPoly.dropline - 1) * 100, ClipStdPoly.ypos, radius, 360 / ClipStdPoly.vertexnum * i + 120);

	for (int i = 0; i < 20; i++)
	{
		poly[i].dropline = 1 + rand() % 5;
		poly[i].vertexnum = 3 + rand() % 4;
		poly[i].xpos = 50 + (poly[i].dropline - 1) * 100;
		poly[i].ypos = 900;

		srt = 0;
		if(srt == 0)		poly[i].scale = rand() % 5;
		else if(srt == 1)	poly[i].shear = rand() % 5;
		else if(srt == 2)	poly[i].rot = rand() % 5;
		else {};

		poly[0].dropline = 1;
		poly[0].vertexnum = 3;
		poly[0].ypos = 140;

		for (int j = 0; j < poly[i].vertexnum; j++)
			poly[i].vertex[j] = Circle(poly[i].xpos, poly[i].ypos, radius, 360 / poly[i].vertexnum * j);

		poly[i] = VertexSetting(poly[i]);
	}

	




	cliped.dropline = NULL;
	cliped.vertexnum = 0;
	cliped.ypos = NULL;
	for (int i = 0; i < cliped.vertexnum; i++)
		cliped.vertex[i] = { 0,0 };

}

Poly VertexSetting(Poly srtpoly)
{
	float tmp_x = srtpoly.xpos;
	float tmp_y = srtpoly.ypos;

	for (int i = 0; i < srtpoly.vertexnum; i++)
	{
		srtpoly.vertex[i].x = srtpoly.vertex[i].x - tmp_x;
		srtpoly.vertex[i].y = srtpoly.vertex[i].y - tmp_y;
	}

	if (srtpoly.rot != 0)
		for (int i = 0; i < srtpoly.vertexnum; i++)
			srtpoly.vertex[i] = rotate(srtpoly.vertex[i], 120 * srtpoly.rot);
	
	if (srtpoly.scale != 0)
		for (int i = 0; i < srtpoly.vertexnum; i++)
			srtpoly.vertex[i] = scale(srtpoly.vertex[i], 0.5 + (0.3 * srtpoly.scale));
	
	if (srtpoly.shear != 0)
		for (int i = 0; i < srtpoly.vertexnum; i++)
			srtpoly.vertex[i] = shearing(srtpoly.vertex[i], 0.1*srtpoly.shear);

	for (int i = 0; i < srtpoly.vertexnum; i++)
	{
		srtpoly.vertex[i].x = srtpoly.vertex[i].x + tmp_x;
		srtpoly.vertex[i].y = srtpoly.vertex[i].y + tmp_y;
	}

	return srtpoly;
}

Point rotate(Point p, int angle)
{
	angle = angle * (3.141592 / 180);

	p.x = cos(angle) * p.x - sin(angle) * p.y;
	p.y = sin(angle) * p.x + cos(angle) * p.y;
	return p;
}
Point scale(Point p, int val)
{
	p.x = val * p.x;
	p.y = val * p.y;
	return p;
}
Point shearing(Point p, int val)
{
	p.x = p.x + val*p.y;
	
	return p;
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
			glVertex2i(100 * lineidx, 0);
			glVertex2i(100 * lineidx, 800);
		}

		glVertex2i(0, 100);
		glVertex2i(500, 100);
	}
	glEnd();
}


GLvoid DrawPoly()
{
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	for (int j = 0; j < 20; j++)
	{
		glBegin(GL_POLYGON);
		for (int i = 0; i < poly[j].vertexnum; i++)
			glVertex2i(poly[j].vertex[i].x, poly[j].vertex[i].y);
		glEnd();
	}


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

	case 'a':
		if(ClipStdPoly.dropline>1)
			ClipStdPoly.dropline--;
		break;
		
	case 'd':
		if (ClipStdPoly.dropline<5)
			ClipStdPoly.dropline++;
		break;

	case 'w':
		//if (ClipStdPoly.vertexnum<6)
		//	ClipStdPoly.vertexnum++;
		poly[0].ypos += 10;

		break;

	case 's':
		//if (ClipStdPoly.vertexnum>3)
		//	ClipStdPoly.vertexnum--;
		poly[0].ypos -= 10;
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
	static int counter = 0;
	static int dropcountidx = 0;

	//counter++;
	//if (counter > 100)
	//{
	//	counter = 0;
	//	if (dropcountidx<20)
	//		dropcountidx++;
	//}
	//
	//for (int i = 0; i < dropcountidx; i++) {
	//	if (poly[i].ypos > -150)
	//		poly[i].ypos--;
	//}
	//

	for (int i = 0; i < ClipStdPoly.vertexnum; i++)
		ClipStdPoly.vertex[i] = Circle(50 + (ClipStdPoly.dropline - 1) * 100, ClipStdPoly.ypos, radius, 360 / ClipStdPoly.vertexnum * i);


	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < poly[j].vertexnum; i++)
			poly[j].vertex[i] = Circle(50 + (poly[j].dropline - 1) * 100, poly[j].ypos, radius, 360 / poly[j].vertexnum * i);

		poly[j] = VertexSetting(poly[j]);

		ClippingChk(j);
	}

	glutPostRedisplay();
	glutTimerFunc(val_timer, Timer, 1);
}

bool InterSectPoint(const Point func_p1, const Point func_p2, const Point clip_p1, const Point clip_p2, Point &Vertex)		// func = dropping polygon edge, clip = clipping area edge
{
	float func;
	float clip;
	
	float under = (clip_p2.y - clip_p1.y) * (func_p2.x - func_p1.x) - (clip_p2.x - clip_p1.x)*(func_p2.y - func_p1.y);
	if (under - 0.0001 < 0 && under + 0.0001 > 0) 
		return false;

	float upperfunc = (clip_p2.x - clip_p1.x)*(func_p1.y - clip_p1.y) - (clip_p2.y - clip_p1.y)*(func_p1.x - clip_p1.x);
	float upperclip = (func_p2.x - func_p1.x)*(func_p1.y - clip_p1.y) - (func_p2.y - func_p1.y)*(func_p1.x - clip_p1.x);

	func = upperfunc / under;
	clip = upperclip / under;

	if (clip < 0.0 || clip > 1.0 || func < 0.0 || func > 1.0) return false;
	if (upperfunc - 0.0001 < 0 && upperfunc + 0.0001 > 0 && upperclip - 0.0001 < 0 && upperclip + 0.0001 >0) return false;

 	Vertex.x = func_p1.x + func * (float)(func_p2.x - func_p1.x);
	Vertex.y = func_p1.y + func * (float)(func_p2.y - func_p1.y);

	return true;
}


GLvoid ClippingChk(int index)
{
	cliped.vertexnum = 0;
	memset(cliped.vertex, NULL, sizeof(cliped.vertex));

	if (poly[index].ypos < 150 && poly[index].dropline == ClipStdPoly.dropline)
	{
		//chk line intersection from 0 to end step by step
		for (int pt_dropidx = 0; pt_dropidx < poly[index].vertexnum-1; pt_dropidx++)
		{
			for (int pt_clipidx = 0; pt_clipidx < ClipStdPoly.vertexnum-1; pt_clipidx++)
			{
				if (InterSectPoint(
					poly[index].vertex[pt_dropidx], poly[index].vertex[pt_dropidx + 1],
					ClipStdPoly.vertex[pt_clipidx], ClipStdPoly.vertex[pt_clipidx + 1], cliped.vertex[cliped.vertexnum]))
					cliped.vertexnum++;
			}
		}

		for (int pt_dropidx = 0; pt_dropidx < poly[index].vertexnum - 1; pt_dropidx++)
		{
			if (InterSectPoint(
				poly[index].vertex[pt_dropidx], poly[index].vertex[pt_dropidx + 1],
				ClipStdPoly.vertex[ClipStdPoly.vertexnum - 1], ClipStdPoly.vertex[0], cliped.vertex[cliped.vertexnum]))
				cliped.vertexnum++;
		}
		
		for (int pt_clipidx = 0; pt_clipidx < ClipStdPoly.vertexnum - 1; pt_clipidx++)
		{
			if (InterSectPoint(
				poly[index].vertex[poly[index].vertexnum - 1], poly[index].vertex[0], 
				ClipStdPoly.vertex[pt_clipidx], ClipStdPoly.vertex[pt_clipidx + 1], cliped.vertex[cliped.vertexnum]))
				cliped.vertexnum++;
		}
		
		if (InterSectPoint(
			poly[index].vertex[poly[index].vertexnum - 1], poly[index].vertex[0], 
			ClipStdPoly.vertex[ClipStdPoly.vertexnum - 1], ClipStdPoly.vertex[0], cliped.vertex[cliped.vertexnum]))
			cliped.vertexnum++;
		
		for (int i = 0; i < poly[index].vertexnum; i++)
		{
			if (ChkVertexin(poly[index].vertex[i]))
			{
				cliped.vertex[cliped.vertexnum] = poly[index].vertex[i];
				cliped.vertexnum++;
			}
		}
	}
}

bool ChkVertexin(Point target)
{
	Point temp;
	for (int i = 0; i < ClipStdPoly.vertexnum; i++)
	{
		if (InterSectPoint({ 50.0 , 100.0 }, target, ClipStdPoly.vertex[i], ClipStdPoly.vertex[i + 1], temp))
			return false;
	}
	if (InterSectPoint({ 50.0 , 100.0 }, target, ClipStdPoly.vertex[0], ClipStdPoly.vertex[ClipStdPoly.vertexnum], temp))
		return false;

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