#include<iostream>
#include<time.h>

#include<gl\glut.h>

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


GLvoid DrawLines(int rad);
GLvoid DrawSpace();
GLvoid DrawPolygon(GLvoid);
GLvoid Circle(Vertex P, float radius, float angle);

int angle = 0;
int angle2 = 0;

float camera_x;
float camera_y;
float camera_z;

void main(int, char *)
{
	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	RegesterCallBack();

	glutMainLoop();
}

GLvoid init(GLvoid)
{
	srand(unsigned(time(NULL)));
	camera_x = 0.0;
	camera_y = 0.0;
	camera_z = 0.0;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	{
		glPushMatrix();
		{
			glPushMatrix();
			{
				glRotatef(angle, 0, 1, 0);
				glPushMatrix();
				{
					glRotatef(90, 1, 0, 0);
					glutWireSphere(40, 10, 10);
				}
				glPopMatrix();
			}
			glPopMatrix();

			glRotated(30, 0, 0, 1);
	//		glPushMatrix();				//-30
	//		{
	//			glRotatef(-30, 0, 0, 1);
	//			glRotatef(angle, 0, 1, 0);
	//			glRotatef(90, 1, 0, 0);
	//			DrawLines(120);
	//			glColor3f(1.0, 1.0, 0);
	//			//glutWireSphere(40, 10, 10);
	//			glPushMatrix();
	//			{
	//				glTranslatef(-120, 0, 0);
	//				//glRotatef(90, 1, 0, 0);
	//				glColor3f(1.0, 0.0, 1.0);
	//				DrawLines(40);
	//				glutWireSphere(15, 10, 10);
	//				glPushMatrix();
	//				{
	//					glRotatef(angle2, 0, 0, 1);
	//					glTranslatef(40, 0, 0);
	//					glColor3f(1.0, 1.0, 0.0);
	//					glutWireSphere(5, 10, 10);
	//				}
	//				glPopMatrix();
	//			}
	//			glPopMatrix();
	//		}
	//		glPopMatrix();
	//
	//		glPushMatrix();				//center
	//		{
	//			glRotatef(angle, 0, 1, 0);
	//			glRotatef(90, 1, 0, 0);
	//			DrawLines(120);
	//			glColor3f(1.0, 1.0, 0);
	//			//glutWireSphere(40, 10, 10);
	//			glPushMatrix();
	//			{
	//				glTranslatef(120, 0, 0);
	//				DrawLines(40);
	//				glColor3f(1.0, 0.0, 1.0);
	//				glutWireSphere(15, 10, 10);
	//				glPushMatrix();
	//				{
	//					glRotatef(angle2, 0, 0, 1);
	//					glTranslatef(40, 0, 0);
	//					glColor3f(1.0, 1.0, 0.0);
	//					glutWireSphere(5, 10, 10);
	//				}
	//				glPopMatrix();
	//			}
	//			glPopMatrix();
	//		}
	//		glPopMatrix();

			glPushMatrix();				// +30
			{
				glRotatef(30, 0, 0, 1);
				glRotatef(angle, 1, 0, 0);
				glRotatef(90, 0, 1, 0);
				DrawLines(120);
				glColor3f(1.0, 1.0, 0);
				glPushMatrix();
				{
					glTranslatef(0, 120, 0);
					DrawLines(40);
					glColor3f(1.0, 0.0, 1.0);
					glutWireSphere(15, 10, 10);
					glPushMatrix();
					{
						glRotatef(angle2, 0, 0, 1);
						glTranslatef(40, 0, 0);
						glColor3f(1.0, 1.0, 0.0);
						glutWireSphere(5, 10, 10);
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();
			glColor3f(1.0, 1.0, 1.0);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glutSwapBuffers();
}

GLvoid DrawLines(int rad)
{
	//glColor3f(1.f, 0.f, 0.f);			// x axis 
	//glBegin(GL_LINES);
	//glVertex3f(-W_Width, 0.0, 0.0);
	//glVertex3f(W_Width, 0.0, 0.0);
	//
	//glColor3f(0.f, 1.f, 0.f);			// y axis
	//glVertex3f(0.0, -W_Height, 0.0);
	//glVertex3f(0.0, W_Height, 0.0);
	//
	//glColor3f(0.f, 0.f, 1.f);			// z axis
	//glVertex3f(0.0, 0.0, -W_Depth);
	//glVertex3f(0.0, 0.0, W_Depth);
	//glEnd();

	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i++) {
		Circle({ 0,0,0 }, rad, i);
	}
	glEnd();
}

GLvoid DrawSpace()
{
	glColor3f(1.0, 1.0, 0);
	glPushMatrix();
	glScalef(1, 0.01, 1);
	glutSolidCube(200);
	glPopMatrix();
}
GLvoid DrawPolygon(GLvoid)
{
	
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -300.0);

	glMatrixMode(GL_MODELVIEW);

	gluLookAt(
		camera_x, 0.8, camera_z,			// eye
		0.0, 0.0, 1.0,							// center
		0.0, 1.0, 0.0);							// up
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

	case 'w':
		camera_y += 0.1;
		break;

	case 's':
		camera_y -= 0.1;
		break;

	case 'd':
		angle++;
		angle2 -= 1;
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
	//angle++;
	//angle2 -= 1;
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

GLvoid Circle(Vertex P, float radius, float _angle)
{
	_angle = _angle * (3.141592 / 180);

	glVertex2f(cos(_angle)*radius + P.x, sin(_angle)*radius + P.y);
}