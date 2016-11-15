#pragma once
#include "ObjProp.h"
#include "Vector3D.h"

class CCamera : public Vec3f
{
public:
	CCamera();
	~CCamera();

private:
	Vec3f m_CameraVector;
	float m_Sensitivity;
	
public:
	void SetCamera();
};

