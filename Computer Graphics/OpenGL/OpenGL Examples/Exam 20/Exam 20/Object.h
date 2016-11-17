#pragma once
#include "ObjProp.h"

class CObject : public ObjProp
{
public:
	CObject();
	~CObject();

	void Move(float Speed, bool isMovex, bool isMovey, bool isMovez);

private:
	float m_Matrix[16];
	int m_RectTopAngle;
	float m_SphereScaleSize;
	float m_TorusMovePos;
	float m_ConeScaleSize;
	float m_DoorPos;
	float ydir;

public:
	void RectTreeRender(float scale);
	void rotateRect(int angle);
	void SphereTreeRender(float scale);
	void scaleSphere(float scale);
	void TorusBuildingRender(float scale);
	void moveTorus(int speed);
	void ConeBuildingRender(float scale);
	void scaleCone(float scale);
	void DoorBuildingRender(float scale);
	void moveDoor(float speed);
};

