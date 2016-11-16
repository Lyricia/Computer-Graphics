#include <iostream>
#include <gl/glut.h>
#include "GLFramework.h"
#include "Scene.h"

CScene::CScene()
{
}
CScene::~CScene()
{
}

void CScene::RenderScene()
{
	glClearColor(1.f, 1.f, 0.0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
}

void CScene::UpdateScene()
{
}

void CScene::BuildScene(CGLFramework * pFramework, int tag)
{
	m_pMasterFramework = pFramework;
	m_iTag = tag;
}

void CScene::MouseInput(int button, int state, int x, int y)
{

}

void CScene::KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;
	}
}
