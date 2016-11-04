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
}

void CScene::UpdateScene()
{
}

void CScene::BuildScene(CGLFramework * pFramework, int tag)
{
	m_pMasterFramework = pFramework;
	m_iTag = tag;
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
