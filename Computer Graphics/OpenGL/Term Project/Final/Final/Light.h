#pragma once
class CLight
{
public:
	CLight();
	~CLight();

private:
	int onoff_light_0 = 0;			//��ü ��� ���ٰž� -> �Ƚ��������m �˻��ҋ�������???������������������
	int onoff_light_1 = 1;			// �¾�� �Դϴ�.
	int onoff_light_2 = 0;			// 
	int onoff_light_3 = 0;
public:
	void insert_light(unsigned char key);
	void Make_Light(float x, float y, float z);
};