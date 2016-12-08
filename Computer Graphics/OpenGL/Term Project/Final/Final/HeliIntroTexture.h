#pragma once
#include "TextureLib.h"

class CIntroTexture
{
public:
	CTextureLibraray m_tex_sea;
	CTextureLibraray m_tex_moon;
	CTextureLibraray m_tex_sky;

	void initTextures() 
	{
		m_tex_sea.SetTexture(L"Image/water.bmp");
		m_tex_moon.SetTexture(L"Image/moon_1.bmp");
		m_tex_sky.SetTexture(L"Image/sky.bmp");
	}
};