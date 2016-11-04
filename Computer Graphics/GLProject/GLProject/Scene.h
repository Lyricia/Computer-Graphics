#pragma once
//this class is basement of other scenes
class CGLFramework;

class CScene
{
public:
	CScene();
	~CScene();

public:
	virtual void RenderScene();	
	virtual void UpdateScene();
	virtual void BuildScene(CGLFramework* pFramework, int tag);
	virtual void KeyInput(unsigned char key, int x, int y);
protected:
	CGLFramework*	m_pMasterFramework;
	int				m_iTag;
};

