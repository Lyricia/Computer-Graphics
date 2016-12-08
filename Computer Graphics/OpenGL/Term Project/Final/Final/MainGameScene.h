#pragma once
#include "Scene.h"
#include "HeliIntroTexture.h"
#include "TextureLib.h"
#include "Helicopter.h"

class CMainGameScene :
	public CScene
{
public:
	CMainGameScene();
	virtual ~CMainGameScene();

public:
	virtual void Update();
	virtual void Render();
	virtual void Reshape();
	virtual void MouseEvent(int button, int state, int x, int y);
	virtual void MouseMove(int x, int y);
	virtual void KeyInput(unsigned char key, int x, int y);
	virtual void KeyUp(unsigned char key, int x, int y);
	virtual void BuildScene(	  CGLFramework* pframework
								, int tag
	);

private:
	CIntroTexture IntroTexture;
	CCamera* m_Camera;

	CHelicopter Helicopter;
	bool CameraMove[4]{ false, };
};

