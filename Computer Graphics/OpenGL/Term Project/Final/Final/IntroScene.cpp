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

typedef class point {
public:
	float x;
	float y;
	float z;
}WSYPOINT;

typedef class flow_class {
	WSYPOINT point{ 0 };

	GLfloat ctrlpoints[20][10][3]{ 0 };
	float quad_dis = 5;
	float quad_count = 200;            //이거 필요없는데 ㅡㅡ 너무많이껴서 버릴수가없어
	float type = 2;
	float flow_h_value = 1;
	float all_height = 0;            //파도넘실넘실효과줄거야!
	float height_type = 0;

	int init_onoff = 1;
public:
	void get_helixyz(float x, float y, float z) {
		point.x = x;
		point.y = y + 100;
		point.z = z;
	}
	void init_flow() {

		if (init_onoff)            //최적화를 위하여
		{
			for (int i = 0; i < 20; i++)
			{
				if (i == 0 || i == 9)
					flow_h_value = -200;
				else if (i == 2 || i == 5)
					flow_h_value = -250;
				else if (i == 1 || i == 3 || i == 7)
					flow_h_value = 100;

				for (int j = 0; j < 10; j++)
				{
					ctrlpoints[i][j][0] = (quad_dis * quad_count / 10 * j);
					ctrlpoints[i][j][1] = flow_h_value;
					ctrlpoints[i][j][2] = (quad_dis * quad_count / 10 * i);

					if (j == 3 || j == 6) {
						ctrlpoints[i][j][1] += 150;
					}
					else if (j == 0 || j == 9) {
						ctrlpoints[i][j][1] -= 200;
					}
				}
			}
			init_onoff = 0;
		}
	}
	void update_flow() {
		//물결을 위아래로 흔들어주는 함수입니다!

		if (height_type == 0) {
			all_height += 2;

			if (all_height == 10) {
				height_type = 1;
			}
		}
		else if (height_type == 1) {
			all_height -= 2;

			if (all_height == -8) {
				height_type = 0;
			}
		}
	}
	void draw_flow() {
		glPushMatrix();

		glTranslatef(point.x, point.y + all_height, point.z);


		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 10, 0.0, 1.0, 30, 10, &ctrlpoints[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);

		glMapGrid2f(100, 0.0, 1.0, 100, 0.0, 1.0);
		glEvalMesh2(GL_FILL, 0, 100, 0, 100);

		glPointSize(2.0);

		//SetColor(103, 203, 255);

		/*
		glBegin(GL_POINTS);
		for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		glVertex3fv(ctrlpoints[i][j]);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		*/
		glPopMatrix();
	}
	/*void draw_world() {

	float h = 0;   //높이

	SetColor(103, 203, 255);

	glPushMatrix(); {

	glTranslatef(point.x, point.y, point.z);

	if (type == 1) {
	glBegin(GL_QUADS); {
	for (int j = 0; j < quad_count; j++) {
	for (int i = 0; i < quad_count; i++) {
	//glVertex3f(100, 0, 100);
	//glVertex3f(-100, 0, 100);
	//glVertex3f(-100, 0, -100);
	//glVertex3f(100, 0, -100);
	if (j % 10 < 5) {
	h = j % 10;
	h = 1;
	}
	else if (j % 10 <= 9) {
	h = 10 - (j % 10);
	h = 1;
	}

	glVertex3f((i)* quad_dis, h, j * quad_dis);
	glVertex3f((i)* quad_dis, h, (j + 1) * quad_dis);
	glVertex3f((i + 1) * quad_dis, h, (j + 1) * quad_dis);
	glVertex3f((i + 1) * quad_dis, h, (j)* quad_dis);

	}
	}
	glEnd();
	}
	}
	else if (type == 2) {
	draw_flow();
	}
	glPopMatrix();
	}
	}
	*/
}FLOW; FLOW flow;

typedef class Light_class_1 {
public:
	//조명은 항상 주석을 달자 조명의 주석안달면 진심 빠가임 ㅇㅇㅇㅇㅇㅇ 노답임 ㅇㅇㅇㅇㅇ

	int onoff_light_0 = 0;         //전체 밝게 해줄거야 -> 안써헤헤헤헿 검사할떔만쓸까???ㅎㅎㅎㅎㅎㅎㅎㅎㅎ
	int onoff_light_1 = 1;         // 태양등 입니다.
	int onoff_light_2 = 0;         // 
	int onoff_light_3 = 0;

	void Make_Light() {
		{
			GLfloat AmbientLight_0[] = { 1.0 , 1.0f , 1.0f , 1.0f };
			GLfloat DiffuseLight_0[] = { 0.0f , 0.0f , 0.0f  , 0.5f };
			GLfloat SpecularLight_0[] = { 0.0, 0.0 , 0.0 , 0.5 };
			GLfloat lightPos_0[] = { 0 ,20000, 0 };
			// 조명을 사용하도록 설정
			glEnable(GL_LIGHTING);

			// 조명 설정
			glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight_0);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight_0);
			glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight_0);
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos_0);
			glEnable(GL_LIGHT0);
		}
		{
			GLfloat AmbientLight_1[] = { 0.0f, 0.0f, 0.1f, 0.3f };
			GLfloat DiffuseLight_1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			//GLfloat DiffuseLight_1[] = { 10.0f, 10.0f, 10.0f, 0.1f };

			GLfloat SpecularLight_1[] = { 0.0, 0.0, 0.1, 0.1f };
			//GLfloat lightPos_1[] = { heli.point.x , heli.point.y + 1000,  heli.point.z - 2600, 1.0 };      //진짜설정하고픈 위치
			//GLfloat Spot_dir_1[] = { 0, -1, 1};
			GLfloat lightPos_1[] = { 0 ,  60, 90, 1.0 };      //사기침

			GLfloat Spot_dir_1[] = { 0, -1, 0 };

			GLfloat SPOT_CUTOFF_1[] = { 60 };
			GLfloat SPOT_EXPONENT_1[] = { 0, 0 };
			GLfloat CONSTANT_ATTENUATION_1[] = { 1, 0, 0 };


			glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight_1);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight_1);
			glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight_1);
			glLightfv(GL_LIGHT1, GL_POSITION, lightPos_1);
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Spot_dir_1);
			glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, SPOT_CUTOFF_1);
			glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, SPOT_EXPONENT_1);
			glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, CONSTANT_ATTENUATION_1);
			glEnable(GL_LIGHT1);

			/*
			glPushMatrix();                                                //태양그리는거 나중에 어따가 뺴버리기
			SetColor(250, 250, 250);
			glTranslatef(heli.point.x, heli.point.y + 1000, heli.point.z - 2600);
			glutSolidSphere(200, 100, 100);
			glPopMatrix();
			*/
		}

		{
			GLfloat AmbientLight_2[] = { -10.0f, -10.0f, -10.0f, 0.5f };
			GLfloat DiffuseLight_2[] = { 0.0f, 0.0f, 0.0f, 0.5f };
			GLfloat SpecularLight_2[] = { 0.0,0.0,0.0, 0.5 };
			GLfloat lightPos_2[] = { 0, 20000, 0, 1.0 };

			glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight_2);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight_2);
			glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight_2);
			glLightfv(GL_LIGHT2, GL_POSITION, lightPos_2);

			glEnable(GL_LIGHT2);
		}

		{
			GLfloat AmbientLight_3[] = { 0.0f, 0.0f, 1.0f, 0.5f };
			GLfloat DiffuseLight_3[] = { 1.0f, 0.0f, 0.0f, 0.5f };
			GLfloat SpecularLight_3[] = { 1.0, 1.0, 1.0, 0.5 };
			GLfloat lightPos_3[] = { 0, 20000, 0, 1.0 };


			glLightfv(GL_LIGHT3, GL_AMBIENT, AmbientLight_3);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, DiffuseLight_3);
			glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight_3);
			glLightfv(GL_LIGHT3, GL_POSITION, lightPos_3);
			glEnable(GL_LIGHT3);
		}

		if (onoff_light_0 == 0)
			glDisable(GL_LIGHT0);

		if (onoff_light_1 == 0)
			glDisable(GL_LIGHT1);

		if (onoff_light_2 == 0)
			glDisable(GL_LIGHT2);

		if (onoff_light_3 == 0)
			glDisable(GL_LIGHT3);

		//색은 glcolor 또는 setcolor으로 설정합니다.
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		//이거 되려나 몰라
		GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
		glMateriali(GL_FRONT, GL_SHININESS, 128);

	}
}LIGHT_1; LIGHT_1 light_1;

int onoff_CM_MOVE = 1;

void CIntroScene::Update()
{
	static float HeliDist = 0;

	if (CameraMove[DIRECTION::FRONT])   m_Camera->Move(DIRECTION::FRONT, 0.5f);
	if (CameraMove[DIRECTION::BACK])   m_Camera->Move(DIRECTION::BACK, 0.5f);
	if (CameraMove[DIRECTION::LEFT])   m_Camera->Move(DIRECTION::LEFT, 0.5f);
	if (CameraMove[DIRECTION::RIGHT])   m_Camera->Move(DIRECTION::RIGHT, 0.5f);

	if (onoff_CM_MOVE == 1) {
		m_Camera->Position.z -= 0.1;
		if (m_Camera->Position.z <= -40) {
			onoff_CM_MOVE = 2;
		}
	}
	else if (onoff_CM_MOVE == 2) {
		m_Camera->Position.z += 0.5;
		m_Camera->Position.y -= 0.2;

	}

	std::cout << m_Camera->Position.z << std::endl;

	glutWarpPointer((CLIENTWIDTH * 0.5), (CLIENTHEIGHT * 0.5));
	m_Camera->SetCamera();

	Helicopter.RotateWing(10);
	Helicopter.MovePosition(0, 900, 1200 - HeliDist);
	
	if (HeliDist)
		HeliDist += 10;

	m_Fade -= 0.005;

	flow.init_flow();
	flow.update_flow();
}


void CIntroScene::Render()
{
	light_1.Make_Light();
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
					glVertex3f(+100.0f, 0, +100.0f);      glTexCoord2f(1.0f, 1.0f);
					glVertex3f(-100.0f, 0, +100.0f);      glTexCoord2f(0.0f, 1.0f);
					glVertex3f(-100.0f, 0, -100.0f);      glTexCoord2f(0.0f, 0.0f);
					glVertex3f(+100.0f, 0, -100.0f);      glTexCoord2f(1.0f, 0.0f);
					glEnd();
				}
			}
			CTextureLibraray::StopUsingTexture2D();
		}
		glPopMatrix();

		//Renderflow
		glPushMatrix();
		{
			/*
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
			glVertex3f(+5.0f, +5.0f, 0);      glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-5.0f, +5.0f, 0);      glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-5.0f, -5.0f, 0);      glTexCoord2f(0.0f, 0.0f);
			glVertex3f(+5.0f, -5.0f, 0);      glTexCoord2f(1.0f, 0.0f);
			glEnd();
			}
			}
			CTextureLibraray::StopUsingTexture2D();
			*/
			flow.get_helixyz(100, -30, 150);
			glTranslatef(-5, -0.53, 50);
			glScalef(0.01f, 0.01f, 0.01f);
			flow.draw_flow();
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
					glVertex3f(+5.0f, +5.0f, 0);      glTexCoord2f(1.0f, 1.0f);
					glVertex3f(-5.0f, +5.0f, 0);      glTexCoord2f(0.0f, 1.0f);
					glVertex3f(-5.0f, -5.0f, 0);      glTexCoord2f(0.0f, 0.0f);
					glVertex3f(+5.0f, -5.0f, 0);      glTexCoord2f(1.0f, 0.0f);
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
					glVertex3f(+100.0f, +100.0f, 0);      glTexCoord2f(1.0f, 1.0f);
					glVertex3f(-100.0f, +100.0f, 0);      glTexCoord2f(0.0f, 1.0f);
					glVertex3f(-100.0f, -100.0f, 0);      glTexCoord2f(0.0f, 0.0f);
					glVertex3f(+100.0f, -100.0f, 0);      glTexCoord2f(1.0f, 0.0f);
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
		glTranslatef(0, 10, m_Camera->Position.z + 0.5f);
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
			glVertex3f(-100, +100, 00);
			glVertex3f(+100, +100, 00);
			glEnd();
		}
		glDisable(GL_BLEND);

	}
	glPopMatrix();

	//flow.get_helixyz(heli.point.x, heli.point.y, heli.point.z);

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
		Sound.StopPlay(0);
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
	/*
	m_Camera->getMouse(x, y);
	m_Camera->SetLookVector();
	*/
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
	std::cout << m_Camera->Position.x << " " << m_Camera->Position.z << std::endl;
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
	//m_Camera->SetCameraPosition(0.f, 11.0f, -10.f);
	//glTranslatef(0, 20, 100);
	m_Camera->SetCameraPosition(0.f, 20.0f, 100.f);

	Helicopter.MovePosition(0, 1000, 1200);

	m_Flow.init_flow();

	Sound.InsertSound("Sound/heli_sound.wav", 0);
	Sound.SoundPlay(0, 0);

	glEnable(GL_DEPTH_TEST);
}
