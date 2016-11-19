#pragma once
#include "ObjProp.h"

class CTorus : public ObjProp
{
public:
	CTorus();
private:
	int m_id;
	float limit;
public:
	void Render(int scale);
	void Move(float speed);
	void SetLimit(int count);
	void init(int _id);
};


