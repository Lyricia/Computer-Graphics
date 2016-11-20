#pragma once
#include "ObjProp.h"

class CBox :
{
public:
	CBox();
	~CBox();
	
private:
	Vec3f MoveVector;

public:
	void Render();
	void SetObjProp(float scale);
	void Move(float speed);
};

