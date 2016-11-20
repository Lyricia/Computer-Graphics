#pragma once
#include "ObjProp.h"
#include "Vector3D.h"

class CBall : public ObjProp
{
public:
	CBall();
	~CBall();

private:
	float m_Matrix[16];
	Vec3f MoveVector;

public:
	void Render(float scale);
	void Rotate(float Speed, bool isMovex, bool isMovey, bool isMovez);
	void Move(float speed);
	void ChangeDir(CColor * color);
	bool boolswitch(bool chker)
	{
		if (chker == true)			return false;
		else if (chker == false)	return true;
		return false;
	}
};