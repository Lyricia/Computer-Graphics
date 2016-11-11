#include "stdafx.h"
#include "GLFramework.h"
#include "MainGameScene.h"



CMainGameScene::CMainGameScene()
{
}


CMainGameScene::~CMainGameScene()
{
}

void CMainGameScene::Update()
{
	m_ptPos.x += 10.f;
	if (m_ptPos.x > m_pMasterFramework->GetWindowSize().x)
		m_ptPos.x -= m_pMasterFramework->GetWindowSize().x;
}

void CMainGameScene::Render()
{
	DrawCircle(m_ptPos.x, m_ptPos.y, 30, 18);
}

void CMainGameScene::Reshape()
{
}

void CMainGameScene::Mouse(int button, int state, int x, int y)
{
	switch (GetMouseState(button, state))
	{
	case GLKeyStateCombine::LBUTTONDOWN:
		break;
	case GLKeyStateCombine::RBUTTONDOWN:
		break;
	case GLKeyStateCombine::LBUTTONUP:
		break;
	case GLKeyStateCombine::RBUTTONUP:
		break;

	}
}

void CMainGameScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);
	glClearColor(0.5, 0.5, 0.8, 1);
}
