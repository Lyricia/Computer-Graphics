#pragma once
#include "TextureLib.h"

class CMainGameSceneTexture
{
public:
	CTextureLibraray m_tex_Tree;

	void initTextures()
	{
		m_tex_Tree.SetTexture(L"Image/tree/Tree111.png");
	}
};