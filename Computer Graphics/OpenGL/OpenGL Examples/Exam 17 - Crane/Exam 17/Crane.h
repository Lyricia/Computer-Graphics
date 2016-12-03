#pragma once
class CVertex
{
public:
	float x;
	float y;
	float z;
};

class CCrane
{
public:
	CCrane();
	~CCrane();

private:
	int bottomangle;
	int middleanglex;
	int middleangley;
	int topanglex;
	int topanglez;

	CVertex Vertex;

public:
	void moveCrane(float speed);
	void moveBottom(int angle, bool isX, bool isY, bool isZ);
	void moveMiddle(int angle, bool isX, bool isY, bool isZ);
	void moveTop(int angle, bool isX, bool isY, bool isZ);
	void Render();
};

