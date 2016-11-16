#pragma once
#include "Scene.h"
#include "GLFramework.h"

class CMenuScene : public CScene
{
public:
	CMenuScene();
	~CMenuScene();

public:
	virtual void RenderScene();
	virtual void UpdateScene();
	virtual void BuildScene(CGLFramework* pFramework, int tag);
	virtual void KeyInput(unsigned char key, int x, int y);
	virtual void MouseInput(int button, int state, int x, int y);
};

