#include "GLFramework.h"

GLvoid CGLFramework::Init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(m_Point_WindowPos.x, m_Point_WindowPos.y);
	glutInitWindowSize(m_Point_WindowSize.x, m_Point_WindowSize.y);
	glutCreateWindow(CAPTION);
}

GLvoid CGLFramework::Reshape(int w, int h)
{
	m_Point_WindowSize = Point2i{ w, h };

	//glViewport(GL_PROJECTION);

	glViewport(0, 0, w, h);
	glOrtho(0.0, 800, 0.0, 600, -1.0, 1.0);
}

GLvoid CGLFramework::drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glFlush();
}

GLvoid CGLFramework::Timer(int val)
{
	counter++;

	std::cout << counter << std::endl;

	glutPostRedisplay();
}

GLvoid CGLFramework::Run()
{
}
