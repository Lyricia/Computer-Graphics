#pragma once
#include "stdafx.h"
#include "Tools.h"
#include "ObjProp.h"

class CFlow :public ObjProp
{
public:
	CFlow();
	~CFlow();
private:
	GLfloat ctrlpoints[20][10][3]{ 0 };
	float quad_dis = 5;
	float quad_count = 200;				//이거 필요없는데 ㅡㅡ 너무많이껴서 버릴수가없어
	float type = 2;
	float flow_h_value = 1;
	float all_height = 0;				//파도넘실넘실효과줄거야!
	float height_type = 0;

	int init_onoff = 1;

public:
	void get_helixyz(float x, float y, float z);
	void init_flow();
	void update_flow();
	void draw_flow();

};

