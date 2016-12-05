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
	glColor3f(1, 0, 0);
	//glutSolidCube(1.0f);

	glPushMatrix();
	{
		glBegin(GL_LINE_STRIP);
		for (float f = 0.f; f <= 1.f; f += 0.05) {
			glVertex3fv(CCardinalSpline::CalcCardinal(
				f, -1.f,
				Vec3f{-0.5, -0.5, 0},
				Vec3f{-0.5, +0.5 ,0},
				Vec3f{ -0.5, -0.5, 0 },
				Vec3f{ -0.5, +0.5 ,0 }
				//Vec3f{+0.5, +0.5, 0},
				//Vec3f{+0.5, -0.5, 0}
			).arr);
		}
		glEnd();

		glPointSize(20);
		glColor3f(1, 1, 0);
		glBegin(GL_POINTS);
		{
			glVertex3fv(Vec3f{ -0.5, -0.5, 0 }.arr);
			glVertex3fv(Vec3f{ -0.5, +0.5 ,0 }.arr);
			glVertex3fv(Vec3f{ +0.5, +0.5, 0 }.arr);
			glVertex3fv(Vec3f{ +0.5, -0.5, 0 }.arr);
		}
		glEnd();
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

void CMainGameScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);
	glClearColor(0.5, 0.5, 0.8, 1);
}
