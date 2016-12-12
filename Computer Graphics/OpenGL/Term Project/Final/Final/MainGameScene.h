#pragma once
#include "Scene.h"
#include "MainGameSceneTexture.h"
#include "SoundManager.h"

class CMainGameScene :
	public CScene
{
public:
	CMainGameScene();
	virtual ~CMainGameScene();

public:
	virtual void Update();
	virtual void Render();
	virtual void Reshape(int w, int h);
	virtual void MouseEvent(int button, int state, int x, int y);
	virtual void MouseMove(int x, int y);
	virtual void KeyInput(unsigned char key, int x, int y);
	virtual void KeyUp(unsigned char key, int x, int y);
	virtual void BuildScene(CGLFramework* pframework
		, int tag
	);

	void DrawTree(float w, float h);
	void DrawBush();
	void DrawHud(float w, float h);
	void DrawDummy(float w, float h);
	void DrawKnife(float w, float h);
	void DrawField();
	
	void RobotMove(int Index);
	void RobotRecog(int Index);
	bool RobotKill(int Index);
	bool IsCanMove();

private:
	CMainGameSceneTexture Texture;
	bool CameraMove[4]{ false, };
	bool m_IsSpecial;
	bool m_IsAttack;
	bool m_IsKnife;

	bool m_IsCrouching;
	bool m_IsDashing;
	float m_PlayerSpeed;
	int m_camera_ypos_delta;
	CCamera* m_Camera;

	Vec3f m_RobotPosition[10];
	float m_RobotDir[10];
	Vec3f m_TreePosition[1000];
	int m_TreeTexIdx[1000];
	
	enum state {stop, move, recog, dead};

	char RobotState[10];

	CSoundManager Sound;
};