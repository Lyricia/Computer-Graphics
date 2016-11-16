#include <iostream>
#include "PlayScene.h"

CPlayScene::CPlayScene()
{
}

CPlayScene::~CPlayScene()
{
}

void CPlayScene::RenderScene()
{
	glClearColor(1.f, 1.f, 1.0, 1);
	glutWireCube(100);
}

void CPlayScene::UpdateScene()
{
	std::cout << "Play Scene" << std::endl;
}	

void CPlayScene::BuildScene(CGLFramework * pFramework, int tag)
{
	CScene::BuildScene(pFramework, tag);
}

void CPlayScene::KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'd':
		m_pMasterFramework->ChangeScene(CScene::Scenelist::MenuScene);
		break;
	}
}

void CPlayScene::MouseInput(int button, int state, int x, int y)
{
}
