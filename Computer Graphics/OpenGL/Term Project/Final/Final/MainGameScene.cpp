#include "stdafx.h"
#include "MainGameScene.h"
#include "GLFramework.h"
#include "Spline.h"


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

	Helicopter.RotateWing(10);

	glutWarpPointer(400, 400);
	m_Camera->SetCamera();
}

void CMainGameScene::Render()
{
	glColor4f(1.f, 1.f, 1.f, 1.f);
	//glutSolidCube(1.0f);
	glPushMatrix();
	{
		glRotatef(180, 0, 1, 0);
		Helicopter.Render();
	}
	glPopMatrix();

	glPushMatrix();
	{
		CTextureLibraray::UsingTexture2D();
		{
			glColor4f(1.f, 1.f, 1.f, 1.f);
			IntroTexture.m_tex_sea.LoadTexture(0);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glBegin(GL_QUADS); {
				glVertex3f(+100.0f, 0, +100.0f);		glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-100.0f, 0, +100.0f);		glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-100.0f, 0, -100.0f);		glTexCoord2f(0.0f, 0.0f);
				glVertex3f(+100.0f, 0, -100.0f);		glTexCoord2f(1.0f, 0.0f);
				glEnd();
			}
		}
		CTextureLibraray::StopUsingTexture2D();
	}

	glPushMatrix();
	{
		CTextureLibraray::UsingTexture2D();
		{
			glTranslatef(0, 20, 100);
			glColor4f(1.f, 1.f, 1.f, 1.f);
			IntroTexture.m_tex_moon.LoadTexture(0);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glBegin(GL_QUADS); {
				glVertex3f(+5.0f, +5.0f, 0);		glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-5.0f, +5.0f, 0);		glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-5.0f, -5.0f, 0);		glTexCoord2f(0.0f, 0.0f);
				glVertex3f(+5.0f, -5.0f, 0);		glTexCoord2f(1.0f, 0.0f); 
				glEnd();
			}
		}
		CTextureLibraray::StopUsingTexture2D();
	}
	glPopMatrix();

	glPushMatrix();
	{
		CTextureLibraray::UsingTexture2D();
		{
			glTranslatef(0, 20, 110);
			glColor4f(1.f, 1.f, 1.f, 1.f);
			IntroTexture.m_tex_sky.LoadTexture(0);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glBegin(GL_QUADS); {
				glVertex3f(+100.0f, +100.0f, 0);		glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-100.0f, +100.0f, 0);		glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-100.0f, -100.0f, 0);		glTexCoord2f(0.0f, 0.0f);
				glVertex3f(+100.0f, -100.0f, 0);		glTexCoord2f(1.0f, 0.0f);
				glEnd();
			}
		}
		CTextureLibraray::StopUsingTexture2D();
	}
	glPopMatrix();
}

void CMainGameScene::Reshape()
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
	glClearColor(0.0f, 0.0f, 0.0f, 1);

	IntroTexture.initTextures();

	m_Camera = m_pMasterFramework->GetCamera();

	m_Camera->SetCameraPosition(0.f, 15.0f, -15.f);

	Helicopter.MovePosition(0, 1000, 0);
}