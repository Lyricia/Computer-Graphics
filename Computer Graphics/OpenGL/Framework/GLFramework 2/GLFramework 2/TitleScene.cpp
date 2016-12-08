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
	m_fFadein += 0.016;
	if (m_fFadein > 1.5f) {
		m_pMasterFramework->BuildScene<CMainGameScene>();
	}
}

void CTitleScene::Render()
{
	auto sz = m_pMasterFramework->GetWindowSize();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.f, 1.f, 1.f, min(m_fFadein, 1.f));
	//glutSolidCube(1.0f);

	glPushMatrix();
	{
		m_texLogo.LoadTexture(0);
		CTextureLibraray::UsingTexture2D();
		{

			glBegin(GL_QUADS);
			{
				glTexCoord2f(+0.0f, +1.0f);					glVertex2f(0.0f, 0.0f);
				glTexCoord2f(+0.0f, +0.0f);					glVertex2f(0.0f, sz.y);
				glTexCoord2f(+1.0f, +0.0f);					glVertex2f(sz.x, sz.y);
				glTexCoord2f(+1.0f, +1.0f);					glVertex2f(sz.x, 0.0f);
			}
			glEnd();

		}
		CTextureLibraray::StopUsingTexture2D();
	}
	glPopMatrix();
	glDisable(GL_BLEND);
}

void CTitleScene::Reshape()
{
	auto sz = m_pMasterFramework->GetWindowSize();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, sz.x, sz.y, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
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

void CTitleScene::KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;
	}
}

void CTitleScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	m_texLogo.SetTexture(L"Image/warp.png");
}
