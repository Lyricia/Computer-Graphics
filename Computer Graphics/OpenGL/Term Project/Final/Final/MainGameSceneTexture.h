#pragma once
#include "TextureLib.h"

class CMainGameSceneTexture
{
public:
	CTextureLibraray m_tex_Tree;
	CTextureLibraray m_tex_UserHUD_notZoom;
	CTextureLibraray m_tex_UserHUD_Zoom;
	CTextureLibraray m_tex_UserHUD_Knife_Ready;
	CTextureLibraray m_tex_UserHUD_Knife_Attack;
	CTextureLibraray m_tex_dummy;

	void initTextures()
	{
		m_tex_Tree.SetTexture(L"Image/tree/Tree2.png");
		m_tex_UserHUD_notZoom.SetTexture(L"Image/FPS3.png");
		m_tex_UserHUD_Zoom.SetTexture(L"Image/FPS2.png");
		m_tex_UserHUD_Knife_Ready.SetTexture(L"Image/Knife_ready.png");
		m_tex_UserHUD_Knife_Attack.SetTexture(L"Image/Knife_attack.png");

		m_tex_dummy.SetTexture(L"Image/dummy.png");
	}
};