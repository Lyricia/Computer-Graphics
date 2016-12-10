#include "stdafx.h"
#include "IntroScene.h"
#include "GLFramework.h"
#include "MainGameScene.h"

CIntroScene::CIntroScene()
{
}


CIntroScene::~CIntroScene()
{
}

void CIntroScene::Update()
{
	static float HeliDist = 0;

	if (CameraMove[DIRECTION::FRONT])	m_Camera->Move(DIRECTION::FRONT, 0.5f);
	if (CameraMove[DIRECTION::BACK])	m_Camera->Move(DIRECTION::BACK, 0.5f);
	if (CameraMove[DIRECTION::LEFT])	m_Camera->Move(DIRECTION::LEFT, 0.5f);
	if (CameraMove[DIRECTION::RIGHT])	m_Camera->Move(DIRECTION::RIGHT, 0.5f);

	glutWarpPointer((CLIENTWIDTH * 0.5), (CLIENTHEIGHT * 0.5));
	m_Camera->SetCamera();

	Helicopter.RotateWing(10);
	Helicopter.MovePosition(0, 900, 1200 - HeliDist);
	if (HeliDist < 1200)
		HeliDist += 5;

	m_Fade -= 0.005;
}
 
void CIntroScene::Render()
{
	glEnable(GL_DEPTH_TEST);

	{
		//Render Helicopter
		glPushMatrix();
		{
			glRotatef(180, 0, 1, 0);
			Helicopter.Render();
		}
		glPopMatrix();

		//Render Sea
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
		glPopMatrix();

		//Render Moon
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

		//Render Sky
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

	//Render FadeScreen
	glPushMatrix();
	{
		glTranslatef(0, 10, m_Camera->Position.z+0.5f);
		//glRotatef(90, 1, 0, 0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS); {
			glColor4f(0, 0, 0, max(m_Fade, 0.0f));
			glVertex3f(+100, 0, 0);
			glVertex3f(-100, 0, 0);
			glVertex3f(-100, 0, +100);
			glVertex3f(+100, 0, +100);
			glEnd();
		}

		glTranslatef(0, 0, 100);
		glBegin(GL_QUADS); {
			glColor4f(0, 0, 0, max(m_Fade, 0.0f));
			glVertex3f(+100, 0, 0);
			glVertex3f(-100, 0, 0);
			glVertex3f(-100, +100,00 );
			glVertex3f(+100, +100,00 );
			glEnd();
		}
		glDisable(GL_BLEND);
		
	}
	glPopMatrix();
}

void CIntroScene::Reshape(int w, int h)
{
}

void CIntroScene::MouseEvent(int button, int state, int x, int y)
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

void CIntroScene::MouseMove(int x, int y)
{
	m_Camera->getMouse(x, y);
	m_Camera->SetLookVector();
}

void CIntroScene::KeyInput(unsigned char key, int x, int y)
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

void CIntroScene::KeyUp(unsigned char key, int x, int y)
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

void CIntroScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);

	IntroTexture.initTextures();

	m_Camera = m_pMasterFramework->GetCamera();
	m_Camera->SetCameraPosition(0.f, 11.0f, -10.f);

	Helicopter.MovePosition(0, 1000, 1200);

	Sound.InsertSound("Sound/heli_sound.wav", 0);
	//glEnable(GL_DEPTH_TEST);
	//Sound.SoundPlay(0, 0);
}