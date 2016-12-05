#include <iostream>
#include <ctime>
#include <cmath>
#include <gl\glut.h>

#define W_Width		500
#define W_Height	700

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
	Point vertex[10];
	int rot;
	int scale;
	int shear;
	bool power;
};


GLvoid RegesterCallBack();


GLvoid drawScene(GLvoid);
GLvoid DrawScoreboard();
GLvoid LineDraw();
GLvoid DrawPoly();
GLvoid Reshape(int w, int h);

GLvoid Keyspecial(int key, int x, int y);

GLvoid Timer(int);
GLvoid Keydown(unsigned char, int, int);
GLvoid initpoly();

Poly VertexSetting(Poly srtpoly);

Point shearing(Point p, double val);
Point rotate(Point p, double angle);
Point scale(Point p, double val);

bool InterSectPoint(const Point func_p1, const Point func_p2, const Point clip_p1, const Point clip_p2, Point &Vertex);
GLvoid ClippingChk(int index);
bool ChkVertexin(Point chkvertex, Poly stdpoly);
GLvoid VertexOrder(int polyindex);
float getangle(Point center, Point p_compare);
Point Circle(float x, float y, float radius, float angle);


Poly poly[20];
Poly ClipStdPoly;
float polyangle[20];
static Poly cliped;
int val_timer = 20;
float radius = 40.0;
int Score = 0;
bool isRunning = false;
bool isScoring = false;
int speedupstart = 10;

void main()
{
	srand((unsigned)time(NULL));

	initpoly();

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 200);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	RegesterCallBack();
	
	glutMainLoop();
}

GLvoid RegesterCallBack()
{
	glutTimerFunc(val_timer, Timer, 1);
	glutKeyboardFunc(Keydown);
	glutSpecialFunc(Keyspecial);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);

}

GLvoid initpoly()
{
	int srt = 0;

	Score = 0;

	ClipStdPoly.dropline = 3;
	ClipStdPoly.vertexnum = 5;
	ClipStdPoly.xpos = 50 + (ClipStdPoly.dropline - 1) * 100;
	ClipStdPoly.ypos = 150;

	for (int i = 0; i < ClipStdPoly.vertexnum; i++)
		ClipStdPoly.vertex[i] = Circle(50 + (ClipStdPoly.dropline - 1) * 100, ClipStdPoly.ypos, radius, 360 / ClipStdPoly.vertexnum * i + 120);

	for (int i = 0; i < 20; i++)
	{
		poly[i].dropline = 1 + rand() % 5;
		poly[i].vertexnum = 3 + rand() % 4;
		poly[i].xpos = 50 + (poly[i].dropline - 1) * 100;
		poly[i].ypos = 800;
		
		srt = rand() % 4;
		//srt = 2;
		if (srt == 0)		poly[i].scale = rand() % 5;
		else if (srt == 1)	poly[i].shear = rand() % 5;
		else if (srt == 2)	poly[i].rot = rand() % 4;
		else {};

		//poly[0].dropline = 1;
		//poly[0].vertexnum = 3;
		//poly[i].xpos = 50 + (poly[i].dropline - 1) * 100;
		//poly[0].ypos = 99;

		for (int j = 0; j < poly[i].vertexnum; j++)
			poly[i].vertex[j] = Circle(poly[i].xpos, poly[i].ypos, radius, 360 / poly[i].vertexnum * j);

		poly[i] = VertexSetting(poly[i]);
	}

	poly[0].power = true;


	cliped.dropline = NULL;
	cliped.vertexnum = 0;
	cliped.ypos = NULL;
	for (int i = 0; i < cliped.vertexnum; i++)
		cliped.vertex[i] = { 0,0 };
	speedupstart = 5 + rand() % 8;

	std::cout << "Game Paused\nPress P to Start!" << std::endl;
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
			srtpoly.vertex[i] = rotate(srtpoly.vertex[i], 45.0 * srtpoly.rot);
	
	if (srtpoly.scale != 0)
		for (int i = 0; i < srtpoly.vertexnum; i++)
			srtpoly.vertex[i] = scale(srtpoly.vertex[i], 1 + (0.2 * srtpoly.scale));
	
	if (srtpoly.shear != 0)
		for (int i = 0; i < srtpoly.vertexnum; i++)
			srtpoly.vertex[i] = shearing(srtpoly.vertex[i], 0.3*srtpoly.shear);

	for (int i = 0; i < srtpoly.vertexnum; i++)
	{
		srtpoly.vertex[i].x = srtpoly.vertex[i].x + tmp_x;
		srtpoly.vertex[i].y = srtpoly.vertex[i].y + tmp_y;
	}

	return srtpoly;
}

Point rotate(Point p, double angle)
{
	angle = angle * (3.141592 / 180);

	Point tmp = p;

	p.x = cos(angle) * tmp.x - sin(angle) * tmp.y;
	p.y = sin(angle) * tmp.x + cos(angle) * tmp.y;
	return p;
}
Point scale(Point p, double val)
{
	p.x = val * p.x;
	p.y = val * p.y;
	return p;
}
Point shearing(Point p, double val)
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

	DrawScoreboard();
	glFlush();
}

GLvoid DrawScoreboard()
{	//scoreboard basement
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glLineWidth(2);
	glBegin(GL_POLYGON);
	{
		glVertex2i(0, 100);
		glVertex2i(500, 100);
		glVertex2i(500, 0);
		glVertex2i(0, 0);
	}
	glEnd();


	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glLineWidth(2);
	glBegin(GL_POLYGON); //guide lines
	{
		glVertex2i(0, 100);
		glVertex2i(500, 100);
		glVertex2i(500, 0);
		glVertex2i(0, 0);
	}
	glEnd();

	glColor4f(1.0f, 0.5f, 1.0f, 1.0f);
	glLineWidth(2);
	glBegin(GL_POLYGON); //guide lines
	{
		glVertex2i(100, 75);
		glVertex2i(100 + 50 * Score, 75);
		glVertex2i(100 + 50 * Score, 25);
		glVertex2i(100, 25);
	}
	glEnd();

	glColor4f(1.0f, 0.5f, 1.0f, 1.0f);
	glLineWidth(2);
	glBegin(GL_LINES); //guide lines
	{
		for (int i = 0; i < 7; i++)
		{
			glVertex2i(100 + 50 * i, 75);
			glVertex2i(100 + 50 * i, 25);
		}
		glVertex2i(100, 75);
		glVertex2i(400, 75);
		glVertex2i(100, 25);
		glVertex2i(400, 25);
	}
	glEnd();


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

		glVertex2i(0, 200);
		glVertex2i(500, 200);
		glVertex2i(0, 450);
		glVertex2i(500, 450);
	}
	glEnd();
}


GLvoid DrawPoly()
{
	for (int j = 0; j < 20; j++)
	{
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		if(poly[j].power)
			glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
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
	glBegin(GL_POLYGON); 
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

GLvoid Keyspecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		if (ClipStdPoly.dropline<5)
			ClipStdPoly.dropline++;
		ClipStdPoly.xpos = 50 + (ClipStdPoly.dropline - 1) * 100;
		break;
	case GLUT_KEY_LEFT:
		if (ClipStdPoly.dropline>1)
			ClipStdPoly.dropline--;
		ClipStdPoly.xpos = 50 + (ClipStdPoly.dropline - 1) * 100;
		break;

	case GLUT_KEY_UP:
		if (ClipStdPoly.vertexnum<6)
			ClipStdPoly.vertexnum++;
		//poly[0].ypos += 1;
		//std::cout << poly[0].ypos <<' ' << (ClipStdPoly.ypos + poly[0].ypos) / 2 << std::endl;
		break;

	case GLUT_KEY_DOWN:
		if (ClipStdPoly.vertexnum>3)
			ClipStdPoly.vertexnum--;
		//poly[0].ypos -= 1;
		//std::cout << poly[0].ypos << ' ' << (ClipStdPoly.ypos + poly[0].ypos) / 2 << std::endl;
		break;

	}
}

GLvoid Keydown(unsigned char key, int x, int y)
{
	if (isRunning)
	{
		switch (key)
		{
		case 32:	//space bar
			isScoring = true;
			break;

		case 'a':				//shearing+
			ClipStdPoly.shear = (ClipStdPoly.shear + 1) % 5;
			break;
		case 'A':				//shearing-
			if (ClipStdPoly.shear > 0)
				ClipStdPoly.shear = (ClipStdPoly.shear - 1) % 5;
			break;

		case 'd':				//rotate+
			ClipStdPoly.rot = (ClipStdPoly.rot + 1) % 4;
			break;
		case 'D':				//rotate-
			if (ClipStdPoly.rot > 0)
				ClipStdPoly.rot = (ClipStdPoly.rot - 1) % 4;
			break;

		case 's':				//scale+
			ClipStdPoly.scale = (ClipStdPoly.scale + 1) % 5;
			break;
		case 'S':				//scale-
			if (ClipStdPoly.scale > 0)
				ClipStdPoly.scale = (ClipStdPoly.scale - 1) % 5;
			break;

		case 'r':
			ClipStdPoly.shear = 0;
			ClipStdPoly.rot = 0;
			ClipStdPoly.scale = 0;
			break;
		}
	}
	switch (key)
	{
	case 'q':
		exit(0);
		break;

		//case 32:	//space bar
		//	isScoring = true;
		//	break;
		//
		//case 'a':				//shearing+
		//	ClipStdPoly.shear = (ClipStdPoly.shear + 1) % 5;
		//	break;
		//case 'A':				//shearing-
		//	if (ClipStdPoly.shear > 0)
		//		ClipStdPoly.shear = (ClipStdPoly.shear - 1) % 5;
		//	break;
		//
		//case 'd':				//rotate+
		//	ClipStdPoly.rot = (ClipStdPoly.rot + 1) % 3;
		//	break;
		//case 'D':				//rotate-
		//	if (ClipStdPoly.rot > 0)
		//		ClipStdPoly.rot = (ClipStdPoly.rot - 1) % 3;
		//	break;
		//
		//case 's':				//scale+
		//	ClipStdPoly.scale = (ClipStdPoly.scale + 1) % 5;
		//	break;
		//case 'S':				//scale-
		//	if (ClipStdPoly.scale > 0)
		//		ClipStdPoly.scale = (ClipStdPoly.scale - 1) % 5;
		//	break;
		//
		//case 'r':
		//	ClipStdPoly.shear = 0;
		//	ClipStdPoly.rot = 0;
		//	ClipStdPoly.scale = 0;
		//	break;

	case 'p':
	case 'P':
		system("cls");
		if (isRunning)
		{
			std::cout << "Game Paused\nPress P to Start!" << std::endl;
			isRunning = false;
		}
		else if (!isRunning)
			isRunning = true;
		break;

	case 'O':
	case 'o':
		initpoly();
		break;

	case 'e':
		break;
	}

	glutPostRedisplay();
}

GLvoid getscore(int idx)
{
	if (poly[idx].dropline == ClipStdPoly.dropline)
	{
		if (poly[idx].power)
		{
			Score++;
			poly[idx].ypos = -100;
			return;
		}
		
		if (poly[idx].ypos > ClipStdPoly.ypos - 50 && poly[idx].ypos < ClipStdPoly.ypos + 50)
		{
			if (poly[idx].scale == ClipStdPoly.scale && poly[idx].rot == ClipStdPoly.rot && poly[idx].shear == ClipStdPoly.shear)
			{
				Score++;
				poly[idx].ypos = -100;
				return; 
			}
		}
	}
}



GLvoid Timer(int val)
{
	static int counter = 0;
	static int dropcountidx = 1;
	static int counterlimit = 400;
	
	int shouldclipidx = 0;

	if (isRunning)
	{
		counter++;
		if (counter > counterlimit)
		{
			counter = 0;
			if (dropcountidx < 20)
				dropcountidx++;
			if (dropcountidx == speedupstart)
			{
				counterlimit = 250;
			}
			std::cout << dropcountidx << std::endl;
		}
		if (dropcountidx < speedupstart)
		{
			for (int i = 0; i < dropcountidx; i++)
			{
				if (poly[i].ypos > -100)
					poly[i].ypos -= 1.5;
			}
		}
		else
		{
			for (int i = 0; i < dropcountidx; i++)
			{
				if (poly[i].ypos > -100)
					poly[i].ypos -= 4;
			}
		}


		for (int i = 0; i < ClipStdPoly.vertexnum; i++)
			ClipStdPoly.vertex[i] = Circle(50 + (ClipStdPoly.dropline - 1) * 100, ClipStdPoly.ypos, radius, 360 / ClipStdPoly.vertexnum * i);

		ClipStdPoly = VertexSetting(ClipStdPoly);

		for (int j = 0; j < 20; j++)
		{
			for (int i = 0; i < poly[j].vertexnum; i++)
				poly[j].vertex[i] = Circle(50 + (poly[j].dropline - 1) * 100, poly[j].ypos, radius, 360 / poly[j].vertexnum * i);
			poly[j] = VertexSetting(poly[j]);

			if (poly[j].ypos < 250)
				shouldclipidx = j;
		
			if (poly[j].ypos < 450 && poly[j].ypos > 440)
			{
				system("cls");
				std::cout << "Poly size :" << poly[j].vertexnum << std::endl;
				std::cout << "Rotate size :" << poly[j].rot << std::endl;
				std::cout << "Scale size :" << poly[j].scale << std::endl;
				std::cout << "Shear size :" << poly[j].shear << std::endl;
			}
		}
		
		ClippingChk(shouldclipidx);
		
		if (isScoring)
		{
			getscore(shouldclipidx);
			isScoring = false;
		}
		if (Score == 6)
		{
			isRunning = false;
			std::cout << "You win" << std::endl;
			std::cout << "Press O to restart" << std::endl;
		}

		if (poly[19].ypos < 50)
		{
			isRunning = false;
			std::cout << "You Lose" << std::endl;
			std::cout << "Press O to restart" << std::endl;
		}
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

	if (poly[index].ypos < 250 && poly[index].dropline == ClipStdPoly.dropline)
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
		
		for (int i = 0; i < poly[index].vertexnum; i++)		//polygon vertex chk if droppoly vertex is in clipstdpoly
		{
			if (ChkVertexin(poly[index].vertex[i], ClipStdPoly))
			{
				cliped.vertex[cliped.vertexnum] = poly[index].vertex[i];
				cliped.vertexnum++;
			}
		}

		for (int i = 0; i < ClipStdPoly.vertexnum; i++)		//polygon vertex chk if droppoly vertex is in clipstdpoly
		{
			if (ChkVertexin(ClipStdPoly.vertex[i], poly[index]))
			{
				cliped.vertex[cliped.vertexnum] = ClipStdPoly.vertex[i];
				cliped.vertexnum++;
			}
		}

		VertexOrder(index);
	}
}

bool ChkVertexin(Point chkvertex, Poly stdpoly)
{
	Point dummy;
	Point A = { (float)stdpoly.xpos , (float)stdpoly.ypos };
	for (int i = 0; i < stdpoly.vertexnum; i++)
	{
		if (InterSectPoint(A, chkvertex, stdpoly.vertex[i], stdpoly.vertex[i + 1], dummy))
			return false;
	}
	if (InterSectPoint(A, chkvertex, stdpoly.vertex[0], stdpoly.vertex[stdpoly.vertexnum-1], dummy))
		return false;

	return true;
}

GLvoid VertexOrder(int polyindex)
{
	Point tmp_center;
	float tmp_angle;
	memset(polyangle, NULL, sizeof(polyangle));

	cliped.xpos = ClipStdPoly.xpos;
	tmp_center.y = (ClipStdPoly.ypos + poly[polyindex].ypos) / 2;
	tmp_center.x = cliped.xpos;

	for (int i = 0; i < cliped.vertexnum; i++)
		polyangle[i] = getangle(tmp_center, cliped.vertex[i]);

	for (int i = cliped.vertexnum; i > 1; i--)
	{
		for (int j = 0; j < i - 1; j++)
		{
			if (polyangle[j] > polyangle[j + 1])
			{
				tmp_angle = polyangle[j];
				polyangle[j] = polyangle[j + 1];
				polyangle[j + 1] = tmp_angle;

				tmp_center = cliped.vertex[j];
				cliped.vertex[j] = cliped.vertex[j + 1];
				cliped.vertex[j + 1] = tmp_center;
			}
		}
	}
	
}

float getangle(Point center, Point p_compare)
{
	return atan2(p_compare.y - center.y, p_compare.x - center.x) * 180 / 3.1415926535;
}

Point Circle(float x, float y, float radius, float angle)
{
	Point P;
	angle = angle * (3.141592 / 180);
	
	P.x = cos(angle)*radius + x;
	P.y = sin(angle)*radius + y;

	return P;
}