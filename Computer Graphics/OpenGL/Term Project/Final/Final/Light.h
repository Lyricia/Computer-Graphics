#pragma once
class CLight
{
public:
	CLight();
	~CLight();

private:
	int onoff_light_0 = 0;			//전체 밝게 해줄거야 -> 안써헤헤헤헿 검사할떔만쓸까???ㅎㅎㅎㅎㅎㅎㅎㅎㅎ
	int onoff_light_1 = 1;			// 태양등 입니다.
	int onoff_light_2 = 0;			// 
	int onoff_light_3 = 0;
public:
	void insert_light(unsigned char key);
	void Make_Light(float x, float y, float z);
};