#pragma once
#include "ObjProp.h"

class CHelicopter : public ObjProp
{
private:
	float x_size = 30;
	float y_size = 30;
	float z_size = 70;

	int wing_style = 1;
	float wing_angle{ 0 };

public:
	CHelicopter();
	~CHelicopter();

	void Render();
	void MovePosition(float x, float y, float z);
	void RotateWing(float speed);
};
