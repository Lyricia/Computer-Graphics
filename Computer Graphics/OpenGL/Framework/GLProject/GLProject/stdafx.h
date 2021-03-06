#pragma once

#include <gl/glut.h>

#include <iostream>
#include <cassert>
#include <ctime>

template<typename Ty>
struct Point2D {
	Ty x, y;
};

using Point2i = Point2D<int>;
using Point2f = Point2D<float>;

enum class GLKeyStateCombine : long
{
	  LBUTTONDOWN	= ((long(GLUT_LEFT_BUTTON)	<< 8) + GLUT_DOWN)
	, RBUTTONDOWN	= ((long(GLUT_RIGHT_BUTTON)	<< 8) + GLUT_DOWN)
	, LBUTTONUP		= ((long(GLUT_LEFT_BUTTON)	<< 8) + GLUT_UP)
	, RBUTTONUP		= ((long(GLUT_RIGHT_BUTTON)	<< 8) + GLUT_UP)
};

constexpr inline GLKeyStateCombine GetMouseState(int button, int state) noexcept { return GLKeyStateCombine((long(button) << 8) + long(state)); }

#define STR_TITLE_CAPTION	"Tutering Sample_2016_2"

#define STARTPOSITION_X		100
#define STARTPOSITION_Y		100

#define CLIENTWIDTH			800
#define CLIENTHEIGHT		600

#define GAMEFPS				1000 / 60

#ifndef PI
#define PI					3.141592f
#endif // !PI

constexpr inline float DegreeToRadian(float degree) noexcept { return degree * PI * 0.005555; }

inline void DrawRectangle(float x, float y, float scale)
{
	glBegin(GL_POLYGON);
	{
		glVertex2d(x - scale, y + scale);
		glVertex2d(x + scale, y + scale);
		glVertex2d(x + scale, y - scale);
		glVertex2d(x - scale, y - scale);
	}
	glEnd();
}

inline void DrawCircle(float x, float y, float scale, int detail)
{
	assert(!(detail < 4) && "적어도 4개 이상의 꼭지점을 만들어야합니다!");

	float IncreaseAngle = 360.f / static_cast<float>(detail);

	glBegin(GL_POLYGON);
	{
		for (float angle = 0; angle < 360; angle += IncreaseAngle)
			glVertex2f(	  x + (cos(DegreeToRadian(angle)) * scale)
						, y + (sin(DegreeToRadian(angle)) * scale)
			);
	}
	glEnd();
}

