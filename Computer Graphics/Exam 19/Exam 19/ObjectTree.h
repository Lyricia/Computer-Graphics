#pragma once
#include "ObjProp.h"

class CObjectTree : public ObjProp
{
public:
	CObjectTree();
	~CObjectTree();

	void Move(float Speed, bool isMovex, bool isMovey, bool isMovez);

private:
	float m_Matrix[16];
	int m_RectTopAngle;
	float m_SphereTopPos, ydir;
public:
	void RectTreeRender();
	void SphereTreeRender();
	void rotateRect(int angle);
	void moveSphere(int pos);
};

