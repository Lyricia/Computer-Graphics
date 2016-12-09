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

private:
	CMainGameSceneTexture Texture;
	bool CameraMove[4]{ false, };
	CCamera* m_Camera;


};

