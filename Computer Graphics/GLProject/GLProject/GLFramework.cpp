#include <cassert>
#include <gl/glut.h>
#include "GLFramework.h"
#include <iostream>


GLvoid CGLFramework::Initialize(GLvoid)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(m_ptWindowPos.x, m_ptWindowPos.y);
	glutInitWindowSize(m_ptWindowSize.x, m_ptWindowSize.y);
	glutCreateWindow(m_szTile);
}

GLvoid CGLFramework::Reshape(int w, int h)
{
	m_ptWindowSize = Point2i { w,h };

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
}

GLvoid CGLFramework::drawScene(GLvoid)
{
	glClearColor(1.f, 1.f, 0.0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
}

GLvoid CGLFramework::Timer(int val)
{
	glutPostRedisplay();
	glutTimerFunc(m_iFPS, m_pfTimer, val);
}

enum {
	RBUTTONDOWN = ((GLUT_RIGHT_BUTTON << 8) + GLUT_DOWN),
	RBUTTONUP = ((GLUT_RIGHT_BUTTON << 8) + GLUT_UP),
	LBUTTONDOWN = ((GLUT_LEFT_BUTTON << 8) + GLUT_DOWN),
	LBUTTONUP = ((GLUT_LEFT_BUTTON << 8) + GLUT_UP),
};

GLvoid CGLFramework::KeyInput(unsigned char key, int x, int y)
{	
	
	switch (key)
	{
	case 'q':
		//exit(0);
		break;
	}
}

GLvoid CGLFramework::MouseInput(int button, int state, int x, int y)
{
	switch ((button << 8) + state)
	{
	case LBUTTONDOWN:
		break;
	case RBUTTONDOWN:
		break;
	case LBUTTONUP:
		break;
	case RBUTTONUP:
		break;
	}
}

GLvoid CGLFramework::Run()
{
	assert((m_pfDrawScene && m_pfReshape && m_pfTimer && m_pfKeyInput)
		&& "No callback function has been set!");

	glutDisplayFunc(m_pfDrawScene);
	glutReshapeFunc(m_pfReshape);
	glutTimerFunc(m_iFPS, m_pfTimer, 1);
	glutKeyboardFunc(m_pfKeyInput);

	glutMainLoop();
}
