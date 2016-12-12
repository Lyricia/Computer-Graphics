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
	if (m_IsCrouching && m_camera_ypos_delta < 7){
		m_camera_ypos_delta += 1;
		m_Camera->Position.y -= (float)m_camera_ypos_delta * 0.1;
	}
	else if (!m_IsCrouching && m_camera_ypos_delta > 0) {
		m_Camera->Position.y += (float)m_camera_ypos_delta * 0.1;
 		m_camera_ypos_delta -= 1;
	}

	for (int i = 0; i < 3; i++) {
		auto k = m_Camera->Position - (m_RobotPosition[i]);
		if (Length(k) < 20 && RobotState[i] != state::dead) {
			BOT[i].robot_shot_status = 1;
		}
		else BOT[i].robot_shot_status = 0;

		
		BOT[i].Robot_timer();
	}
	for(int i=0; i<10; i++)
		RobotMove(i);

	if (CameraMove[DIRECTION::FRONT])	m_Camera->Move(DIRECTION::FRONT, m_PlayerSpeed);
	if (CameraMove[DIRECTION::BACK])	m_Camera->Move(DIRECTION::BACK, m_PlayerSpeed);
	if (CameraMove[DIRECTION::LEFT])	m_Camera->Move(DIRECTION::LEFT, m_PlayerSpeed);
	if (CameraMove[DIRECTION::RIGHT])	m_Camera->Move(DIRECTION::RIGHT, m_PlayerSpeed);

	glutWarpPointer((CLIENTWIDTH * 0.5), (CLIENTHEIGHT * 0.5));
	m_Camera->SetCamera();
}

void CMainGameScene::Render()
{
	//glEnable(GL_DEPTH_TEST);

	//Draw Field
	glPushMatrix();
	{
		glScalef(0.01, 0.01, 0.01);
		DrawField();

		DrawDummy(0.01f, 0.01f);
	}
	glPopMatrix();

	//Draw Robot
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		{
			glTranslatef(m_RobotPosition[i].x, m_RobotPosition[i].y, m_RobotPosition[i].z);
			glPushMatrix();
			{
				if (RobotState[i] == state::dead)
					glRotatef(90, 1, 0, 0);
				glTranslatef(0, 1.5, 0);
				glRotatef(-m_RobotDir[i], 0, 1, 0);
				glScalef(0.005, 0.005, 0.005);
				BOT[0].Make_Robot(0, 0, 0, 0);
			}
			glPopMatrix();
		}
		glPopMatrix();

	}


	glPushMatrix();
	{
		glTranslatef(m_RobotPosition[3].x, m_RobotPosition[3].y, m_RobotPosition[3].z);
		glPushMatrix();
		{
			if (RobotState[3] == state::dead)
				glRotatef(90, 1, 0, 0);
			glTranslatef(0, 1.5, 0);
			glRotatef(-90, 0, 1, 0);
			glScalef(0.05, 0.05, 0.05);
			BOT[0].Make_Robot(0, 0, 0, 0);
		}
		glPopMatrix();
	}
	glPopMatrix();

	//Draw Tree
	glPushMatrix();
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		for (int i = 0; i < 200; i++) {
			glPushMatrix();
			Texture.m_tex_Tree[m_TreeTexIdx[i]].LoadTexture(0);
			glTranslatef(m_TreePosition[i].x, 0, m_TreePosition[i].z);
			glPushMatrix();
			{
				//glScalef(0.7, 0.7, 0.7);
				DrawTree(10.0, 10.0);
				glRotatef(90, 0, 1, 0);
				DrawTree(10.0, 10.0);
			}
			glPopMatrix();
			glPopMatrix();
		}
		glDisable(GL_BLEND);
	}
	glPopMatrix();


	//Draw Bush
	glPushMatrix();
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glPushMatrix();
		{
			Texture.m_tex_bush[2].LoadTexture(0);
			glTranslatef(10, 0, 23);
			glPushMatrix();
			{
				glScalef(0.01, 0.01, 0.01);
				DrawBush();
			}
			glPopMatrix();
		}
		glPopMatrix(); 

		for (int i = 0; i < 6; i++) {
			glPushMatrix();
			{
				glTranslatef(-70 + 10 * i, 0, 28);
				Texture.m_tex_bush[i].LoadTexture(0);
				glScalef(0.01, 0.01, 0.01);
				DrawBush();
			}
			glPopMatrix();
		}
		glDisable(GL_BLEND);
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
			if (!m_IsKnife) {
				if (!m_IsSpecial) {
					glRotatef(180, 0, 1, 0);
					glTranslatef(2.5, -10, -10);
					DrawHud(7, 5.5);
				}
				else if (m_IsSpecial) {
					glRotatef(180, 0, 1, 0);
					glTranslatef(-0.4, -6.2, -10);
					DrawHud(4, 4);
				}
			}
			else if (m_IsKnife)
			{
				if (!m_IsAttack) {
					glRotatef(180, 0, 1, 0);
					glTranslatef(7,-6,-10);
					DrawKnife(3.5,3.5);
				}
				else if (m_IsAttack) {
					//glRotatef(-10, 0, 0, 1);
					glRotatef(180, 0, 1, 0);
					glTranslatef(3, -8, -10);
					DrawKnife(8, 4);
				}
			}
		}
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
	glPopMatrix();

	//dummy
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
		m_IsAttack = true;
		Sound.SoundPlay(2, 2);
		for (int i = 0; i < 10; i++) {
			if (RobotKill(i)){
				RobotState[i] = state::dead;
				m_RobotPosition[i].y == 0.1;
				BOT[i].robot_arm_status = 0;
				BOT[i].robot_head_status = 0;
				BOT[i].robot_leg_status = 0;
				BOT[i].RunOrWalk = 0;
			}
		}
		break;
	case GLKeyStateCombine::RBUTTONDOWN:
		m_IsSpecial = boolswitch(m_IsSpecial);
		break;
	case GLKeyStateCombine::LBUTTONUP:
		m_IsAttack = false;
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
		if(IsCanMove())
			CameraMove[DIRECTION::FRONT] = true;
		else
			CameraMove[DIRECTION::FRONT] = false;
		break;
	case 's':
		if (IsCanMove())
			CameraMove[DIRECTION::BACK] = true;
		else
			CameraMove[DIRECTION::BACK] = false;
		break;
	case 'a':
		if (IsCanMove())
			CameraMove[DIRECTION::LEFT] = true;
		else
			CameraMove[DIRECTION::LEFT] = false;
		break;
	case 'd':
		if (IsCanMove())
			CameraMove[DIRECTION::RIGHT] = true;
		else
			CameraMove[DIRECTION::RIGHT] = false;
		break;
	case 'u':
		m_Camera->Position.y++;
		break;
	case 'j':
		m_Camera->Position.y--;
		break;
		
	case 'z':
		for (int i = 0; i < 10; i++) {
			RobotRecog(i);
		}
		Sound.SoundPlay(1, 1);
		break;

	case '1':
		m_IsKnife = false;
		break;

	case '2':
		m_IsKnife = true;
		break;

	case '6':
		for (int i = 0; i < 3; i++) {
			BOT[i].robot_shot_status = 1;
		}
		break;

	case 'f':
		m_IsAttack = true;
		break;

	case 'r':
		m_IsDashing = boolswitch(m_IsDashing);
		if (m_IsDashing) m_PlayerSpeed = 1.0f;
		else if (!m_IsDashing) m_PlayerSpeed = 0.5f;
		break;
	case 'c':
		if(m_camera_ypos_delta == 0 || m_camera_ypos_delta == 7)
			m_IsCrouching = boolswitch(m_IsCrouching);
		if (m_IsCrouching)			m_PlayerSpeed = 0.03f;
		else if (!m_IsCrouching)	m_PlayerSpeed = 0.2f;
		break;

	default:
		BOT[0].control_robot(key);
		break;
	}

	std::cout << m_Camera->Position.x << " " << m_Camera->Position.z << std::endl;
}

void CMainGameScene::KeyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		if (IsCanMove())
			CameraMove[DIRECTION::FRONT] = false;
		else
			CameraMove[DIRECTION::FRONT] = false;
		break;
	case 's':
		if (IsCanMove())
			CameraMove[DIRECTION::BACK] = false;
		else
			CameraMove[DIRECTION::BACK] = false;
		break;
	case 'a':
		if (IsCanMove())
			CameraMove[DIRECTION::LEFT] = false;
		else
			CameraMove[DIRECTION::LEFT] = false;
		break;
	case 'd':
		if (IsCanMove())
			CameraMove[DIRECTION::RIGHT] = false;
		else
			CameraMove[DIRECTION::RIGHT] = false;
		break;

	case 'f':
		m_IsAttack = false;
		break;
	}	
}

void CMainGameScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);
	m_Camera = m_pMasterFramework->GetCamera();
	
	Texture.initTextures();

	m_PlayerSpeed = 0.2f;

	m_IsSpecial = false;
	m_IsKnife = false;
	m_IsAttack = false;
	m_IsCrouching = false;
	m_IsDashing = false;
	m_camera_ypos_delta = 0.f;
	m_Camera->Position = { -72.5, 4, 27 };

	for (int i = 0; i < 10; i++) {
		m_RobotPosition[i] = { 0, 0, 0 };
		RobotState[i] = state::stop;
	}
	for (int i = 0; i < 200; i++) {
		m_TreePosition[i].x = -65 + rand() % 140;
		m_TreePosition[i].z = -90 + rand() % 100;
		m_TreeTexIdx[i] = 2 + rand() % 8;
	}

	m_RobotPosition[1] = { -30, 0, -116 };
	m_RobotPosition[2] = { -15, 0, -116 };
	m_RobotPosition[3] = {5, 0, -225};
	Sound.InsertSound("Sound/Main_BGM.ogg", 0);
	Sound.InsertSound("Sound/whiparam.mp3", 1, false);
	Sound.InsertSound("Sound/main_gun_sound.wav", 2, false);
	Sound.SoundPlay(0, 0);
}

void CMainGameScene::DrawTree(float w, float h)
{
	CTextureLibraray::UsingTexture2D();
	{
		glColor4f(1.f, 1.f, 1.f, 1.0f);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

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
		glPopMatrix();
	}
	CTextureLibraray::StopUsingTexture2D();
}

void CMainGameScene::DrawBush()
{
	CTextureLibraray::UsingTexture2D();
	{
		glColor4f(1.f, 1.f, 1.f, 1.0f);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glPushMatrix();
		glBegin(GL_QUADS); 
		{
			//앞!!!
			glTexCoord2f(0, 1.0f);
			glVertex3f(-300, 300, 300);

			glTexCoord2f(0, 0);
			glVertex3f(-300, 0, 300);

			glTexCoord2f(1.0f, 0);
			glVertex3f(300, 0, 300);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(300, 300, 300);

			//뒤!! 뒤더라도 앞에서봤을떄의 앞 면이 오도록 그립니다! ->우리의 시연은 뒤돌아보지않아요 ?? 이거방향나중에바꿀생각하고있어라원성연
			glTexCoord2f(0, 1.0f);
			glVertex3f(-300, 300, -300);

			glTexCoord2f(0, 0);
			glVertex3f(-300, 0, -300);

			glTexCoord2f(1.0f, 0);
			glVertex3f(300, 0, -300);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(300, 300, -300);

			//왼쪽~~!!	안에서보는게 아마 중요할것 같지않나?? 아닐까??	->글쎼?? 어떨거같아?? 밖에서보는걸로가자! 그래!

			glTexCoord2f(0, 1.0f);
			glVertex3f(-300, 300, -300);

			glTexCoord2f(0, 0);
			glVertex3f(-300, 0, -300);

			glTexCoord2f(1.0f, 0);
			glVertex3f(-300, 0, +300);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-300, 300, +300);

			//오른쪽!!

			glTexCoord2f(0, 1.0f);
			glVertex3f(300, 300, 300);

			glTexCoord2f(0, 0);
			glVertex3f(300, 0, 300);

			glTexCoord2f(1.0f, 0);
			glVertex3f(300, 0, -300);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(300, 300, -300);


		}
		glEnd();
		glPopMatrix();
	}
	CTextureLibraray::StopUsingTexture2D();
}

void CMainGameScene::DrawHud(float w, float h)
{
	CTextureLibraray::UsingTexture2D();
	{
		glColor4f(1.f, 1.f, 1.f, 1.0f);
		if(!m_IsSpecial)
			Texture.m_tex_UserHUD_notZoom.LoadTexture(0);
		else if(m_IsSpecial)
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

void CMainGameScene::DrawKnife(float w, float h)
{
	CTextureLibraray::UsingTexture2D();
	{
		glColor4f(1.f, 1.f, 1.f, 1.0f);
		if (!m_IsAttack)
			Texture.m_tex_UserHUD_Knife_Ready.LoadTexture(0);
		else if (m_IsAttack)
			Texture.m_tex_UserHUD_Knife_Attack.LoadTexture(0);
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

void CMainGameScene::DrawField()
{
	CTextureLibraray::UsingTexture2D();
	{
		glColor4f(1.f, 1.f, 1.f, 1.0f);

		//Water
		{
			Texture.m_tex_Field_Water.LoadTexture(0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			glPushMatrix();
			{
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0.0, 100.0f);
					glVertex3f(8000, -2000, -20000);

					glTexCoord2f(0.0, 0.0f);
					glVertex3f(8000, -2000, 4000);

					glTexCoord2f(100.0f, 0.0f);
					glVertex3f(20000, -2000, 4000);

					glTexCoord2f(100.0f, 100.0f);
					glVertex3f(20000, -2000, -20000);

					// 여기서 하는거는 계곡 물!!

					glTexCoord2f(0.0, 10.0f);
					glVertex3f(-8000, -500, -18000);

					glTexCoord2f(0.0, 0.0f);
					glVertex3f(-8000, -500, -12000);

					glTexCoord2f(10.0f, 0.0f);
					glVertex3f(8000, -2000, -12000);

					glTexCoord2f(10.0f, 10.0f);
					glVertex3f(8000, -2000, -18000);
				}
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_BLEND);
		}

		//Water Fall
		{
			Texture.m_tex_Field_Waterfall.LoadTexture(0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			glPushMatrix();
			{
				glBegin(GL_QUADS);
				{

					glTexCoord2f(1.0, 1.0f);
					glVertex3f(-8000, 2000, -12000);

					glTexCoord2f(1.0, 0.0f);
					glVertex3f(-8000, -600, -12000);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(-8000, -600, -18000);

					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(-8000, 2000, -18000);
				}
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_BLEND);
		}

		//Cliff
		{
			Texture.m_tex_Field_Cliff.LoadTexture(0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			glPushMatrix();
			{
				glBegin(GL_QUADS);
				{
					glTexCoord2f(16.0, 2.0f);
					glVertex3f(-8000, 0, -12000);

					glTexCoord2f(16.0, 0.0f);
					glVertex3f(-8000, -2000, -12000);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(8000, -2000, -12000);

					glTexCoord2f(0.0f, 2.0f);
					glVertex3f(8000, 0, -12000);


					glTexCoord2f(0.0, 2.0f);
					glVertex3f(-8000, 0, -18000);

					glTexCoord2f(0.0, 0.0f);
					glVertex3f(-8000, -2000, -18000);

					glTexCoord2f(16.0f, 0.0f);
					glVertex3f(8000, -2000, -18000);

					glTexCoord2f(16.0f, 2.0f);
					glVertex3f(8000, 0, -18000);
				}
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_BLEND);
		}

		//Tree Wall
		{
			Texture.m_tex_Field_TreeWall.LoadTexture(0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			glPushMatrix();
			{
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0.0, 1.0f);				glVertex3f(-8000, 2000, 4000);
					glTexCoord2f(0.0, 0.0f);				glVertex3f(-8000, 0, 4000);
					glTexCoord2f(4.0f, 0.0f);				glVertex3f(-8000, 0, -12000);
					glTexCoord2f(4.0f, 1.0f);				glVertex3f(-8000, 2000, -12000);

					glTexCoord2f(4.0f, 1.0f);				glVertex3f(-8000, 2000, -18000);
					glTexCoord2f(4.0f, 0.0f);				glVertex3f(-8000, 0, -18000);
					glTexCoord2f(0.0, 0.0f);				glVertex3f(-8000, 0, -34000);
					glTexCoord2f(0.0, 1.0f);				glVertex3f(-8000, 2000, -34000);

					glTexCoord2f(0.0, 1.0f);				glVertex3f(-8000, 2000, 3000);
					glTexCoord2f(0.0, 0.0f);				glVertex3f(-8000, 0, 3000);
					glTexCoord2f(4.0f, 0.0f);				glVertex3f(8000, 0, 3000);
					glTexCoord2f(4.0f, 1.0f);				glVertex3f(8000, 2000, 3000);
				}
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_BLEND);
		}

		//Ground
		{
			Texture.m_tex_Field_Ground.LoadTexture(0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			glPushMatrix();
			{
				glBegin(GL_QUADS);
				{
					// 여기서 하는건 알다시피 그거! 강건너기전!!!
					glTexCoord2f(-20.0f, -30.0f);					glVertex3f(-8000, 0, -12000);
					glTexCoord2f(-20.0f, 30.0f);					glVertex3f(-8000, 0, 3000);
					glTexCoord2f(20.0f, 30.0f);						glVertex3f(8000, 0, 3000);
					glTexCoord2f(20.0f, -30.0f);					glVertex3f(8000, 0, -12000);

					// 강건넌 후!!!
					glTexCoord2f(-20.0f, -30.0f);					glVertex3f(-8000, 0, -18000);
					glTexCoord2f(-20.0f, 30.0f);					glVertex3f(-8000, 0, -34000);
					glTexCoord2f(20.0f, 30.0f);						glVertex3f(8000, 0, -34000);
					glTexCoord2f(20.0f, -30.0f);					glVertex3f(8000, 0, -18000);
				}
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_BLEND);
		}

		//Bridge
		{
			Texture.m_tex_Field_Bridge.LoadTexture(0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			glPushMatrix();
			{
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0.0, 4.0f);					glVertex3f(-3000, 1, -18000);
					glTexCoord2f(0.0, 0.0f);					glVertex3f(-3000, 1, -12000);
					glTexCoord2f(1.0f, 0.0f);					glVertex3f(-2000, 1, -12000);
					glTexCoord2f(1.0f, 4.0f);					glVertex3f(-2000, 1, -18000);
				}
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_BLEND);
		}

		//castle_wall
		{
			Texture.m_tex_castle.LoadTexture(0);

			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			glBegin(GL_QUADS);

			// 왼쪽아래먼저 해보자!!!
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(-6000, 2000, -20000);

			glTexCoord2f(0.0, 0.0f);
			glVertex3f(-6000, 0, -20000);

			glTexCoord2f(2.0f, 0.0f);
			glVertex3f(-3000, 0, -20000);

			glTexCoord2f(2.0f, 1.0f);
			glVertex3f(-3000, 2000, -20000);

			{
				{
					glTexCoord2f(0.0, 1.0f);
					glVertex3f(-3000, 2000, -20000);

					glTexCoord2f(0.0, 0.0f);
					glVertex3f(-3000, 0, -20000);

					glTexCoord2f(0.1f, 0.0f);
					glVertex3f(-3000, 0, -20100);

					glTexCoord2f(0.1f, 1.0f);
					glVertex3f(-3000, 2000, -20100);
				}

				glTexCoord2f(0.0, 1.0f);
				glVertex3f(-5950, 2000, -20100);

				glTexCoord2f(0.0, 0.0f);
				glVertex3f(-5950, 0, -20100);

				glTexCoord2f(2.0f, 0.0f);
				glVertex3f(-3000, 0, -20100);

				glTexCoord2f(2.0f, 1.0f);
				glVertex3f(-3000, 2000, -20100);
			}

			// 왼아 대각
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-7000, 2000, -21000);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-7000, 0, -21000);

			glTexCoord2f(0.0, 0.0f);
			glVertex3f(-6000, 0, -20000);

			glTexCoord2f(0.0, 1.0f);
			glVertex3f(-6000, 2000, -20000);

			{
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-6900, 2000, -21100);

				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(-6900, 0, -21100);

				glTexCoord2f(0.0, 0.0f);
				glVertex3f(-5950, 0, -20100);

				glTexCoord2f(0.0, 1.0f);
				glVertex3f(-5950, 2000, -20100);
			}

			//왼

			glTexCoord2f(4.0f, 1.0f);
			glVertex3f(-7000, 2000, -21000);

			glTexCoord2f(4.0f, 0.0f);
			glVertex3f(-7000, 0, -21000);

			glTexCoord2f(0.0, 0.0f);
			glVertex3f(-7000, 0, -29000);

			glTexCoord2f(0.0, 1.0f);
			glVertex3f(-7000, 2000, -29000);

			{
				glTexCoord2f(4.0f, 1.0f);
				glVertex3f(-6900, 2000, -21100);

				glTexCoord2f(4.0f, 0.0f);
				glVertex3f(-6900, 0, -21100);

				glTexCoord2f(0.0, 0.0f);
				glVertex3f(-6900, 0, -28900);

				glTexCoord2f(0.0, 1.0f);
				glVertex3f(-6900, 2000, -28900);
			}

			// 왼뒤대각

			glTexCoord2f(0.0, 1.0f);
			glVertex3f(-7000, 2000, -29000);

			glTexCoord2f(0.0, 0.0f);
			glVertex3f(-7000, 0, -29000);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-6000, 0, -30000);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-6000, 2000, -30000);

			{
				glTexCoord2f(0.0, 1.0f);
				glVertex3f(-6900, 2000, -29000);

				glTexCoord2f(0.0, 0.0f);
				glVertex3f(-6900, 0, -29000);

				glTexCoord2f(4.0f, 0.0f);
				glVertex3f(-6000, 0, -30000);

				glTexCoord2f(4.0f, 1.0f);
				glVertex3f(-6000, 2000, -30000);
			}

			// 뒤

			glTexCoord2f(0.0, 1.0f);
			glVertex3f(-6000, 2000, -30000);

			glTexCoord2f(0.0, 0.0f);
			glVertex3f(-6000, 0, -30000);

			glTexCoord2f(4.0f, 0.0f);
			glVertex3f(6000, 0, -30000);

			glTexCoord2f(4.0f, 1.0f);
			glVertex3f(6000, 2000, -30000);

			// 뒤 오른쪽 대각

			glTexCoord2f(0.0, 1.0f);
			glVertex3f(6000, 2000, -30000);

			glTexCoord2f(0.0, 0.0f);
			glVertex3f(6000, 0, -30000);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(7000, 0, -29000);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(7000, 2000, -29000);


			//오른쪽

			glTexCoord2f(4.0f, 1.0f);
			glVertex3f(7000, 2000, -29000);

			glTexCoord2f(4.0f, 0.0f);
			glVertex3f(7000, 0, -29000);

			glTexCoord2f(0.0, 0.0f);
			glVertex3f(7000, 0, -21000);

			glTexCoord2f(0.0, 1.0f);
			glVertex3f(7000, 2000, -21000);

			//오앞대각

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(7000, 2000, -21000);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(7000, 0, -21000);

			glTexCoord2f(0.0, 0.0f);
			glVertex3f(6000, 0, -20000);

			glTexCoord2f(0.0, 1.0f);
			glVertex3f(6000, 2000, -20000);

			{
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(7000, 2000, -21000);

				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(7000, 0, -21000);

				glTexCoord2f(0.0, 0.0f);
				glVertex3f(5900, 0, -20100);

				glTexCoord2f(0.0, 1.0f);
				glVertex3f(5900, 2000, -20100);
			}

			// 오른쪽이야
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(-2000, 2000, -20000);

			glTexCoord2f(0.0, 0.0f);
			glVertex3f(-2000, 0, -20000);

			glTexCoord2f(2.0f, 0.0f);
			glVertex3f(6000, 0, -20000);

			glTexCoord2f(2.0f, 1.0f);
			glVertex3f(6000, 2000, -20000);

			{
				{
					glTexCoord2f(0.0, 1.0f);
					glVertex3f(-2000, 2000, -20000);

					glTexCoord2f(0.0, 0.0f);
					glVertex3f(-2000, 0, -20000);

					glTexCoord2f(0.1f, 0.0f);
					glVertex3f(-2000, 0, -20100);

					glTexCoord2f(0.1f, 1.0f);
					glVertex3f(-2000, 2000, -20100);
				}
				glTexCoord2f(0.0, 1.0f);
				glVertex3f(-2000, 2000, -20100);

				glTexCoord2f(0.0, 0.0f);
				glVertex3f(-2000, 0, -20100);

				glTexCoord2f(2.0f, 0.0f);
				glVertex3f(6000, 0, -20100);

				glTexCoord2f(2.0f, 1.0f);
				glVertex3f(6000, 2000, -20100);
			}

			glEnd();
			glDisable(GL_TEXTURE_2D);

			//glPopMatrix();
		}
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

void CMainGameScene::RobotMove(int Index)
{
	if (RobotState[Index] == state::recog) {
		Vec3f Robot_to_player = m_Camera->Position - m_RobotPosition[Index];
		Robot_to_player = Normalize(Robot_to_player);
		m_RobotDir[Index] = atan2f(Robot_to_player.x, Robot_to_player.y);
		m_RobotPosition[Index] += Robot_to_player;
		m_RobotPosition[Index].y = 0;
	}
}

void CMainGameScene::RobotRecog(int Index)
{
	if (Length(m_Camera->Position - m_RobotPosition[Index]) < 50) {
		if (RobotState[Index] != state::dead) {
			if (RobotState[Index] != state::recog) {
				BOT[Index].robot_head_status = 1;
				BOT[Index].robot_leg_status = 1;
				BOT[Index].RunOrWalk = 1;
				RobotState[Index] = state::recog;
			}
		}
	}
}

bool CMainGameScene::RobotKill(int Index)
{
	auto k = m_RobotPosition[Index] - m_Camera->Position;
	if (m_IsKnife) {
		if (Length(k) < 5)
			return true;
		else
			return false;
	}
	else {
		for (int i = 0; i < 100; i++) {
			if (Length((m_Camera->Position + m_Camera->getLookvector() * i) - m_RobotPosition[Index]) < 2)
				return true;
		}
		return false;
	}
}

bool CMainGameScene::IsCanMove()
{
	if (m_Camera->Position.x < -80){
		m_Camera->Position.x = -79;
		return false;
	}
	if (m_Camera->Position.x > +80) {
		m_Camera->Position.x = 79;
		return false;
	}
	if (m_Camera->Position.z > 30) {
		m_Camera->Position.z = 29;
		return false;
	}	
	return true;
}