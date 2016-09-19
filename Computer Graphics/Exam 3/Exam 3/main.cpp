#include<iostream>
#include<time.h>

#include<gl\glut.h>

#define W_Width		600
#define W_Height	600

GLvoid RegesterCallBack();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keydown(unsigned char, int, int);

GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid init(GLvoid);

GLvoid Prot_Draw(GLvoid);

GLvoid DrawPolygon(GLvoid);


struct Point
{
	int x;
	int y;
	int end;
};



int space_x;
int space_y;

Point pt[50];
int pt_index = 0;
int poly_count = 0;

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
	space_x = 600 / 3;
	space_y = 600 / 3;

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
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glLineWidth(5);
	glBegin(GL_LINES);
	{
		glVertex2i(space_x, 0);
		glVertex2i(space_x, 600);
		glVertex2i(space_x * 2, 0);
		glVertex2i(space_x * 2, 600);

		glVertex2i(0, space_y);
		glVertex2i(600, space_y);
		glVertex2i(0, space_y * 2);
		glVertex2i(600, space_y * 2);
	}
	glEnd();

	Prot_Draw();

	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 600.0, 0.0, 600.0, -1.0, 1.0);
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
		pt[pt_index] = { x,600 - y,0 };
		pt_index++;
		poly_count++;
	}

}

GLvoid DrawPolygon(GLvoid)
{
	for (int i = 0; pt[i].end != 2; i++)
	{
		
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glLineWidth(5);
		glBegin(GL_POLYGON);

		//for (int i = pt_index - poly_count; i < poly_count; i++)
		//	glVertex2i(pt[i].x, pt[i].y);

		glEnd();

	}
}

GLvoid Prot_Draw(GLvoid)
{
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glLineWidth(5);
	glBegin(GL_LINES);
	{
		glVertex2i(20, 550);
		glVertex2i(180, 450);
		glVertex2i(220, 350);
		glVertex2i(380, 250);
		glVertex2i(420, 150);
		glVertex2i(580, 50);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glVertex2i(220, 550);
		glVertex2i(250, 430);
		glVertex2i(380, 500);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glVertex2i(420, 550);
		glVertex2i(520, 530);
		glVertex2i(580, 430);
		glVertex2i(480, 430);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glVertex2i(20, 350);
		glVertex2i(120, 330);
		glVertex2i(150, 230);
		glVertex2i(100, 230);
		glVertex2i(30, 280);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glVertex2i(420, 350);
		glVertex2i(450, 230);
		glVertex2i(580, 300);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glVertex2i(20, 150);
		glVertex2i(120, 130);
		glVertex2i(180, 30);
		glVertex2i(80, 30);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glVertex2i(220, 150);
		glVertex2i(320, 130);
		glVertex2i(350, 30);
		glVertex2i(300, 30);
		glVertex2i(230, 80);
	}
	glEnd();

}