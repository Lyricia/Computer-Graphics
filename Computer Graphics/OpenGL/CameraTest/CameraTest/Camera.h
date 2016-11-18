#pragma once
#include "ObjProp.h"
#include "Vector3D.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

private:
	CAngle m_angle;
	Vec3f m_CameraPosition{ 0,1,0 };
	Vec3f m_LookVector{ 0.0f, 0.0f, 1.0f };
	int oldMousePostion_x, oldMousePostion_y;
	int newMousePostion_x, newMousePostion_y;
	float m_Sensitivity{ 0.01f };
	
public:
	void SetCamera();
	void SetLookVector(); // get mouse move x, y
	void getMouse(int x, int y);
};

