#pragma once
#include "ObjProp.h"

class CBall : public ObjProp
{
public:
	CBall();
	~CBall();

private:
	float m_Matrix[16];
	

public:
	void Render(float scale);
	void SetRotate(float pitch, float yaw, float roll);
	void Move(float Speed, bool isMovex, bool isMovey, bool isMovez);
	void setcolor(unsigned char red, unsigned char green, unsigned char blue) {
		Color.red = red;
		Color.green = green;
		Color.blue = blue;
	}
};

