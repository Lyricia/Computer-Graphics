#pragma once
#include "Scene.h"

class CTitleScene :
	public CScene
{
public:
	CTitleScene();
	virtual ~CTitleScene();
	
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

	Point2f			m_ptPos			{100,100}	;
	CTextureLibraray m_texLogo;
	CTextureLibraray m_texLogo2;
	bool TextureChange{ false };
	float m_fFadein = 0.0f;
};

