#include "stdafx.h"
#include "Tools.h"
#include "GLFramework.h"
#include "MainGameScene.h"
#include "Robot.h"


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

	BOT.Robot_timer();
}


void CMainGameScene::Render()
{
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	{
		glTranslatef(0, 10, 0);
		glScalef(0.01, 0.01, 0.01);
		glRotatef(180, 0, 1, 0);
		BOT.Make_Robot(0, 0, 0, 0);
	}
	glPopMatrix();
	
	glColor3f(1, 0, 0);
	glutSolidCube(10);
	
	glPushMatrix();
	{
		glRotatef(180, 0, 1, 0);
		DrawTree(10.0, 10.0);
		glTranslatef(10, 0, 1);
		DrawTree(10.0, 10.0);
	}
	glPopMatrix();


	//Camera User HUD
	glPushMatrix();
	{
		glDisable(GL_DEPTH_TEST);
		glTranslatef(m_Camera->Position.x, m_Camera->Position.y, m_Camera->Position.z);
		glRotatef(90, 0, 1, 0);
		glRotatef(-m_Camera->Angle.yaw, 0, 1, 0);
		glRotatef(-m_Camera->Angle.pitch, 1, 0, 0);
		glPushMatrix();
		{
			if (!IsZoom) {
				glRotatef(180, 0, 1, 0);
				glTranslatef(2, -10, -10);
				DrawHud(5.5, 5.5);
			}
			else if (IsZoom) {
				glRotatef(180, 0, 1, 0);
				glTranslatef(-0.4, -6.2, -10);
				DrawHud(4, 4);
			}
		}
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(1000, 1000, 1000);
		DrawDummy(0.01f, 0.01f);
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
		IsZoom = boolswitch(IsZoom);
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
	default:
		BOT.control_robot(key);
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
	IsZoom = false;
}

void CMainGameScene::DrawTree(float w, float h)
{
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

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(w, 2 * h, 0);
			glTexCoord2f(0, 1.0f);
			glVertex3f(-w, 2 * h, 0);
			glTexCoord2f(0, 0.0f);
			glVertex3f(-w, 0, 0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1 * w, 0, 0);
			glEnd();
		}
		glDisable(GL_BLEND);
		glPopMatrix();
	}
	CTextureLibraray::StopUsingTexture2D();
}

void CMainGameScene::DrawHud(float w, float h)
{
	CTextureLibraray::UsingTexture2D();
	{
		glColor4f(1.f, 1.f, 1.f, 1.0f);
		if(!IsZoom)
			Texture.m_tex_UserHUD_notZoom.LoadTexture(0);
		else if(IsZoom)
			Texture.m_tex_UserHUD_Zoom.LoadTexture(0);
		glEnable(GL_BLEND); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glPushMatrix();

		glBegin(GL_QUADS); {

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(w, 2 * h, 0);
			glTexCoord2f(0, 1.0f);
			glVertex3f(-w, 2 * h, 0);
			glTexCoord2f(0, 0.0f);
			glVertex3f(-w, 0, 0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1 * w, 0, 0);
			glEnd();
		}
		glDisable(GL_BLEND);
		glPopMatrix();
	}
	CTextureLibraray::StopUsingTexture2D();
}

void CMainGameScene::DrawDummy(float w, float h)
{
	CTextureLibraray::UsingTexture2D();
	{
		glColor4f(1.f, 1.f, 1.f, 1.0f);

		Texture.m_tex_dummy.LoadTexture(0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glPushMatrix();

		glBegin(GL_QUADS); {

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(w, 2 * h, 0);
			glTexCoord2f(0, 1.0f);
			glVertex3f(-w, 2 * h, 0);
			glTexCoord2f(0, 0.0f);
			glVertex3f(-w, 0, 0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1 * w, 0, 0);
			glEnd();
		}
		glDisable(GL_BLEND);
		glPopMatrix();
	}
	CTextureLibraray::StopUsingTexture2D();
}