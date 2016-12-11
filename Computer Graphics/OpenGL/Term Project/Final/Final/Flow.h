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
	float quad_count = 200;				//�̰� �ʿ���µ� �Ѥ� �ʹ����̲��� ������������
	float type = 2;
	float flow_h_value = 1;
	float all_height = 0;				//�ĵ��ѽǳѽ�ȿ���ٰž�!
	float height_type = 0;

	int init_onoff = 1;

public:
	void get_helixyz(float x, float y, float z);
	void init_flow();
	void update_flow();
	void draw_flow();

};

