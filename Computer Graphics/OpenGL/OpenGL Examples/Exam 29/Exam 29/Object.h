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
	void RectTreeRender();
	void rotateRect(int angle);
	void SphereTreeRender();
	void scaleSphere(float scale);
	void TorusBuildingRender();
	void moveTorus(int speed);
	void ConeBuildingRender();
	void scaleCone(float scale);
	void DoorBuildingRender();
	void moveDoor(float speed);
	void PyramidRender();
	void moveOrbit();

};

