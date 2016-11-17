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
	Vec3f m_CameraVector{ 0,1,0 };
	Vec3f m_LookVector{ 0,0,1 };
	float m_Sensitivity{ 0.5 };
	
public:
	void SetCamera();
	void SetLookVector(int x, int y); // get mouse move x, y

};

