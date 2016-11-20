#pragma once
#include "ObjProp.h"

class CPlane : public ObjProp
{
public:
	CPlane(int id);
	~CPlane();
private:
	int m_id;
	float limit;

public:
	void Render();
	void Move(float speed);
	void SetLimit(int count);
	void init(int _id);
};

