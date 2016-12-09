#pragma once
#include "Scene.h"
#include "HeliIntroTexture.h"
#include "Helicopter.h"
#include "SoundManager.h"

class CIntroScene :
	public CScene
{
public:
	CIntroScene();
	virtual ~CIntroScene();

public:
	virtual void Update();
	virtual void Render();
	virtual void Reshape(int w, int h);
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
	CSoundManager Sound;
	bool CameraMove[4]{ false, };

	float m_Fade = 1.0f;
};

