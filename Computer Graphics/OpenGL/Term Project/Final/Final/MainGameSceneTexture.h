#pragma once
#include "TextureLib.h"

class CMainGameSceneTexture
{
public:
	CTextureLibraray m_tex_Tree[10];
	CTextureLibraray m_tex_UserHUD_notZoom;
	CTextureLibraray m_tex_UserHUD_Zoom;
	CTextureLibraray m_tex_UserHUD_Knife_Ready;
	CTextureLibraray m_tex_UserHUD_Knife_Attack;

	CTextureLibraray m_tex_Field_TreeWall;
	CTextureLibraray m_tex_Field_Water;
	CTextureLibraray m_tex_Field_Waterfall;
	CTextureLibraray m_tex_Field_Cliff;
	CTextureLibraray m_tex_Field_Bridge;
	CTextureLibraray m_tex_Field_Ground;

	CTextureLibraray m_tex_bush[6];

	CTextureLibraray m_tex_dummy;
	CTextureLibraray m_tex_castle;

	void initTextures()
	{
		m_tex_Tree[0].SetTexture(L"Image/tree/tree1.png");
		m_tex_Tree[1].SetTexture(L"Image/tree/tree2.png");
		m_tex_Tree[2].SetTexture(L"Image/tree/tree3.png");
		m_tex_Tree[3].SetTexture(L"Image/tree/tree4.png");
		m_tex_Tree[4].SetTexture(L"Image/tree/tree5.png");
		m_tex_Tree[5].SetTexture(L"Image/tree/tree6.png");
		m_tex_Tree[6].SetTexture(L"Image/tree/tree7.png");
		m_tex_Tree[7].SetTexture(L"Image/tree/tree8.png");
		m_tex_Tree[8].SetTexture(L"Image/tree/tree9.png");
		m_tex_Tree[9].SetTexture(L"Image/tree/tree10.png");

		m_tex_bush[0].SetTexture(L"Image/bush/bush_1_alpha.png");
		m_tex_bush[1].SetTexture(L"Image/bush/bush_2_alpha.png");
		m_tex_bush[2].SetTexture(L"Image/bush/bush_3_alpha.png");
		m_tex_bush[3].SetTexture(L"Image/bush/bush_4_alpha.png");
		m_tex_bush[4].SetTexture(L"Image/bush/bush_5_alpha.png");
		m_tex_bush[5].SetTexture(L"Image/bush/bush_6_alpha.png");

		m_tex_UserHUD_notZoom.SetTexture(L"Image/FPS3.png");
		m_tex_UserHUD_Zoom.SetTexture(L"Image/FPS2.png");
		m_tex_UserHUD_Knife_Ready.SetTexture(L"Image/Knife_ready.png");
		m_tex_UserHUD_Knife_Attack.SetTexture(L"Image/Knife_attack.png");

		m_tex_Field_TreeWall.SetTexture(L"Image/Field/tree/tree_wall.bmp");
		m_tex_Field_Water.SetTexture(L"Image/Field/water.bmp");
		m_tex_Field_Waterfall.SetTexture(L"Image/Field/waterfall.bmp");
		m_tex_Field_Cliff.SetTexture(L"Image/Field/cliff.bmp");
		m_tex_Field_Bridge.SetTexture(L"Image/Field/bridge_wood.bmp");
		m_tex_Field_Ground.SetTexture(L"Image/Field/grass_2.bmp");
	
		m_tex_dummy.SetTexture(L"Image/dummy.png");

		m_tex_castle.SetTexture(L"Image/Field/brick_wall.bmp");
	}
};