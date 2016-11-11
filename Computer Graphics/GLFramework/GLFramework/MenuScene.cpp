#include <iostream>
#include "MenuScene.h"

CMenuScene::CMenuScene()
{
}

CMenuScene::~CMenuScene()
{
}

void CMenuScene::RenderScene()
{
	glClearColor(1.f, 0., 0.0, 1);
	glutWireCube(100);
}

void CMenuScene::UpdateScene()
{
	std::cout << "Menu Scene" << std::endl;
}

void CMenuScene::BuildScene(CGLFramework * pFramework, int tag)
{
	CScene::BuildScene(pFramework, tag);
}

void CMenuScene::KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'd':
		m_pMasterFramework->ChangeScene(CScene::Scenelist::PlayScene);
		break;
	}
}

void CMenuScene::MouseInput(int button, int state, int x, int y)
{
}
