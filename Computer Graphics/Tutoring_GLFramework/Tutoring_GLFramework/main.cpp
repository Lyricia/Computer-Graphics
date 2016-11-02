#include "GLFramework.h"

namespace {		//익명 프레임워크
	CGLFramework framework;
}

GLvoid RegesterCallBack();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Timer(int);

int val_timer = 1;

void main()
{
	srand(unsigned(time(NULL)));

	framework.Init();
	framework.Run();

	framework.Init();
	RegesterCallBack();

	glutMainLoop();
}


GLvoid RegesterCallBack()
{
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(val_timer, Timer, 1);
}

GLvoid drawScene(GLvoid)
{	framework.drawScene();	}

GLvoid Reshape(int w, int h)
{	framework.Reshape(w, h);	}

GLvoid Timer(int val)
{	
	framework.Timer(val);
	glutTimerFunc(val_timer, Timer, 1);
}
