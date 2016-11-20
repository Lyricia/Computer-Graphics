#pragma once
#include "ObjProp.h"

class CPlane : public ObjProp
{
public:
	CPlane();
	~CPlane();

private:
	Vec3f m_NormalVector;
	Vec3f m_PlaneVertex[4];
	float m_Matrix[16];
	float angle;
public:
	void SetPlane();
	void SetNormalVector(Vec3f a, Vec3f b);
	Vec3f GetNormalVector();
	float GetPosition(float x);
	void VectorRotate(float Speed, bool isMovex, bool isMovey, bool isMovez);
	void Render();
};

