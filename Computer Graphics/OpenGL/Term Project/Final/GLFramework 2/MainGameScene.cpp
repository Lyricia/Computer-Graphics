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
	
}

void CMainGameScene::Render()
{
	glColor4f(1.f, 1.f, 1.f, 1.f);
	//glutSolidCube(1.0f);

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
	auto sz = m_pMasterFramework->GetWindowSize();
	m_Camera.SetAspect(static_cast<float>(sz.x) / static_cast<float>(sz.y));
	m_Camera.LookAt();
}

void CMainGameScene::Mouse(int button, int state, int x, int y)
{
	switch (GetMouseState(button, state))
	{
	case GLKeyStateCombine::LBUTTONDOWN:
		m_Camera.Move({0, 0, -1});
		break;
	case GLKeyStateCombine::RBUTTONDOWN:
		m_Camera.Move({ 0, 0, 1 });
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
	}
}

void CMainGameScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);
	glClearColor(0.5, 0.5, 0.8, 1);

	IntroTexture.initTextures();
}