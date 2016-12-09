#pragma once
#include <gl\glut.h>
#include "ObjProp.h"

class CWave	: public ObjProp
{
private:
	GLfloat ctrlpoints[20][10][3]{ 0 };
	float quad_dis = 5;
	float quad_count = 200;				//�̰� �ʿ���µ� �Ѥ� �ʹ����̲��� ������������
	float type = 2;
	float wave_h_value = 1;
	float all_height = 0;				//�ĵ��ѽǳѽ�ȿ���ٰž�!
	float height_type = 0;

	bool init_onoff = true;

public:
	CWave();
	~CWave();
	
	void Set_Wavepos(float x, float y, float z);
	void init_Wave();
	void Update_Wave();
	void Render_Wave();
};

