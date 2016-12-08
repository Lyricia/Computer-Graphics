#pragma once
#include <cmath>
#include "Vector3D.h"

class CCardinalSpline
{
public:
	static Vec3f CalcCardinal(float u, float tension, 
								Vec3f p0, Vec3f p1, Vec3f p2, Vec3f p3 )
	{
		float s = (1 - tension) * 0.5f;
		auto a = -s * p0 + (2.0f - s) * p1 + (s - 2.0f)*p2 + s*p3;
		auto b = 2*s*p0 + (s - 3.0f)*p1 + (3.0f - 2*s)*p2 - s*p3;
		auto c = -s*p0 + s * p2;
		auto d = p1;

		
		return a*pow(u, 3) + b*pow(u, 2) + c*u + d;
	}
};