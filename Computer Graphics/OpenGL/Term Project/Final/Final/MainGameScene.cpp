#include "stdafx.h"
#include "Tools.h"
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
	if (CameraMove[DIRECTION::FRONT])	m_Camera->Move(DIRECTION::FRONT, 0.5f);
	if (CameraMove[DIRECTION::BACK])	m_Camera->Move(DIRECTION::BACK, 0.5f);
	if (CameraMove[DIRECTION::LEFT])	m_Camera->Move(DIRECTION::LEFT, 0.5f);
	if (CameraMove[DIRECTION::RIGHT])	m_Camera->Move(DIRECTION::RIGHT, 0.5f);

	glutWarpPointer((CLIENTWIDTH * 0.5), (CLIENTHEIGHT * 0.5));
	m_Camera->SetCamera();
}


void CMainGameScene::Render()
{
	glutSolidCube(10);

	glPushMatrix();
	{
		glRotatef(180, 0, 1, 0);
		DrawTree(10.0, 10.0);
		glTranslatef(10, 0, 1);
		DrawTree(10.0, 10.0);
	}
	glPopMatrix();
}

void CMainGameScene::Reshape(int w, int h)
{
}

void CMainGameScene::MouseEvent(int button, int state, int x, int y)
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

void CMainGameScene::MouseMove(int x, int y)
{
	m_Camera->getMouse(x, y);
	m_Camera->SetLookVector();
}

void CMainGameScene::KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;
	case 'w':
		CameraMove[DIRECTION::FRONT] = true;
		break;
	case 's':
		CameraMove[DIRECTION::BACK] = true;
		break;
	case 'a':
		CameraMove[DIRECTION::LEFT] = true;
		break;
	case 'd':
		CameraMove[DIRECTION::RIGHT] = true;
		break;
	}
}

void CMainGameScene::KeyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		CameraMove[DIRECTION::FRONT] = false;
		break;
	case 's':
		CameraMove[DIRECTION::BACK] = false;
		break;
	case 'a':
		CameraMove[DIRECTION::LEFT] = false;
		break;
	case 'd':
		CameraMove[DIRECTION::RIGHT] = false;
		break;
	}
}


void CMainGameScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);
	Texture.initTextures();

	m_Camera = m_pMasterFramework->GetCamera();
}

void CMainGameScene::DrawTree(float w, float h)
{
	glEnable(GL_DEPTH_TEST);
	CTextureLibraray::UsingTexture2D();
	{
		glColor4f(1.f, 1.f, 1.f, 1.0f);

		Texture.m_tex_Tree.LoadTexture(0); 
		glEnable(GL_BLEND); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glPushMatrix();

		glBegin(GL_QUADS); {

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1 * w, 0, 0);
			glTexCoord2f(0, 0.0f);
			glVertex3f(-w, 0, 0);
			glTexCoord2f(0, 1.0f);
			glVertex3f(-w, 2 * h, 0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(w, 2 * h, 0);
			glEnd();
		}

		glDisable(GL_BLEND);
		glPopMatrix();
	}
	CTextureLibraray::StopUsingTexture2D();
}