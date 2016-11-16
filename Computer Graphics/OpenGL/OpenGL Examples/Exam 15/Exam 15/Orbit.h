#pragma once

struct Vertex
{
	float x;
	float y;
	float z;
};

class COrbit
{
public:
	COrbit();
	~COrbit();

public:
	void DrawOrbit(int radius);
	void DrawPlanet(int orbitradius, int sphereradius, int angle, int shaftangle);
	void Circle(Vertex P, float radius, float angle);
};

