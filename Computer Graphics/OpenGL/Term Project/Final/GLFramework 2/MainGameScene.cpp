#include "stdafx.h"
#include "GLFramework.h"
#include "MainGameScene.h"
#include "Spline.h"


CMainGameScene::CMainGameScene()
{
}


CMainGameScene::~CMainGameScene()
{
}

void CMainGameScene::Update()
{
	m_Camera->SetCamera();
}

void CMainGameScene::Render()
{
	glColor4f(1.f, 1.f, 1.f, 1.f);
	glutSolidCube(1.0f);

	glPushMatrix();
	{
		CTextureLibraray::UsingTexture2D();
		{
			IntroTexture.m_tex_sea.LoadTexture(0);
			DrawQuad({ 0,0,0 }, 1.f, false);
		}
		CTextureLibraray::StopUsingTexture2D();
	}
	glPopMatrix();
}

void CMainGameScene::Reshape()
{
	//auto sz = m_pMasterFramework->GetWindowSize();

	m_Camera->SetCamera();
	//m_Camera.SetAspect(static_cast<float>(sz.x) / static_cast<float>(sz.y));
	//m_Camera.LookAt();
}

void CMainGameScene::Mouse(int button, int state, int x, int y)
{
	m_Camera->getMouse(x, y);
 	m_Camera->SetLookVector();

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

void CMainGameScene::KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;

	case 'w':
		m_Camera->Move(DIRECTION::FRONT, 0.1f);
		break;
	case 's':
		m_Camera->Move(DIRECTION::BACK, 0.1f);
		break;
	case 'a':
		m_Camera->Move(DIRECTION::LEFT, 0.1f);
		break;
	case 'd':
		m_Camera->Move(DIRECTION::RIGHT, 0.1f);
		break;
	}
}

void CMainGameScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);
	glClearColor(0.0f, 0.0f, 0.0f, 1);

	IntroTexture.initTextures();

	m_Camera = m_pMasterFramework->GetCamera();

	m_Camera->SetCameraPosition(0, 0, -1.f);
	m_Camera->SetViewpoint(-0.5f);
}