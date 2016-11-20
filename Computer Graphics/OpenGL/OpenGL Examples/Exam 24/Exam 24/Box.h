#pragma once
#include "ObjProp.h"

class CBox : public ObjProp
{
public:
	CBox();
	~CBox();

private:
	const Vec3f GravityVector{ 0.f, -1.f, 0.f };
	Vec3f m_MoveVector;
	float m_angle;
public:
	void Render();
	void Rotate();
	void SetAngle(float angle);
	void SetPosition(float y);
	float GetPosition();
	void Move(float speed, Vec3f externalVector, float ypos);
};

