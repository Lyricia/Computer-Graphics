#include "stdafx.h"
#include "GLFramework.h"
#include "MainGameScene.h"
#include "TitleScene.h"


CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Update()
{
}

void CTitleScene::Render()
{
}

void CTitleScene::Reshape()
{
}

void CTitleScene::Mouse(int button, int state, int x, int y)
{
	switch (GetMouseState(button, state))
	{
	case GLKeyStateCombine::LBUTTONDOWN:
		m_pMasterFramework->BuildScene<CMainGameScene>();
		break;
	case GLKeyStateCombine::RBUTTONDOWN:
		break;
	case GLKeyStateCombine::LBUTTONUP:
		break;
	case GLKeyStateCombine::RBUTTONUP:
		break;

	}
}

void CTitleScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);
	glClearColor(0.7, 0.7, 0.8, 1);

}
