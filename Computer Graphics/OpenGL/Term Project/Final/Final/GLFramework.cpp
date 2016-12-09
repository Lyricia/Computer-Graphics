#include "stdafx.h"
#include "GLFramework.h"
#include "TitleScene.h"
#include "IntroScene.h"


CGLFramework::~CGLFramework()
{
	for (auto p : m_arrScene) if (p) delete p;
}

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
	m_pCurrentScene->Reshape(w, h);
	
}

GLvoid CGLFramework::drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_pCurrentScene->Render();

	glutSwapBuffers();
}

GLvoid CGLFramework::Timer(int val)
{
	m_pCurrentScene->Update();

	glutPostRedisplay();
	glutTimerFunc(m_iFPS, m_pfTimer, val);
}

GLvoid CGLFramework::MouseMove(int x, int y)
{
	m_pCurrentScene->MouseMove(x, y);
}

GLvoid CGLFramework::MouseEvent(int button, int state, int x, int y)
{
	m_pCurrentScene->MouseEvent(button, state, x, y);
}

GLvoid CGLFramework::KeyInput(unsigned char key, int x, int y)
{
	m_pCurrentScene->KeyInput(key, x, y);
	switch (key)
	{
	case 'q':
		//exit(0);
		break;
	}
}

GLvoid CGLFramework::KeyUp(unsigned char key, int x, int y)
{
	m_pCurrentScene->KeyUp(key, x, y);
}

GLvoid CGLFramework::Run()
{
	assert((m_pfDrawScene && m_pfReshape && m_pfTimer 
		&& m_pfMouseEvent && m_pfKeyInput && m_pfMouseMove && m_pfKeyUp)
		&& "No callback function has been set!");
	glClearColor(0.5, 0.5, 0.8, 1);
	
	glutMouseFunc(m_pfMouseEvent);
	glutPassiveMotionFunc(m_pfMouseMove);
	glutKeyboardFunc(m_pfKeyInput);
	glutKeyboardUpFunc(m_pfKeyUp);
	glutDisplayFunc(m_pfDrawScene);
	glutReshapeFunc(m_pfReshape);
	glutTimerFunc(m_iFPS, m_pfTimer, 1);

	BuildScene<CTitleScene>();

	glutMainLoop();
}
