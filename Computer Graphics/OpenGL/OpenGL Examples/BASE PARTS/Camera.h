#pragma once
#include "ObjProp.h"
#include "Vector3D.h"

class CCamera : public ObjProp
{
public:
	CCamera();
	~CCamera();

private:
	Vec3f m_LookVector{ 0.0f, 0.0f, 1.0f };
	int newMousePostion_x, newMousePostion_y;
	int oldMousePostion_x, oldMousePostion_y;
	float m_Sensitivity{ 0.001f };
	float dist;
	
public:
	void SetCamera();
	void SetCameraPosition(float x, float y, float z);
	void SetCameraPosition(Vec3f _positioninput);
	void SetLookVector(); // get mouse move x, y
	void getMouse(int x, int y);
	void Move(DIRECTION dir, float speed);
};

